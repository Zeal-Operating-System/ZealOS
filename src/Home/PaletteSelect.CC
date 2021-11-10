
I64 selected = 1;
I64 dir_length = 5;
U8 files[5];// = 1,2,3,4,5;

U0 PaletteChange()
{
	DocClear;
	
	CDirEntry	*tmpde1 = NULL, *tmpde2;
	U8			*st;
	I64			 csize = 0xFFFF, c = 0xFFFF, res = 0;
	U8			files[0];

	tmpde1 = FilesFind("~/PaletteEditor/Palettes/*.CC");

	if (tmpde1)
	{

		if(selected > 6) selected = 6;
		if(selected < 1) selected = 1;

//		Free(st);
		st = MAllocIdent(tmpde1->full_name);
		StrLastRemove(st, "/");
		if (!st[2])
			StrCopy(st + 2, "/");
		//Find max columns
//		tmpde2 = tmpde1;
//		while (tmpde2)
//		{
//			if (tmpde2->size > csize)
//				csize = tmpde2->size;
//			if (tmpde2->clus > c)
//				c = tmpde2->clus;
//			tmpde2 = tmpde2->next;
//		}
//		csize = Bsr(csize) / 4 + 1;
//		c = Bsr(c) / 4 + 1;
		while (tmpde1)
		{
			tmpde2 = tmpde1->next;
//			files[res] = tmpde1-name;
			res++;
//			dir_length++;
			FileExtRemove(tmpde1);
			if (selected==res) "$$GREEN$$%s\n",tmpde1->name;
			else "$$BLACK$$%s\n",tmpde1->name;

						
			DirEntryDel(tmpde1);
			tmpde1 = tmpde2;
		}
//		Free(st);
	}
//	I64 i;
//	for(i=0;i<dir_length;i++)
//	{
//		//if (selected==res) "$$GREEN$$%s\n",files[i];
//		"$$WHITE$$%s\n",files[i];
//	}
}


public U0 PaletteSelect()
{
	I64 arg1,arg2,ch=0;

	// this is terrible, shouldnt rescan everytime you select...
	// i guess it'll update the treelist tho lmao
	PaletteChange;

	try {
		while(TRUE) {
			switch(MessageScan(&arg1,&arg2,1<<MESSAGE_KEY_DOWN|1<<MESSAGE_KEY_UP)) {
				case MESSAGE_KEY_DOWN:
					ch=arg1;
					switch(ch){
						case CH_CTRLZ: selected--; PaletteChange; break;
						case CH_CTRLX: selected++; PaletteChange; break;
						case CH_ESC:
						case CH_SHIFT_ESC:
							throw;
					}
					break;
				}
			Refresh;
		}
	}
	catch
		PutExcept;

}


PaletteSelect;