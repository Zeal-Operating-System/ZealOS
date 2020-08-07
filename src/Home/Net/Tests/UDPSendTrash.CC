CAddressInfo	*result	= NULL;
I64				 error	= DNSGetAddressInfo("zenithos.org", NULL, &result);
I64				 i = 0;

if (error < 0)
{
	ZenithErr("failed at DNS Get Address Info.\n");
}
else
{
	CUDPSocket			*u = UDPSocket(AF_INET);
	CSocketAddressIPV4	*ipv4_addr = result->address;

	ipv4_addr->port = EndianU16(80);
	U8 *b = CAlloc(4);
	b[0] = 0xDE;
	b[1] = 0xAD;
	b[2] = 0xBE;
	b[3] = 0xEF;
	UDPSocketSendTo(u, b, 4, ipv4_addr);
}
