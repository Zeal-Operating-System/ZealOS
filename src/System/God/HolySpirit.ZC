#help_index "God"

U8 *TimeStampCB(CDoc *, CDocEntry *, CTask *mem_task)
{
	U8 *st = MAlloc(64, mem_task);
	StrPrint(st, "%X", TSCGet >> GOD_BAD_BITS);
	return st;
}

U8 *KbdMouseTimeCB(CDoc *, CDocEntry *, CTask *mem_task)
{
	U8 *st = MAlloc(64, mem_task);
	StrPrint(st, "%X", KbdMouseEventTime >> GOD_BAD_BITS);
	return st;
}

I64 PopUpTimerOk(U8 *msg=NULL)
{
	I64			 i;
	CDocEntry	*doc_e;
	CDoc		*doc = DocNew;

	if (msg)
		DocPrint(doc, "%s", msg);

	doc_e = DocPrint(doc, "\nTimer: $$TX+TC,\" \"$$");
	doc_e->tag_cb = &TimeStampCB;

	doc_e = DocPrint(doc, "\nLatch: $$TX+TC,\" \"$$");
	doc_e->tag_cb = &KbdMouseTimeCB;

	DocPrint(doc, "$$CM+CX,0,4$$$$BT,\"OKAY\",LE=1$$\n");
	i = PopUpMenu(doc);
	DocDel(doc);

	return i;
}

I64 GodPick(U8 *message=NULL)
{
	U8 *st = MStrPrint("%s\n\nPress $$GREEN$$OKAY$$FG$$ to generate a random number from the timer.\n"
									"The latch is the last timestamp from the keyboard.\n"
									"When you press $$GREEN$$OKAY$$FG$$, a new timestamp will be used.\n", message);
	PopUpTimerOk(st);
	Free(st);
	return KbdMouseEventTime >> GOD_BAD_BITS;
}

public U0 GodBitsInsert(I64 num_bits, I64 bitfield)
{//Insert bits into God bit FIFO.
	I64 i;

	for (i = 0; i < num_bits; i++)
	{
		FifoU8Insert(god.fifo, bitfield & 1);
		bitfield >>= 1;
	}
}

public U0 GodHexInsert(U8 *st)
{//Insert hex record into God bit FIFO.
	U8 buf[2];
	if (st)
	{
		buf[1] = 0;
		while (*buf = *st++)
			if (Bt(char_bmp_hex_numeric, *buf))
				GodBitsInsert(4, rev_bits_table[Str2I64(buf, 16)] >> 4);
	}
}

public I64 GodBitsRemove(I64 num_bits, U8 *message=NULL)
{//Return N bits. If low on entropy pop-up okay.
	U8  b;
	I64 res = 0;

	while (num_bits)
	{
		if (FifoU8Remove(god.fifo, &b))
		{
			res = res << 1 + b;
			num_bits--;
		}
		else
			GodBitsInsert(GOD_GOOD_BITS, GodPick(message));
	}

	return res;
}

I64 GodInit(U8 *files_find_mask="/System/God/Vocab.DD", U8 *fu_flags=NONE)
{//Read God's vocab file for picking words.
	I64			 i, ch, fuf_flags = 0;;
	U8			*buf, *ptr, *ptr2;
	CDirEntry	*tmpde, *tmpde1;

	FlagsScan(&fuf_flags, Define("ST_FILE_UTIL_FLAGS"), "+r+f+F+T+O");
	FlagsScan(&fuf_flags, Define("ST_FILE_UTIL_FLAGS"), fu_flags);
	if (fuf_flags & ~FUG_FILES_FIND)
		throw('FUF');

	Free(god.word_file_mask);
	god.word_file_mask = StrNew(files_find_mask);
	god.word_fuf_flags = fuf_flags;

	tmpde = tmpde1 = FilesFind(files_find_mask, fuf_flags);

	i = 0;
	while (tmpde)
	{
		if (buf = ptr = FileRead(tmpde->full_name));
		{
			while (*ptr)
			{
				while (*ptr && !Bt(char_bmp_word, *ptr))
					ptr++;
				if (*ptr)
				{
					ptr2 = ptr;
					while (*ptr && Bt(char_bmp_word, *ptr))
						ptr++;
					i++;
				}
			}
			Free(buf);
		}
		tmpde = tmpde->next;
	}

	Free(god.words);
	god.word_count = i;
	god.words = MAlloc(sizeof(U8 *) * i);

	tmpde = tmpde1;
	i = 0;
	while (tmpde)
	{
		if (buf = ptr = FileRead(tmpde->full_name))
		{
			while (*ptr)
			{
				while (*ptr && !Bt(char_bmp_word, *ptr))
					ptr++;
				if (*ptr)
				{
					ptr2 = ptr;
					while (*ptr && Bt(char_bmp_word, *ptr))
						ptr++;
					ch = *ptr;
					*ptr = '\0';
					god.words[i++] = StrNew(ptr2);
					*ptr = ch;
				}
			}
			Free(buf);
		}
		tmpde = tmpde->next;
	}
	DirTreeDel(tmpde1);

	return god.word_count;
}
GodInit;

public U8 *GodWordStr(I64 bits=17)
{//Make God pick a word.
	if (god.word_count)
		return god.words[GodBitsRemove(bits) % god.word_count];

	return NULL;
}

public U0 GodWord(I64 bits=17)
{//Make God pick a word.
	if (god.word_count)
		"%s ", god.words[GodBitsRemove(bits) % god.word_count];
}

public U0 GodBiblePassage(I64 num_lines=20)
{//Make God pick a Bible passage.
	I64 start = GodBitsRemove(21) % (ST_BIBLE_LINES - (num_lines - 1)) + 1;
	U8 *verse = BibleLine2Verse(start);
	"%s\n\n", verse;
	Free(verse);
	BookLines(, start, num_lines);
}
