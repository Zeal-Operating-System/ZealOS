Bool ISOInit(CDrive *drive, I64 blk)
{
	CBlkDev			*bd  = drive->bd;
	I64				 spc = bd->blk_size >> BLK_SIZE_BITS, i = blk / spc, drv_offset = 0;
	CISOPriDesc		*iso = MAlloc(bd->blk_size);
	CISODirEntry	*de;
	Bool			 unlock, res = FALSE;
	U8				 buf[8];

	try
	{
		unlock = DriveLock(drive);
		drive->fs_type = FSt_ISO9660;
		drive->spc = spc;
		drive->data_area = drive->root_clus = drive->drv_offset = bd->drv_offset = drive->size = 0;
		while (TRUE)
		{
			drive->size = MaxI64(drive->size, (i + 1) * spc);
			BlkRead(drive, iso, i * spc, spc);
			buf[0](U32) = iso->id[0](U32);
			buf[4](U16) = iso->id[4](U8);
			switch (ListMatch(buf, "CD001\0CDW02\0BEA01\0BOOT2\0NSR02\0NSR03\0TEA01\0", LMF_EXACT))
			{
				case 0:
					switch (iso->type)
					{
						case ISOT_BOOT_RECORD:
							drv_offset += (2 * DVD_BLK_SIZE + DVD_BLK_SIZE) / BLK_SIZE;
							break;

						case ISOT_SUPPLEMENTARY_DESC:
							de = &iso->root_dir_record;
							drive->size = iso->vol_space_size.little * bd->blk_size >> BLK_SIZE_BITS;
							if (!StrCompare(iso->publisher_id, "ZenithOS RedSea"))
							{
								drive->fs_type = FSt_REDSEA;
								bd->drv_offset = drive->drv_offset = 19 << 2 + drv_offset;
								bd->max_blk = drive->size - 1;
								drive->size -= bd->drv_offset;
								RedSeaInit(drive);
							}
							else
								drive->root_clus = de->loc.little;
							res = TRUE;
							goto di_done;

						case ISOT_TERMINATOR:
							throw('Drive');
					}
					break;

				default: //Its normal for ISO3346 to read NULL blk as terminator
					PrintErr("File System Not Supported\n");
					throw('Drive');
			}
			i++;
		}
di_done:
		Free(iso);
		if (unlock)
			DriveUnlock(drive);
	}
	catch
	{
		drive->fs_type = FSt_ISO9660;
		drive->spc = spc;
		drive->drv_offset = bd->drv_offset = drive->data_area = drive->root_clus = 0;
		Free(iso);
		if (unlock)
			DriveUnlock(drive);
	}

	return res;
}

U0 DVDImageRead(U8 dvd_drive_let, U8 *out_name)
{//Read entire CD/DVD image into ISO file.
	CDrive	*drive	= Letter2Drive(dvd_drive_let);
	CBlkDev	*bd		= drive->bd;
	U8		*buf	= MAlloc(COPY_BUF_BLKS << BLK_SIZE_BITS), *out_name2 = ExtDefault(out_name, "ISO");
	CFile	*f		= FOpen(out_name2, "w");
	I64		 n, spc = bd->blk_size >> BLK_SIZE_BITS, blk = 0, count, retry;

	BlkDevInit(bd);
	if (bd->type != BDT_ATAPI)
		throw('BlkDev');
	if (!out_name)
		out_name = blkdev.default_iso_filename;
	count = CeilU64(drive->size, spc);
	while (count > 0)
	{
		if (count > COPY_BUF_BLKS)
			n = COPY_BUF_BLKS;
		else
			n = count;
		if (n > bd->max_reads)
			n = bd->max_reads;

		retry = 4;
		while (--retry)
			if (ATAPIReadBlks2(bd, tS + 7.0 + 0.004 * n / spc, buf, blk / spc, n / spc, TRUE))
//n is 0x800 if max_reads.	Up to 8 additional seconds
				break;

		if (!retry)
			ATAPIReadBlks2(bd, 0, buf, blk / spc, n / spc, TRUE);

		FBlkWrite(f, buf, blk, n);
		count -= n;
		blk += n;
	}
	FClose(f);
	Free(buf);
	Free(out_name2);
}

class CDualBuf
{
	U8		*buf0, *buf1;
	I64		 in_buf, out_buf, count;
	U8		*filename;
	CBlkDev	*dvd_bd;
};

U0 DVDImageWriteTask(CDualBuf *d)
{
	U8		*buf;
	I64		 n, blk = 0, count = d->count;
	CFile	*f;

	if (FileAttr(d->filename) & RS_ATTR_CONTIGUOUS)
		f = FOpen(d->filename, "rc");
	else
		f = FOpen(d->filename, "r");
	while (count > 0)
	{
		if (count > COPY_BUF_BLKS)
			n = COPY_BUF_BLKS;
		else
			n = count;
		if (n > d->dvd_bd->max_writes)
			n = d->dvd_bd->max_writes;
		if (d->in_buf & 1)
			buf = d->buf1;
		else
			buf = d->buf0;
		while (d->in_buf>d->out_buf + 1)
			Yield;
		FBlkRead(f, buf, blk, n);
		d->in_buf++;
		count -= n;
		blk += n;
	}
	FClose(f);
}

U0 DVDImageWrite(U8 dvd_drive_let, U8 *in_name=NULL, I64 media_type=MT_DVD)
{//Write CD/DVD ISO file to disk.
	CDualBuf	*d = CAlloc(sizeof(CDualBuf));
	U8			*buf, *in_name2, *in_name3;
	I64			 i, n, spc, blk = 0, count;
	CDrive		*drive = Letter2Drive(dvd_drive_let);
	CBlkDev		*bd = drive->bd, *bd2;
	CTask		*task;
	CFile		*f;

	if (!in_name)
		in_name = blkdev.default_iso_filename;
	in_name3 = ExtDefault(in_name, "ISO");
	in_name2 = FileNameAbs(in_name3);
	f=FOpen(in_name2, "r");
	if (!f)
	{
		Free(d);
		return;
	}
	count = (FSize(f) + BLK_SIZE - 1) >> BLK_SIZE_BITS;
	FClose(f);
	if (bd->type != BDT_ATAPI)
		throw('BlkDev');
	bd2 = Letter2BlkDev(*in_name2);
	while (bd2->lock_fwding)
		bd2 = bd2->lock_fwding;  //If two blkdevs on same controller, use one lock
	if ((bd2->type == BDT_ATA || bd2->type == BDT_ATAPI) && bd2->base0 == bd->base0)
	{
		PrintErr("Can't burn CD/DVD on same ATA controller as file.\n\n");
		throw('BlkDev');
	}

	bd->flags |= BDF_READ_ONLY_OVERRIDE;
	BlkDevInit(bd);
	spc = bd->blk_size >> BLK_SIZE_BITS;
	if (drive->size < count)
		drive->size = count;

	d->filename = in_name2;
	d->dvd_bd = bd;
	d->buf0 = MAlloc(COPY_BUF_BLKS << BLK_SIZE_BITS);
	d->buf1 = MAlloc(COPY_BUF_BLKS << BLK_SIZE_BITS);
	d->count = count;

	task = Spawn(&DVDImageWriteTask, d, "Write CD/DVD");
	while (d->in_buf <= d->out_buf)
		Yield;

	BlkDevLock(bd);
	ATAPIWaitReady(bd, 0);

	progress1 = 0;
	progress1_max = count;
	StrCopy(progress1_desc, "Writing");
	while (count > 0)
	{
		if (count > COPY_BUF_BLKS)
			n = COPY_BUF_BLKS;
		else
			n = count;
		if (n > bd->max_writes)
			n = bd->max_writes;
		if (d->out_buf & 1)
			buf = d->buf1;
		else
			buf = d->buf0;
		while (d->in_buf <= d->out_buf)
			Yield;
		ATAPIWriteBlks(bd, buf, blk / spc, (n + spc - 1) / spc);
		d->out_buf++;
		count -= n;
		blk += n;
		progress1 += n;
	}
	ATAPISync(bd);

	progress1 = 0;
	progress1_max = 2;
	StrCopy(progress1_desc, "Closing");
	for (i = 0; i < 2; i++)
	{
		ATAPIClose(bd, 0x100, i); //Close tracks
		progress1++;
	}

	ATAPISync(bd);

	ATAPIClose(bd, 0x200); //close disk
	ATAPISync(bd);
	if (media_type == MT_DVD)
	{
		ATAPIClose(bd, 0x300);
		ATAPISync(bd);
	}

	*progress1_desc = 0;
	progress1 = progress1_max = 0;

	bd->flags &= ~BDF_READ_ONLY_OVERRIDE;
	BlkDevUnlock(bd);
	Free(d->buf0);
	Free(d->buf1);
	Free(in_name2);
	Free(in_name3);
	Free(d);
}
