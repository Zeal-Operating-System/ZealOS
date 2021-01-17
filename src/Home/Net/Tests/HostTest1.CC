U8 dns_mac[6] = {0xF0, 0x0D, 0xBE, 0xAD, 0xDE, 0xAF};

U32 dns_ip = 0x51525354;


U0 HostTest()
{
	ARPCachePut(dns_ip, dns_mac);	// Force entry into ARP Cache so IPV4 can match it with GetMACAddressForIP
	DNSSetResolverIPV4(dns_ip);		// Forcing so DNSSendQuestion succeeds


	"\n$BG,8$Type $FG,0$G2;$FG$ if it crashes$BG$\n\n";
	Host("zenithos.org");

}

HostTest;