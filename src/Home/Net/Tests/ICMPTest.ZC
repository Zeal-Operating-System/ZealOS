
U8 dst_mac[6] = {0xF0, 0x0D, 0xBE, 0xAD, 0xDE, 0xAF};

U32 dst_ip = 0x01020304;

U0 ICMPTest()
{
	U8 *data_payload = CAlloc(8);

	*(data_payload(U64 *)) = EndianU64(0xDEADC0DEBEEFFADE);

	ARPCachePut(dst_ip, dst_mac); // Force entry into ARP Cache so IPV4 can match it with IPV4AddressMACGet

	while (TRUE)
	{
		ICMPReplySend(dst_ip, EndianU16(0xDEAD), EndianU16(0xBEEF), EndianU16(0xC0DE), data_payload, 8);
		Sleep(300);
	}

}

ICMPTest;