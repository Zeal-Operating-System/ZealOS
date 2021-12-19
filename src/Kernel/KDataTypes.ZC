U0 LinkedListDel(U8 **_list)
{//Free entire linked-list.
	U8 **tmpl;

	while (_list)
	{
		tmpl = *_list;
		Free(_list);
		_list = tmpl;
	}
}

U8 *LinkedListCopy(U8 **_list, CTask *mem_task=NULL)
{//MAlloc ident copy of entire linked-list.
	U8 *res = NULL, **tmpl = &res;

	while (_list)
	{
		tmpl = *tmpl = MAllocIdent(_list, mem_task);
		_list = *_list;
	}

	return res;
}

I64 LinkedListCount(U8 **_list)
{//Count of nodes in linked-list.
	I64 res = 0;

	while (_list)
	{
		res++;
		_list = *_list;
	}

	return res;
}

I64 LinkedListSize(U8 **_list)
{//Mem size of all nodes in linked-list.
	I64 res = 0;

	while (_list)
	{
		res += MSize2(_list);
		_list = *_list;
	}

	return res;
}

U0 QueueDel(CQueue *head, Bool querem=FALSE)
{//Free entries in queue, not head.
	CQueue *tmpq = head->next, *tmpq1;

	while (tmpq != head)
	{
		tmpq1 = tmpq->next;
		if (querem)
			QueueRemove(tmpq);
		Free(tmpq);
		tmpq = tmpq1;
	}
}

CQueue *QueueCopy(CQueue *head, CTask *mem_task=NULL)
{//MAlloc ident copy of entire queue and head.
	CQueue *res = MAllocIdent(head, mem_task), *tmpq = head->next, *tmpq1;

	QueueInit(res);
	while (tmpq != head)
	{
		tmpq1 = MAllocIdent(tmpq, mem_task);
		QueueInsert(tmpq1, res->last);
		tmpq = tmpq->next;
	}

	return res;
}

I64 QueueCount(CQueue *head)
{//Count of nodes in queue, not head.
	CQueue	*tmpq = head->next;
	I64		 res = 0;

	while (tmpq != head)
	{
		res++;
		tmpq = tmpq->next;
	}

	return res;
}

I64 QueueSize(CQueue *head)
{//Mem size of all nodes in queue, not head.
	CQueue	*tmpq = head->next;
	I64		 res = 0;

	while (tmpq != head)
	{
		res += MSize2(tmpq);
		tmpq = tmpq->next;
	}

	return res;
}

CQueueVectU8 *QueueVectU8New(I64 min_idx=0)
{//Create new queue vecter.
	CQueueVectU8 *res = MAlloc(sizeof(CQueueVectU8));

	QueueInit(res);
	res->total_count = res->node_count = 0;
	res->min_idx = min_idx;

	return res;
}

U0 QueueVectU8Put(CQueueVectU8 *v, I64 idx, U8 ch)
{//Put U8 at idx i.
	CQueueVectU8 *tmpv;

	idx -= v->min_idx;
	if (idx<0)
		return;
	if (idx<v->total_count)
	{
		tmpv = v;
		do
		{
			idx -= tmpv->node_count;
			if (idx < 0)
			{
				tmpv->body[idx + tmpv->node_count] = ch;
				return;
			}
			tmpv = tmpv->next;
		}
		while (tmpv != v);

	}
	else
		idx -= v->total_count;

	while (TRUE)
	{
		tmpv = v->last;
		if (tmpv->node_count >= QUE_VECT_U8_COUNT)
		{
			tmpv = MAlloc(sizeof(CQueueVectU8));
			tmpv->node_count = 0;
			QueueInsert(tmpv, v->last);
		}
		if (idx--)
		{
			tmpv->body[tmpv->node_count++] = 0;
			v->total_count++;
		}
		else
		{
			tmpv->body[tmpv->node_count++] = ch;
			v->total_count++;
			break;
		}
	}
}

U0 QueueVectU8Del(CQueueVectU8 *v)
{//Free entire queue vector.
	if (v)
	{
		QueueDel(v);
		Free(v);
	}
}

I64 QueueVectU8Get(CQueueVectU8 *v, I64 idx)
{//Get U8 at idx i.
	CQueueVectU8 *tmpv;

	idx -= v->min_idx;
	if (!(0 <= idx<v->total_count))
		return 0;
	tmpv = v;
	do
	{
		idx -= tmpv->node_count;
		if (idx < 0)
			return tmpv->body[idx + tmpv->node_count];
		tmpv = tmpv->next;
	}
	while (tmpv != v);

	return 0;
}

CFifoU8 *FifoU8New(I64 size, CTask *mem_task=NULL)
{//Create new fifo.
	CFifoU8 *f;

	if (!mem_task)
		mem_task = Fs;

	f = MAlloc(sizeof(CFifoU8), mem_task);
	f->buf		= MAlloc(size, mem_task);
	f->mask		= size - 1;
	f->in_ptr	= 0;
	f->out_ptr	= 0;

	return f;
}

U0 FifoU8Del(CFifoU8 *f)
{//Free fifo.
	Free(f->buf);
	Free(f);
}

Bool FifoU8Insert(CFifoU8 *f, U8 b)
{//Insert U8 into fifo.
	I64 new_in_ptr;

	PUSHFD
	CLI
	new_in_ptr = (f->in_ptr + 1) & f->mask;
	if (new_in_ptr == f->out_ptr)
	{
		POPFD
		return FALSE;
	}
	else
	{
		f->buf[f->in_ptr] = b;
		f->in_ptr = new_in_ptr;
		POPFD
		return TRUE;
	}
}

Bool FifoU8Remove(CFifoU8 *f, U8 *_b)
{//Remove U8 from fifo.
	PUSHFD
	CLI
	if (f->in_ptr == f->out_ptr)
	{
		POPFD
		return FALSE;
	}
	else
	{
		*_b = f->buf[f->out_ptr];
		f->out_ptr = (f->out_ptr + 1) & f->mask;
		POPFD
		return TRUE;
	}
}

Bool FifoU8Peek(CFifoU8 *f, U8 *_b)
{//Peek at front of fifo and don't remove.
	PUSHFD
	CLI
	if (f->in_ptr == f->out_ptr)
	{
		POPFD
		return FALSE;
	}
	else
	{
		*_b = f->buf[f->out_ptr];
		POPFD
		return TRUE;
	}
}

U0 FifoU8Flush(CFifoU8 *f)
{//Flush fifo getting rid of all U8's.
	PUSHFD
	CLI
	f->out_ptr = f->in_ptr;
	POPFD
}

I64 FifoU8Count(CFifoU8 *f)
{//Count of U8's in fifo.
	I64 res;

	PUSHFD
	CLI
	if (f->out_ptr > f->in_ptr)
		res = f->mask + 1 - (f->out_ptr - f->in_ptr);
	else
		res = f->in_ptr - f->out_ptr;
	POPFD

	return res;
}

CFifoI64 *FifoI64New(I64 size, CTask *mem_task=NULL)
{//Create new fifo.
	CFifoI64 *f;

	if (!mem_task)
		mem_task = Fs;

	f = MAlloc(sizeof(CFifoI64), mem_task);
	f->buf		= MAlloc(size * sizeof(I64), mem_task);
	f->mask		= size - 1;
	f->in_ptr	= 0;
	f->out_ptr	= 0;

	return f;
}

U0 FifoI64Del(CFifoI64 *f)
{//Free fifo.
	Free(f->buf);
	Free(f);
}

Bool FifoI64Ins(CFifoI64 *f, I64 q)
{//Insert I64 into fifo.
	I64 new_in_ptr;

	PUSHFD
	CLI
	new_in_ptr = (f->in_ptr + 1) & f->mask;
	if (new_in_ptr == f->out_ptr)
	{
		POPFD
		return FALSE;
	}
	else
	{
		f->buf[f->in_ptr] = q;
		f->in_ptr = new_in_ptr;
		POPFD
		return TRUE;
	}
}

Bool FifoI64Remove(CFifoI64 *f, I64 *_q)
{//Remove I64 from fifo.
	PUSHFD
	CLI
	if (f->in_ptr == f->out_ptr)
	{
		POPFD
		return FALSE;
	}
	else
	{
		*_q = f->buf[f->out_ptr];
		f->out_ptr = (f->out_ptr + 1) & f->mask;
		POPFD
		return TRUE;
	}
}

Bool FifoI64Peek(CFifoI64 *f, I64 *_q)
{//Peek at front of fifo and don't remove.
	PUSHFD
	CLI
	if (f->in_ptr == f->out_ptr)
	{
		POPFD
		return FALSE;
	}
	else
	{
		*_q = f->buf[f->out_ptr];
		POPFD
		return TRUE;
	}
}

U0 FifoI64Flush(CFifoI64 *f)
{//Flush fifo getting rid of all I64's.
	PUSHFD
	CLI
	f->out_ptr = f->in_ptr;
	POPFD
}

I64 FifoI64Count(CFifoI64 *f)
{//Count of I64's in fifo.
	I64 res;

	PUSHFD
	CLI
	if (f->out_ptr > f->in_ptr)
		res = f->mask + 1 - (f->out_ptr - f->in_ptr);
	else
		res = f->in_ptr - f->out_ptr;
	POPFD

	return res;
}
