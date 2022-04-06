U0 UDPSocketTest()
{
	"Before any sockets added:\n";
	UDPRep;

	CUDPSocket			*u0 = UDPSocket(AF_INET);
	CUDPSocket			*u1 = UDPSocket(AF_INET);
	CUDPSocket			*u2 = UDPSocket(AF_INET);
	CUDPSocket			*u3 = UDPSocket(AF_INET);
	CUDPSocket			*u4 = UDPSocket(AF_INET);
	CUDPSocket			*u5 = UDPSocket(AF_INET);

	CSocketAddressIPV4	*i0 = CAlloc(sizeof(CSocketAddressIPV4));
	CSocketAddressIPV4	*i1 = CAlloc(sizeof(CSocketAddressIPV4));
	CSocketAddressIPV4	*i2 = CAlloc(sizeof(CSocketAddressIPV4));
	CSocketAddressIPV4	*i3 = CAlloc(sizeof(CSocketAddressIPV4));
	CSocketAddressIPV4	*i4 = CAlloc(sizeof(CSocketAddressIPV4));
	CSocketAddressIPV4	*i5 = CAlloc(sizeof(CSocketAddressIPV4));

	i0->port			= EndianU16(30);
	i0->family			= AF_INET;
	i0->address.address	= 0xDEADBEEF;

	i1->port			= EndianU16(25);
	i1->family			= AF_INET;
	i1->address.address = 0xF00DBABE;

	i2->port			= EndianU16(35);
	i2->family			= AF_INET;
	i2->address.address = 0xC0C0D0D0;

	i3->port			= EndianU16(20);
	i3->family			= AF_INET;
	i3->address.address = 0xF007BA11;

	i4->port			= EndianU16(28);
	i4->family			= AF_INET;
	i4->address.address = 0x0B0E5EED;

	i5->port			= EndianU16(37);
	i5->family			= AF_INET;
	i5->address.address = 0x00ABCDEF;

	UDPSocketBind(u0, i0);
	UDPSocketBind(u1, i1);
	UDPSocketBind(u2, i2);
	UDPSocketBind(u3, i3);
	UDPSocketBind(u4, i4);
	UDPSocketBind(u5, i5);

	"All sockets now bound. Currently bound:\n";
	UDPRep;
	"\n";

	UDPSocketClose(u0);
	"After remove first socket\n";
	UDPRep;
	"\n";

	UDPSocketClose(u1);
	"After remove second socket\n";
	UDPRep;
	"\n";

	UDPSocketClose(u2);
	"After remove third socket\n";
	UDPRep;
	"\n";

	UDPSocketClose(u3);
	"After remove fourth socket\n";
	UDPRep;
	"\n";

	UDPSocketClose(u4);
	"After remove fifth socket\n";
	UDPRep;
	"\n";

	UDPSocketClose(u5);
	"After remove sixth socket\n";
	UDPRep;
	"\n";

	Free(i0);
	Free(i1);
	Free(i2);
	Free(i3);
	Free(i4);
	Free(i5);
}

UDPSocketTest;