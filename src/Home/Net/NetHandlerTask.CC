U0 IPV4Handler(CEthernetFrame *ethernet_frame)
{
	CIPV4Packet packet;

	IPV4ParsePacket(&packet, ethernet_frame);

	ARPCachePut(packet.source_ip_address, ethernet_frame->source_address);

	switch (packet.protocol)
	{
		case IP_PROTOCOL_ICMP:
			ZenithLog("IPV4 HANDLER: ICMP.\n");
			ICMPHandler(&packet);
			break;
		case IP_PROTOCOL_TCP:
			break;
		case IP_PROTOCOL_UDP:
			ZenithLog("IPV4 HANDLER: UDP.\n");
			UDPHandler(&packet);
			break;
	}
}

U0 HandleNetQueueEntry(CNetQueueEntry *entry)
{
	CEthernetFrame ethernet_frame;

	EthernetFrameParse(&ethernet_frame, entry->frame, entry->length);

	switch (ethernet_frame.ethertype)
	{
		case ETHERTYPE_ARP:
			ZenithLog("HANDLE NETQUEUE ENTRY: ARP.\n");
			ARPHandler(&ethernet_frame);
			break;
		case ETHERTYPE_IPV4:
			ZenithLog("HANDLE NETQUEUE ENTRY: IPV4.\n");
			IPV4Handler(&ethernet_frame);
			break;
	}
}

U0 NetHandlerTask(I64)
{
	while (TRUE)
	{
		CNetQueueEntry *entry = NetQueuePull();

		if (entry)
		{
			ZenithLog("NET HANDLER TASK: Caught NetQueue Entry, handling.\n");
			HandleNetQueueEntry(entry);
		}
		else
		{
			LBts(&Fs->task_flags, TASKf_IDLE);
			//ZenithLog("IDLE: NetHandler\n");
			Yield;
		}
			
	}
	ZenithErr("Net Handler Task exit! Debug!\n"); // shouldn't ever reach this
}

net_handler_task = Spawn(&NetHandlerTask, NULL, "NetQueueHandler");

