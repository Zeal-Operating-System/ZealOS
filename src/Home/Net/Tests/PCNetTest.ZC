U0 PCNetTest()
{
	U8 *packet_buffer;
	I64 de_index;

	while (TRUE)
	{
		de_index = PCNetTransmitPacketAllocate(&packet_buffer, 8);

		*(packet_buffer(U64 *)) = EndianU64(0xDEADBEEFC0DEFADE);

		PCNetTransmitPacketFinish(de_index);
		Sleep(300);
	}
}

PCNetTest;