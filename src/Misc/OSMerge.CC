CDirEntry OSFilesMGFind(CDirEntry *needle_entry, CDirEntry *haystack_list)
{
	while (haystack_list)
	{
		if (!StrCompare(needle_entry->name, haystack_list->name))
			return haystack_list;
		haystack_list = haystack_list->next;
	}

	return NULL;
}

U0 OSFilesMergeInner(CDirEntry *tmpde1, CDirEntry *tmpde2, I64 *_fuf_flags, I64 *_df_flags)
{
	CDirEntry	*tmpde;
	U8			*new;

	while (tmpde1 && !(*_df_flags & DF_ABORT_ALL_FILES))
	{
		tmpde = OSFilesMGFind(tmpde1, tmpde2);
		if (!tmpde)
		{
			"$$BROWN$$Does Not Exist:%s$$FG$$\n", tmpde1->full_name;
			new = StrNew(tmpde1->full_name);
			new[0] = tmpde2->full_name[0]; // shortcut to quickly get drive letter
			Copy(tmpde1->full_name, new);
			Free(new);
		}
		else
		{
			if (tmpde1->attr & RS_ATTR_DIR)
				OSFilesMergeInner(tmpde1->sub, tmpde->sub, _fuf_flags, _df_flags);
			else
			{
				if (AbsI64(tmpde1->datetime - tmpde->datetime) > CDATE_FREQ * 2) {//slop
					"%s", tmpde1->full_name;
					'\n';
					if (Bt(_fuf_flags, FUf_DIFF))
					{
						if (FilesFindMatch(tmpde1->full_name, FILEMASK_TXT))
							Diff(tmpde->full_name, tmpde1->full_name, _df_flags);
					}
				}
			}
		}
		tmpde1 = tmpde1->next;
	}
}

U0 OSFilesMerge(U8 *dst_files_find_mask="/*", U8 *src_files_find_mask="/*", U8 *fu_flags=NULL)
{ // See $LK+PU,"Merge",A="FF:::/System/Utils/Merge.CC,public U0 Merge"$.
	I64			 df_flags = 0, fuf_flags = 0;
	CDirEntry	*tmpde1 = NULL, *tmpde2 = NULL;

	FlagsScan(&fuf_flags, Define("ST_FILE_UTIL_FLAGS"), "+r");
	FlagsScan(&fuf_flags, Define("ST_FILE_UTIL_FLAGS"), fu_flags);
	if (fuf_flags & ~(FUG_FILES_FIND | FUF_DIFF))
		throw('FUF');
	PrintWarn("This is based strictly on file dates.\n");
	tmpde1 = FilesFind(src_files_find_mask, fuf_flags & FUG_FILES_FIND);
	tmpde2 = FilesFind(dst_files_find_mask, fuf_flags & FUG_FILES_FIND);
	fuf_flags &= FUF_DIFF;
	OSFilesMergeInner(tmpde1, tmpde2, &fuf_flags, &df_flags);
	DirTreeDel(tmpde1);
	DirTreeDel(tmpde2);
}


U0 OSMerge(U8 dst_drv, U8 src_drv=':')
{
	U8 *dst = MStrPrint("%C:/", dst_drv);
	U8 *src = MStrPrint("%C:/", src_drv);

	CopyTree(src, "B:/");
	OSFilesMerge("B:/", dst, "+d");
	"Format %C:/ ? ", dst_drv;
	Format(dst_drv);
	CopyTree("B:/", dst);

	BootHDIns(dst_drv);
}

