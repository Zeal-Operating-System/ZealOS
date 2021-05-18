
U8 src[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xC0, 0xDE};
U8 dst[6] = {0xF0, 0x0D, 0xBE, 0xAD, 0xDE, 0xAF};

U0 EthernetTest()
{
	U8 *packet_buffer;
	I64 de_index;

	while (TRUE)
	{
		de_index = EthernetFrameAllocate(&packet_buffer, src, dst, 0x0000, 8);

		*(packet_buffer(U64 *)) = EndianU64(0xC0DEFADEDEADBEEF);

		EthernetFrameFinish(de_index);
		Sleep(300);
	}
}

EthernetTest;