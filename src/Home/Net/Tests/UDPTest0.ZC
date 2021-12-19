U8 dst_mac[6] = {0xF0, 0x0D, 0xBE, 0xAD, 0xDE, 0xAF};

U32 src_ip = 0x30313233;
U32 dst_ip = 0x01020304;

U0 UDPTest()
{
	U8 *udp_payload;
	I64 de_index;

	ARPCachePut(dst_ip, dst_mac); // Force entry into ARP Cache so IPV4 can match it with IPV4AddressMACGet

	while (TRUE)
	{
		de_index = UDPPacketAllocate(&udp_payload, src_ip, 0xDEAD, dst_ip, 0xBEEF, 8);

		*(udp_payload(U64 *)) = EndianU64(0xDEADBEEFC0DEFADE);

		UDPPacketFinish(de_index);
		Sleep(300);

	}

}

UDPTest;
