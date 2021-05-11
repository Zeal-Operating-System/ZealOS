CTCPSocket *tcp = TCPSocket(AF_INET);
U8 *buffer = CAlloc(8);

*buffer = EndianU64(0xDEADBEEFC0DEFADE);

tcp->timeout = TCP_TIMEOUT;

ClassRep(tcp);

CSocketAddressIPV4 *socket_addr = CAlloc(sizeof(CSocketAddressIPV4));

CIPV4Address addr;
PresentationToNetwork(AF_INET, "127.0.0.1", &addr);

socket_addr->port = EndianU16(0xBEEF);
socket_addr->family = AF_INET;
socket_addr->address.address = addr.address;

"\nTrying to connect the socket\n";
if (TCPSocketConnect(tcp, socket_addr) == 0)
	"\nSocket connected.\n";
else
	"\nFailed to connect.\n";

"\n\nTrying to Send data\n";
if (TCPSocketSend(tcp, buffer, 8) > 0)
	"\nData sent\n";
else
	"\nData not sent\n";

ClassRep(tcp_globals.bound_socket_tree);

Sleep(5000);

"\n\nTrying to close the socket\n";
TCPSocketClose(tcp);
"\nSocket Closed.";

Sleep(500);

//NetStop;

//NetStart;