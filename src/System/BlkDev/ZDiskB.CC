#help_index "File/Internal"
I64 DirTreeSerializeSize(CDirEntry *tmpde)
{
	I64 res = 0;

	while (tmpde)
	{
		res += CDIR_SIZE + 1;
		if (tmpde->attr & RS_ATTR_DIR)
			res += DirTreeSerializeSize(tmpde->sub);
		tmpde = tmpde->next;
	}

	return res + 1;
}
I64 DirTreeSerializeFill(CDirEntry *tmpde, U8 *dst)
{
	I64 res = 0, i;

	while (tmpde)
	{
		*dst++ = 1;
		res++;
		MemCopy(dst, &tmpde->start, CDIR_SIZE);
		dst += CDIR_SIZE;
		res += CDIR_SIZE;
		if (tmpde->attr & RS_ATTR_DIR)
		{
			i = DirTreeSerializeFill(tmpde->sub, dst);
			dst += i;
			res += i;
		}
		tmpde = tmpde->next;
	}
	*dst = 0;

	return res + 1;
}
public U8 *DirTreeSerialize(CDirEntry *tmpde, I64 *_size=NULL)
{//Serialize tree returned from $LK,"FilesFind",A="MN:FilesFind"$() into a one contiguous U8 array.
	I64 size = DirTreeSerializeSize(tmpde);
	U8 *buf = MAlloc(size);

	DirTreeSerializeFill(tmpde, buf);
	if (_size)
		*_size = size;

	return buf;
}

U8 *DirTreeUnserialize2(U8 *src, CDirEntry **tmpde)
{
	CDirEntry *tmpde1;

	if (*src++)
	{
		tmpde1 = CAlloc(sizeof(CDirEntry));
		*tmpde = tmpde1;
		MemCopy(&tmpde1->start, src, CDIR_SIZE);
		src += CDIR_SIZE;
		if (tmpde1->attr & RS_ATTR_DIR)
			src = DirTreeUnserialize2(src, &tmpde1->sub);
		src = DirTreeUnserialize2(src, &tmpde1->next);
	}
	else
		*tmpde = NULL;

	return src;
}
public CDirEntry *DirTreeUnserialize(U8 *src)
{//Unserialize tree to make it like a tree returned from $LK,"FilesFind",A="MN:FilesFind"$().
	CDirEntry *tmpde = NULL;

	DirTreeUnserialize2(src, &tmpde);

	return tmpde;
}

#help_index "File/Program Routines"
U0 FOFlatten(CDirEntry *tmpde, CDirEntry **a, I64 *i)
{
	CDirEntry *tmpde1;

	while (tmpde)
	{
		tmpde1 = tmpde->next;
		if (tmpde->attr & RS_ATTR_DIR)
		{
			FOFlatten(tmpde->sub, a, i);
			DirEntryDel(tmpde);
		}
		else
		{
			a[*i] = tmpde;
			*i = *i + 1;
		}
		tmpde = tmpde1;
	}
}

I64 Size1(CDirEntry *tmpde,I64 round_to)
{
	I64 res = 0, i;

	while (tmpde)
	{
		i = tmpde->size;

		if (round_to)
			i = CeilU64(tmpde->size, round_to);
		if (tmpde->attr & RS_ATTR_DIR)
			i += Size1(tmpde->sub, round_to);
		tmpde->user_data = i; //Store size in user_data member
		res += i;
		tmpde = tmpde->next;
	}

	return res;
}
public I64 Size(U8 *files_find_mask="/*", U8 *fu_flags=NULL, I64 round_to=0)
{//Total size of files in mask.
//Does not include directory size of base directory, but does include size of sub directories.
	I64			 fuf_flags = 0, res = 0;
	CDirEntry	*tmpde1 = NULL;

	FlagsScan(&fuf_flags, Define("ST_FILE_UTIL_FLAGS"), "+r");
	FlagsScan(&fuf_flags, Define("ST_FILE_UTIL_FLAGS"), fu_flags);
	if (tmpde1 = FilesFind(files_find_mask, fuf_flags & FUG_FILES_FIND))
	{
		res = Size1(tmpde1, round_to);
		DirTreeDel(tmpde1);
	}

	return res;
}

public I64 FileCount(CDirEntry *tmpde)
{//Count of files in $LK,"CDirEntry",A="MN:CDirEntry"$ tree.
	I64 count = 0;

	while (tmpde)
	{
		if (tmpde->attr & RS_ATTR_DIR)
			count += FileCount(tmpde->sub);
		else
			count++;
		tmpde = tmpde->next;
	}

	return count;
}

#help_index "File/Cmd Line (Typically);Cmd Line (Typically)"
public I64 FF(U8 *files_find_mask, U8 *fu_flags=NULL)
{//Files find. List files matching mask.
	I64			 count = 0, fuf_flags = 0;
	CDirEntry	*tmpde, *tmpde1;

	FlagsScan(&fuf_flags, Define("ST_FILE_UTIL_FLAGS"), "+r+f+F");
	FlagsScan(&fuf_flags, Define("ST_FILE_UTIL_FLAGS"), fu_flags);
	tmpde = tmpde1 = FilesFind(files_find_mask, fuf_flags);
	while (tmpde)
	{
		PutFileLink(tmpde->full_name);
		'\n';
		count++;
		tmpde = tmpde->next;
	}
	DirTreeDel(tmpde1);

	return count;
}
