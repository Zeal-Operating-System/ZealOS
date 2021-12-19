CTCPSocket *tcp = TCPSocket(AF_INET);
CTCPSocket *new;

ClassRep(tcp);

CSocketAddressIPV4 *addr = CAlloc(sizeof(CSocketAddressIPV4));

addr->port = EndianU16(0xBEEF);
addr->family = AF_INET;
addr->address.address = INADDR_ANY;

TCPSocketBind(tcp, addr);
TCPSocketListen(tcp, 32);

"\nTry TCPSocketClose(tcp);\n";
/*
ClassRep(tcp_globals.bound_socket_tree);

tcp->timeout = TCP_TIMEOUT;
while (TRUE)
{
	new = TCPSocketAccept(tcp);

	if (new)
	{
		"\n\nSocket accepted\n\n";
		ClassRep(new);
		break;
	}
	else
		Sleep(1);
}

*/

/*
"\nTrying to close the accepted socket:\n";
TCPSocketClose(new);

"\nTrying to close the original Listening socket\n";
TCPSocketClose(tcp);*/