U0 DiskCacheInit(I64 size_in_U8s)
{
	CCacheBlk	*tmpc;
	I64			 i, count;

	while (LBts(&sys_semas[SEMA_DISK_CACHE], 0))
		Yield;
	Free(blkdev.cache_ctrl);
	Free(blkdev.cache_base);
	Free(blkdev.cache_hash_table);
	if (size_in_U8s < 0x2000)
	{
		blkdev.cache_ctrl		= NULL;
		blkdev.cache_base		= NULL;
		blkdev.cache_hash_table	= NULL;
	}
	else
	{
		blkdev.cache_ctrl = SysCAlloc(offset(CCacheBlk.body));
		blkdev.cache_base = SysMAlloc(size_in_U8s);
		QueueInit(blkdev.cache_ctrl);

		count = MSize(blkdev.cache_base) / sizeof(CCacheBlk);
		blkdev.cache_size = count * BLK_SIZE;
		for (i = 0; i < count; i++)
		{
			tmpc = blkdev.cache_base+i;
			QueueInsert(tmpc, blkdev.cache_ctrl->last_lru);
			tmpc->next_hash	= tmpc->last_hash = tmpc;
			tmpc->drive		= NULL;
			tmpc->blk		= 0;
		}

		blkdev.cache_hash_table = SysMAlloc(DISK_CACHE_HASH_SIZE * sizeof(U8 *) * 2);
		for (i = 0; i < DISK_CACHE_HASH_SIZE; i++)
		{
			tmpc = blkdev.cache_hash_table(U8 *) + i * sizeof(U8 *) * 2 - offset(CCacheBlk.next_hash);
			tmpc->next_hash = tmpc->last_hash = tmpc;
		}
	}
	LBtr(&sys_semas[SEMA_DISK_CACHE], 0);
}

I64 DiskCacheHash(I64 blk)
{
	I64 i = blk & (DISK_CACHE_HASH_SIZE - 1);

	return blkdev.cache_hash_table(U8 *) + i << 4 - offset(CCacheBlk.next_hash);
}

U0 DiskCacheQueueRemove(CCacheBlk *tmpc)
{
	QueueRemove(tmpc);
	tmpc->next_hash->last_hash = tmpc->last_hash;
	tmpc->last_hash->next_hash = tmpc->next_hash;
}

U0 DiskCacheQueueIns(CCacheBlk *tmpc)
{
	CCacheBlk *tmp_n, *tmp_l;

	QueueInsert(tmpc, blkdev.cache_ctrl->last_lru);
	tmp_l = DiskCacheHash(tmpc->blk);
	tmp_n = tmp_l->next_hash;
	tmpc->last_hash = tmp_l;
	tmpc->next_hash = tmp_n;
	tmp_l->next_hash = tmp_n->last_hash = tmpc;
}

CCacheBlk *DiskCacheFind(CDrive *drive, I64 blk)
{
	CCacheBlk *tmpc, *tmpc1 = DiskCacheHash(blk);

	tmpc = tmpc1->next_hash;
	while (tmpc != tmpc1)
	{
		if (tmpc->drive == drive && tmpc->blk == blk)
			return tmpc;
		tmpc = tmpc->next_hash;
	}
	return NULL;
}

U0 DiskCacheAdd(CDrive *drive, U8 *buf, I64 blk, I64 count)
{
	CCacheBlk *tmpc;

	if (blkdev.cache_base)
	{
		while (LBts(&sys_semas[SEMA_DISK_CACHE], 0))
			Yield;
		while (count-- > 0)
		{
			if (!(tmpc = DiskCacheFind(drive, blk)))
				tmpc = blkdev.cache_ctrl->next_lru;
			DiskCacheQueueRemove(tmpc);
			MemCopy(&tmpc->body, buf, BLK_SIZE);
			tmpc->drive = drive;
			tmpc->blk   = blk;
			DiskCacheQueueIns(tmpc);
			blk++;
			buf += BLK_SIZE;
		}
		LBtr(&sys_semas[SEMA_DISK_CACHE], 0);
	}
}

U0 DiskCacheInvalidate2(CDrive *drive)
{
	CCacheBlk *tmpc, *tmpc1;

	if (blkdev.cache_base)
	{
		while (LBts(&sys_semas[SEMA_DISK_CACHE], 0))
			Yield;
		tmpc = blkdev.cache_ctrl->last_lru;
		while (tmpc != blkdev.cache_ctrl)
		{
			tmpc1 = tmpc->last_lru;
			if (tmpc->drive == drive)
			{
				DiskCacheQueueRemove(tmpc);
				tmpc->drive		= NULL;
				tmpc->blk		= 0;
				tmpc->next_hash	= tmpc->last_hash = tmpc;
				QueueInsert(tmpc, blkdev.cache_ctrl->last_lru);
			}
			tmpc = tmpc1;
		}
		LBtr(&sys_semas[SEMA_DISK_CACHE], 0);
	}
}

U0 RCache(CDrive *drive, U8 **_buf, I64 *_blk, I64 *_count)
{
	CCacheBlk *tmpc;

	if (blkdev.cache_base)
	{
		while (LBts(&sys_semas[SEMA_DISK_CACHE], 0))
			Yield;
//fetch leading blocks from cache
		while (*_count > 0)
		{
			if (tmpc = DiskCacheFind(drive, *_blk))
			{
				MemCopy(*_buf, &tmpc->body, BLK_SIZE);
				*_count -= 1;
				*_buf += BLK_SIZE;
				*_blk += 1;
			}
			else
				break;
		}
//fetch trailing blocks from cache
		while (*_count > 0)
		{
			if (tmpc = DiskCacheFind(drive, *_blk + *_count - 1))
			{
				MemCopy(*_buf + (*_count - 1) << BLK_SIZE_BITS, &tmpc->body, BLK_SIZE);
				*_count -= 1;
			}
			else
				break;
		}
		LBtr(&sys_semas[SEMA_DISK_CACHE], 0);
	}
}
