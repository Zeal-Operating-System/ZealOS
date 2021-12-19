U0 RawAccess(I64 drv_let=0)
{
	CDrive	*drive = Letter2Drive(drv_let);
	CBlkDev *bd = Letter2BlkDev(drv_let);
	I64		 blk, old_offset, old_size;
	U8		*buf = MAlloc(BLK_SIZE);

	DriveRep;
	PressAKey;

	ClassRep(drive);
	PressAKey;

	ClassRep(bd);
	PressAKey;

	//Temporarily change partition range to full device.
	//Normally, you are limited to just your partition.
	//This is obviously $BK,1$dangerous$BK,0$!
	old_offset	=drive->drv_offset;
	old_size	=drive->size;
	drive->drv_offset = 0;
	drive->size		  = bd->max_blk + 1;

	try
	{
		blk = I64Get("Block to Read: ", old_offset, 0, bd->max_blk);
		BlkRead(drive, buf, blk, 1);
		Dump(buf, BLK_SIZE);
	}
	catch
		PutExcept;

	drive->drv_offset = old_offset;
	drive->size		  = old_size;

	Free(buf);
}

RawAccess;

//See $LK,"BlkRead",A="MN:BlkRead"$(), $LK,"BlkWrite",A="MN:BlkWrite"$(), $LK,"DriveLock",A="MN:DriveLock"$(), $LK,"DriveUnlock",A="MN:DriveUnlock"$()
//$LK,"BlkDump",A="MN:BlkDump"$(), $LK,"ClusDump",A="MN:ClusDump"$(), $LK,"BlkDevLock",A="MN:BlkDevLock"$() and $LK,"BlkDevUnlock",A="MN:BlkDevUnlock"$().
