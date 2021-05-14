/*
	Chat program proof-of-concept using UDP.

	Tested on Bridged Mode with two VMs under the same router (same and different computers),
	and on NAT Network Mode with two VMs using the same virtualized NAT.

*/

U8				*dest_ip_string		= StrGet("Destination IPV4: "),
				*port_string		= StrGet("RX & TX UDP Port: ");
CIPV4Address	*dest_address		= CAlloc(sizeof(CIPV4Address));

I64				 port				= Str2I64(port_string);
CTask			*chat_display_task	= NULL;
CTask			*chat_message_task	= NULL;

U0 ChatDisplayTask(I64)
{ // display received messages.
	DocTermNew;
	DocCursor;
	DocPrint(, "$$WW,1$$");

	while (TaskValidate(chat_message_task))
	{
		Refresh;
	}
}

U0 ChatMessageTask(I64)
{ // take in text.
	U8	*message;
	I64  de_index;
	U8	*payload;

	DocTermNew;
	DocPrint(, "$$WW,1$$");

	while (message = StrGet("> ",, SGF_SHIFT_ESC_EXIT))
	{
		DocBottom(chat_display_task->put_doc);
		DocPrint(chat_display_task->put_doc, "$$BG,BLUE$$$$BLACK$$<local>$$FG$$$$BG$$ %s\n", message);

		de_index = UDPPacketAllocate(&payload, ipv4_globals.local_ip, port, dest_address->address, port, StrLen(message));
		MemCopy(payload, message, StrLen(message));
		UDPPacketFinish(de_index);

		DocClear;
		DocPrint(, "$$WW,1$$");

	}
}

U0 ChatInit()
{
	chat_message_task = Spawn(&ChatMessageTask, NULL, "UDP Chat Message");
	chat_display_task = Spawn(&ChatDisplayTask, NULL, "UDP Chat");
	chat_message_task->win_inhibit = WIG_USER_TASK_DEFAULT;
	chat_display_task->win_inhibit = WIG_USER_TASK_DEFAULT;
	LBts(&chat_message_task->display_flags, DISPLAYf_SHOW);
	LBts(&chat_display_task->display_flags, DISPLAYf_SHOW);

	WinFocus(chat_display_task);
	WinFocus(chat_message_task);

	chat_display_task->win_top		= 2;
	chat_display_task->win_bottom	= TEXT_ROWS / 3;
	chat_display_task->win_left		= TEXT_COLS / 3;
	chat_display_task->win_right	= TEXT_COLS / 3 * 2;

	chat_message_task->win_top		= chat_display_task->win_bottom + 2;
	chat_message_task->win_bottom	= chat_message_task->win_top + 3;
	chat_message_task->win_left		= chat_display_task->win_left;
	chat_message_task->win_right	= chat_display_task->win_right;

}

U0 Chat()
{
	CUDPSocket			*udp_socket = UDPSocket(AF_INET);
	CSocketAddressIPV4	*sock_addr = CAlloc(sizeof(CSocketAddressIPV4));
	U8					*buffer[ETHERNET_FRAME_SIZE];

//	MemSet(buffer, 0, ETHERNET_FRAME_SIZE);

	"\nIP entered: %s\n", dest_ip_string;

	while (PresentationToNetwork(AF_INET, dest_ip_string, dest_address) == -1)
	{
		"ERROR: Bad IP entered. Retry.\n";
		dest_ip_string = StrGet("Destination IPV4: ");
	}

	ChatInit;

	sock_addr->port				= EndianU16(port);
	sock_addr->family			= AF_INET;
	sock_addr->address.address	= dest_address->address;
	UDPSocketBind(udp_socket, sock_addr);

	"\nIP entered: %s\n", dest_ip_string;

	while (TaskValidate(chat_message_task))
	{
		if (UDPSocketReceiveFrom(udp_socket, buffer, ETHERNET_FRAME_SIZE, NULL) != -1)
		{
			DocBottom(chat_display_task->put_doc);
			DocPrint(chat_display_task->put_doc, "$$BG,PURPLE$$$$BLACK$$<%s>$$FG$$$$BG$$  %s\n", dest_ip_string, buffer);//NetworkToPresentation(AF_INET, dest_address));
			MemSet(buffer, 0, ETHERNET_FRAME_SIZE);
		}

		Refresh;

	}

	Free(sock_addr);
	UDPSocketClose(udp_socket);

}

Chat;