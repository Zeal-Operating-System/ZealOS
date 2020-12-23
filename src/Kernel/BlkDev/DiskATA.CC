#define ATAPI_FORMAT_UNIT			EndianU16(0x04)
#define ATAPI_START_STOP_UNIT		EndianU16(0x1B)
#define ATAPI_READ_CAPACITY			EndianU16(0x25)
#define ATAPI_SEEK					EndianU16(0x2B)
#define ATAPI_SYNC_CACHE			EndianU16(0x35)
#define ATAPI_READ_TRACK_INFO		EndianU16(0x52)
#define ATAPI_CLOSE_TRACK_SESSION	EndianU16(0x5B)
#define ATAPI_READ					EndianU16(0xA8)
#define ATAPI_WRITE					EndianU16(0xAA)
#define ATAPI_SET_CD_SPEED			EndianU16(0xBB)

U0 ATABlkSel(CBlkDev *bd, I64 blk, I64 count)
{
	if (bd->type != BDT_ATAPI && bd->base1)
		OutU8(bd->base1 + ATAR1_CTRL, 0x8);
	if (bd->flags & BDF_EXT_SIZE)
	{ //48 Bit LBA?
		OutU8(bd->base0 + ATAR0_NSECT,	count.u8[1]);
		OutU8(bd->base0 + ATAR0_SECT,	blk.u8[3]);
		OutU8(bd->base0 + ATAR0_LCYL,	blk.u8[4]);
		OutU8(bd->base0 + ATAR0_HCYL,	blk.u8[5]);
		OutU8(bd->base0 + ATAR0_NSECT,	count);
		OutU8(bd->base0 + ATAR0_SECT,	blk);
		OutU8(bd->base0 + ATAR0_LCYL,	blk.u8[1]);
		OutU8(bd->base0 + ATAR0_HCYL,	blk.u8[2]);
		OutU8(bd->base0 + ATAR0_SEL,	0xEF | bd->unit << 4);
	}
	else
	{ //28 Bit LBA
		OutU8(bd->base0 + ATAR0_NSECT,	count);
		OutU8(bd->base0 + ATAR0_SECT,	blk);
		OutU8(bd->base0 + ATAR0_LCYL,	blk.u8[1]);
		OutU8(bd->base0 + ATAR0_HCYL,	blk.u8[2]);
		OutU8(bd->base0 + ATAR0_SEL,	0xE0 | bd->unit << 4 | blk.u8[3]);
	}
}

Bool ATAWaitNotBUSY(CBlkDev *bd, F64 timeout)
{
	I64 i;

	do
	{
		for (i = 0; i < 3; i++)
			if (!(InU8(bd->base0 + ATAR0_STAT) & ATAS_BSY))
				return TRUE;
		Yield;
	}
	while (!(0 < timeout < tS));

	return FALSE;
}

Bool ATAWaitDRQ(CBlkDev *bd, F64 timeout)
{
	I64 i;

	do
	{
		for (i = 0; i < 3; i++)
			if (InU8(bd->base0 + ATAR0_STAT) & ATAS_DRQ)
				return TRUE;
		Yield;
	}
	while (!(0 < timeout < tS));

	return FALSE;
}

Bool ATANop(CBlkDev *bd, F64 timeout)
{
	if (bd->flags & BDF_EXT_SIZE)
		OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
	else
		OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

	OutU8(bd->base0 + ATAR0_FEAT,	0);
	OutU8(bd->base0 + ATAR0_CMD,	ATA_NOP);
	return ATAWaitNotBUSY(bd, timeout);
}

U0 ATACmd(CBlkDev *bd, U8 cmd)
{
	OutU8(bd->base0 + ATAR0_FEAT,	0);
	OutU8(bd->base0 + ATAR0_CMD,	cmd);
	bd->last_time = tS;
	PortNop;
}

Bool ATAGetRes(CBlkDev *bd, F64 timeout, U8 *buf, I64 count, I64 _avail, Bool one_read)
{
	I64 avail, overflow;

	bd->flags &= ~BDF_LAST_WAS_WRITE;
	MemSet(buf, 0, count);
	while (count > 0)
	{
		if (!ATAWaitDRQ(bd, timeout))
			return FALSE;
		if (_avail)
			avail = _avail;
		else
			avail = InU8(bd->base0 + ATAR0_HCYL) << 8 + InU8(bd->base0 + ATAR0_LCYL);
		if (avail)
		{
			if (avail > count)
			{
				overflow = avail - count;
				avail = count;
			}
			else
				overflow = 0;

			if (avail & 2)
				RepInU16(buf, avail >> 1, bd->base0 + ATAR0_DATA);
			else
				RepInU32(buf, avail >> 2, bd->base0 + ATAR0_DATA);

			count -= avail;
			buf += avail;
			while (overflow > 0)
			{
				InU16(bd->base0 + ATAR0_DATA);
				overflow -= 2;
				if (0 < timeout < tS)
					return FALSE;
			}
			if (one_read)
				break;
		}
		else
			Yield;
	}
	return ATAWaitNotBUSY(bd, timeout);
}

Bool ATAPIWritePacketWord(CBlkDev *bd, F64 timeout, ...)
{
	I64 i;

	for (i = 0; i < argc; i++)
	{
		if (!ATAWaitDRQ(bd, timeout))
			return FALSE;

		OutU16(bd->base0 + ATAR0_DATA, EndianU16(argv[i]));
		bd->last_time = tS;
	}

	return TRUE;
}

Bool ATAPISetMaxSpeed(CBlkDev *bd)
{
	if (bd->flags & BDF_EXT_SIZE)
		OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
	else
		OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

	OutU8(bd->base0 + ATAR0_LCYL, 0);
	OutU8(bd->base0 + ATAR0_HCYL, 0);
	ATACmd(bd, ATA_PACKET);
	ATAPIWritePacketWord(bd, 0, ATAPI_SET_CD_SPEED, 0xFFFF, 0xFFFF, 0, 0, 0);

	return ATAWaitNotBUSY(bd, 0);
}

Bool ATAPISeek(CBlkDev *bd, I64 native_blk)
{
	if (bd->flags & BDF_EXT_SIZE)
		OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
	else
		OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

	OutU8(bd->base0 + ATAR0_LCYL, 0);
	OutU8(bd->base0 + ATAR0_HCYL, 0);
	ATACmd(bd, ATA_PACKET);
	ATAPIWritePacketWord(bd, 0, ATAPI_SEEK, native_blk >> 16, native_blk, 0, 0, 0);

	return ATAWaitNotBUSY(bd, 0);
}

Bool ATAPIStartStop(CBlkDev *bd, F64 timeout, Bool start)
{
	I64 i;

	if (start)
		i = 0x100;
	else
		i = 0;
	if (bd->flags & BDF_EXT_SIZE)
		OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
	else
		OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

	ATACmd(bd, ATA_PACKET);
//Start/Stop
	if (ATAPIWritePacketWord(bd, timeout, ATAPI_START_STOP_UNIT, 0, i, 0, 0, 0))
		return ATAWaitNotBUSY(bd, timeout);
	else
		return FALSE;
}

I64 ATAGetDevId(CBlkDev *bd, F64 timeout, Bool keep_id_record)
{
	I64  res		= BDT_NULL;
	U16 *id_record	= NULL;

	if (bd->type != BDT_ATAPI && bd->base1)
		OutU8(bd->base1 + ATAR1_CTRL, 0x8);
	if (bd->flags & BDF_EXT_SIZE)
		OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
	else
		OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

	ATACmd(bd, ATA_IDENTIFY);
	if (ATAWaitNotBUSY(bd, timeout))
	{
		if (InU8(bd->base0 + ATAR0_STAT) & ATAS_ERR)
			res = BDT_ATAPI;
		else
		{
			id_record = ZCAlloc(512);
			if (ATAGetRes(bd, timeout, id_record, 512, 512, FALSE))
				res = BDT_ATA;
			else
			{
				Free(id_record);
				id_record = NULL;
			}
		}
	}
	if (keep_id_record)
	{
		 Free(bd->dev_id_record);
		 bd->dev_id_record = id_record;
	}

	return res;
}

I64 ATAReadNativeMax(CBlkDev *bd, F64 timeout)
{//Returns zero on error
	I64  res  = 0;
	Bool okay = TRUE;

	if (bd->type == BDT_ATAPI)
	{
		if (bd->flags & BDF_EXT_SIZE)
			OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
		else
			OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

		ATACmd(bd, ATA_DEV_RST);
		if (!ATAWaitNotBUSY(bd, 0))
			okay = FALSE;
	}
	else
	{
		while (InU8(bd->base0 + ATAR0_STAT) & ATAS_BSY)
		{
			if (bd->flags & BDF_LAST_WAS_WRITE)
				OutU16(bd->base0 + ATAR0_DATA, 0);
			else
				InU16(bd->base0 + ATAR0_DATA);
			Yield;
			if (0 < timeout < tS)
				return FALSE;
		}
		if (ATAGetDevId(bd, timeout, TRUE) == BDT_NULL)
			okay = FALSE;
		else
			BEqual(&bd->flags, BDf_EXT_SIZE, Bt(&bd->dev_id_record[86], 10));
	}
	if (okay)
	{
		if (bd->flags & BDF_EXT_SIZE && bd->base1)
		{
			OutU8(bd->base1 + ATAR1_CTRL,	0x8);
			OutU8(bd->base0 + ATAR0_SEL,	0xEF | bd->unit << 4);

			ATACmd(bd, ATA_READ_NATIVE_MAX_EXT);
			if (ATAWaitNotBUSY(bd, timeout))
			{
				res.u8[0] = InU8(bd->base0 + ATAR0_SECT);
				res.u8[1] = InU8(bd->base0 + ATAR0_LCYL);
				res.u8[2] = InU8(bd->base0 + ATAR0_HCYL);

				OutU8(bd->base1+ATAR1_CTRL, 0x80);
				res.u8[3] = InU8(bd->base0 + ATAR0_SECT);
				res.u8[4] = InU8(bd->base0 + ATAR0_LCYL);
				res.u8[5] = InU8(bd->base0 + ATAR0_HCYL);

				if (res >> 24 == res & 0xFFFFFF)
				{//Kludge to make QEMU work
					bd->flags &= ~BDF_EXT_SIZE;
					res &= 0xFFFFFF;
				}
			}
		}
		else
		{
			if (bd->type != BDT_ATAPI && bd->base1)
				OutU8(bd->base1 + ATAR1_CTRL, 0x8);
			OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);
			ATACmd(bd, ATA_READ_NATIVE_MAX);
			if (ATAWaitNotBUSY(bd, timeout))
			{
				res.u8[0] = InU8(bd->base0 + ATAR0_SECT);
				res.u8[1] = InU8(bd->base0 + ATAR0_LCYL);
				res.u8[2] = InU8(bd->base0 + ATAR0_HCYL);
				res.u8[3] = InU8(bd->base0 + ATAR0_SEL) & 0xF;
			}
		}
	}
	return bd->max_blk = res;
}

I64 ATAPIReadCapacity(CBlkDev *bd, I64 *_blk_size=NULL)
{//Supposedly this can return a res +/- 75 sects.
//Error might just be for music.
	Bool unlock = BlkDevLock(bd);
	U32  buf[2];

	if (ATAWaitNotBUSY(bd, 0))
	{
		if (bd->flags & BDF_EXT_SIZE)
			OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
		else
			OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

		OutU8(bd->base0 + ATAR0_LCYL, 8);
		OutU8(bd->base0 + ATAR0_HCYL, 0);
		ATACmd(bd, ATA_PACKET);
		ATAPIWritePacketWord(bd, 0, ATAPI_READ_CAPACITY, 0, 0, 0, 0, 0);

		if (!ATAGetRes(bd, 0, buf, 8, 0, TRUE))
			buf[0] = buf[1] = 0;
	}
	else
		buf[0] = buf[1] = 0;

	if (unlock)
		BlkDevUnlock(bd);
	if (_blk_size)
		*_blk_size = EndianU32(buf[1]);

	return EndianU32(buf[0]);
}

CATAPITrack *ATAPIReadTrackInfo(CBlkDev *bd, I64 blk)
{
	CATAPITrack	*res	= CAlloc(sizeof(CATAPITrack));
	Bool		 unlock	= BlkDevLock(bd);

	if (ATAWaitNotBUSY(bd, 0))
	{
		if (bd->flags & BDF_EXT_SIZE)
			OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
		else
			OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

		OutU8(bd->base0 + ATAR0_LCYL, sizeof(CATAPITrack) & 0xFF);
		OutU8(bd->base0 + ATAR0_HCYL, sizeof(CATAPITrack) >> 8);

		ATACmd(bd, ATA_PACKET);
		ATAPIWritePacketWord(bd,
							 0,
							 ATAPI_READ_TRACK_INFO,
							 blk.u16[1],
							 blk.u16[0],
							 (sizeof(CATAPITrack) & 0xFF00) >> 8,
							 (sizeof(CATAPITrack) & 0x00FF) << 8,
							 0);

		if (!ATAGetRes(bd, 0, res, sizeof(CATAPITrack), 0, TRUE))
		{
			Free(res);
			res = NULL;
		}
	}
	else
	{
		Free(res);
		res = NULL;
	}
	if (unlock)
		BlkDevUnlock(bd);
	return res;
}

Bool ATAInit(CBlkDev *bd)
{
	Bool unlock = BlkDevLock(bd), okay = FALSE;

	if (bd->type == BDT_ATAPI)
		bd->flags &= ~BDF_EXT_SIZE;
	else
		bd->flags |= BDF_EXT_SIZE;

	if (ATAReadNativeMax(bd, tS + 0.1))
	{
		ATABlkSel(bd, bd->max_blk, 0);
		if (bd->flags & BDF_EXT_SIZE)
			ATACmd(bd, ATA_SET_MAX_EXT);
		else
			ATACmd(bd, ATA_SET_MAX);

		if (ATAWaitNotBUSY(bd, 0))
		{
			okay = TRUE;
			if (bd->type == BDT_ATAPI)
			{
				if (ATAPIStartStop(bd, 0, TRUE))
				{
					if (!ATAPISetMaxSpeed(bd))
						okay = FALSE;
				}
				else
					okay = FALSE;
			}
		}
	}
	if (unlock)
		BlkDevUnlock(bd);

	return okay;
}

Bool ATAPIWaitReady(CBlkDev *bd, F64 timeout)
{
	do
	{
		if (!ATAWaitNotBUSY(bd, timeout) || !ATANop(bd, timeout) || !ATAPIStartStop(bd, timeout, TRUE))
			return FALSE;
		if (InU8(bd->base0 + ATAR0_STAT) & ATAS_DRDY && !InU8(bd->base0 + ATAR0_FEAT));
			return TRUE;

		ATAInit(bd);
		Yield;
	}
	while (!(0 < timeout < tS));

	return FALSE;
}

U0 ATAReadBlks(CBlkDev *bd, U8 *buf, I64 blk, I64 count)
{
	I64  retries = 3;
	Bool unlock  = BlkDevLock(bd);

	retry:
	ATABlkSel(bd, blk, count);
	if (bd->flags & BDF_EXT_SIZE)
		ATACmd(bd, ATA_READ_MULTI_EXT);
	else
		ATACmd(bd, ATA_READ_MULTI);

	if (!ATAGetRes(bd, tS + 1.0, buf, count * bd->blk_size, BLK_SIZE, FALSE))
	{
		if (retries--)
		{
			ATAWaitNotBUSY(bd, 0);
			goto retry;
		}
		else
			throw('BlkDev');
	}

	blkdev.read_count += (count * bd->blk_size) >> BLK_SIZE_BITS;

	if (unlock)
		BlkDevUnlock(bd);
}

I64 ATAProbe(I64 base0, I64 base1, I64 unit)
{
	CBlkDev bd;

	MemSet(&bd, 0, sizeof(CBlkDev));
	bd.type = BDT_ATAPI;
	bd.base0 = base0;
	bd.base1 = base1;
	bd.unit = unit;
	bd.blk_size = DVD_BLK_SIZE;

	return ATAGetDevId(&bd, tS + 0.1, FALSE);
}

Bool ATAPIReadBlks2(CBlkDev *bd, F64 timeout, U8 *buf, I64 native_blk, I64 count, Bool lock)
{
	Bool res = FALSE, unlock;

	if (count <= 0)
		return FALSE;
	if (lock)
		unlock = BlkDevLock(bd);
	if (ATAPIWaitReady(bd, timeout))
	{
		if (bd->flags & BDF_EXT_SIZE)
			OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
		else
			OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

		OutU8(bd->base0 + ATAR0_LCYL, bd->blk_size);
		OutU8(bd->base0 + ATAR0_HCYL, bd->blk_size.u8[1]);
		ATACmd(bd, ATA_PACKET);

		if (ATAPIWritePacketWord(bd, timeout, ATAPI_READ, native_blk.u16[1], native_blk, count.u16[1], count, 0) &&
			ATAGetRes(bd, timeout, buf, count * bd->blk_size, 0, FALSE))
		{
			blkdev.read_count += (count * bd->blk_size) >> BLK_SIZE_BITS;
			res = TRUE;
		}
	}
//	ATAPIStartStop(bd, 0, FALSE);
	if (lock && unlock)
		BlkDevUnlock(bd);

	return res;
}

U0 ATAPIReadBlks(CBlkDev *bd, U8 *buf, I64 blk, I64 count)
{
	CDrive	*drive		= Letter2Drive(bd->first_drive_let);
	I64		 retry, spc = bd->blk_size >> BLK_SIZE_BITS, n, blk2, l2 = bd->max_reads << 1 + spc << 1;
	U8		*dvd_buf	= MAlloc(l2 << BLK_SIZE_BITS);

	if (count > 0)
	{
		if (blk <= bd->max_reads)
			blk2 = 0;
		else
			blk2 = FloorU64(blk-bd->max_reads, spc);

		if (blk2 + l2 > drive->size + drive->drv_offset)
			l2 = drive->size + drive->drv_offset - blk2;

		n = (l2 + spc - 1) / spc;

		retry = 4;
		while (--retry)
			if (ATAPIReadBlks2(bd, tS + 7.0 + 0.004 * n, dvd_buf, blk2 / spc, n, TRUE))
//n is 0x800 if max_reads.	Up to 8 additional seconds
				break;
		if (!retry)
			ATAPIReadBlks2(bd, 0, dvd_buf, blk2 / spc, n, TRUE);
		if (bd->flags & BDF_READ_CACHE)
			DiskCacheAdd(drive, dvd_buf, blk2, n * spc);

		MemCopy(buf, dvd_buf + (blk - blk2) << BLK_SIZE_BITS, count << BLK_SIZE_BITS);
	}
	Free(dvd_buf);
}

Bool ATARBlks(CDrive *drive, U8 *buf, I64 blk, I64 count)
{
	I64		 n;
	CBlkDev	*bd = drive->bd;

	while (count > 0)
	{
		n = count;
		if (n > bd->max_reads)
			n = bd->max_reads;

		if (bd->type == BDT_ATAPI)
			ATAPIReadBlks(bd, buf, blk, n);
		else
			ATAReadBlks(bd, buf, blk, n);

		buf += n << BLK_SIZE_BITS;
		blk += n;
		count -= n;
	}
	return TRUE;
}

U0 ATAWriteBlks(CBlkDev *bd, U8 *buf, I64 blk, I64 count)
{//For low level disk access.
//Use BlkWrite() instead.
	I64  i, U32s_avail, sects_avail, retries = 3;
	F64  timeout;
	Bool unlock = BlkDevLock(bd);

retry:
	ATABlkSel(bd, blk, count);
	if (bd->flags & BDF_EXT_SIZE)
		ATACmd(bd, ATA_WRITE_MULTI_EXT);
	else
		ATACmd(bd, ATA_WRITE_MULTI);

	bd->flags |= BDF_LAST_WAS_WRITE;
	while (count > 0)
	{
		timeout = tS + 1.0;
		while (TRUE)
		{
			i = InU8(bd->base0 + ATAR0_STAT);
			if (!(i & ATAS_DRDY) || !(i & ATAS_DRQ))
			{
				Yield;
			}
			else
				break;
			if (/* i&ATAS_ERR||*/ tS > timeout)
			{
				if (retries--)
				{
					ATAWaitNotBUSY(bd, 0);
					goto retry;
				}
				else
					throw('BlkDev');
			}
		}
		sects_avail = 1;
		U32s_avail = sects_avail << BLK_SIZE_BITS >> 2;
		RepOutU32(buf, U32s_avail, bd->base0 + ATAR0_DATA);
		buf += U32s_avail << 2;
		count -= sects_avail;
		retries = 3;
	}
	ATAWaitNotBUSY(bd, 0);
	if (unlock)
		BlkDevUnlock(bd);
}

Bool ATAPISync(CBlkDev *bd)
{
	Bool okay = TRUE;

	if (!ATAWaitNotBUSY(bd, 0))
		okay = FALSE;
	else
	{
		if (bd->flags & BDF_EXT_SIZE)
			OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
		else
			OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

		OutU8(bd->base0 + ATAR0_LCYL, 0);
		OutU8(bd->base0 + ATAR0_HCYL, 0);
		ATACmd(bd, ATA_PACKET);
		ATAPIWritePacketWord(bd, 0, ATAPI_SYNC_CACHE, 0, 0, 0, 0, 0);

		if (!ATAWaitNotBUSY(bd, 0))
			okay = FALSE;
	}

	return okay;
}

U0 ATAPIClose(CBlkDev *bd, I64 close_field=0x200, I64 track=0)
{//0x200 CD/DVD part 1
// 0x300		DVD part 2
	if (bd->flags & BDF_EXT_SIZE)
		OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
	else
		OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

	OutU8(bd->base0 + ATAR0_LCYL, 0);
	OutU8(bd->base0 + ATAR0_HCYL, 0);
	ATACmd(bd, ATA_PACKET);
	ATAPIWritePacketWord(bd, 0, ATAPI_CLOSE_TRACK_SESSION, close_field, track, 0, 0, 0);

	ATAWaitNotBUSY(bd, 0);
}

U0 ATAPIWriteBlks(CBlkDev *bd, U8 *buf, I64 native_blk, I64 count)
{
	I64 U32s_avail;
	U8 *buf2;

	ATAWaitNotBUSY(bd, 0);
	ATAPISeek(bd, native_blk);

	OutU8(bd->base0 + ATAR0_FEAT, 0);
	OutU8(bd->base0 + ATAR0_LCYL, bd->blk_size);
	OutU8(bd->base0 + ATAR0_HCYL, bd->blk_size.u8[1]);

	if (bd->flags & BDF_EXT_SIZE)
		OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
	else
		OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

	OutU8(bd->base0 + ATAR0_CMD, ATA_PACKET);
	ATAPIWritePacketWord(bd, 0, ATAPI_FORMAT_UNIT, native_blk.u16[1], native_blk, count.u16[1], count, 0);

	bd->flags |= BDF_LAST_WAS_WRITE;

	ATAWaitNotBUSY(bd, 0);
	ATAPISeek(bd, native_blk);

	if (bd->flags & BDF_EXT_SIZE)
		OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
	else
		OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

	OutU8(bd->base0 + ATAR0_LCYL, bd->blk_size);
	OutU8(bd->base0 + ATAR0_HCYL, bd->blk_size.u8[1]);
	ATACmd(bd, ATA_PACKET);
	ATAPIWritePacketWord(bd, 0, ATAPI_WRITE, native_blk.u16[1], native_blk, count.u16[1], count, 0);

	buf2 = buf + bd->blk_size * count;
	while (buf < buf2)
	{
		ATAWaitDRQ(bd, 0);
		U32s_avail = (InU8(bd->base0 + ATAR0_HCYL) << 8 + InU8(bd->base0 + ATAR0_LCYL)) >> 2;
		if (buf + U32s_avail << 2 > buf2)
			U32s_avail = (buf2-buf) >> 2;
		if (U32s_avail)
		{
			RepOutU32(buf, U32s_avail, bd->base0 + ATAR0_DATA);
			buf += U32s_avail << 2;
			blkdev.write_count += U32s_avail >> (BLK_SIZE_BITS - 2);
		}
	}
	ATAWaitNotBUSY(bd, 0);
}

Bool ATAWBlks(CDrive *drive, U8 *buf, I64 blk, I64 count)
{
	I64		 n, spc;
	CBlkDev	*bd = drive->bd;
	Bool	 unlock;

	spc = bd->blk_size >> BLK_SIZE_BITS;

	if (bd->type == BDT_ATAPI)
	{
		unlock = BlkDevLock(bd);
		ATAPIWaitReady(bd, 0);
	}
	while (count > 0)
	{
		n = count;
		if (n > bd->max_writes)
			n = bd->max_writes;

		if (bd->type == BDT_ATAPI)
			ATAPIWriteBlks(bd, buf, blk / spc, (n + spc - 1) / spc);
		else
			ATAWriteBlks(bd, buf, blk, n);

		buf += n << BLK_SIZE_BITS;
		blk += n;
		count -= n;
		blkdev.write_count += n;
	}
	if (bd->type == BDT_ATAPI)
	{
		ATAPISync(bd);
//		ATAPIStartStop(bd,0,FALSE);
		if (unlock)
			BlkDevUnlock(bd);
	}

	return TRUE;
}
