I64 DirIndexList(U8 *files_find_mask)
{
	CDirEntry	*tmpde1 = NULL, *tmpde2;
	I64			 res = 0;
	U8			*st, *st_full;

	tmpde1 = FilesFind(files_find_mask);

	if (tmpde1)
	{
		"%s\n", tmpde1->full_name;

		while (tmpde1)
		{
			tmpde2 = tmpde1->next;
			res++;

			if (tmpde1->attr & RS_ATTR_DIR)
			{
				st		= MStrPrint("%s/%s", tmpde1->name, "index.html");
				st_full	= MStrPrint("%s/%s", tmpde1->full_name, "index.html");
				PutFileLink(st, st_full);
				Free(st);
				Free(st_full);
//				PutDirLink(tmpde1->name, tmpde1->full_name);
			}
			else
				PutFileLink(tmpde1->name, tmpde1->full_name);

			'\n';
			DirEntryDel(tmpde1);
			tmpde1 = tmpde2;
		}
	}
	else
		"No matching entries\n";

	return res;
}
