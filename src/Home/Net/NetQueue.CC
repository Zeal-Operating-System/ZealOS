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


/*	PCNet reroutes PCI interrupts to software. See $LK,"PCNet",A="FF:C:/Home/Net/PCNet.CC,I_PCNET0"$.
	Net Handler interrupt is generated whenever an entry is
	pushed to the NetQueue. See $LK,"NetHandler",A="FF:C:/Home/Net/NetHandler.CC,I_NETHANDLER"$ */

#define I_PCNET0		I_USER + 0
#define I_PCNET1		I_USER + 1
#define I_PCNET2		I_USER + 2
#define I_PCNET3		I_USER + 3
#define I_NETHANDLER	I_USER + 4

#define INT_DEST_CPU	0

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

		NetLog("NETQUEUE PULL: Removing entry from queue.");
		QueueRemove(entry);
	}
	else // Queue is empty if head->next is head itself.
	{
		entry = NULL;
	}

	return entry;
}

U0 NetQueuePush(U8 *data, I64 length)
{/*	Pushes a copy of the packet data and length
	into the Net Queue. The NetQueueEntry is inserted
	after the last entry of net_queue to keep new
	items in the back of the Queue, old in front. */ 

	CNetQueueEntry *entry = CAlloc(sizeof(CNetQueueEntry));

	entry->length = length;

	MemCopy(entry->frame, data, length);

	QueueInsert(entry, net_queue->last);

	// Generate Net Handler interrupt.
	NetLog("NETQUEUE PUSH COPY: Generating NetHandler interrupt.");
	MPInt(I_NETHANDLER, INT_DEST_CPU);
}


NetQueueInit;