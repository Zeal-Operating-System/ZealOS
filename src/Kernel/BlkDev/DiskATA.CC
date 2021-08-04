/* // TODO: implement this in AHCI ATAPI
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
*/

/* // TODO: implement this in AHCI ATAPI
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
*/

/* // TODO: get AHCI ATAPI Sync to work, keep this here until it does
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
*/

/* // TODO: get AHCI ATAPI Close to work, keep this here until it does
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
*/

/* // TODO: get AHCI ATAPI WriteBlks to work, keep this here until it does
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
*/
