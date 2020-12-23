#define DIVN_GOOD_BITS	24
#define DIVN_BAD_BITS	4

class CDivinationGlobals
{
	U8	**words,
		*word_file_mask;

	I64	word_fuf_flags,
		word_count;
	CFifoU8	*fifo;
} divine;

MemSet(&divine, 0, sizeof(CDivinationGlobals));
divine.fifo = FifoU8New(2048 * 8);

U8 *TimeStampCB(CDoc *, CDocEntry *, CTask *mem_task)
{
	U8 *st = MAlloc(64, mem_task);

	StrPrint(st, "%X", TSCGet >> DIVN_BAD_BITS);

	return st;
}

U8 *KbdMouseTimeCB(CDoc *, CDocEntry *, CTask *mem_task)
{
	U8 *st = MAlloc(64, mem_task);

	StrPrint(st, "%X", KbdMouseEventTime >> DIVN_BAD_BITS);

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

I64 DivinePick(U8 *msg=NULL)
{
	U8 *st = MStrPrint("%s\n\nPress $$GREEN$$OKAY$$FG$$ to generate a random number from the timer.\n"
									"The latch is the last timestamp from the keyboard.\n"
									"When you press $$GREEN$$OKAY$$FG$$, a new timestamp will be used.\n", msg);
	PopUpTimerOk(st);
	Free(st);
	return KbdMouseEventTime >> DIVN_BAD_BITS;
}

public U0 DivineBitsInsert(I64 num_bits, I64 bitfield)
{//Insert bits info divination bit fifo.
	I64 i;

	for (i = 0; i < num_bits; i++)
	{
		FifoU8Insert(divine.fifo, bitfield & 1);
		bitfield >>= 1;
	}
}

public I64 DivineBitsRemove(I64 num_bits, U8 *msg=NULL)
{//Return N bits. If low on entropy pop-up okay.
	U8  b;
	I64 res = 0;

	while (num_bits)
	{
		if (FifoU8Remove(divine.fifo, &b))
		{
			res = res << 1 + b;
			num_bits--;
		}
		else
			DivineBitsInsert(DIVN_GOOD_BITS, DivinePick(msg));
	}

	return res;
}

I64 DivineInit(U8 *files_find_mask="/Misc/Vocab.DD")
{
	I64			 i, ch, fuf_flags = 0;;
	U8			*buf, *ptr, *ptr2;
	CDirEntry	*tmpde, *tmpde1;

	FlagsScan(&fuf_flags, Define("ST_FILE_UTIL_FLAGS"), "+r+f+F+T+O");
	if (fuf_flags & ~FUG_FILES_FIND)
		throw('FUF');

	//Free(divine.word_file_mask);
	divine.word_file_mask = StrNew(files_find_mask);
	divine.word_fuf_flags = fuf_flags;

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

	Free(divine.words);
	divine.word_count = i;
	divine.words = MAlloc(sizeof(U8 *) * i);

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
					divine.words[i++] = StrNew(ptr2);
					*ptr = ch;
				}
			}
			Free(buf);
		}
		tmpde = tmpde->next;
	}
	DirTreeDel(tmpde1);

	return divine.word_count;
}

DivineInit;

public U8 *DivineWordStr(I64 bits=17)
{//Divine a word.
	if (divine.word_count)
		return divine.words[DivineBitsRemove(bits) % divine.word_count];

	return NULL;
}

public U0 DivineWord(I64 bits=17)
{//Divine a word.
	if (divine.word_count)
		"%s ", divine.words[DivineBitsRemove(bits) % divine.word_count];
}
