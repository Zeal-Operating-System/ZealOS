U0 BgtDataRead()
{
	CBgtEntry 		*tmpb;
	CBgtTemplate	*tmpt;
	I64 			 i, count, size;
	U8				*b, *ptr;
	I64 			 max_num;
	U8			    **s = StrFileRead(bgt_string_file, &max_num);

	MemSet(&b_head, 0, sizeof(CBgtEntry));
	QueueInit(&b_head);
	b_head.date = Now;
	MemSet(&t_head, 0, sizeof(CBgtTemplate));
	QueueInit(&t_head);
	t_head.b.date = Now;

	if (ptr = b = FileRead(bgt_data_file, &size))
	{
		count = *ptr(I64 *)++;
		for (i = 0; i < count; i++)
		{
			tmpb = CAlloc(sizeof(CBgtEntry));
			MemCopy(&tmpb->start, ptr, BE_SIZE);
			tmpb->credit = StrNew(s[tmpb->credit_idx]);
			tmpb->debit  = StrNew(s[tmpb->debit_idx]);
			tmpb->desc	 = StrNew(s[tmpb->desc_idx]);
			QueueInsert(tmpb, b_head.last);
			ptr += BE_SIZE;
		}

		count = *ptr(I64 *)++;
		for (i = 0; i < count; i++)
		{
			tmpt = CAlloc(sizeof(CBgtTemplate));
			MemCopy(&tmpt->start, ptr, BT_SIZE);
			ptr += BT_SIZE;
			MemCopy(&tmpt->b.start, ptr, BE_SIZE);
			ptr += BE_SIZE;
			tmpt->b.credit	= StrNew(s[tmpt->b.credit_idx]);
			tmpt->b.debit	= StrNew(s[tmpt->b.debit_idx]);
			tmpt->b.desc	= StrNew(s[tmpt->b.desc_idx]);
			QueueInsert(tmpt, t_head.last);
		}
	}

	StrFileArrDel(s, max_num);
	Free(b);

	BgtAcctsUpdate;
}

U0 BgtDataWrite()
{
	I64				 i, num = 0, size, count1, count2;
	CHashTable		*table = HashTableNew(1024);
	CBgtEntry 		*tmpb;
	CBgtTemplate	*tmpt;
	CHashGeneric	*tmph;
	U8				*buf, *ptr;

	for (i = 0; i <= accts_table->mask; i++)
	{
		tmph=accts_table->body[i];
		while (tmph)
		{
			StrFileAdd(tmph->str, &num, table); //Cosmetics -- make accts appear first.
			tmph = tmph->next;
		}
	}

	tmpb = b_head.next;
	count1 = 0;
	while (tmpb != &b_head)
	{
		if (tmpb->type != BE_TEMPLATE_COPY)
		{
			tmpb->credit_idx	= StrFileAdd(tmpb->credit, &num, table);
			tmpb->debit_idx 	= StrFileAdd(tmpb->debit, &num, table);
			tmpb->desc_idx		= StrFileAdd(tmpb->desc, &num, table);
			count1++;
		}
		tmpb = tmpb->next;
	}

	tmpt = t_head.next;
	count2 = 0;
	while (tmpt != &t_head)
	{
		tmpt->b.credit_idx	= StrFileAdd(tmpt->b.credit, &num, table);
		tmpt->b.debit_idx 	= StrFileAdd(tmpt->b.debit, &num, table);
		tmpt->b.desc_idx	= StrFileAdd(tmpt->b.desc, &num, table);
		count2++;
		tmpt = tmpt->next;
	}
	StrFileWrite(bgt_string_file, table);
	StrFileDel(table);

	size = sizeof(I64) * 2 + count1 * BE_SIZE + count2 * (BT_SIZE + BE_SIZE);
	buf = ptr = MAlloc(size);

	MemCopy(ptr, &count1, sizeof(I64));
	ptr += sizeof(I64);
	tmpb=b_head.next;
	while (tmpb != &b_head)
	{
		if (tmpb->type != BE_TEMPLATE_COPY)
		{
			MemCopy(ptr, &tmpb->start, BE_SIZE);
			ptr += BE_SIZE;
		}
		tmpb = tmpb->next;
	}

	MemCopy(ptr, &count2, sizeof(I64));
	ptr += sizeof(I64);
	tmpt=t_head.next;
	while (tmpt != &t_head)
	{
		MemCopy(ptr, &tmpt->start, BT_SIZE);
		ptr += BT_SIZE;
		MemCopy(ptr, &tmpt->b.start, BE_SIZE);
		ptr += BE_SIZE;
		tmpt = tmpt->next;
	}

	FileWrite(bgt_data_file, buf, size);
	Free(buf);
}

U0 BgtDel()
{
	CBgtEntry 		*tmpb, *tmpb1;
	CBgtTemplate	*tmpt, *tmpt1;

	tmpb = b_head.next;
	while (tmpb != &b_head)
	{
		tmpb1 = tmpb->next;
		BgtEntryDel2(tmpb);
		Free(tmpb);
		tmpb = tmpb1;
	}
	tmpt = t_head.next;
	while (tmpt != &t_head)
	{
		tmpt1 = tmpt->next;
		BgtEntryDel2(&tmpt->b);
		Free(tmpt);
		tmpt = tmpt1;
	}
	StrFileDel(accts_table);
	accts_table = NULL;
	accts_table_strs = 0;
}
