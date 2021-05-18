
U0 DHCPTest()
{
	while (TRUE)
	{
		DHCPDiscoverSend(0xDEADBEEF);
		Sleep(300);
		DHCPRequestSend(0xDEADBEEF, 0xC0DEFADE, 0xFEEDFACE);
		Sleep(300);
	}
}

DHCPTest;