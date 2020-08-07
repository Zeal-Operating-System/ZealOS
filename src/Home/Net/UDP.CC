//#include "IPV4"
//#include "ICMP" // this is wrong and only doing this because we're just in dev right now. probably need approach like Shrine, MakeNet, idk.
//#include "Sockets"

#define UDP_MAX_PORT	65535

class CUDPHeader
{
	U16 source_port;
	U16 destination_port;
	U16 length;
	U16 checksum;
};

class CUDPSocket
{
	CSocket					*socket;
	I64						 receive_timeout_ms;
	I64						 receive_max_timeout;
	U8						*receive_buffer;
	I64						 receive_len;
	CSocketAddressStorage	 receive_address;	// based on ->family, cast or assign to a var as IPV4/IPV6 CSocketAddress
	U16						 bound_to;			// represents the currently bound port

	CSocketAddressStorage	 from_address;	// when UDP Handler sees UDP packet, this is filled with where the packet came from.
											// recvfrom uses this to fill its address_out parameter.
};

/***************************************************

UDP Bound Socket Tree Classes & Functions

***************************************************/

class CUDPTreeQueue
{ // next, last for CQueue implementation.
	CUDPTreeQueue	*next;
	CUDPTreeQueue	*last;
	CUDPSocket		*socket;
};

class CUDPTreeNode
{
	I64				 port;
	CUDPTreeNode	*left;
	CUDPTreeNode	*right;
	CUDPTreeQueue	*queue;
};

CUDPTreeNode *UDPTreeNodeInit()
{ // init new empty tree/node.
	CUDPTreeNode *tree_node = CAlloc(sizeof(CUDPTreeNode));

	return tree_node;
}

U0 UDPTreeNodeAdd(CUDPTreeNode *node, CUDPTreeNode *tree)
{ // using temp and last allows avoiding recursion and non-growing stack issues.
	CUDPTreeNode *temp_tree = tree;
	CUDPTreeNode *last_tree = temp_tree;

	while (temp_tree)
	{ // loop ends when temp_tree hits a NULL node.
		if (node->port < temp_tree->port)
		{ // if node smaller, go left
			last_tree = temp_tree;
			temp_tree = temp_tree->left;
		}
		else
		{ // if node equal or larger, go right
			last_tree = temp_tree;
			temp_tree = temp_tree->right;
		}
	}
	// once while loop ends, this results in last_tree
	// being the resulting tree to store the node inside of.

	// recompute the direction and set.
	if (node->port < last_tree->port)// if node smaller, go left
		last_tree->left = node;
	else // if node equal or larger, go right
		last_tree->right = node;
}

CUDPTreeNode *UDPTreeNodeParamAdd(I64 node_port, CUDPTreeNode *tree)
{ // add a node using params, return pointer to the node
	CUDPTreeNode *result = UDPTreeNodeInit;
	result->port = node_port;

	UDPTreeNodeAdd(result, tree);

	return result;
}

CUDPTreeNode *UDPTreeNodeParamInit(I64 port)
{
	CUDPTreeNode *result = UDPTreeNodeInit;
	result->port = port;

	return result;
}

CUDPTreeNode *UDPTreeNodeFind(I64 port, CUDPTreeNode *tree)
{
	CUDPTreeNode *temp_tree = tree;

	while (temp_tree)
	{
		if (port < temp_tree->port) // if value smaller, go left
			temp_tree = temp_tree->left;
		else if (port > temp_tree->port) // if value larger, go right
			temp_tree = temp_tree->right;
		else // if value equal, match found.
			break;
	}
	return temp_tree; // ! NULL if not found.
}

CUDPTreeNode *UDPTreeNodePop(I64 port, CUDPTreeNode *tree)
{ // mimics TreeNodeFind. pops whole sub-tree, original tree loses whole branch.
	CUDPTreeNode *parent_tree = tree;
	CUDPTreeNode *temp_tree	  = parent_tree;
	Bool is_left  = FALSE;
	Bool is_right = FALSE;

	while (temp_tree)
	{
		if (port < temp_tree->port)
		{
			parent_tree	= temp_tree;
			temp_tree	= temp_tree->left;
			is_right	= FALSE;
			is_left		= TRUE;
		}
		else if (port > temp_tree->port)
		{
			parent_tree	= temp_tree;
			temp_tree	= temp_tree->right;
			is_right	= TRUE;
			is_left		= FALSE;
		}
		else // if value equal, match found.
			break;	
	}

	if (temp_tree)
	{ //if we found it, clear its parents link to the node
		if (is_left)
		{
			parent_tree->left = NULL;
		}
		else if (is_right)
		{
			parent_tree->right = NULL;
		}
	}

	return temp_tree; // NULL if not found.
}

CUDPTreeNode *UDPTreeNodeSinglePop(I64 port, CUDPTreeNode *tree)
{	// pop a tree off, then add back in its sub-trees to main tree.
	// original node sub-trees are cleared.
	// TODO: double check this logic ensure it's sound.
	CUDPTreeNode *node	= UDPTreeNodePop(port, tree);
	CUDPTreeNode *left	= node->left;
	CUDPTreeNode *right	= node->right;

	if (node)
	{
		if (left)
		{ // if node has left tree, add the tree
			UDPTreeNodeAdd(left, tree);
			node->left = NULL;
		}
		if (right)
		{ // if node has right tree, add the tree.
			UDPTreeNodeAdd(right, tree);
			node->right = NULL;
		}
	}

	return node;
}
/* TODO: determine if necessary to implement
U0 UDPTreeNodeFree(CUDPTreeNode *node)
{	// only clears and frees the node. !! if node has subtrees, 
	// they will be left floating. use with caution to avoid memory leaks
	// ... uh.. what to do with the inner CTreeQueue floating around ..? we need to fix that too right?
	// .. what does CQueue functions give us. QueueRemove is our best bet,
	// i guess it will just try to swap around the next last ptrs.
}
*/
U0 UDPTreeNodeQueueInit(CUDPTreeNode *node)
{
	node->queue = CAlloc(sizeof(CUDPTreeQueue));
	QueueInit(node->queue);
}

U0 UDPTreeNodeQueueAdd(CUDPSocket *socket, CUDPTreeNode *node)
{
	CUDPTreeQueue *new_entry;

	if (!node->queue)
	{
		UDPTreeNodeQueueInit(node);
		node->queue->socket = socket;
	}
	else
	{
		new_entry = CAlloc(sizeof(CUDPTreeQueue));
		QueueInit(new_entry);
		new_entry->socket = socket;
		QueueInsert(new_entry, node->queue->last);
	}
}

// refactored to UDPTreeNodeQueueSocketFind for Socket-call level functions
CUDPTreeQueue *UDPTreeNodeQueueSocketFind(CUDPSocket *socket, CUDPTreeNode *node)
{
	CUDPTreeQueue *temp_queue;

	if (node->queue)
	{

		if (node->queue->socket == socket)
			return node->queue;

		temp_queue = node->queue->next;
		while (temp_queue != node->queue)
		{
			if (temp_queue->socket == socket)
				return temp_queue;
			temp_queue = temp_queue->next;
		}
	}

	return NULL;
}

CUDPTreeQueue *UDPTreeNodeQueueIPV4Find(U32 address, CUDPTreeNode *node)
{	// address should be pulled from an instance of CIPV4Address (TODO... double check what bit order we're in ?)
	// TODO: should INADDR_ANY entries be stored and looped, or keep current returning ASAP at INNADDR_ANY ?

	CUDPTreeQueue		*temp_queue = node->queue;
	CSocketAddressIPV4	*temp_ip;

	if (temp_queue)
	{
		do
		{
			if (temp_queue->socket->receive_address.family == AF_INET)
			{
				temp_ip = &temp_queue->socket->receive_address;
				ZenithLog("UDPTreeNodeQueueIPV4Find: addr, nodequeue addr: %08X, %08X\n",
							address, temp_ip->address.address);

				if (temp_ip->address.address == address || temp_ip->address.address == INADDR_ANY)
				{
					ZenithLog("UDPTreeNodeQueueIPV4Find: Address match: addr, nodequeue: %08X, %08X \n",
								address, temp_ip->address.address);
					return temp_queue;
				}
			}

			temp_queue = temp_queue->next;
		}
		while (temp_queue != node->queue);
	}

	return NULL;
}

CUDPTreeQueue *UDPTreeNodeQueueSocketSinglePop(CUDPSocket *socket, CUDPTreeNode *node)
{ // search by socket, pop a single UDPTreeQueue off the node, return popped queue.
	CUDPTreeQueue *temp_queue = UDPTreeNodeQueueSocketFind(socket, node);
	CUDPTreeQueue *temp_next;
	CUDPTreeQueue *temp_last;

	if (temp_queue)
	{
		temp_next = temp_queue->next;
		temp_last = temp_queue->last;

		if (temp_queue != temp_next)
		{ // if 2 or more entries in queue, stitch next&last, loop found queue
			temp_last->next  = temp_next;
			temp_next->last  = temp_last;
			temp_queue->next = temp_queue;
			temp_queue->last = temp_queue;

			if (temp_queue == node->queue) // if entry to pop is node queue head, change head to next
				node->queue = temp_next;
		}
		else if (temp_queue == temp_next == temp_last)
			node->queue = NULL; // only one entry in queue, NULL node-queue link and pop the queue.
	}
	return temp_queue; // if not found, NULL.
}

/*
CUDPTreeQueue *UDPTreeNodeQueueSinglePop(U32 address, CUDPTreeNode *node)
{ // pop a single UDPTreeQueue off the node, return popped queue.
	CUDPTreeQueue *temp_queue = UDPTreeNodeQueueFind(address, node);

	if (temp_queue)
		Debug("When is this method needed ?");

		//QueueRemove(temp_queue);
		// links between queue entries pop out this and stitch back together. popped entry might have old links?

	return temp_queue; // if not found, NULL.
}
*/

/***************************************************/

class CUDPGlobals
{

	CUDPTreeNode *bound_socket_tree;

} udp_globals;


U0 UDPGlobalsInit()
{
	udp_globals.bound_socket_tree = NULL;
}

I64 UDPPacketAllocate(U8 **frame_out,
					  U32 source_ip,
					  U16 source_port,
					  U32 destination_ip,
					  U16 destination_port,
					  I64 length)
{
	U8 *ethernet_frame;
	I64 de_index;
	CUDPHeader *header;

	de_index = IPV4PacketAllocate(&ethernet_frame,
								  IP_PROTOCOL_UDP,
								  source_ip,
								  destination_ip,
								  sizeof(CUDPHeader) + length);
	if (de_index < 0)
	{
		ZenithLog("UDP PACKET ALLOCATE: Ethernet Frame Allocate failed.\n");
		return de_index;
	}

	header = ethernet_frame;

	header->source_port			= EndianU16(source_port);
	header->destination_port	= EndianU16(destination_port);
	header->length				= EndianU16(sizeof(CUDPHeader) + length);
	header->checksum			= 0;

//	ClassRep(header);

	*frame_out = ethernet_frame + sizeof(CUDPHeader);

	return de_index;
}

U0 UDPPacketFinish(I64 de_index)
{ // alias for IPV4PacketFinish, alias for EthernetFrameFinish, alias for driver send packet
	IPV4PacketFinish(de_index);
}

I64 UDPParsePacket(U16 *source_port_out,
				   U16 *destination_port_out,
				   U8 **data_out,
				   I64 *length_out,
				   CIPV4Packet *packet)
{

	// check ip protocol? probably redundant

	CUDPHeader *header = packet->data;

	// TODO: Shrine has FIXME, validate packet length!

	*source_port_out		= EndianU16(header->source_port);
	*destination_port_out	= EndianU16(header->destination_port);

	*data_out	= packet->data   + sizeof(CUDPHeader);
	*length_out	= packet->length - sizeof(CUDPHeader);

	return 0;

}

//CUDPSocket *UDPSocket(U16 domain, U16 type) // should this even be allowed? why not just UDPSocket; ? it could just know its domain and type.
CUDPSocket *UDPSocket(U16 domain=AF_UNSPEC)
{
	U16 type = SOCKET_DATAGRAM;
	CUDPSocket *udp_socket = CAlloc(sizeof(CUDPSocket));

	udp_socket->socket = Socket(domain, type);
	
	udp_socket->receive_address.family = domain; // INET, INET6, or unspecified

	return udp_socket;

}

I64 UDPSocketBind(CUDPSocket *udp_socket, CSocketAddressStorage *address_source)
{
	CUDPTreeNode *temp_node;
	CSocketAddressIPV4 *ipv4_source;
	CSocketAddressIPV4 *ipv4_receive;
	CSocketAddressIPV6 *ipv6_source;
	CSocketAddressIPV6 *ipv6_receive;
	U16 port;

	switch (udp_socket->socket->state)
	{
		case SOCKET_STATE_READY: //	Socket State machine must be in init state
			break;

		default:
			ZenithErr("UDP SOCKET BIND: Failed, Socket state-machine must be in READY state.\n");
			return -1;
	}

	if (udp_socket->bound_to) 
	{
		ZenithErr("UDP SOCKET BIND: UDP Socket currently Bound.\n");
		return -1;
	}

	switch (address_source->family)
	{
		case AF_INET:

			if (udp_socket->receive_address.family == AF_INET6)
			{
				ZenithErr("UDP SOCKET BIND: Incompatible Address type.\n");
				return -1;
			}

			ipv4_source  = address_source;
			ipv4_receive = &udp_socket->receive_address;

			ipv4_receive->address.address	= ipv4_source->address.address; // bind socket to address in parameter.
			ipv4_receive->port				= ipv4_source->port; // ... consistency would say keep in Big Endian ...

			port = EndianU16(ipv4_source->port); // port member should be Big Endian,  so now we're going L.E (?)

			break;

		case AF_INET6:

			if (udp_socket->receive_address.family == AF_INET)
			{
				ZenithErr("UDP SOCKET BIND: Incompatible Address type.\n");
				return -1;
			}

			ipv6_source = address_source;
			ipv6_receive = &udp_socket->receive_address;
			// ...
			// ...

			port = EndianU16(ipv6_source->port); // port member should be Big Endian,  so now we're going L.E (?)

			Debug("TODO: IPV6 UDP BIND");

			break;

		case AF_UNSPEC:
			Debug("TODO: AF_UNSPEC UDP BIND -- param family");

			break;
	}

	// at this point, Socket and Address have matching family values

	if (udp_globals.bound_socket_tree)
	{
		// look for our port.
		temp_node = UDPTreeNodeFind(port, udp_globals.bound_socket_tree);

		if (temp_node)
		{ // if we find we have bound sockets at port, check address before adding to queue
			switch (address_source->family)
			{
				case AF_INET:
					// TODO: will any INADDR_ANY sockets bound at the port break this?
					if (UDPTreeNodeQueueIPV4Find(ipv4_receive->address.address, temp_node))
					{
						ZenithErr("UDP SOCKET BIND: Address already in Bound Socket Tree !\n");
						return -1;
					}
					else
					{ // if no address match, free to add socket to the node queue
						UDPTreeNodeQueueAdd(udp_socket, temp_node);
					}

				case AF_INET6:
					Debug("TODO: IPV6 UDP BIND");
					break;

				case AF_UNSPEC:
					Debug("TODO: AF_UNSPEC UDP BIND -- found in bound tree");
					break;
			}
		}
		else
		{ // if we get no node back from port search, we didn't find it and are free to add a new node.
			temp_node = UDPTreeNodeParamAdd(port, udp_globals.bound_socket_tree); // add new node with port, return its *.
			UDPTreeNodeQueueAdd(udp_socket, temp_node);
		}
	}
	else // if no bound sockets, we init the tree as a new node
	{
		udp_globals.bound_socket_tree = UDPTreeNodeParamInit(port); //... shouuuld be in L.E .. ?
		UDPTreeNodeQueueAdd(udp_socket, udp_globals.bound_socket_tree); // add the udp socket to the port queue
		// maybe more checks to do before this, dunno rn.
	}

	udp_socket->bound_to = port;

	SocketBind(udp_socket->socket); // Advance Socket state-machine to BIND REQ state.

	switch (udp_socket->socket->state)
	{
		case SOCKET_STATE_BIND_REQ: //	if BIND request success, set BOUND.
			udp_socket->socket->state = SOCKET_STATE_BOUND;
			break;

		default:
			ZenithErr("UDP SOCKET BIND: Failed, Misconfigured Socket state-machine.\n");
			return -1;
	}

	return 0;
}

I64 UDPSocketClose(CUDPSocket *udp_socket)
{ // close, pop, and free the socket from the bound tree.
	CUDPTreeNode *node;
	CUDPTreeQueue *queue;

	SocketClose(udp_socket->socket); // TODO: testing on closing a socket while another task is using it
	// after low-level socket close, even if protocol level socket fails close, it is now disabled (state is close request)

	node = UDPTreeNodeFind(udp_socket->bound_to, udp_globals.bound_socket_tree);

	if (node)
		queue = UDPTreeNodeQueueSocketFind(udp_socket, node);
	else
	{
		Debug("Didn't find node at socket during UDPSocketClose!\n");
		return -1;
	}

	if (queue)
	{
		UDPTreeNodeQueueSocketSinglePop(udp_socket, node);

		Free(udp_socket->socket);
//		Free(udp_socket->receive_buffer); // i think we'll still need to keep this
		Free(udp_socket);
		Free(queue);
	}
	else
	{
		Debug("Didn't find queue at socket during UDPSocketClose!\n");
		return -1;
	}
	


	return 0;
}

// UDPSocketConnect (Shrine just has FIXME: 'implement')

// UDPListen (Shrine just has no_warns, not implemented)

I64 UDPSocketReceiveFrom(CUDPSocket *udp_socket, U8 *buffer, I64 len, CSocketAddressStorage *address_out)
{ // ommitted I64 addrlen, flags not implemented
	CSocketAddressIPV4 *ipv4_socket_addr;
	CSocketAddressIPV6 *ipv6_socket_addr;

	switch (udp_socket->socket->state)
	{
		case SOCKET_STATE_OPEN:  //	Socket State machine must
		case SOCKET_STATE_BOUND: // be in connected or bound state
			break;

		default:
			ZenithErr("UDP SOCKET RECEIVE FROM: Socket state-machine must be in OPEN or BOUND state.\n");
			return -1;
	}

	udp_socket->receive_buffer	= buffer;
	udp_socket->receive_len		= len;

	if (udp_socket->receive_timeout_ms != 0)
		udp_socket->receive_max_timeout = counts.jiffies + udp_socket->receive_timeout_ms * JIFFY_FREQ / 1000;

//	ClassRep(udp_socket);
	ZenithLog("UDP SOCKET RECEIVE FROM: udp_socket->receive_buffer: 0x%0X.\n", udp_socket->receive_buffer);
	while (udp_socket->receive_buffer != NULL)
	{ // 'Check for timeout'
		if (udp_socket->receive_timeout_ms != 0 && counts.jiffies > udp_socket->receive_max_timeout)
		{ // Shrine has TODO: 'seterror(EWOULDBLOCK)' investigate this
			udp_socket->receive_len = -1; // ?
			ZenithErr("UDP SOCKET RECEIVE FROM: Timed out.\n");
			break;
		}

		Yield;
	}

	if (address_out)
	{
//		switch (udp_socket->receive_address.family)
		switch (udp_socket->from_address.family)
		{
			case AF_INET:
				ipv4_socket_addr = address_out;
//				MemCopy(ipv4_socket_addr, &udp_socket->receive_address, sizeof(CSocketAddressIPV4));
				MemCopy(ipv4_socket_addr, &udp_socket->from_address, sizeof(CSocketAddressIPV4));
				break;
			case AF_INET6:
				ipv6_socket_addr = address_out;
//				MemCopy(ipv6_socket_addr, &udp_socket->receive_address, sizeof(CSocketAddressIPV6));
				MemCopy(ipv6_socket_addr, &udp_socket->from_address, sizeof(CSocketAddressIPV6));
				break;
			case AF_UNSPEC:
				Debug("TODO: UDP Receive From Error AF_UNSPEC UDPSocket Address Family\n");
				break;
		}
	}

	SocketReceiveFrom(udp_socket->socket);

	return udp_socket->receive_len;
}

I64 UDPSocketSendTo(CUDPSocket *udp_socket, U8 *buffer, I64 len, CSocketAddressStorage *destination_addr)
{
	CSocketAddressStorage *dest;
	CSocketAddressIPV4 *ipv4_destination;
	CSocketAddressIPV6 *ipv6_destination;
	U8 *ethernet_frame;
	I64 de_index;

	switch (udp_socket->socket->state)
	{
		case SOCKET_STATE_OPEN:  //	Socket State machine must
		case SOCKET_STATE_BOUND: // be in connected or bound state for send.
			dest = &udp_socket->receive_address; // if already bound, ignore param destination
			break;								 // and use stored address as send address.

		case SOCKET_STATE_READY: // If socket state is initial, attempt to bind it to destination.
			ZenithLog("UDP SOCKET SEND TO: Socket unbound. Attempting Bind at address parameter.\n");
			UDPSocketBind(udp_socket, destination_addr);
			dest = destination_addr;
			break;

		default:
			ZenithErr("UDP SOCKET SEND TO: Socket state-machine must be in OPEN, BOUND or READY  state.\n");
			return -1;
	}

	switch (dest->family)
	{
		case AF_INET:
			ipv4_destination = dest;

			de_index = UDPPacketAllocate(&ethernet_frame,
										 IPV4GetAddress(),
										 0,
										 EndianU32(ipv4_destination->address.address),
										 EndianU16(ipv4_destination->port),
										 len); // is get address parens redundant?
			break;
		case AF_INET6:
			ipv6_destination = dest;
			Debug("TODO: IPV6 Not implemented yet");
			break;
		case AF_UNSPEC:
			Debug("TODO: Error UDP Send To AF_UNSPEC\n");
			break;
	}

	if (de_index < 0)
		return -1;

	MemCopy(ethernet_frame, buffer, len); // copies the data in buffer param into the ethernet frame

	UDPPacketFinish(de_index);
	return 0;
}

// UDPSocketSetOpt ?

I64 UDPHandler(CIPV4Packet *packet)
{ // TODO: Need either two UDP handlers for IPv4/IPv6, or logic changes if IPV6 is desired.
	U16					 source_port;
	U16					 destination_port;
	U8					*data;
	I64					 length;
	CUDPTreeNode		*node;
	CUDPTreeQueue		*queue;
	CUDPSocket			*udp_socket;
	CSocketAddressIPV4	*ipv4_addr;
	I64					 num_receive;

	ZenithLog("UDP HANDLER: Beginning handling UDP Packet.\n");
/*	ZenithWarn("UDP HANDLER:		Yielding for a little bit as a debug.\n");
	ZenithWarn("UDP HANDLER:		...\n");
	I64 c = counts.jiffies;
	while (counts.jiffies < c + 1000)
		Yield;
	ZenithWarn("UDP HANDLER:		...\n");*/

	I64 error = UDPParsePacket(&source_port, &destination_port, &data, &length, packet);

	if (error < 0)
	{
		ZenithErr("UDP HANDLER: Packet Parse Error.\n");
		return error;
	}

	if (udp_globals.bound_socket_tree)
	{
		node = UDPTreeNodeFind(destination_port, udp_globals.bound_socket_tree);
		if (node)
		{
			queue = UDPTreeNodeQueueIPV4Find(packet->destination_ip_address, node); // TODO: make sure bit order is correct here!!
			if (queue)
			{
				udp_socket = queue->socket;
				ZenithLog("UDP HANDLER: Port and Address are in bound tree.\n");
			}
			else
			{
				ZenithWarn("UDP HANDLER: Found node for port, but address is not in node queue.\n");
				ZenithWarn("             UDP packet dest ip: 0x%0X.\n", packet->destination_ip_address);
				return -1;
			}
		}
		else
		{
			ZenithWarn("UDP HANDLER: Node for Port is not in tree.\n");
			return -1;
		}
	}
	else
	{
		ZenithWarn("UDP HANDLER: Socket tree is currently empty.\n");
		return -1;
	}

	ZenithLog("UDP HANDLER: Checking if UDP Socket's Receive-Buffer exists. UDPSocket at: 0x%0X \n", udp_socket);
	ZenithLog("             It probably exists, wtf going on ? udp_socket->receive_buffer: 0x%0X.\n", udp_socket->receive_buffer);
	// at this point, udp_socket is set, otherwise has already returned -1.
	if (udp_socket->receive_buffer)
	{
		ZenithLog("UDP HANDLER: Saw UDP Socket receive buffer exists, about to copy data into it.\n");
		num_receive = udp_socket->receive_len;

		if (num_receive > length)
		{
			ZenithWarn("UDP HANDLER: Truncating UDP socket receive length. num_receive , len : %d, %d\n",
				num_receive, length);
			num_receive = length;
		}

		MemCopy(udp_socket->receive_buffer, data, num_receive);

		// Shrine has comment 'signal that we received something'
		// In UDPSocketRecvFrom, a given buffer is set as receive buffer.
		// Handler sees socket has buffer, copies data to that buffer,
		// then clears the socket's pointer for it. Actual buffer location
		// itself is untouched.
		udp_socket->receive_buffer	= NULL;
		udp_socket->receive_len		= num_receive;

//		ipv4_addr = &udp_socket->receive_address;
		ipv4_addr = &udp_socket->from_address;

		ipv4_addr->family			= AF_INET;
		ipv4_addr->port				= EndianU16(source_port);
		ipv4_addr->address.address	= EndianU32(packet->source_ip_address);
		ZenithLog("UDP HANDLER: Copying packet source IP (BE) to FROM_ADDRESS of UDP Socket: %08X \n", ipv4_addr->address.address);
	}

	return error;
}

// the socket functions just act on the socket state machine.
// ZenithErr and return fail vals if socket FSM improperly used.
// Careful with Free()'s.

UDPGlobalsInit;