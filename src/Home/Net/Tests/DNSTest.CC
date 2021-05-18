U8 dns_mac[6] = {0xF0, 0x0D, 0xBE, 0xAD, 0xDE, 0xAF};

U32 dns_ip = 0x51525354;

U0 DNSTest()
{

	U8			**labels = CAlloc(4);
	U8			**l = labels;
	CDNSQuestion *q = CAlloc(sizeof(CDNSQuestion));

	if (dns_globals.addr_family == AF_UNSPEC)
	{
		ARPCachePut(dns_ip, dns_mac);	// Force entry into ARP Cache so IPV4 can match it with IPV4AddressMACGet
		DNSResolverIPV4Set(dns_ip);		// Forcing so DNSQuestionSend succeeds
	}

	q->q_name.labels		= labels;
	q->q_name.num_labels	= 4;

	*(l++) = StrNew("test1");
	*(l++) = StrNew("test2");
	*(l++) = StrNew("test3");
	*(l++) = StrNew("test4");

	while (TRUE)
	{

		DNSQuestionSend(0xDEAD, 0xBEEF, q);
		Sleep(300);
	}
}

DNSTest;