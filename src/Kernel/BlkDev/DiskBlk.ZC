#define ZERO_BUF_SIZE 	2048
U0 BlkWriteZero(CDrive *drive, I64 blk, I64 count)
{//Fill block count with zeros in Drive.
	I64  n;
	U8	*z = CAlloc(ZERO_BUF_SIZE << BLK_SIZE_BITS);
	Bool show_progress;

	if (count > ZERO_BUF_SIZE && drive->bd->type != BDT_RAM)
	{
		progress1 = 0;
		progress1_max = count;
		StrCopy(progress1_desc, "Zeroing");
		show_progress = TRUE;
	}
	else
		show_progress = FALSE;
	while (count > 0)
	{
		n = count;
		if (n > ZERO_BUF_SIZE)
			n = ZERO_BUF_SIZE;
		BlkWrite(drive, z, blk, n);
		blk += n;
		count -= n;
		if (show_progress)
			progress1 += n;
		Yield;	//Prevent locking
	}
	Free(z);
	if (show_progress)
	{
		*progress1_desc = 0;
		progress1 = progress1_max = 0;
	}
}

Bool BlkRead(CDrive *drive, U8 *buf, I64 blk, I64 count)
{//Read block count from Drive to buf.
	Bool	 res = TRUE, unlock;
	CBlkDev	*bd  = drive->bd;

	if (count <= 0)
		return TRUE;
	DriveCheck(drive);
	try
	{
		unlock = DriveLock(drive);
		BlkDevInit(bd);
		if (drive->drv_offset && blk < drive->drv_offset || blk + count > drive->drv_offset + drive->size)
			throw('Drive');
		if (bd->flags & BDF_READ_CACHE)
			RCache(drive, &buf, &blk, &count);
		if (count > 0)
		{
			switch (bd->type)
			{
				case BDT_RAM:
					MemCopy(buf, bd->RAM_disk + blk << BLK_SIZE_BITS, count << BLK_SIZE_BITS);
					break;

				case BDT_ISO_FILE_READ:
				case BDT_ISO_FILE_WRITE:
					FBlkRead(bd->file_disk, buf, blk, count);
					break;

				case BDT_ATA:
					res = AHCIAtaRBlks(drive, buf, blk, count);
					break;
				case BDT_ATAPI:
					res = AHCIAtapiRBlks(drive, buf, blk, count);
					break;
			}
			bd->last_time = tS;
			if (bd->flags & BDF_READ_CACHE)
				DiskCacheAdd(drive, buf, blk, count);
		}
		if (unlock)
			DriveUnlock(drive);
	}
	catch
		if (unlock)
			DriveUnlock(drive);

	return res;
}

Bool BlkWrite(CDrive *drive, U8 *buf, I64 blk, I64 count)
{//Write block count from buf to Drive.
	Bool	 res = TRUE, unlock;
	CBlkDev	*bd  = drive->bd;

	if (count <= 0)
		return TRUE;
	DriveCheck(drive);
	try
	{
		unlock = DriveLock(drive);
		BlkDevInit(bd);
		if (bd->flags & BDF_READ_ONLY && !(bd->flags & BDF_READ_ONLY_OVERRIDE))
			throw('BlkDev');
		if (drive->drv_offset && blk<drive->drv_offset || blk + count>drive->drv_offset + drive->size)
			throw('Drive');
		if (count > 0)
		{
			switch (bd->type)
			{
				case BDT_RAM:
					MemCopy(bd->RAM_disk + blk << BLK_SIZE_BITS, buf, count << BLK_SIZE_BITS);
					break;

				case BDT_ISO_FILE_READ:
				case BDT_ISO_FILE_WRITE:
					FBlkWrite(bd->file_disk, buf, blk, count);
					break;

				case BDT_ATA:
				case BDT_ATAPI:
					res = AHCIAtaWBlks(drive, buf, blk, count);
					break;
			}
			bd->last_time = tS;
			if (bd->flags & BDF_READ_CACHE)
				DiskCacheAdd(drive, buf, blk, count);
		}
		if (unlock)
			DriveUnlock(drive);
	}
	catch
		if (unlock)
			DriveUnlock(drive);

	return res;
}
