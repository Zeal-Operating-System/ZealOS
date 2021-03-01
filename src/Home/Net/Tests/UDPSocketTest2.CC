U0 UDPSocketTest()
{
	CUDPSocket			*u = UDPSocket(AF_INET);
	CSocketAddressIPV4	*i = CAlloc(sizeof(CSocketAddressIPV4));

	i->port				= EndianU16(64222);
	i->family			= AF_INET;
	i->address.address	= INADDR_ANY;

	UDPSocketBind(u, i);

	"UDP Socket bound at port %d.\n", EndianU16(i->port);
	"Send UDP data to the VM, then run UDPRep to see received message data in report.\n";

	while (!CharScan)
		Refresh;

	UDPSocketClose(u);

	Free(i);
}

UDPSocketTest;