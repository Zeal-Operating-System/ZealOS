
U0 IDEATABlkSel(CBlkDev *bd, I64 blk, I64 count)
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

Bool IDEATAWaitNotBUSY(CBlkDev *bd, F64 timeout)
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

Bool IDEATAWaitDRQ(CBlkDev *bd, F64 timeout)
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

Bool IDEATANop(CBlkDev *bd, F64 timeout)
{
	if (bd->flags & BDF_EXT_SIZE)
		OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
	else
		OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

	OutU8(bd->base0 + ATAR0_FEAT,	0);
	OutU8(bd->base0 + ATAR0_CMD,	ATA_NOP);
	return IDEATAWaitNotBUSY(bd, timeout);
}

U0 IDEATACmd(CBlkDev *bd, U8 cmd)
{
	OutU8(bd->base0 + ATAR0_FEAT,	0);
	OutU8(bd->base0 + ATAR0_CMD,	cmd);
	bd->last_time = tS;
	PortNop;
}

Bool IDEATAGetRes(CBlkDev *bd, F64 timeout, U8 *buf, I64 count, I64 _avail, Bool one_read)
{
	I64 avail, overflow;

	bd->flags &= ~BDF_LAST_WAS_WRITE;
	MemSet(buf, 0, count);
	while (count > 0)
	{
		if (!IDEATAWaitDRQ(bd, timeout))
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
	return IDEATAWaitNotBUSY(bd, timeout);
}

Bool IDEATAPIWritePacketWord(CBlkDev *bd, F64 timeout, ...)
{
	I64 i;

	for (i = 0; i < argc; i++)
	{
		if (!IDEATAWaitDRQ(bd, timeout))
			return FALSE;

		OutU16(bd->base0 + ATAR0_DATA, EndianU16(argv[i]));
		bd->last_time = tS;
	}

	return TRUE;
}

Bool IDEATAPISetMaxSpeed(CBlkDev *bd)
{
	if (bd->flags & BDF_EXT_SIZE)
		OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
	else
		OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

	OutU8(bd->base0 + ATAR0_LCYL, 0);
	OutU8(bd->base0 + ATAR0_HCYL, 0);
	IDEATACmd(bd, ATA_PACKET);
	IDEATAPIWritePacketWord(bd, 0, ATAPI_SET_CD_SPEED, 0xFFFF, 0xFFFF, 0, 0, 0);

	return IDEATAWaitNotBUSY(bd, 0);
}

Bool IDEATAPISeek(CBlkDev *bd, I64 native_blk)
{
	if (bd->flags & BDF_EXT_SIZE)
		OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
	else
		OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

	OutU8(bd->base0 + ATAR0_LCYL, 0);
	OutU8(bd->base0 + ATAR0_HCYL, 0);
	IDEATACmd(bd, ATA_PACKET);
	IDEATAPIWritePacketWord(bd, 0, ATAPI_SEEK, native_blk >> 16, native_blk, 0, 0, 0);

	return IDEATAWaitNotBUSY(bd, 0);
}

Bool IDEATAPIStartStop(CBlkDev *bd, F64 timeout, Bool start)
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

	IDEATACmd(bd, ATA_PACKET);
//Start/Stop
	if (IDEATAPIWritePacketWord(bd, timeout, ATAPI_START_STOP_UNIT, 0, i, 0, 0, 0))
		return IDEATAWaitNotBUSY(bd, timeout);
	else
		return FALSE;
}

I64 IDEATAGetDevId(CBlkDev *bd, F64 timeout, Bool keep_id_record)
{
	I64  res		= BDT_NULL;
	U16 *id_record	= NULL;

	if (bd->type != BDT_ATAPI && bd->base1)
		OutU8(bd->base1 + ATAR1_CTRL, 0x8);
	if (bd->flags & BDF_EXT_SIZE)
		OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
	else
		OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

	IDEATACmd(bd, ATA_IDENTIFY);
	if (IDEATAWaitNotBUSY(bd, timeout))
	{
		if (InU8(bd->base0 + ATAR0_STAT) & ATAS_ERR)
			res = BDT_ATAPI;
		else
		{
			id_record = SysCAlloc(512);
			if (IDEATAGetRes(bd, timeout, id_record, 512, 512, FALSE))
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

I64 IDEATAReadNativeMax(CBlkDev *bd, F64 timeout)
{//Returns zero on error
	I64  res  = 0;
	Bool okay = TRUE;

	if (bd->type == BDT_ATAPI)
	{
		if (bd->flags & BDF_EXT_SIZE)
			OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
		else
			OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

		IDEATACmd(bd, ATA_DEV_RST);
		if (!IDEATAWaitNotBUSY(bd, 0))
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
		if (IDEATAGetDevId(bd, timeout, TRUE) == BDT_NULL)
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

			IDEATACmd(bd, ATA_READ_NATIVE_MAX_EXT);
			if (IDEATAWaitNotBUSY(bd, timeout))
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
			IDEATACmd(bd, ATA_READ_NATIVE_MAX);
			if (IDEATAWaitNotBUSY(bd, timeout))
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

I64 IDEATAPIReadCapacity(CBlkDev *bd, I64 *_blk_size=NULL)
{//Supposedly this can return a res +/- 75 sects.
//Error might just be for music.
	Bool unlock = BlkDevLock(bd);
	U32  buf[2];

	if (IDEATAWaitNotBUSY(bd, 0))
	{
		if (bd->flags & BDF_EXT_SIZE)
			OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
		else
			OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

		OutU8(bd->base0 + ATAR0_LCYL, 8);
		OutU8(bd->base0 + ATAR0_HCYL, 0);
		IDEATACmd(bd, ATA_PACKET);
		IDEATAPIWritePacketWord(bd, 0, ATAPI_READ_CAPACITY, 0, 0, 0, 0, 0);

		if (!IDEATAGetRes(bd, 0, buf, 8, 0, TRUE))
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

CATAPITrack *IDEATAPIReadTrackInfo(CBlkDev *bd, I64 blk)
{
	CATAPITrack	*res	= CAlloc(sizeof(CATAPITrack));
	Bool		 unlock	= BlkDevLock(bd);

	if (IDEATAWaitNotBUSY(bd, 0))
	{
		if (bd->flags & BDF_EXT_SIZE)
			OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
		else
			OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

		OutU8(bd->base0 + ATAR0_LCYL, sizeof(CATAPITrack) & 0xFF);
		OutU8(bd->base0 + ATAR0_HCYL, sizeof(CATAPITrack) >> 8);

		IDEATACmd(bd, ATA_PACKET);
		IDEATAPIWritePacketWord(bd,
							 0,
							 ATAPI_READ_TRACK_INFO,
							 blk.u16[1],
							 blk.u16[0],
							 (sizeof(CATAPITrack) & 0xFF00) >> 8,
							 (sizeof(CATAPITrack) & 0x00FF) << 8,
							 0);

		if (!IDEATAGetRes(bd, 0, res, sizeof(CATAPITrack), 0, TRUE))
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

I64 IDEATAProbe(I64 base0, I64 base1, I64 unit)
{
	CBlkDev bd;

	MemSet(&bd, 0, sizeof(CBlkDev));
	bd.type = BDT_ATAPI;
	bd.base0 = base0;
	bd.base1 = base1;
	bd.unit = unit;
	bd.blk_size = DVD_BLK_SIZE;

	return IDEATAGetDevId(&bd, tS + 0.1, FALSE);
}

Bool IDEATAPISync(CBlkDev *bd)
{
	Bool okay = TRUE;

	if (!IDEATAWaitNotBUSY(bd, 0))
		okay = FALSE;
	else
	{
		if (bd->flags & BDF_EXT_SIZE)
			OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
		else
			OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

		OutU8(bd->base0 + ATAR0_LCYL, 0);
		OutU8(bd->base0 + ATAR0_HCYL, 0);
		IDEATACmd(bd, ATA_PACKET);
		IDEATAPIWritePacketWord(bd, 0, ATAPI_SYNC_CACHE, 0, 0, 0, 0, 0);

		if (!IDEATAWaitNotBUSY(bd, 0))
			okay = FALSE;
	}

	return okay;
}

U0 IDEATAPIClose(CBlkDev *bd, I64 close_field=0x200, I64 track=0)
{//0x200 CD/DVD part 1
// 0x300		DVD part 2
	if (bd->flags & BDF_EXT_SIZE)
		OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
	else
		OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

	OutU8(bd->base0 + ATAR0_LCYL, 0);
	OutU8(bd->base0 + ATAR0_HCYL, 0);
	IDEATACmd(bd, ATA_PACKET);
	IDEATAPIWritePacketWord(bd, 0, ATAPI_CLOSE_TRACK_SESSION, close_field, track, 0, 0, 0);

	IDEATAWaitNotBUSY(bd, 0);
}

U0 IDEATAPIWriteBlks(CBlkDev *bd, U8 *buf, I64 native_blk, I64 count)
{
	I64 U32s_avail;
	U8 *buf2;

	IDEATAWaitNotBUSY(bd, 0);
	IDEATAPISeek(bd, native_blk);

	OutU8(bd->base0 + ATAR0_FEAT, 0);
	OutU8(bd->base0 + ATAR0_LCYL, bd->blk_size);
	OutU8(bd->base0 + ATAR0_HCYL, bd->blk_size.u8[1]);

	if (bd->flags & BDF_EXT_SIZE)
		OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
	else
		OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

	OutU8(bd->base0 + ATAR0_CMD, ATA_PACKET);
	IDEATAPIWritePacketWord(bd, 0, ATAPI_FORMAT_UNIT, native_blk.u16[1], native_blk, count.u16[1], count, 0);

	bd->flags |= BDF_LAST_WAS_WRITE;

	IDEATAWaitNotBUSY(bd, 0);
	IDEATAPISeek(bd, native_blk);

	if (bd->flags & BDF_EXT_SIZE)
		OutU8(bd->base0 + ATAR0_SEL, 0xEF | bd->unit << 4);
	else
		OutU8(bd->base0 + ATAR0_SEL, 0xE0 | bd->unit << 4);

	OutU8(bd->base0 + ATAR0_LCYL, bd->blk_size);
	OutU8(bd->base0 + ATAR0_HCYL, bd->blk_size.u8[1]);
	IDEATACmd(bd, ATA_PACKET);
	IDEATAPIWritePacketWord(bd, 0, ATAPI_WRITE, native_blk.u16[1], native_blk, count.u16[1], count, 0);

	buf2 = buf + bd->blk_size * count;
	while (buf < buf2)
	{
		IDEATAWaitDRQ(bd, 0);
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
	IDEATAWaitNotBUSY(bd, 0);
}
