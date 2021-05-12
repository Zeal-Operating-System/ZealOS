CTCPSocket *tcp = TCPSocket(AF_INET);
tcp->timeout = TCP_TIMEOUT;

ClassRep(tcp);

CSocketAddressIPV4 *socket_addr = CAlloc(sizeof(CSocketAddressIPV4));

CIPV4Address addr;
PresentationToNetwork(AF_INET, "10.0.2.7", &addr);

socket_addr->port = EndianU16(0xBEEF);
socket_addr->family = AF_INET;
socket_addr->address.address = addr.address;

"\nTrying to connect the socket\n";
if (TCPSocketConnect(tcp, socket_addr) == 0)
	"\nSocket connected.\n";


ClassRep(tcp_globals.bound_socket_tree);

Sleep(5000);

"\nTrying to close the socket\n";
TCPSocketClose(tcp);

Sleep(500);

//NetStop;

//NetStart;