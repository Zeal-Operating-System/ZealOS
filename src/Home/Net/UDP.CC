#define UDP_MAX_PORT	65535

class CUDPHeader
{
	U16 source_port;
	U16 destination_port;
	U16 length;
	U16 checksum;
};

class CUDPMessageQueue:CQueue
{ // each bound socket queues data. recv functions & handler use this.
	U8						*data;				// contains the UDP payload data.
	I64						 data_length;		// size of payload data.
	I64						 received_length;	// amount of the data received so far.
	CSocketAddressStorage	 from_address;	// when UDP Handler sees UDP packet, this is filled with where packet came from.
											// recvfrom uses this to fill its address_out parameter.
};

class CUDPSocket
{
	CSocket					*socket;
	CUDPMessageQueue		*receive_queue;
	CSocketAddressStorage	 receive_address;	// based on ->family, cast or assign to a var as IPV4/IPV6 CSocketAddress
	I64						 receive_timeout_ms;
	I64						 receive_max_timeout;
	U16						 bound_to;			// represents the currently bound port
};

/***************************************************

UDP Bound Socket Tree Classes & Functions

***************************************************/

class CUDPTreeQueue:CQueue
{
	CUDPSocket		*socket;
};

class CUDPTreeNode
{
	CUDPTreeNode	*left;
	CUDPTreeNode	*right;
	CUDPTreeQueue	*queue;
	I64				 port;
};

CUDPTreeNode *UDPTreeNodeInit()
{ // init new empty tree/node. Init socket queue head links.
	CUDPTreeNode *tree_node = CAlloc(sizeof(CUDPTreeNode));

	tree_node->queue = CAlloc(sizeof(CQueue));
	QueueInit(tree_node->queue);

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
	Bool		  is_left  = FALSE;
	Bool		  is_right = FALSE;

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

U0 UDPTreeNodeQueueAdd(CUDPSocket *socket, CUDPTreeNode *node)
{
	CUDPTreeQueue *new_entry;

	new_entry = CAlloc(sizeof(CUDPTreeQueue));
	new_entry->socket = socket;
	QueueInsert(new_entry, node->queue->last);
}

CUDPTreeQueue *UDPTreeNodeQueueSocketFind(CUDPSocket *socket, CUDPTreeNode *node)
{
	CUDPTreeQueue *temp_queue;

	temp_queue = node->queue->next;
	while (temp_queue != node->queue)
	{
		if (temp_queue->socket == socket)
			return temp_queue;
		temp_queue = temp_queue->next;
	}

	return NULL;
}

CUDPTreeQueue *UDPTreeNodeQueueIPV4Find(U32 address, CUDPTreeNode *node)
{	// address should be pulled from an instance of CIPV4Address (TODO... double check what bit order we're in ?)
	// TODO: should INADDR_ANY entries be stored and looped, or keep current returning ASAP at INNADDR_ANY ?

	CUDPTreeQueue		*temp_queue = node->queue->next;
	CSocketAddressIPV4	*temp_ip;

	while (temp_queue != node->queue)
	{
		if (temp_queue->socket->receive_address.family == AF_INET)
		{
			temp_ip = &temp_queue->socket->receive_address;
			NetLog("UDPTreeNodeQueueIPV4Find: Comparing:     addr, nodequeue addr: %08X, %08X",
					address, temp_ip->address.address);

			if (temp_ip->address.address == address || temp_ip->address.address == INADDR_ANY)
			{
				NetLog("UDPTreeNodeQueueIPV4Find: Address match: addr, nodequeue addr: %08X, %08X ",
						address, temp_ip->address.address);

				return temp_queue;
			}
		}

		temp_queue = temp_queue->next;
	}

	return NULL;
}

CUDPTreeQueue *UDPTreeNodeQueueSocketSinglePop(CUDPSocket *socket, CUDPTreeNode *node)
{ // search by socket, pop a single UDPTreeQueue off the node, return popped queue.
	CUDPTreeQueue *temp_queue = UDPTreeNodeQueueSocketFind(socket, node);

	if (temp_queue)
	{
		QueueRemove(temp_queue);

	}

	return temp_queue; // if not found, NULL.
}

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
	U8			*ethernet_frame;
	I64			 de_index;
	CUDPHeader	*header;

	de_index = IPV4PacketAllocate(&ethernet_frame,
								  IP_PROTOCOL_UDP,
								  source_ip,
								  destination_ip,
								  sizeof(CUDPHeader) + length);
	if (de_index < 0)
	{
		NetLog("UDP PACKET ALLOCATE: Ethernet Frame Allocate failed.");
		return de_index;
	}

	header = ethernet_frame;

	header->source_port			= EndianU16(source_port);
	header->destination_port	= EndianU16(destination_port);
	header->length				= EndianU16(sizeof(CUDPHeader) + length);
	header->checksum			= 0;

	*frame_out = ethernet_frame + sizeof(CUDPHeader);

	return de_index;
}

U0 UDPPacketFinish(I64 de_index)
{ // alias for IPV4PacketFinish, alias for EthernetFrameFinish, alias for driver send packet
	IPV4PacketFinish(de_index);
}

I64 UDPPacketParse(U16 *source_port_out,
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

CUDPSocket *UDPSocket(U16 domain=AF_UNSPEC)
{
	U16			type = SOCKET_DATAGRAM;
	CUDPSocket *udp_socket = CAlloc(sizeof(CUDPSocket));

	udp_socket->socket = Socket(domain, type);
	
	udp_socket->receive_address.family = domain; // INET, INET6, or unspecified

	return udp_socket;

}

I64 UDPSocketBind(CUDPSocket *udp_socket, CSocketAddressStorage *address_source)
{
	CUDPTreeNode	   *head = udp_globals.bound_socket_tree;
	CUDPTreeNode	   *temp_node;
	CUDPMessageQueue   *message_queue;
	CSocketAddressIPV4 *ipv4_source;
	CSocketAddressIPV4 *ipv4_receive;
	CSocketAddressIPV6 *ipv6_source;
	CSocketAddressIPV6 *ipv6_receive;
	U16					port;

	switch (udp_socket->socket->state)
	{
		case SOCKET_STATE_READY: //	Socket State machine must be in init state
			break;

		default:
			NetErr("UDP SOCKET BIND: Failed, Socket state-machine must be in READY state.");
			return -1;
	}

	if (udp_socket->bound_to) 
	{
		NetErr("UDP SOCKET BIND: UDP Socket currently Bound.");
		return -1;
	}

	switch (address_source->family)
	{
		case AF_INET:

			if (udp_socket->receive_address.family == AF_INET6)
			{
				NetErr("UDP SOCKET BIND: Incompatible Address type.");
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
				NetErr("UDP SOCKET BIND: Incompatible Address type.");
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

	if (head)
	{
		// look for our port.
		temp_node = UDPTreeNodeFind(port, head);

		if (temp_node)
		{ // if we find we have bound sockets at port, check address before adding to queue
			switch (address_source->family)
			{
				case AF_INET:
					// TODO: will any INADDR_ANY sockets bound at the port break this?
					if (UDPTreeNodeQueueIPV4Find(ipv4_receive->address.address, temp_node))
					{
						NetErr("UDP SOCKET BIND: Address already in Bound Socket Tree !");
						return -1;
					}
					else
					{ // if no address match, free to add socket to the node queue
						UDPTreeNodeQueueAdd(udp_socket, temp_node);
					}

					break;

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
			temp_node = UDPTreeNodeParamAdd(port, head); // add new node with port, return its *.
			UDPTreeNodeQueueAdd(udp_socket, temp_node);
		}
	}
	else // if no bound sockets, we init the tree as a new node
	{
		udp_globals.bound_socket_tree = head = UDPTreeNodeParamInit(port); //... shouuuld be in L.E .. ?
		UDPTreeNodeQueueAdd(udp_socket, head); // add the udp socket to the port queue
		// maybe more checks to do before this, dunno rn.
	}

	udp_socket->bound_to = port;

	udp_socket->receive_queue = message_queue = CAlloc(sizeof(CUDPMessageQueue));
	QueueInit(message_queue); // acts as head. add messages to but don't remove head.

	SocketBind(udp_socket->socket); // Advance Socket state-machine to BIND REQ state.

	switch (udp_socket->socket->state)
	{
		case SOCKET_STATE_BIND_REQ: //	if BIND request success, set BOUND.
			udp_socket->socket->state = SOCKET_STATE_BOUND;
			break;

		default:
			NetErr("UDP SOCKET BIND: Failed, Misconfigured Socket state-machine.");
			return -1;
	}

	return 0;
}

I64 UDPSocketClose(CUDPSocket *udp_socket)
{ // close, pop, and free the socket from the bound tree.
	CUDPTreeNode		*head = udp_globals.bound_socket_tree;
	CUDPTreeNode		*node;
	CUDPTreeQueue		*queue;
	CUDPMessageQueue	*message;

	SocketClose(udp_socket->socket); // TODO: testing on closing a socket while another task is using it
	// after low-level socket close, even if protocol level socket fails close, it is now disabled (state is close request)

	node = UDPTreeNodeFind(udp_socket->bound_to, head);

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

		if (node->queue == node->queue->next)
		{ // if we popped the only queue on the node, remove the node.
			if (node == head)
			{ // head is the global. if node is the global, change it and add branches.
				if (node->left)
				{
					udp_globals.bound_socket_tree = head = node->left;
					if (node->right)
						UDPTreeNodeAdd(node->right, head);
				}
				else if (node->right)
					udp_globals.bound_socket_tree = node->right;
				else
					udp_globals.bound_socket_tree = NULL;
			}
			else // if node is not the global, just pop it from the tree
				UDPTreeNodeSinglePop(node->port, head);

			Free(node);
		}

		Free(udp_socket->socket);

		message = udp_socket->receive_queue->next;
		while (message != udp_socket->receive_queue)
		{
			NetWarn("UDP SOCKET CLOSE: Freeing message @ 0x%X", message);
			Free(message->data);
			QueueRemove(message);
			Free(message);
			message = udp_socket->receive_queue->next;
		}

		NetWarn("UDP SOCKET CLOSE: Freeing message queue & socket.");
		Free(udp_socket->receive_queue);
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
	CSocketAddressIPV4	*ipv4_socket_addr;
	CSocketAddressIPV6	*ipv6_socket_addr;
	CUDPMessageQueue	*message;

	switch (udp_socket->socket->state)
	{
		case SOCKET_STATE_OPEN:  //	Socket State machine must
		case SOCKET_STATE_BOUND: // be in connected or bound state
			break;

		default:
			NetErr("UDP SOCKET RECEIVE FROM: Socket state-machine must be in OPEN or BOUND state.");
			return -1;
	}

	if (len < 0)
	{
		NetErr("UDP SOCKET RECEIVE FROM: Invalid length requested.");
		return -1;
	}

	if (udp_socket->receive_timeout_ms != 0)
		udp_socket->receive_max_timeout = counts.jiffies + udp_socket->receive_timeout_ms * JIFFY_FREQ / 1000;

	message = udp_socket->receive_queue;

	while (message == message->next)
	{ // wait for a message to be added to queue. head is non-message.
		if (udp_socket->receive_timeout_ms == 0)
			return -1; // if no timeout set and didn't see message, bail early

		if (counts.jiffies > udp_socket->receive_max_timeout)
		{ // Shrine has TODO: 'seterror(EWOULDBLOCK)' investigate this
			NetErr("UDP SOCKET RECEIVE FROM: Timed out.");
			return -1;
		}

		Yield;
	}

	NetLog("UDP SOCKET RECEIVE FROM: Saw message in receive queue.");

	message = message->next;

	if (address_out)
	{
		switch (message->from_address.family)
		{
			case AF_INET:
				ipv4_socket_addr = address_out;
				MemCopy(ipv4_socket_addr, &message->from_address, sizeof(CSocketAddressIPV4));
				break;
			case AF_INET6:
				ipv6_socket_addr = address_out;
				MemCopy(ipv6_socket_addr, &message->from_address, sizeof(CSocketAddressIPV6));
				break;
			case AF_UNSPEC:
				NetWarn("UDP Receive From AF_UNSPEC UDPSocket Address Family\n");
				break;
		}
	}


	if (len >= message->data_length - message->received_length)
	{
		NetLog("UDP SOCKET RECEIVE FROM: Requested length longer than data. Truncating.");
		len = message->data_length - message->received_length;
		MemCopy(buffer, message->data + message->received_length, len);

		NetWarn("UDP SOCKET RECEIVE FROM: Freeing message and removing from queue.");
		// all data pulled, release message
		QueueRemove(message);
		Free(message->data);
		Free(message);
	}
	else
	{
		NetLog("UDP SOCKET RECEIVE FROM: Requsted length shorter than data at message.");
		MemCopy(buffer, message->data + message->received_length, len);
		message->received_length += len;
	}

	SocketReceiveFrom(udp_socket->socket);

	return len;
}

I64 UDPSocketSendTo(CUDPSocket *udp_socket, U8 *buffer, I64 len, CSocketAddressStorage *destination_addr)
{
	CSocketAddressStorage	*dest;
	CSocketAddressIPV4		*ipv4_destination;
	CSocketAddressIPV6		*ipv6_destination;
	U8						*ethernet_frame;
	I64						 de_index;

	switch (udp_socket->socket->state)
	{
		case SOCKET_STATE_OPEN:  //	Socket State machine must
		case SOCKET_STATE_BOUND: // be in connected or bound state for send.
			dest = &udp_socket->receive_address; // if already bound, ignore param destination
			break;								 // and use stored address as send address.

		case SOCKET_STATE_READY: // If socket state is initial, attempt to bind it to destination.
			NetLog("UDP SOCKET SEND TO: Socket unbound. Attempting Bind at address parameter.");
			UDPSocketBind(udp_socket, destination_addr);
			dest = destination_addr;
			break;

		default:
			NetErr("UDP SOCKET SEND TO: Socket state-machine must be in OPEN, BOUND or READY  state.");
			return -1;
	}

	switch (dest->family)
	{
		case AF_INET:
			ipv4_destination = dest;

			de_index = UDPPacketAllocate(&ethernet_frame,
										 IPV4AddressGet(),
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
	CUDPTreeNode		*head = udp_globals.bound_socket_tree;
	CUDPTreeNode		*node;
	CUDPTreeQueue		*queue;
	CUDPMessageQueue	*messages_head;
	CUDPMessageQueue	*message;
	CUDPSocket			*udp_socket;
	CSocketAddressIPV4	*ipv4_addr;

	NetLog("UDP HANDLER: Beginning handling UDP Packet.");

	I64 error = UDPPacketParse(&source_port, &destination_port, &data, &length, packet);

	if (error < 0)
	{
		NetErr("UDP HANDLER: Packet Parse Error.");
		return error;
	}

	if (head)
	{
		node = UDPTreeNodeFind(destination_port, head);
		if (node)
		{
			queue = UDPTreeNodeQueueIPV4Find(packet->source_ip_address, node); // TODO: make sure bit order is correct here!!
			if (queue)
			{
				udp_socket = queue->socket;
				NetLog("UDP HANDLER: Port and Address are in bound tree.");
			}
			else
			{
				NetWarn("UDP HANDLER: Found node for port, but address is not in node queue.");
				NetWarn("             UDP packet dest ip: 0x%0X.", packet->destination_ip_address);
				return -1;
			}
		}
		else
		{
			NetWarn("UDP HANDLER: Node for Port is not in tree.");
			return -1;
		}
	}
	else
	{
		NetWarn("UDP HANDLER: Socket tree is currently empty.");
		return -1;
	}
	// at this point, udp_socket is set, otherwise has already returned -1.


	NetLog("UDP HANDLER: Putting data payload into message queue.");

	messages_head = udp_socket->receive_queue;

	message = CAlloc(sizeof(CUDPMessageQueue));
	QueueInsertRev(message, messages_head);

	message->data = CAlloc(length);
	MemCopy(message->data, data, length);
	message->data_length = length;

	ipv4_addr = &message->from_address;

	ipv4_addr->family			= AF_INET;
	ipv4_addr->port				= EndianU16(source_port);
	ipv4_addr->address.address	= EndianU32(packet->source_ip_address);
	NetLog("UDP HANDLER: Copying packet source IP (BE) to FROM_ADDRESS of UDP Socket: %08X ", ipv4_addr->address.address);

	NetLog("UDP HANDLER: Data payload succesfully placed in message queue.");

	return error;
}

// the socket functions just act on the socket state machine.
// NetErr and return fail vals if socket FSM improperly used.
// Careful with Free()'s.


class CUDPRepEntry:CQueue
{
	CUDPTreeNode *node;
};

U0 UDPTreeNodeRep(CUDPTreeNode *node)
{
	CUDPTreeQueue		*queue = node->queue->next;
	CUDPSocket			*socket;
	CSocketAddressIPV4	*ipv4_addr;
	CSocketAddressIPV6	*ipv6_addr;
	U8					*string;
	CUDPMessageQueue	*message;

	"Port $$YELLOW$$%d$$FG$$ (UDP Node @ $$CYAN$$0x%X$$FG$$):\n", node->port, node;

	while (queue != node->queue)
	{

		socket = queue->socket;

		switch (socket->receive_address.family)
		{

			case AF_UNSPEC:
				break;

			case AF_INET:
				ipv4_addr = &socket->receive_address;
				string = MStrPrint("%d.%d.%d.%d",
							ipv4_addr->address.address.u8[3],
							ipv4_addr->address.address.u8[2],
							ipv4_addr->address.address.u8[1],
							ipv4_addr->address.address.u8[0]); // todo: kludge, endianness...

				"	$$BROWN$$%s$$FG$$ (UDP Tree Queue @ $$CYAN$$0x%X$$FG$$):\n", string, queue;
				Free(string);

				break;

			case AF_INET6:
				ipv6_addr = &socket->receive_address;

				break;

			default:
				break;

		}

		"		Timeout: %dms\n", socket->receive_timeout_ms;
		if (socket->receive_queue) // todo: move socket messages Queue alloc from bind to creation to avoid check?
		{
			message = socket->receive_queue->next;
			while (message != socket->receive_queue)
			{
				"		Queued Message @ $$CYAN$$0x%X$$FG$$:\n", message;
				switch (message->from_address.family)
				{
					case AF_UNSPEC:
						string = StrNew("AF_UNSPEC");
						break;
					case AF_INET:
						ipv4_addr = &message->from_address;
						string = NetworkToPresentation(ipv4_addr->family, &ipv4_addr->address);
						break;
					case AF_INET6:
						string = StrNew("IPV6");
						break;
					default:
						string = StrNew("INVALID");
						break;
				}
				"			From Address:			$$BROWN$$%s$$FG$$\n", string;
				"			Data length:			%d\n", message->data_length;
				"			Received data length:	%d\n", message->received_length;

				Free(string);

				message = message->next;
			}
		}

		queue = queue->next;
	}

	"\n";
}

U0 UDPRep()
{
	CUDPTreeNode	*node = udp_globals.bound_socket_tree;
	CUDPRepEntry	*head;
	CUDPRepEntry	*entry;
	CUDPRepEntry	*temp_entry;

	"$$LTBLUE$$UDP Report:$$FG$$\n\n";

	if (node)
	{
		head = CAlloc(sizeof(CUDPRepEntry));
		QueueInit(head); // no QueueRemove the head

		entry = CAlloc(sizeof(CUDPRepEntry));
		entry->node = node;
		QueueInsert(entry, head);

		// perform depth-first-search while Entry Queue has nodes not fully visited.
		while (entry != head)
		{
			if (entry->node->left)
			{ // if node has one, add an Entry for the left branch, continue loop.
				temp_entry = CAlloc(sizeof(CUDPRepEntry));
				temp_entry->node = entry->node->left;
				QueueInsertRev(temp_entry, head);

				// if left branch, but no right: toss early, now fully traveled.
				if (!entry->node->right)
				{
					QueueRemove(entry);
					UDPTreeNodeRep(entry->node);
					Free(entry);
				}

				entry = temp_entry;
			}
			else if (entry->node->right)
			{ // if no left, but right: add right to queue, pop Entry, Rep, set entry to right.
				temp_entry = CAlloc(sizeof(CUDPRepEntry));
				temp_entry->node = entry->node->right;
				QueueInsertRev(temp_entry, head);

				QueueRemove(entry);
				UDPTreeNodeRep(entry->node);
				Free(entry);

				entry = temp_entry;
			}
			else
			{ // pop Entry, Rep, if last Entry in Queue has right add it, pop & Rep travelled Entry, entry = right.
				QueueRemove(entry);
				UDPTreeNodeRep(entry->node);
				Free(entry);

				if (head->last != head)
				{
					temp_entry = head->last;

					if (temp_entry->node->right)
					{
						entry = temp_entry;

						temp_entry = CAlloc(sizeof(CUDPRepEntry));
						temp_entry->node = entry->node->right;
						QueueInsertRev(temp_entry, head);

						QueueRemove(entry);
						UDPTreeNodeRep(entry->node);
						Free(entry);

						entry = temp_entry;
					}
					else
					{
						QueueRemove(temp_entry);
						UDPTreeNodeRep(temp_entry->node);
						Free(temp_entry);

						entry = head->last;
					}
				}
				else
					break;
			}
		}

		Free(head);
	}
	else
		"No UDP Sockets currently bound.\n\n";
}

UDPGlobalsInit;