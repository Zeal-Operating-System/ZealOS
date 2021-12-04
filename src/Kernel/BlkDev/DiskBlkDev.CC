Bool BlkDevLock(CBlkDev *bd)
{//Make this task have exclusive access to BlkDev.
	BlkDevCheck(bd);

	while (bd->lock_fwding)
		bd = bd->lock_fwding; //If two blkdevs on same controller, use just one lock

	if (!Bt(&bd->locked_flags, BDlf_LOCKED) || bd->owning_task != Fs)
	{
		while (LBts(&bd->locked_flags, BDlf_LOCKED))
			Yield;

		bd->owning_task = Fs;
		return TRUE;
	}
	else
		return FALSE;
}

Bool BlkDevUnlock(CBlkDev *bd, Bool reset=FALSE)
{//Release exclusive lock on access to BlkDev.
	BlkDevCheck(bd);

	while (bd->lock_fwding)
		bd = bd->lock_fwding; //If two blkdevs on same controller, use just one lock

	if (Bt(&bd->locked_flags, BDlf_LOCKED) && bd->owning_task == Fs)
	{
		if (reset)
			bd->flags &= ~(BDF_INITIALIZED | BDF_INIT_IN_PROGRESS);
		bd->owning_task = NULL;
		LBtr(&bd->locked_flags, BDlf_LOCKED);
		Yield; //Prevent deadlock
		return TRUE;
	}
	else
		return FALSE;
}

Bool BlkDevInit(CBlkDev *bd)
{
	CDirEntry	 de;
	U8			 buf[STR_LEN];
	CDrive		*drive = Letter2Drive(bd->first_drive_let);
	Bool		 res   = FALSE;

	if (!LBts(&bd->flags, BDf_INITIALIZED))
	{
		bd->flags |= BDF_INIT_IN_PROGRESS;
		switch (bd->type)
		{
			case BDT_RAM:
				if (!bd->RAM_disk)
				{
					bd->RAM_disk = SysMAlloc((bd->max_blk + 1) << BLK_SIZE_BITS);
					bd->max_blk = MSize(bd->RAM_disk) >> BLK_SIZE_BITS - 1;
				}
				drive->fs_type = FSt_REDSEA;
				drive->size = bd->max_blk + 1 - bd->drv_offset;
				if (RedSeaValidate(bd->first_drive_let))
					RedSeaInit(drive);
				else
					RedSeaFormat(bd->first_drive_let);
				res = TRUE;
				break;

			case BDT_ISO_FILE_READ:
				if (FileFind(bd->file_disk_name, &de, FUF_JUST_FILES))
				{
					bd->max_blk = de.size >> BLK_SIZE_BITS - 1;
					try
						bd->file_disk = FOpen(bd->file_disk_name, "rc", bd->max_blk + 1);
					catch
					{
						if (Fs->except_ch == 'File')
							PrintErr("Not Contiguous.  Move file to filename.ISO.C.\n");
						Fs->catch_except = TRUE;
					}
					if (bd->file_disk)
					{
						drive->fs_type = FSt_REDSEA;
						drive->size = bd->max_blk + 1 - bd->drv_offset;
						if (RedSeaValidate(bd->first_drive_let))
						{
							RedSeaInit(drive);
							res = TRUE;
						}
						else
							PrintErr("Not RedSea\n");
					}
				}
				break;

			case BDT_ISO_FILE_WRITE:
				if (!bd->file_disk_name)
				{
					StrPrint(buf, "%C:/Drive%C.ISO.C", blkdev.boot_drive_let, bd->first_drive_let);
					bd->file_disk_name = SysStrNew(buf);
				}
				if (bd->max_blk < 7)
					bd->max_blk = 7;
				bd->file_disk = FOpen(bd->file_disk_name, "wc", bd->max_blk + 1);
				drive->fs_type = FSt_REDSEA;
				drive->size = bd->max_blk + 1 - bd->drv_offset;
				RedSeaFormat(bd->first_drive_let);
				CallExtStr("RedSeaISO9660", bd->file_disk_name, bd->first_drive_let);
				res = TRUE;
				break;

			case BDT_ATA:
				bd->max_reads = 128;
				bd->max_writes = 1;
				res = AHCIAtaInit(bd);
				break;

			case BDT_ATAPI:
//0xFFFF*4 is too big for Terry's taste
				bd->max_reads = 0x800 * 4;
//max of maybe a quarter of disk cache
				if (bd->max_reads > blkdev.cache_size / BLK_SIZE / 4)
					bd->max_reads = blkdev.cache_size / BLK_SIZE / 4 & ~3;
				if (bd->max_reads < 128)
					bd->max_reads = 128;
				bd->max_writes = 0xFFFF * 4;
				if (res = AHCIAtaInit(bd))
					drive->size = bd->max_blk + 1;
				break;
		}
		if (res && bd->flags & BDF_READ_CACHE)
			DiskCacheInvalidate(drive);
		bd->flags &= ~BDF_INIT_IN_PROGRESS;
	}
	else
		res = TRUE;

	return res;
}

U0 BlkDevsRelease()
{//When task dies, release all owned BlkDevs.
	I64		 i;
	CBlkDev	*bd;

	for (i = 0; i < BLKDEVS_NUM; i++)
	{
		bd = &blkdev.blkdevs[i];
		if (bd->owning_task == Fs && bd->bd_signature == BD_SIGNATURE_VAL)
			BlkDevUnlock(bd, TRUE);
	}
}

CBlkDev *BlkDevNextFreeSlot(U8 first_drive_let, I64 type)
{//Locate free slot for new BlkDev, like during $LK,"Mount",A="MN:Mount"$().
	I64		 i = 0;
	CBlkDev	*res;

	if (Letter2BlkDevType(first_drive_let) != type)
		throw('BlkDev');
	do
	{
		res = &blkdev.blkdevs[i];
		if (res->bd_signature != BD_SIGNATURE_VAL)
		{
			MemSet(res, 0, sizeof(CBlkDev));
			res->first_drive_let = first_drive_let;
			res->type = type;
			res->flags = BDF_READ_CACHE;
			res->blk_size = BLK_SIZE;
			res->max_blk = 0xEFFFFFFF;
			switch (type)
			{
				case BDT_RAM:
					res->flags &= ~BDF_READ_CACHE;
					break;

				case BDT_ISO_FILE_READ:
					res->flags |= BDF_READ_ONLY;
					break;

				case BDT_ATAPI:
					res->flags |= BDF_REMOVABLE|BDF_READ_ONLY;
					res->blk_size = DVD_BLK_SIZE;
					break;
			}
			return res;
		}
	}
	while (++i < BLKDEVS_NUM);

	throw('BlkDev');
	return NULL; //never gets here
}

U0 BlkDevDel(CBlkDev *bd)
{//Delete BlkDev
	DriveBlkDevDel(bd);
	FClose(bd->file_disk);
	Free(bd->file_disk_name);
	Free(bd->dev_id_record);
	MemSet(bd, 0, sizeof(CBlkDev));
}

CBlkDev *BlkDevCheck(CBlkDev *bd, Bool except=TRUE)
{//Check for valid BlkDev. Throw exception.
	if (!bd || bd->bd_signature != BD_SIGNATURE_VAL || !(BDT_NULL<bd->type < BDT_TYPES_NUM))
	{
		if (except)
			throw('BlkDev');
		else
			return NULL;
	}
	else
		return bd;
}

CBlkDev *Letter2BlkDev(U8 drv_let=0, Bool except=TRUE)
{//Drive letter to BlkDev pointer.
	CDrive *drive;

	if (drive = Letter2Drive(drv_let, except))
		return BlkDevCheck(drive->bd, except);
	else
		return NULL;
}

U0 BlkDevRep()
{ // Block Device Report.
// blkdev.blkdevs[i].
	I64 i;
	CBlkDev *b = blkdev.blkdevs;

	for (i = 0; i < BLKDEVS_NUM; i++)
	{
		if (b[i].bd_signature == BD_SIGNATURE_VAL)
		{
			"\nBlock Device #%d:\n", i;
			"\tBlock Device Type:\t%Z\n", b[i].type, "ST_BLKDEV_TYPES";
			"\tFirst Drive Letter:\t%C\n", b[i].first_drive_let;
			if (b[i].ahci_port)
			{
				"\tAHCI Port number:\t%d\n", b[i].port_num;
				"\tAHCI Port address:\t0x%X\n", b[i].ahci_port;
			}
			if (b[i].RAM_disk)
				"\tRAM disk address:\t0x%X\n", b[i].RAM_disk;
			if (b[i].file_disk_name)
				"\tFile:\t\t\t\t%s\n", b[i].file_disk_name;
			"\tBlock Size:\t\t\t%d\n", b[i].blk_size;
			"\tDrive Max Block:\t0x%X\n", b[i].max_blk;
		}
	}
	"\n";
}
