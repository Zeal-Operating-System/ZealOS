I64 DirIndexList(U8 *files_find_mask)
{
	CDirEntry	*tmpde1 = NULL, *tmpde2;
	I64			 res = 0;
	U8			*st, *st_full;

	tmpde1 = FilesFind(files_find_mask);

	if (tmpde1)
	{
		st = MAllocIdent(tmpde1->full_name);
		StrLastRemove(st, "/");
		if (!st[2])
			StrCopy(st + 2, "/");

		"Directory of %s\n", st;

		Free(st);

		while (tmpde1)
		{
			tmpde2 = tmpde1->next;
			res++;

			if (tmpde1->attr & RS_ATTR_DIR)
			{
				st		= MStrPrint("%s/", tmpde1->name);
				st_full	= MStrPrint("%s/%s", tmpde1->full_name, "index.html");
				"$$BG,YELLOW$$";
				PutFileLink(st, st_full);
				"$$BG$$";
				Free(st);
				Free(st_full);
			}
			else
				PutFileLink(tmpde1->name, tmpde1->full_name);

			'\n';
			DirEntryDel(tmpde1);
			tmpde1 = tmpde2;
		}
		"\n\n";
	}
	else
		"No matching entries\n";

	return res;
}


