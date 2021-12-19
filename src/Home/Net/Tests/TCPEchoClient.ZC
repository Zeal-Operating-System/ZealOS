CTCPSocket	*tcp			= TCPSocket(AF_INET);
//U8			 buffer_size	= 16;
//U8			*buffer			= CAlloc(buffer_size);
U8			*buffer			= "Hello world";
U8			 buffer_size	= StrLen(buffer);

CSocketAddressIPV4 *socket_addr = CAlloc(sizeof(CSocketAddressIPV4));

//*buffer = EndianU64(0xDEADBEEFC0DEFADE);

U0 TCPTest()
{
	tcp->timeout = TCP_TIMEOUT * 3;

	CIPV4Address addr;
	PresentationToNetwork(AF_INET, "10.0.2.7", &addr);

	socket_addr->port			 = EndianU16(0xBEEF);
	socket_addr->family			 = AF_INET;
	socket_addr->address.address = addr.address;

	ClassRep(tcp);

	"\nTrying to connect the socket\n";
	if (TCPSocketConnect(tcp, socket_addr) == 0)
		"\nSocket connected.\n";
	else
		"\nFailed to connect.\n";

	ClassRep(tcp);

	"\n\nTrying to Send data\n";
	if (TCPSocketSend(tcp, buffer, buffer_size) > 0)
		"\nData sent\n";
	else
		"\nData not sent\n";


	"\n\nTrying to Receive data\n";
	if (TCPSocketReceive(tcp, buffer, buffer_size) > 0)
		"\nData received\n";
	else
		"\nData not received\n";

	"\n\n";

	DumpMem(buffer, buffer_size);

	ClassRep(tcp_globals.bound_socket_tree);

	Sleep(5000);

	"\n\nTrying to close the connected socket\n";
	if (TCPSocketClose(tcp) == 0)
		"\nSocket closed.";
	else
		"\nSocket close failed.";

	Sleep(500);

	//NetStop;

	//NetStart;
}


TCPTest;
