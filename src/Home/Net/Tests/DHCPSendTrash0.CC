
U0 DHCPSendTrash()
{
	while (TRUE)
	{
		DHCPSendDiscover(0xDEADBEEF);
		Sleep(300);
		DHCPSendRequest(0xDEADBEEF, 0xC0DEFADE, 0xFEEDFACE);
		Sleep(300);
	}
}

DHCPSendTrash;