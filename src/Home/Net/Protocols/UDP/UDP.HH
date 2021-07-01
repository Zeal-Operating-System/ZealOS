#define UDP_MAX_PORT	65535

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

class CUDPTreeQueue:CQueue
{
	CUDPSocket		*socket;
};

class CUDPTreeNode:CBST
{
	CUDPTreeQueue	*queue;
};

class CUDPRepEntry:CQueue
{
	CUDPTreeNode *node;
};

class CUDPHeader
{
	U16 source_port;
	U16 destination_port;
	U16 length;
	U16 checksum;
};


class CUDPGlobals
{

	CUDPTreeNode *bound_socket_tree;

} udp_globals;

