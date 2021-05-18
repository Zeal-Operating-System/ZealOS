U8 dst_mac[6] = {0xF0, 0x0D, 0xBE, 0xAD, 0xDE, 0xAF};

U32 dst_ip = 0x01020304;

U0 DHCPTest()
{ // DHCPConfigure (if not already configured), then send UDP test data.

	U8 *udp_payload;
	I64 de_index;

	ARPCachePut(dst_ip, dst_mac); // Force entry into ARP Cache so IPV4 can match it with IPV4AddressMACGet

	if (ipv4_globals.local_ip == 0)
		DHCPConfigure;

	while (TRUE)
	{

		de_index = UDPPacketAllocate(&udp_payload, ipv4_globals.local_ip, 0xDEAD, dst_ip, 0xBEEF, 8);

		*(udp_payload(U64 *)) = EndianU64(0xDEADBEEFC0DEFADE);

		UDPPacketFinish(de_index);
		Sleep(300);
	}
}

DHCPTest;
