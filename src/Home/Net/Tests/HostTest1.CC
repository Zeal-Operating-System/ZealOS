U8 dns_mac[6] = {0xF0, 0x0D, 0xBE, 0xAD, 0xDE, 0xAF};

U32 dns_ip = 0x51525354;


U0 HostTest()
{
	if (dns_globals.addr_family == AF_UNSPEC)
	{
		ARPCachePut(dns_ip, dns_mac);	// Force entry into ARP Cache so IPV4 can match it with IPV4AddressMACGet
		DNSResolverIPV4Set(dns_ip);		// Forcing so DNSQuestionSend succeeds
	}

	Host("zenithos.org");

}

HostTest;