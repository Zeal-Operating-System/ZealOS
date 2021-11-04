#help_index "AutoComplete/Dictionary"

acd.has_words = FileFind(ACD_WORD_FILENAME);
acd.has_defs  = FileFind(ACD_DEF_FILENAME);

public U0 ACDWordsLoad()
{//Put words from word list into hash table.
	I64			  size;
	CHashGeneric *tmph;
	U8			 *in_ptr, *in_start, *st2;
	U16			 *d;

	acd.num_words = 0;

	if (in_ptr = FileRead(ACD_WORD_FILENAME, &size))
	{
		in_start = in_ptr;
		Free(acd.word_list);
		acd.word_list = SysMAlloc(size);
		MemCopy(acd.word_list, in_start, size);
		acd.word_list_size = size;

		while (in_ptr < in_start + size)
		{
			if (*in_ptr == ACD_WORD_CHAR)
				in_ptr++;
			if (*in_ptr)
			{
				st2 = MStrUtil(in_ptr, SUF_TO_UPPER);
				tmph = SysCAlloc(sizeof(CHashGeneric) + StrLen(st2) + 1);
				StrCopy(tmph + 1, st2);
				Free(st2);
				in_ptr += StrLen(in_ptr) + 1;
				tmph->str = tmph + 1;
				tmph->use_count = 1;
				tmph->type = HTT_DICT_WORD;
				d = in_ptr;
				tmph->user_data0 = *d;
				in_ptr += 2;
				HashAdd(tmph, ac.hash_table);
				acd.num_words++;
			}
			else
				in_ptr += 3;
		}
		Free(in_start);
	}
}

#help_index "AutoComplete"
CHashAC *ACHashAdd(U8 *w)
{
	CHashAC *tmpw = HashFind(w, ac.hash_table, HTT_WORD);

	if (tmpw)
	{
		tmpw->hits++;
		return tmpw;
	}
	tmpw = SysCAlloc(sizeof(CHashAC));
	tmpw->str		= SysStrNew(w);
	tmpw->type		= HTT_WORD;
	tmpw->use_count	= 1;
	tmpw->hits		= 1;
	HashAdd(tmpw, ac.hash_table);
	ac.num_words++;
	return tmpw;
}

U0 ACSingleFileAdd(U8 *buf)
{
	I64 ch;
	U8 *ptr = buf, *ptr2, *ptr3;

	while (TRUE)
	{
		while (TRUE)
		{
			if (ch = *ptr++)
			{
				if (Bt(char_bmp_alpha_numeric, ch))
					break;
			}
			else
				return;
		}
		ptr3 = ptr;
		ptr2 = ptr;
		ptr--;

		while (TRUE)
		{
			if (ch = *ptr2++)
			{
				if (Bt(char_bmp_alpha_numeric, ch))
					*ptr3++ = ch;
				else if (ch != CH_CURSOR)
					break;
			}
			else
			{
				ptr2--;
				break;
			}
		}
		*ptr3 = 0;
		ACHashAdd(ptr);
		ptr = ptr2;
	}
}

U0 ACMainFileListTraverse(U8 *files_find_mask)
{
	U8		  *buf;
	CDirEntry *tmpde, *tmpde1;

	try
	{
		tmpde = tmpde1 = FilesFind(files_find_mask, FUF_RECURSE | FUF_JUST_TXT | FUF_JUST_FILES | FUF_CLUS_ORDER);
		while (tmpde)
		{
			"%s\n", tmpde->full_name;
			buf = FileRead(tmpde->full_name);
			ACSingleFileAdd(buf);
			Free(buf);
			tmpde = tmpde->next;
		}
	}
	catch
		Fs->catch_except = TRUE;

	DirTreeDel(tmpde1);
}

public U0 ACInit(U8 *mask=NULL)
{//Read files and build AutoComplete statistics.
	LBtr(&sys_run_level, RLf_AUTOCOMPLETE);
	AutoComplete;
	while (LBts(&ac.flags, ACf_INIT_IN_PROGRESS))
		Yield;

	HashTableDel(ac.hash_table);
	ac.hash_table = HashTableNew(2048, sys_task);

	ac.num_words = 0;
	Free(ac.cur_word);
	ac.cur_word = NULL;

	if (mask)
		ACMainFileListTraverse(mask);

	ACDWordsLoad;
	RegDefault("AutoComplete", "ac.col = TEXT_COLS-34;ac.row = 10;");
	RegExe("AutoComplete");
	LBtr(&ac.flags, ACf_INIT_IN_PROGRESS);
	LBts(&sys_run_level, RLf_AUTOCOMPLETE);
	AutoComplete(ON);
}

I64 AutoCompleteSize()
{
	if (ac.hash_table)
		return HashTableSize2(ac.hash_table) + MSize2(acd.word_list);
	else
		return 0;
}
