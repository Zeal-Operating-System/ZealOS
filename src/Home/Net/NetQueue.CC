/*	Shrine mentions possibly using two FIFOs
	(in our case, Queues) for pending and
	empty frames. If logical to implement,
	perhaps Zenith NetQueue code should
	do something similar to that idea.

	Each Ethernet Frame will be represented
	as an entry in a CQueue. */

class CNetQueueEntry:CQueue
{
	I64 length; //todo: change to packet_length?
	U8	frame[ETHERNET_FRAME_SIZE];
};

/*	global variable, holds pointer of Ethernet Queue.
	This acts as the Head of the Queue, Entries act
	as the Tail of the Queue. 
	Upon QueueInit, ->next and ->last are set to
	itself, the Head. */

CQueue *net_queue; // no QueueRemove the Head! only Entries!

/*	Net Handler Task is set idle and active depending
	on if entries in Net Queue. See $LK,"NetHandlerTask",A="FF:C:/Home/Net/NetHandlerTask.CC,net_handler_task"$ */

CTask *net_handler_task = NULL;

U0 NetQueueInit()
{
	net_queue = CAlloc(sizeof(CQueue));
	QueueInit(net_queue);
}

CNetQueueEntry *NetQueuePull()
{/*	Returns a pointer to a CNetQueueEntry,
	or NULL pointer if Net Queue is empty. */
	CNetQueueEntry *entry;

	if (net_queue->next != net_queue)
	{
		entry = net_queue->next;
		QueueRemove(entry);
	}
	else // Queue is empty if head->next is head itself.
	{
		entry = NULL;
	}

	return entry;
}

U0 NetQueuePushCopy(U8 *data, I64 length)
{/*	Pushes a copy of the packet data and length
	into the Net Queue. The NetQueueEntry is inserted
	after the last entry of net_queue to keep new
	items in the back of the Queue, old in front. */ 
	CNetQueueEntry *entry = CAlloc(sizeof(CNetQueueEntry));

	entry->length = length;
	MemCopy(entry->frame, data, length);

	QueueInsert(entry, net_queue->last);

	//Set Net Handler Task active.
	ZenithLog("ACTIVE: NetHandler\n");
	if (net_handler_task)
		LBtr(&net_handler_task->task_flags, TASKf_IDLE);


}

NetQueueInit;