U0 IPV4Handler(CEthernetFrame *ethernet_frame)
{
	CIPV4Packet packet;

	IPV4ParsePacket(&packet, ethernet_frame);

	ARPCachePut(packet.source_ip_address, ethernet_frame->source_address);

	switch (packet.protocol)
	{
		case IP_PROTOCOL_ICMP:
			NetLog("IPV4 HANDLER: ICMP.");
			ICMPHandler(&packet);
			break;

		case IP_PROTOCOL_TCP:
			break;

		case IP_PROTOCOL_UDP:
			NetLog("IPV4 HANDLER: UDP.");
			UDPHandler(&packet);
			break;
	}

	NetLog("IPV4 HANDLER: Exiting.");
}

U0 HandleNetQueueEntry(CNetQueueEntry *entry)
{
	CEthernetFrame ethernet_frame;

	EthernetFrameParse(&ethernet_frame, entry->frame, entry->length);

	switch (ethernet_frame.ethertype)
	{
		case ETHERTYPE_ARP:
			NetLog("HANDLE NETQUEUE ENTRY: ARP.");
			ARPHandler(&ethernet_frame);
			break;

		case ETHERTYPE_IPV4:
			NetLog("HANDLE NETQUEUE ENTRY: IPV4.");
			IPV4Handler(&ethernet_frame);
			break;
	}

	NetLog("HANDLE NETQUEUE ENTRY: Exiting.");
}

interrupt U0 NetHandler()
{
	CNetQueueEntry *entry;

	while (entry = NetQueuePull())
	{
		NetLog("NET HANDLER: Caught NetQueue Entry, handling.");
		HandleNetQueueEntry(entry);
	}

	*(dev.uncached_alias + LAPIC_EOI)(U32*) = 0;
}

U0 NetHandlerInit()
{
	IntEntrySet(I_NETHANDLER, &NetHandler);
}

NetHandlerInit;
