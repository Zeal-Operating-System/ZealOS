
U0 HandleNetQueueEntry(CNetQueueEntry *entry)
{
	CEthernetFrame ethernet_frame;

	EthernetFrameParse(&ethernet_frame, entry->frame, entry->length);

	switch (ethernet_frame.ethertype)
	{
		case ETHERTYPE_ARP:
			ARPHandler(&ethernet_frame);
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
			LBts(&Fs->task_flags, TASKf_SUSPENDED);
			Yield;
		}
			
	}
}

net_handler_task = Spawn(&NetHandlerTask, NULL, "NetQueueHandler",,);