CTCPSocket	*tcp			= TCPSocket(AF_INET);
CTCPSocket	*new;
U8			 buffer_size	= TCP_MSS;
U8			*buffer			= CAlloc(buffer_size);

CSocketAddressIPV4 *socket_addr = CAlloc(sizeof(CSocketAddressIPV4));

U0 TCPTest()
{
	tcp->timeout = TCP_TIMEOUT * 3;

	ClassRep(tcp);

	socket_addr->port			 = EndianU16(0xBEEF);
	socket_addr->family			 = AF_INET;
	socket_addr->address.address = INADDR_ANY;

	"\nTrying to bind socket.\n";
	if (TCPSocketBind(tcp, socket_addr) == 0)
		"\nSocket bound.\n";
	else
		"\nFailed to bind socket.\n";

	"\nTrying to listen on socket.\n";
	if (TCPSocketListen(tcp, 5) == 0)
		"\nSocket now listening.\n";
	else
		"\nFail to listen on socket.\n";

	"\nTrying to accept a connection\n";
	if ((new = TCPSocketAccept(tcp)) != NULL)
		"\nNew socket connected.\n";
	else
	{
		"\nFailed to accept.\n";
		return;
	}

	"\n\nTrying to Receive data\n";

	if (TCPSocketReceive(new, buffer, buffer_size) > 0)
		"\nData received\n";
	else
		"\nData not received\n";

	"\n\n";

	Dump(buffer, buffer_size, FALSE);

	"\n\n";

	"\nTrying to Send data\n";
	if (TCPSocketSend(new, buffer, buffer_size) > 0) // echo back
		"\nData sent.\n";
	else
		"\nData not sent\n";

	ClassRep(tcp_globals.bound_socket_tree);

	Sleep(5000);

	"\n\nTrying to close the accepted socket\n";
	if (TCPSocketClose(new) == 0)
		"\nSocket Closed.";
	else
		"\nSocket close failed."

	"\n\nTrying to close the listening socket\n";
	if (TCPSocketClose(tcp) == 0)
		"\nSocket Closed.";
	else
		"\nSocket close failed.";



	Sleep(500);

	//NetStop;

	//NetStart;
}

TCPTest;