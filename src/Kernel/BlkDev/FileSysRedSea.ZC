// See $LK,"RedSea File System",A="FI:::/Doc/RedSea.DD"$

U0 RedSeaFreeFreeList(CDrive *drive)
{
	CFreeList	*tmpf, *tmpf1;
	Bool		 unlock;
	try
	{
		unlock = DriveLock(drive);
		if (tmpf = drive->next_free)
		{
			while (tmpf != &drive->next_free)
			{
				tmpf1 = tmpf->next;
				Free(tmpf);
				tmpf = tmpf1;
			}
		}
		drive->next_free = NULL;
		if (unlock)
			DriveUnlock(drive);
	}
	catch
		if (unlock)
			DriveUnlock(drive);
}

U0 RedSeaFreeListBuild(CDrive *drive)
{
	Bool		 unlock;
	CFreeList	*tmpf;
	I64			 i, first = drive->data_area, max_blk = drive->size + drive->drv_offset;

	try
	{
		unlock = DriveLock(drive);
		if (drive->next_free)
			RedSeaFreeFreeList(drive);
		QueueInit(&drive->next_free);
		while (first < max_blk)
		{
			i = 0;	//count free clus
			while (first + i < max_blk)
			{
				DriveFATBlkSet(drive, first + i);
				if (Bt(drive->cur_fat_blk, (first + i - drive->data_area) & (BLK_SIZE << 3 - 1)))
					break;
				else
					i++;
			}
			if (i)
			{
				tmpf = SysMAlloc(sizeof(CFreeList));
				tmpf->size  = i;
				tmpf->start = first;
				QueueInsert(tmpf, drive->last_free);
			}
			first += i + 1;
		}
		if (unlock)
			DriveUnlock(drive);
	}
	catch
		if (unlock)
			DriveUnlock(drive);
}

U0 RedSeaInit(CDrive *drive)
{
	CRedSeaBoot	br;
	Bool		unlock;

	try
	{
		unlock = DriveLock(drive);
		BlkRead(drive, &br, drive->drv_offset, 1);
		if (br.signature != MBR_PT_REDSEA || br.signature2 != 0xAA55)
			throw('Drive');
		drive->fs_type		= FSt_REDSEA;
		RedSeaFreeFreeList(drive);
		drive->spc			= 1;
		drive->size			= br.sects;
		drive->data_area	= drive->drv_offset + br.bitmap_sects;
		drive->root_clus	= br.root_clus;
		drive->fat1	= drive->fat2 = drive->drv_offset + 1;
		DriveFATBlkAlloc(drive);
		if (unlock)
			DriveUnlock(drive);
	}
	catch
		if (unlock)
			DriveUnlock(drive);
}

Bool RedSeaValidate(U8 drv_let)
{
	CDrive		*drive;
	CRedSeaBoot	 br;

	if ((drive = Letter2Drive(drv_let, FALSE)) && drive->fs_type == FSt_REDSEA &&
			BlkRead(drive, &br, drive->drv_offset, 1) && br.signature == MBR_PT_REDSEA && br.signature2 == 0xAA55)
		return TRUE;
	else
		return FALSE;
}

U0 RedSeaFormat(U8 drv_let, Bool quick=TRUE)
{
	U8			*root_dir;
	CDirEntry	*d_native;
	CRedSeaBoot	*br = CAlloc(BLK_SIZE);
	CDrive		*drive = Letter2Drive(drv_let);
	I64			 i, n, root_dir_blks;

	try
	{
		DriveLock(drive);
//			DriveTypeSet(drv_let, FSt_REDSEA);
		DriveTypeSet(drv_let, FSt_FAT32);
		drive->fs_type		= FSt_REDSEA;
		br->signature		= MBR_PT_REDSEA;
		br->signature2		= 0xAA55;
		br->drv_offset		= drive->drv_offset; //For CD/DVD image copy.
		br->sects			= drive->size;
		n = (br->sects + BLK_SIZE << 3 - 1) / BLK_SIZE << 3;
		br->bitmap_sects	= n;
		br->unique_id		= TSCGet^Now()(U64);
		br->root_clus		= 0;

		if (quick)
			i = n + 1;
		else
			i = drive->size;
		BlkWriteZero(drive, drive->drv_offset, i);

		BlkWrite(drive, br, drive->drv_offset, 1);
		RedSeaInit(drive);
		ClusAlloc(drive, 0, 1, FALSE); //Alloc #1

		root_dir_blks = MaxI64(1, drive->bd->init_root_dir_blks);
		br->root_clus = ClusAlloc(drive, 0, root_dir_blks, FALSE);
		BlkWrite(drive, br, drive->drv_offset, 1);
		root_dir = CAlloc(BLK_SIZE * root_dir_blks);

		d_native = root_dir - offset(CDirEntry.start);

		d_native->attr		= RS_ATTR_DIR | RS_ATTR_CONTIGUOUS;
		*d_native->name		= '.';
		d_native->clus		= br->root_clus;
		d_native->size		= BLK_SIZE * root_dir_blks;
		d_native->datetime	= Now;

		d_native(U8 *) += CDIR_SIZE;

		*d_native->name		= '.';
		d_native->name[1]	= '.';
		d_native->attr		= RS_ATTR_DIR | RS_ATTR_CONTIGUOUS;
		d_native->clus		= br->root_clus;
		d_native->datetime	= Now;

		BlkWrite(drive, root_dir, br->root_clus, root_dir_blks);
		RedSeaInit(drive);
		DriveUnlock(drive);
	}
	catch
		DriveUnlock(drive);
	Free(br);
	Free(root_dir);
}

Bool RedSeaFileFind(CDrive *drive, I64 cur_dir_clus, U8 *name, CDirEntry *_res, I64 fuf_flags=0)
{//$LK,"FUF_JUST_DIRS",A="MN:FUF_JUST_DIRS"$, $LK,"FUF_JUST_FILES",A="MN:FUF_JUST_FILES"$
	CDirEntry	*buf, *buf2, *ptr;
	U8			 dname[CDIR_FILENAME_LEN];
	I64			 ch;
	Bool		 res = FALSE, unlock;

	if (fuf_flags & ~FUG_FILE_FIND)
		throw('FUF');
	MemSet(_res, 0, sizeof(CDirEntry));
	DriveCheck(drive);
	if (drive->fs_type != FSt_REDSEA)
		PrintErr("Not RedSea Drive\n");
	else if (!CFileNameTo(dname, name))
		PrintErr("Invalid FileName: \"%s\".\n", name);
	else
		try
		{
			unlock = DriveLock(drive);
			buf2 = MAlloc(BLK_SIZE);
			BlkRead(drive, buf2, cur_dir_clus, 1);

			ptr = buf2(U8 *) - offset(CDirEntry.start);
			buf = MAlloc(ptr->size);
			BlkRead(drive, buf, cur_dir_clus, ptr->size >> BLK_SIZE_BITS);
			Free(buf2);

			ptr = buf(U8 *) - offset(CDirEntry.start);
			*ptr->name = '.';
			ptr->name[1] = 0;
			while (TRUE)
			{
				if (!(ch = *ptr->name))
					break;
				else if (!(ptr->attr & RS_ATTR_DELETED) &&
						 !(fuf_flags & FUF_JUST_DIRS    && !(ptr->attr & RS_ATTR_DIR)) &&
						 !(fuf_flags & FUF_JUST_FILES   &&   ptr->attr & RS_ATTR_DIR)  &&
						 !StrCompare(dname, ptr->name))
				{
					MemCopy(&_res->attr, &ptr->attr, CDIR_SIZE);
					res = TRUE;
					goto rsff_done;
				}
				ptr(U8 *) += CDIR_SIZE;
			}
rsff_done:
			Free(buf);
			if (unlock)
				DriveUnlock(drive);
		}
		catch
			if (unlock)
				DriveUnlock(drive);

	return res;
}

U8 *RedSeaFileRead(CDrive *drive, U8 *cur_dir, U8 *filename, I64 *_size, I64 *_attr)
{
	U8			*buf = NULL;
	CDirEntry	 de;
	I64			 c, blk_count, cur_dir_clus;

	DriveCheck(drive);
	*_size = 0;
	*_attr = 0;
	if (drive->fs_type != FSt_REDSEA)
		PrintErr("Not RedSea Drive\n");
	else
		try
		{
			DriveLock(drive);
			cur_dir_clus = Name2DirClus(drive, cur_dir);
			if (RedSeaFileFind(drive, cur_dir_clus, filename, &de, FUF_JUST_FILES))
			{
				blk_count = (de.size + BLK_SIZE - 1) >> BLK_SIZE_BITS;
				buf = MAlloc(blk_count << BLK_SIZE_BITS + 1);
				c = de.clus;
				c = BlkRead(drive, buf, c, blk_count);
				buf[de.size] = 0; //Terminate
				*_size = de.size;
				*_attr = FileAttr(de.name, de.attr);
			}
			DriveUnlock(drive);
		}
		catch
			DriveUnlock(drive);

	return buf;
}

Bool RedSeaCd(U8 *name, I64 cur_dir_clus)
{
	CDirEntry de;

	if (Fs->cur_dv->fs_type != FSt_REDSEA)
		PrintErr("Not RedSea Drive\n");
	else if (RedSeaFileFind(Fs->cur_dv, cur_dir_clus, name, &de, FUF_JUST_DIRS))
		return TRUE;
	else
		PrintErr("File not found: \"%s\".\n", name);

	return FALSE;
}

U0 RedSeaFreeClus(CDrive *drive, I64 c, I64 count)
{
	CFreeList	*tmpf;
	Bool		 found = FALSE, unlock, unlock_break;

	DriveCheck(drive);
	if (!c)
		return;
	if (drive->fs_type != FSt_REDSEA)
		PrintErr("Not RedSea Drive\n");
	else
		try
		{
			unlock_break = BreakLock;
			unlock = DriveLock(drive);
			if (!drive->next_free)
				RedSeaFreeListBuild(drive);
			tmpf = drive->next_free;
			while (!found && tmpf != &drive->next_free)
			{
				if (tmpf->start + tmpf->size == c)
				{
					tmpf->size += count;
					found = TRUE;
				}
				else if (c + count == tmpf->start)
				{
					tmpf->size += count;
					tmpf->start = c;
					found = TRUE;
				}
				tmpf = tmpf->next;
			}
			if (!found)
			{
				tmpf = SysMAlloc(sizeof(CFreeList));
				tmpf->size  = count;
				tmpf->start = c;
				QueueInsert(tmpf, drive->last_free);
			}
			while (count-- > 0)
			{
				DriveFATBlkSet(drive, c);
				LBtr(drive->cur_fat_blk, (c - drive->data_area) & (BLK_SIZE << 3 - 1));
				LBts(&drive->fat_blk_dirty, 0);
				c++;
			}
			DriveFATBlkClean(drive);

			if (unlock)
				DriveUnlock(drive);
			if (unlock_break)
				BreakUnlock;
		}
		catch
		{
			if (unlock)
				DriveUnlock(drive);
			if (unlock_break)
				BreakUnlock;
		}
}

I64 RedSeaAllocClus(CDrive *drive, I64 count)
{
	CFreeList	*tmpf, *best_free = NULL;
	I64			 i, first, best_size = I64_MAX;
	Bool		 unlock, unlock_break;

	if (count <= 0)
		throw('Drive');
	try
	{
		unlock_break = BreakLock;
		unlock = DriveLock(drive);
		if (!drive->next_free)
			RedSeaFreeListBuild(drive);
		tmpf = drive->next_free;
		while (tmpf != &drive->next_free)
		{
			if (tmpf->size >= count && tmpf->size < best_size)
			{
				best_free = tmpf;
				best_size = tmpf->size;
				if (tmpf->size == count)
					break;
			}
			tmpf = tmpf->next;
		}
		if (!best_free)
			throw('Drive');
		first = best_free->start;
		for (i = 0; i < count; i++)
		{
			DriveFATBlkSet(drive, first + i);
			LBts(drive->cur_fat_blk, (first + i - drive->data_area) & (BLK_SIZE << 3 - 1));
			LBts(&drive->fat_blk_dirty, 0);
		}
		DriveFATBlkClean(drive);
		if (best_free->size -= count)
			best_free->start += count;
		else
		{
			QueueRemove(best_free);
			Free(best_free);
		}
		if (unlock)
			DriveUnlock(drive);
		if (unlock_break)
			BreakUnlock;
	}
	catch
	{
		if (unlock)
			DriveUnlock(drive);
		if (unlock_break)
			BreakUnlock;
	}

	return first;
}

Bool RedSeaDirNew(CDrive *drive, U8 *cur_dir, CDirEntry *tmpde, Bool free_old_chain)
{
	CDirEntry	*buf, *buf2, *ptr, de2;
	CRedSeaBoot	*br;
	I64			 c, ch, i = 1, j = 0, n = BLK_SIZE / CDIR_SIZE, dir_size, cur_dir_clus;
	Bool		 written = FALSE, unlock, unlock_break;
	U8			*tmp, *parent_dir;

	try
	{
		unlock_break = BreakLock;
		tmpde->attr |= RS_ATTR_CONTIGUOUS;
		unlock = DriveLock(drive);
		cur_dir_clus = Name2DirClus(drive, cur_dir);
		buf2 = MAlloc(BLK_SIZE);
		BlkRead(drive, buf2, cur_dir_clus, 1);

		ptr = buf2(U8 *) - offset(CDirEntry.start);
		buf = MAlloc(ptr->size);
		BlkRead(drive, buf, cur_dir_clus, ptr->size >> BLK_SIZE_BITS);

		dir_size = ptr->size;
		ptr = buf(U8 *) - offset(CDirEntry.start) + CDIR_SIZE;
		Free(buf2);
		while (TRUE)
		{
			if (!(ch = *ptr->name))
			{
				if (!written)
					MemCopy(&ptr->start, &tmpde->start, CDIR_SIZE);
				if ((i + 1) * CDIR_SIZE + j << BLK_SIZE_BITS < dir_size)
					BlkWrite(drive, buf(U8 *) + j << BLK_SIZE_BITS, cur_dir_clus + j, 1);
				else
				{
					buf2 = CAlloc(dir_size + BLK_SIZE);
					MemCopy(buf2, buf, dir_size);
					RedSeaFreeClus(drive, cur_dir_clus, dir_size >> BLK_SIZE_BITS);
					dir_size += BLK_SIZE;
					c = ClusAlloc(drive, 0, dir_size >> BLK_SIZE_BITS, TRUE);
					Free(buf);
					buf = buf2;
					ptr = buf(U8 *) - offset(CDirEntry.start);
					ptr->size = dir_size;
					ptr->clus = c;
					BlkWrite(drive, buf, c, dir_size >> BLK_SIZE_BITS);
					if (cur_dir_clus == drive->root_clus)
					{
						br = CAlloc(BLK_SIZE);
						BlkRead(drive, br, drive->drv_offset, 1);
						br->root_clus = c;
						BlkWrite(drive, br, drive->drv_offset, 1);
						Free(br);
						drive->root_clus = c;
					}
					else
					{
						tmp = StrNew(cur_dir);
						parent_dir = StrNew(cur_dir);
						StrLastRemove(parent_dir, "/", tmp);
						if (!*parent_dir)
						{
							Free(parent_dir);
							parent_dir = StrNew("/");
						}
						if (RedSeaFileFind(drive, Name2DirClus(drive, parent_dir), tmp, &de2, FUF_JUST_DIRS))
						{
							de2.clus = c;
							de2.size = dir_size;
							RedSeaDirNew(drive, parent_dir, &de2, FALSE);
						}
						else
							throw('Drive');
						Free(tmp);
						Free(parent_dir);
					}
				}
				break;
			}
			else if (ptr->attr & RS_ATTR_DELETED)
			{
				if (!written)
				{
					MemCopy(&ptr->start, &tmpde->start, CDIR_SIZE);
					BlkWrite(drive, buf(U8 *) + j << BLK_SIZE_BITS, cur_dir_clus + j, 1);
					written = TRUE;
				}
			}
			else
			{
				if (!StrCompare(tmpde->name, ptr->name))
				{
					if (free_old_chain)
						RedSeaFreeClus(drive, ptr->clus, (ptr->size + BLK_SIZE - 1) >> BLK_SIZE_BITS);
					if (!written)
						MemCopy(&ptr->start, &tmpde->start, CDIR_SIZE);
					else
						ptr->attr |= RS_ATTR_DELETED;
					BlkWrite(drive, buf(U8 *) + j << BLK_SIZE_BITS, cur_dir_clus + j, 1);
					break;
				}
			}
			ptr(U8 *) += CDIR_SIZE;
			if (++i >= n)
			{
				j++;
				i = 0;
			}
		}
		Free(buf);
		if (unlock)
			DriveUnlock(drive);
		if (unlock_break)
			BreakUnlock;
	}
	catch
	{
		if (unlock)
			DriveUnlock(drive);
		if (unlock_break)
			BreakUnlock;
	}

	return FALSE;
}

I64 RedSeaFilesDel(CDrive *drive, U8 *cur_dir, U8 *files_find_mask, I64 fuf_flags, Bool del_dir, Bool print_message)
{
	CDirEntry	*buf, *buf2, *ptr;
	I64			 i = 0, res = 0, ch, j = 0, n = BLK_SIZE / CDIR_SIZE, cur_dir_clus;
	Bool		 unlock_break;

	try
	{
		unlock_break = BreakLock;
		DriveLock(drive);
		cur_dir_clus = Name2DirClus(drive, cur_dir);
		buf2 = MAlloc(BLK_SIZE);
		BlkRead(drive, buf2, cur_dir_clus, 1);

		ptr = buf2(U8 *) - offset(CDirEntry.start);
		buf = MAlloc(ptr->size);
		BlkRead(drive, buf, cur_dir_clus, ptr->size >> BLK_SIZE_BITS);
		Free(buf2);

		ptr = buf(U8 *) - offset(CDirEntry.start);
		*ptr->name   = '.';
		ptr->name[1] = 0;
		while (TRUE)
		{
			if (!(ch = *ptr->name))
				break;
			else if (!(ptr->attr & RS_ATTR_DELETED) && ch != '.' &&
					(del_dir || !(ptr->attr & RS_ATTR_DIR)) && FilesFindMatch(ptr->name, files_find_mask, fuf_flags))
			{
				if (!(ptr->attr & RS_ATTR_DIR))
					res++;
				if (print_message)
					"Del %s\n", ptr->name;
				ptr->attr |= RS_ATTR_DELETED;
				BlkWrite(drive, buf(U8 *) + j << BLK_SIZE_BITS, cur_dir_clus + j, 1);
				RedSeaFreeClus(drive, ptr->clus, (ptr->size + BLK_SIZE - 1) >> BLK_SIZE_BITS);
			}
			ptr(U8 *) += CDIR_SIZE;
			if (++i >= n)
			{
				j++;
				i = 0;
			}
		}
		Free(buf);
		DriveUnlock(drive);
		if (unlock_break)
			BreakUnlock;
	}
	catch
	{
		DriveUnlock(drive);
		if (unlock_break)
			BreakUnlock;
	}

	return res;
}

I64 RedSeaFileWrite(CDrive *drive, U8 *cur_dir, U8 *name, U8 *buf, I64 size, CDate cdt, I64 attr)
{
	CDirEntry	de;
	I64			c = 0, blk_count;

	MemSet(&de, 0, sizeof(CDirEntry));
	if (size < 0)
		size = 0;
	if (drive->fs_type != FSt_REDSEA)
		PrintErr("Not RedSea Drive\n");
	else if (!CFileNameTo(de.name, name))
		PrintErr("Invalid FileName: \"%s\".\n", name);
	else
	{
		RedSeaFilesDel(drive, cur_dir, de.name, 0, FALSE, FALSE);
		de.size = size;
		if (blk_count = (size + BLK_SIZE - 1) >> BLK_SIZE_BITS)
			c = ClusAlloc(drive, 0, blk_count, TRUE); //Always contiguous
		else
			c = INVALID_CLUS;
		de.clus		= c;
		de.attr		= attr|RS_ATTR_CONTIGUOUS;
		de.datetime	= cdt;
		if (blk_count)
			BlkWrite(drive, buf, c, blk_count);
		RedSeaDirNew(drive, cur_dir, &de, TRUE);
	}
	return c;
}

CDirEntry *RedSeaFilesFind(U8 *files_find_mask, I64 fuf_flags, CDirEntry *parent=NULL)
{
	CDrive		*drive = Fs->cur_dv;
	CDirEntry	*buf, *buf2, *ptr, *res = NULL, *tmpde;
	I64			 ch, cur_dir_clus;

	if (fuf_flags & ~FUG_FILES_FIND)
		throw('FUF');
	try
	{
		DriveLock(drive);
		cur_dir_clus = Name2DirClus(drive, Fs->cur_dir);
		buf2 = MAlloc(BLK_SIZE);
		BlkRead(drive, buf2, cur_dir_clus, 1);

		ptr = buf2(U8 *) - offset(CDirEntry.start);
		buf = MAlloc(ptr->size);
		BlkRead(drive, buf, cur_dir_clus, ptr->size >> BLK_SIZE_BITS);
		Free(buf2);

		ptr = buf(U8 *) - offset(CDirEntry.start);
		*ptr->name   = '.';
		ptr->name[1] = 0;
		ptr(U8 *) += CDIR_SIZE;
		ptr->clus = Name2ParentDirClus(drive, Fs->cur_dir);
		ptr(U8 *) -= CDIR_SIZE;
		while (TRUE)
		{
			if (!(ch = *ptr->name))
				break;
			else if (!(ptr->attr & RS_ATTR_DELETED))
			{
				tmpde = CAlloc(sizeof(CDirEntry));
				MemCopy(&tmpde->start, &ptr->start, CDIR_SIZE);
				tmpde->parent = parent;
				if (Bt(&fuf_flags, FUf_RECURSE) && tmpde->attr & RS_ATTR_DIR && *tmpde->name != '.')
				{
					tmpde->next = res;
					res = tmpde;
					tmpde->full_name = DirNameAbs(tmpde->name);
					DriveUnlock(drive);
					if (Cd(tmpde->name))
					{
						tmpde->sub = RedSeaFilesFind(files_find_mask, fuf_flags, tmpde);
						Cd("..");
					}
					DriveLock(drive);
				}
				else
				{
					tmpde->full_name = FileNameAbs(tmpde->name);
					if ((tmpde->attr & RS_ATTR_DIR || !Bt(&fuf_flags, FUf_JUST_DIRS)) &&
						!(Bt(&fuf_flags, FUf_RECURSE) && *tmpde->name == '.' && tmpde->attr & RS_ATTR_DIR) &&
						FilesFindMatch(tmpde->full_name, files_find_mask, fuf_flags))
					{
						tmpde->next = res;
						res = tmpde;
					}
					else
						DirEntryDel(tmpde);
				}
			}
			ptr(U8 *) += CDIR_SIZE;
		}
		Free(buf);
		DriveUnlock(drive);
	}
	catch
		DriveUnlock(drive);

	return res;
}

Bool RedSeaMkDir(CDrive *drive, U8 *cur_dir, U8 *name, I64 entry_count)
{//entry_count is for preallocating dir blocks.
	I64			 c, cur_dir_clus = Name2DirClus(drive, cur_dir), size = CeilU64((entry_count + 3) << 6, BLK_SIZE);
#assert CDIR_SIZE == 64
	U8			*buf = CAlloc(size);
	CDirEntry	*d_native = buf - offset(CDirEntry.start);
	Bool		 unlock_break;

	try
	{
		unlock_break = BreakLock;
		c = FileWrite(name, buf, size, 0, RS_ATTR_DIR);
		d_native->attr		= RS_ATTR_DIR | RS_ATTR_CONTIGUOUS;
		StrCopy(d_native->name, name);
		d_native->clus		= c;
		d_native->size		= size;
		d_native->datetime	= Now;
		d_native(U8 *) += CDIR_SIZE;

		d_native->attr		= RS_ATTR_DIR | RS_ATTR_CONTIGUOUS;
		*d_native->name		= '.';
		d_native->name[1]	= '.';
		d_native->name[2]	= 0;
		d_native->clus		= cur_dir_clus;
		d_native->size		= 0;
		d_native->datetime	= Now;
		BlkWrite(drive, buf, c, 1);
		Free(buf);
		if (unlock_break)
			BreakUnlock;
	}
	catch
		if (unlock_break)
			BreakUnlock;

	return TRUE;
}
