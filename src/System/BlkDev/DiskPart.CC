#help_index "Install;File/Cmd Line (Typically);Cmd Line (Typically)"

#define ROUND_DRIVE_TO	(63 * 255)
#define DRIVE_HEADER	63

class CPlannedDrive
{
	CPlannedDrive	*next, *last;
	I64				 size;
	Bool			 pri;
};

public I64 DiskPart(U8 drv_let=0, ...)
{/*Partition the disk containing partition drv_let.

drv_let=0 means add new drive that is not already mounted.

>DiskPart('C',0.5,0.25,0.25); //Make three.  50% C, 25% D, 25% E, round-up to blk.

*/
	CBlkDev			*bd;
	CPlannedDrive	 head, *tmppp;
	CMasterBoot		 mbr;
	Bool			 pri = TRUE;
	I64				 ext_base, drv_let2, pri_count = 0, i, start_offset, offset, total, remaining, cur_arg = 0;

	"This command does not play well\n"
	"with other operating systems.\n"
	"You really should use another\n"
	"operating system's partitioner.\n"
	"If you use this, it may, in fact,\n"
	"make your hard drive impossible\n"
	"to repartition with other operating\n"
	"until you set block zero to zero\n"
	"with $$LK,\"BootMHDZero\",\"MN:BootMHDZero\"$$()\n\n\n"
	"Continue";
	if (argc <= cur_arg && !YorN)
		return 0;
	'\n';

	if (drv_let && !Letter2BlkDev(drv_let, FALSE))
		drv_let = 0;
	if (!drv_let && !(drv_let = Mount(TRUE)) || !(bd = Letter2BlkDev(drv_let, FALSE)) || bd->type != BDT_ATA)
		return 0;

	total = bd->max_blk + 1;
	QueueInit(&head);
	drv_let2 = bd->first_drive_let;
	remaining = FloorU64(bd->max_blk + 1, ROUND_DRIVE_TO);
	while (FloorU64(remaining, ROUND_DRIVE_TO) >= ROUND_DRIVE_TO)
	{
		tmppp = MAlloc(sizeof(CPlannedDrive));
		do
		{
			"$$RED$$Partition %C$$FG$$\n", drv_let2;
			tmppp->pri = FALSE;
			if (pri)
			{
				"Primary Partition";
				if (argc>cur_arg || YorN)
				{
					pri_count++;
					tmppp->pri = TRUE;
					if (pri_count == 3)
						pri = FALSE;
				}
				else
					pri = FALSE;
			}
			"\nBlocks Remaining:%d (0x%X)\n", remaining - DRIVE_HEADER, remaining - DRIVE_HEADER;
			if (argc > cur_arg)
				tmppp->size = MinI64(CeilU64(MaxI64(remaining, DRIVE_HEADER), ROUND_DRIVE_TO),
								CeilU64(argv[cur_arg++](F64) * total, ROUND_DRIVE_TO));
			else
				tmppp->size = CeilU64(I64Get("Size in Blocks  :", remaining - DRIVE_HEADER) + DRIVE_HEADER, ROUND_DRIVE_TO);
		}
		while (!(ROUND_DRIVE_TO <= tmppp->size <= FloorU64(remaining, ROUND_DRIVE_TO)));

		QueueInsert(tmppp, head.last);
		remaining -= tmppp->size;
		drv_let2++;
	}

	"\n\n!!! Repartition Drive !!!\n\n";
	tmppp = head.next;
	drv_let2 = bd->first_drive_let;
	while (tmppp != &head)
	{
		"Drive %C:%08X ", drv_let2, tmppp->size;
		if (tmppp->pri)
			"Primary\n";
		else
			"Logical\n";
		tmppp = tmppp->next;
		drv_let2++;
	}
	if (!argc && !AreYouSure)
		goto pd_done;

	remaining = FloorU64(bd->max_blk + 1, ROUND_DRIVE_TO) - ROUND_DRIVE_TO;
	tmppp = head.next;
	MemSet(&mbr, 0, BLK_SIZE);
	mbr.signature = 0xAA55;
	offset = 0;
	for (i = 0; i < pri_count; i++)
	{
		mbr.p[i].active		= 0x80;
		mbr.p[i].start_head	= 0;
		mbr.p[i].start_cyl	= 0x101;
		mbr.p[i].type		= 1; //Will get set different.
		mbr.p[i].end_head	= 0xFE;
		mbr.p[i].end_cyl	= 0xFFFF;
		mbr.p[i].offset		= DRIVE_HEADER + offset;
		mbr.p[i].size		= tmppp->size - DRIVE_HEADER;
		offset += tmppp->size;
		remaining -= tmppp->size;
		tmppp = tmppp->next;
	}
	if (!i)
		i++;
	if (tmppp != &head)
	{
		mbr.p[i].active		= 0x80;
		mbr.p[i].start_head	= 0;
		mbr.p[i].start_cyl	= 0x101;
		mbr.p[i].type		= 0xF;
		mbr.p[i].end_head	= 0xFE;
		mbr.p[i].end_cyl	= 0xFFFF;
		mbr.p[i].offset		= offset;
		mbr.p[i].size		= remaining;
		ext_base = offset;
	}
	AHCIAtaBlksWrite(bd, &mbr, 0, 1);

	while (tmppp != &head)
	{
		start_offset = offset;
		MemSet(&mbr, 0, BLK_SIZE);
		mbr.signature = 0xAA55;

		mbr.p[0].active		= 0x80;
		mbr.p[0].start_head	= 1;
		mbr.p[0].start_cyl	= 0x101;
		mbr.p[0].type		= 1; //Will get set different.
		mbr.p[0].end_head	= 0xFE;
		mbr.p[0].end_cyl	= 0xFFFF;
		mbr.p[0].offset		= DRIVE_HEADER;
		mbr.p[0].size		= tmppp->size - DRIVE_HEADER;
		offset += tmppp->size;
		tmppp = tmppp->next;
		if (tmppp != &head)
		{
			mbr.p[1].active		= 0x80;
			mbr.p[1].start_head	= 0;
			mbr.p[1].start_cyl	= 0x101;
			mbr.p[1].type		= 5;
			mbr.p[1].end_head	= 0xFE;
			mbr.p[1].end_cyl	= 0xFFFF;
			mbr.p[1].offset		= offset - ext_base;
			mbr.p[1].size		= tmppp->size;
		}
		AHCIAtaBlksWrite(bd, &mbr, start_offset, 1);
	}

	bd->flags &= ~(BDF_INITIALIZED | BDF_INIT_IN_PROGRESS);
	BlkDevAdd(bd,, FALSE, TRUE);
	for (i = bd->first_drive_let; i < drv_let2; i++)
		Format(i,, FALSE);

		pd_done:
	while (head.next != &head)
	{
		tmppp = head.next;
		QueueRemove(tmppp);
		Free(tmppp);
	}

	return total;
}
