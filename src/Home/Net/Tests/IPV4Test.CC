U8 dst_mac[6] = {0xF0, 0x0D, 0xBE, 0xAD, 0xDE, 0xAF};

U32 src_ip = 0x30313233;
U32 dst_ip = 0x01020304;

U0 IPV4Test()
{
	U8 *ipv4_packet_buffer;
	I64 de_index;

	ARPCachePut(dst_ip, dst_mac); // Force entry into ARP Cache so IPV4 can match it with IPV4AddressMACGet

	while (TRUE)
	{
		de_index = IPV4PacketAllocate(&ipv4_packet_buffer, 0xFF, src_ip, dst_ip, 8);

		*(ipv4_packet_buffer(U64 *)) = EndianU64(0xBEEFDEADFADEC0DE);

		IPV4PacketFinish(de_index);
		Sleep(300);
	}
}

IPV4Test;