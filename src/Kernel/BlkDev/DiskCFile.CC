I64 FSize(CFile *f)
{//Report size of opened file in bytes.
	if (f)
		return f->de.size;
	else
		return 0;
}

CFile *FOpen(U8 *filename, U8 *flags, I64 count=0)
{//Allows flags "r","w","w+". "c" for contiguous.
//(It uses $LK,"StrOcc",A="MN:StrOcc"$() for 'w', 'r', '+', 'c')
	CFile		*f = CAlloc(sizeof(CFile));
	CDirContext	*dirc;
	U8			*full_name;
	Bool		 contiguous = StrOcc(flags, 'c');

	f->clus = INVALID_CLUS;
	f->fblk_num = 0;
	if (count > 0)
		f->max_blk = count - 1;
	else
		f->max_blk = I64_MAX;
	f->file_clus_num = INVALID_CLUS;
	full_name = FileNameAbs(filename);
	f->drive = Letter2Drive(*full_name);
	if (f->drive->fs_type == FSt_REDSEA)
		contiguous = TRUE;
	if (contiguous)
	{
		f->flags |= FF_CONTIGUOUS;
		if (f->drive->fs_type != FSt_REDSEA && !(FileAttr(filename) & RS_ATTR_CONTIGUOUS))
			throw('File');
	}
	f->clus_buf = CAlloc(f->drive->spc << BLK_SIZE_BITS);
	if (StrOcc(flags, 'w'))
	{
		f->flags = f->flags | FF_WRITE | FF_NEEDS_WRITE;
		if (StrOcc(flags, '+'))
		{
			if (FileFind(full_name, &f->de, FUF_JUST_FILES))
			{
				Free(full_name);
				if (contiguous)
					f->max_blk = (FSize(f) + BLK_SIZE - 1) >> BLK_SIZE_BITS - 1;
				return f;
			}
		}
		else
			Del(full_name,,, FALSE);
		f->de.full_name = full_name;
		f->flags |= FF_NEW_FILE;
		if (dirc = DirContextNew(full_name))
		{
			StrCopy(f->de.name, dirc->mask);
			if (count > 0)
			{//We pre-alloc the whole thing.
				f->de.clus = ClusAlloc(f->drive,0, (count + f->drive->spc - 1) / f->drive->spc, contiguous);
				f->de.size = count << BLK_SIZE_BITS;
				DirNew(dirc->drive, Fs->cur_dir, &f->de, TRUE);
				f->flags &= ~FF_NEW_FILE;
			}
			DirContextDel(dirc);
			return f;
		}
	}
	else
	{
		if (FileFind(full_name, &f->de, FUF_JUST_FILES))
		{
			Free(full_name);
			f->max_blk = (FSize(f) + BLK_SIZE - 1) >> BLK_SIZE_BITS - 1;
			return f;
		}
	}
	Free(f->clus_buf);
	Free(full_name);
	Free(f);

	return NULL;
}

U0 FClose(CFile *f)
{//Close CFile, updating directory.
	CDirContext *dirc;

	if (f)
	{
		if (f->flags & FF_BUF_DIRTY)
		{
			ClusWrite(f->drive, f->clus_buf, f->clus, 1);
			f->flags &= ~FF_BUF_DIRTY;
		}
		if (f->flags & FF_NEEDS_WRITE)
		{
			if (dirc = DirContextNew(f->de.full_name))
			{
				if (!(f->flags & FF_USE_OLD_DATETIME))
					f->de.datetime = Now;
				if (f->flags & FF_NEW_FILE)
					DirNew(dirc->drive, Fs->cur_dir, &f->de, TRUE);
				else
					DirNew(dirc->drive, Fs->cur_dir, &f->de, FALSE);
				DirContextDel(dirc);
			}
			else
				throw('File');
		}
		Free(f->clus_buf);
		Free(f->de.full_name);
		Free(f);
	}
}

I64 FSetClus(CFile *f, I64 c, I64 blk, Bool read)
{
	CDrive	*drive = f->drive;
	I64		 i;

	if (f->clus != c)
	{
		if (f->flags & FF_BUF_DIRTY)
		{
			i = drive->spc;
			if (f->max_blk != I64_MAX)
			{
				i = f->max_blk + 1 - f->file_clus_num * drive->spc;
				if (i > drive->spc)
					i = drive->spc;
			}
			ClusBlkWrite(drive, f->clus_buf, f->clus, i);
			f->flags = f->flags & ~FF_BUF_DIRTY;
		}
		f->clus = c;
		f->file_clus_num = blk / drive->spc;
		if (read)
		{
			i = drive->spc;
			if (f->max_blk != I64_MAX)
			{
				i = f->max_blk + 1 - f->file_clus_num * drive->spc;
				if (i > drive->spc)
					i = drive->spc;
			}
			c = ClusBlkRead(drive, f->clus_buf, c, i);
		}
	}

	return c;
}

Bool FBlkRead(CFile *f, U8 *buf, I64 blk=FFB_NEXT_BLK, I64 count=1)
{//Read [nth,n+count) blocks of file.
	CDrive	*drive = f->drive;
	I64		 spc   = drive->spc, i, j, c = f->de.clus;

	if (!f || !drive)
		return FALSE;
	if (blk == FFB_NEXT_BLK)
		blk = f->fblk_num;
	if (blk + count - 1 > f->max_blk)
		return FALSE;
	if (count <= 0)
		return TRUE;

	if (f->flags & FF_CONTIGUOUS)
	{
		BlkRead(drive, buf, Clus2Blk(drive, c) + blk, count);
		blk += count;
	}
	else
	{
		i = blk / spc;
		if (0 <= f->file_clus_num <= i)
		{
			c = f->clus;
			i -= f->file_clus_num;
		}
		if (i > 0)
			c = ClusNumNext(drive, c, i);

		if (i = blk % spc)
		{
			c = FSetClus(f, c, blk, TRUE);
			if (count < spc - i)
				j = count;
			else
				j = spc - i;
			MemCopy(buf, f->clus_buf + i << BLK_SIZE_BITS, j << BLK_SIZE_BITS);
			buf += j << BLK_SIZE_BITS;
			count -= j;
			blk += j;
		}
		while (count >= spc)
		{
			c = FSetClus(f, c, blk, TRUE);
			MemCopy(buf, f->clus_buf, spc << BLK_SIZE_BITS);
			buf += spc << BLK_SIZE_BITS;
			count -= spc;
			blk += spc;
		}
		if (count > 0)
		{
			c = FSetClus(f, c, blk, TRUE);
			MemCopy(buf, f->clus_buf, count << BLK_SIZE_BITS);
			buf += count<<BLK_SIZE_BITS;
			blk += count;
		}
	}
	f->fblk_num = blk;

	return TRUE;
}

Bool FBlkWrite(CFile *f, U8 *buf, I64 blk=FFB_NEXT_BLK, I64 count=1)
{//Write [nth,n+count) blocks of file.
	CDrive	*drive = f->drive;
	I64		 spc   = drive->spc, i, j, c = f->de.clus, c1;

	if (!f || !drive)
		return FALSE;
	if (blk == FFB_NEXT_BLK)
		blk = f->fblk_num;
	if (blk + count - 1 > f->max_blk)
		return FALSE;
	if (!(f->flags & FF_WRITE))
		return FALSE;
	if (count <= 0)
		return TRUE;
	if (f->flags & FF_CONTIGUOUS)
	{
		BlkWrite(drive, buf, Clus2Blk(drive, c) + blk, count);
		blk += count;
	}
	else
	{
		if (!c)
		{
			c = ClusAlloc(drive, 0, 1, FALSE);
			f->file_clus_num = 0;
			f->clus = c;
			f->de.clus = c;
			f->flags |= FF_NEEDS_WRITE | FF_NEW_FILE;
		}
		i = blk / spc;
		if (0 <= f->file_clus_num <= i)
		{
			c = f->clus;
			i -= f->file_clus_num;
		}
		while (i > 0)
		{
			c1 = c;
			c = ClusNumNext(drive, c1, 1);
			if (c == INVALID_CLUS)
			{
				c = ClusAlloc(drive, c1, i, FALSE);
				if (i > 1)
					c = ClusNumNext(drive, c, i - 1);
				break;
			}
			else
				i--;
		}

		if (i = blk % spc)
		{
			FSetClus(f, c, blk, TRUE);
			if (count < spc - i)
				j = count;
			else
				j = spc - i;
			MemCopy(f->clus_buf + BLK_SIZE * i, buf, j << BLK_SIZE_BITS);
			f->flags |= FF_BUF_DIRTY;
			buf += j << BLK_SIZE_BITS;
			count -= j;
			blk += j;
			if (count > 0)
			{
				c1 = c;
				c = ClusNumNext(drive, c1, 1);
				if (c == INVALID_CLUS)
					c = ClusAlloc(drive, c1, 1, FALSE);
			}
		}
		while (count >= spc)
		{
			FSetClus(f, c, blk, FALSE);
			MemCopy(f->clus_buf, buf, spc << BLK_SIZE_BITS);
			f->flags |= FF_BUF_DIRTY;
			buf += spc << BLK_SIZE_BITS;
			count -= spc;
			blk += spc;
			if (count > 0)
			{
				c1 = c;
				c = ClusNumNext(drive, c1, 1);
				if (c == INVALID_CLUS)
					c = ClusAlloc(drive, c1, 1, FALSE);
			}
		}
		if (count > 0)
		{
			FSetClus(f, c, blk, TRUE);
			MemCopy(f->clus_buf, buf, count << BLK_SIZE_BITS);
			f->flags |= FF_BUF_DIRTY;
			buf += count << BLK_SIZE_BITS;
			blk += count;
		}
		if (f->de.size < blk << BLK_SIZE_BITS)
			f->de.size = blk << BLK_SIZE_BITS;
	}
	f->fblk_num = blk;

	return TRUE;
}
