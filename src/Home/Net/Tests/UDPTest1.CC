U0 UDPTest()
{

	CAddressInfo	*result	= NULL;
	I64				 error;
	U8				*b;

	if (ipv4_globals.local_ip == 0)
	{ // This test needs to have the network configured first.
		NetConfigure;
	}

	error = DNSAddressInfoGet("zenithos.org", NULL, &result);
	if (error < 0)
	{
		NetErr("failed at DNS Get Address Info.");
	}
	else
	{
		CUDPSocket			*u = UDPSocket(AF_INET);
		CSocketAddressIPV4	*ipv4_addr = result->address;

		ipv4_addr->port = EndianU16(80);
		b = CAlloc(4);
		b[0] = 0xDE;
		b[1] = 0xAD;
		b[2] = 0xBE;
		b[3] = 0xEF;

		while (TRUE)
		{
			UDPSocketSendTo(u, b, 4, ipv4_addr);
			Sleep(300);
		}
	}
}

UDPTest;