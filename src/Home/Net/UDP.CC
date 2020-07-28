//#include "IPV4"
#include "ICMP" // this is wrong and only doing this because we're just in dev right now. probably need approach like Shrine, MakeNet, idk.
#include "Sockets"

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
	CSocket *socket;

	I64 receive_timeout_ms;
	I64 receive_max_timeout;

	U8 *receive_buffer;
	I64 receive_len;

	CSocketAddressStorage receive_address; // based on ->family, cast or assign pointer as IPV4/IPV6 CSocketAddress

	U16	bound_to; // represents the currently bound port
};




////////////////////////////////////////////////////
// UDP Bound Socket Tree Classes & Functions

class CUDPTreeQueue
{ // next, last for CQueue implementation.
	CUDPTreeQueue *next;
	CUDPTreeQueue *last;

	CUDPSocket *socket;
};

class CUDPTreeNode
{
	I64 port;

	CUDPTreeNode *left;
	CUDPTreeNode *right;

	CUDPTreeQueue *queue;
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
	CUDPTreeNode *temp_tree	= parent_tree;
	Bool is_left = FALSE;
	Bool is_right = FALSE;

	while (temp_tree)
	{
		if (port < temp_tree->port)
		{
			parent_tree = temp_tree;
			temp_tree = temp_tree->left;
			is_right = FALSE;
			is_left = TRUE;
		}
		else if (port > temp_tree->port)
		{
			parent_tree = temp_tree;
			temp_tree = temp_tree->right;
			is_right = TRUE;
			is_left = FALSE;
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
	CUDPTreeNode *node = UDPTreeNodePop(port, tree);
	CUDPTreeNode *left = node->left;
	CUDPTreeNode *right = node->right;

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

U0 UDPTreeNodeFree(CUDPTreeNode *node)
{	// only clears and frees the node. !! if node has subtrees, 
	// they will be left floating. use with caution to avoid memory leaks
	// ... uh.. what to do with the inner CTreeQueue floating around ..? we need to fix that too right?
	// .. what does CQueue functions give us. QueueRemove is our best bet,
	// i guess it will just try to swap around the next last ptrs.
}

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

CUDPTreeQueue *UDPTreeNodeQueueFind(U32 address, CUDPTreeNode *node)
{ // address should be pulled from an instance of CIPV4Address (TODO... double check what bit order we're in ?)

	CUDPTreeQueue *temp_queue;

	if (node->queue)
	{
		if (node->queue->socket->receive_address.family != AF_INET)
			Debug("This method was made for IPV4, UDP can be IPV4 or IPV6. excessive casting bad, TODO: revise method.");

		if (node->queue->socket->receive_address(CSocketAddressIPV4).address == address)
			return node->queue;

		temp_queue = node->queue->next;
		while (temp_queue != node->queue)
		{
			if (temp_queue->socket->receive_address(CSocketAddressIPV4).address == address)
				return temp_queue;

			temp_queue = temp_queue->next;
		}
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
			temp_last->next = temp_next;
			temp_next->last = temp_last;
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
// end UDP Bound Socket functions & classes
////////////////////////////////////////////////////









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
		ZenithLog("UDP Ethernet Frame Allocate failed.\n");
		return de_index;
	}

	header = ethernet_frame;

	header->source_port = EndianU16(source_port);
	header->destination_port = EndianU16(destination_port);
	header->length = EndianU16(sizeof(CUDPHeader) + length);
	header->checksum = 0;

	*frame_out = ethernet_frame + sizeof(CUDPHeader);

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

	// Shrine has FIXME, validate packet length!

	*source_port_out = EndianU16(header->source_port);
	*destination_port_out = EndianU16(header->destination_port);

	*data_out = packet->data + sizeof(CUDPHeader);
	*length_out = packet->length - sizeof(CUDPHeader);

	return 0;

}

//CUDPSocket *UDPSocket(U16 domain, U16 type) // should this even be allowed? why not just UDPSocket; ? it could just know its domain and type.
CUDPSocket *UDPSocket(U16 domain)
{
	U16 type = SOCKET_DATAGRAM;

	if (domain != AF_INET)
		Debug("Non IPV4 UDP Sockets not implemented yet !\n");

//	if (type != SOCKET_DATAGRAM)
//		Debug("UDP Sockets must be of type SOCKET DATAGRAM"); // maybe just return null if wrong type and ZenithErr

	CUDPSocket *udp_socket = CAlloc(sizeof(CUDPSocket));

	udp_socket->socket = Socket(domain, type);
	
	udp_socket->receive_address.family = domain; // INET or INET6

	return udp_socket;

}

I64 UDPSocketBind(CUDPSocket *udp_socket, CSocketAddressStorage *address_in) // I64 addr_len ?? does it really matter that much
{
	//if we put in addr len do a check its valid for ipv4 and ipv6 based on family

	CUDPTreeNode *temp_node;
	CSocketAddressIPV4 *ipv4_socket_addr;
	U16 port;

	switch (udp_socket->socket->state)
	{
		case SOCKET_STATE_READY: //	Socket State machine must be in init state
			break;

		default:
			ZenithErr("Unsuccessful UDP Socket Bind: Socket state-machine must be in READY state.\n");
			return -1;
	}

	if (udp_socket->bound_to) 
	{
		ZenithErr("Attempted UDP Socket Bind while UDP socket currently bound.");
		return -1;
	}

	if (address_in->family != AF_INET) Debug("Non IPV4 socket binds not implemented !");

	ipv4_socket_addr = address_in;

	udp_socket->receive_address(CSocketAddressIPV4).address.address = ipv4_socket_addr->address.address;
	// bind socket to address in parameter.
	udp_socket->receive_address(CSocketAddressIPV4).port = ipv4_socket_addr->port;
	// ... consistency would say keep in Big Endian ...

	port = EndianU16(ipv4_socket_addr->port); // port member should be Big Endian,  so now we're going L.E (?)

	if (udp_globals.bound_socket_tree)
	{
		// look for our port.
		temp_node = UDPTreeNodeFind(port, udp_globals.bound_socket_tree);

		if (temp_node)
		{ // if we find we have bound sockets at port, check address before adding to queue
			if (UDPTreeNodeQueueFind(udp_socket->receive_address(CSocketAddressIPV4).address.address, temp_node))
			{
				ZenithErr("Attempted UDP Socket Bind at an address already in Bound Socket Tree !\n");
				return -1;
			}
			else
			{ // if no address match, free to add socket to the node queue
				UDPTreeNodeQueueAdd(udp_socket, temp_node);
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
			ZenithErr("Unsuccessful UDP Socket Bind: Misconfigured Socket state-machine.\n");
			return -1;
	}

	return 0;
}

I64 UDPSocketClose(CUDPSocket *udp_socket)
{ // close, pop, and free the socket from the bound tree.
	CUDPTreeNode *node;
	CUDPTreeQueue *queue;

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

I64 UDPSocketReceiveFrom(CUDPSocket *udp_socket, U8 *buffer, I64 len, CSocketAddressStorage *src_address)
{ // ommitted I64 addrlen, flags not implemented
	CSocketAddressIPV4 *ipv4_socket_addr;
	CSocketAddressIPV6 *ipv6_socket_addr;

	udp_socket->receive_buffer	= buffer;
	udp_socket->receive_len		= len;

	if (udp_socket->receive_timeout_ms != 0)
		udp_socket->receive_max_timeout = counts.jiffies + udp_socket->receive_timeout_ms * JIFFY_FREQ / 1000;

	while (udp_socket->receive_buffer != NULL)
	{ // 'Check for timeout'
		if (udp_socket->receive_timeout_ms != 0 && counts.jiffies > udp_socket->receive_max_timeout)
		{ // Shrine has TODO: 'seterror(EWOULDBLOCK)' investigate this
			udp_socket->receive_len = -1; // ?
			break;
		}

		Yield;
	}

	if (src_address)
	{
		switch (udp_socket->receive_address.family)
		{
			case AF_INET:
				ipv4_socket_addr = src_address;
				MemCopy(ipv4_socket_addr, &udp_socket->receive_address, sizeof(CSocketAddressIPV4));
				break;
			case AF_INET6:
				ipv6_socket_addr = src_address;
				MemCopy(ipv6_socket_addr, &udp_socket->receive_address, sizeof(CSocketAddressIPV6));
				break;
		}
	}

	return udp_socket->receive_len;
}

// UDPSocketSendTo

// UDPSocketSetOpt ?

// UDPHandle

// the socket functions just act on the socket state machine.
// ZenithErr and return fail vals if socket FSM improperly used.
// Careful with Free()'s.

UDPGlobalsInit;





















































































