U0 UDPSocketTest()
{
	CUDPSocket			*u0 = UDPSocket(AF_INET);
	CUDPSocket			*u1 = UDPSocket(AF_INET);
	CSocketAddressIPV4	*i0 = CAlloc(sizeof(CSocketAddressIPV4));
	CSocketAddressIPV4	*i1 = CAlloc(sizeof(CSocketAddressIPV4));

	i0->port			= EndianU16(80);
	i0->family			= AF_INET;
	i0->address.address	= 0xDEADBEEF;

	i1->port			= EndianU16(68);
	i1->family			= AF_INET;
	i1->address.address = 0xF00DBABE;

	UDPSocketBind(u0, i0);

	ClassRep(udp_globals.bound_socket_tree);

	UDPSocketBind(u1, i1);

	"Before remove first socket\n";
	UDPRep;
	"\n";

	UDPSocketClose(u0);

	"After remove first socket\n";
	UDPRep;
	"\n";

	UDPSocketClose(u1);

	"After both sockets removed\n";
	UDPRep;
	"\n";

	Free(i0);
	Free(i1);
}

UDPSocketTest;