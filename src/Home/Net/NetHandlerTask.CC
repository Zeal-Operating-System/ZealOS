U0 IPV4Handler(CEthernetFrame *ethernet_frame)
{
	CIPV4Packet packet;

	IPV4ParsePacket(&packet, ethernet_frame);

	ARPCachePut(packet.source_ip_address, ethernet_frame->source_address);

	switch (packet.protocol)
	{
		case IP_PROTOCOL_ICMP:
			ZenithLog("IPV4 Handler: ICMP.\n");
			ICMPHandler(&packet);
			break;
		case IP_PROTOCOL_TCP:
			break;
		case IP_PROTOCOL_UDP:
			ZenithLog("IPV4 Handler: UDP.\n");
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
			ARPHandler(&ethernet_frame);
			break;
		case ETHERTYPE_IPV4:
			IPV4Handler(&ethernet_frame);
			break;
	}
}

U0 NetHandlerTask(I64)
{
	while (TRUE)
	{
		CNetQueueEntry *entry = NetQueuePull;

		if (entry)
		{
			HandleNetQueueEntry(entry);
		}
		else
		{
			LBts(&Fs->task_flags, TASKf_IDLE);
			//ZenithLog("IDLE: NetHandler\n");
			Yield;
		}
			
	}
}

net_handler_task = Spawn(&NetHandlerTask, NULL, "NetQueueHandler",,);