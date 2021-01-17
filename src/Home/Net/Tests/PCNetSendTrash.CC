U0 PCNetSendTrash()
{
	U8 *packet_buffer;
	I64 de_index;

	while (TRUE)
	{
		de_index = PCNetAllocateTransmitPacket(&packet_buffer, 8);

		*(packet_buffer(U64 *)) = EndianU64(0xDEADBEEFC0DEFADE);

		PCNetFinishTransmitPacket(de_index);
		Sleep(300);
	}
}

PCNetSendTrash;