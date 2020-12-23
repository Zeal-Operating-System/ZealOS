Bool BootDVDProbe(CBlkDev *bd)
{
	U8		*img = CAlloc(DVD_BLK_SIZE);
	I64		 i;
	Bool	 res = FALSE;

	"Port: %04X,%04X Unit: %02X  ", bd->base0, bd->base1, bd->unit;
	if (ATAProbe(bd->base0, bd->base1, bd->unit) == BDT_ATAPI)
	{
		" ATAPI";
		if (ATAPIStartStop(bd, tS + 5.0, TRUE))
		{
			" Started";
			for (i = 0; i < 2; i++)
			{//Retry
				if (ATAPIReadBlks2(bd, tS + 7.0, img, sys_boot_blk, 1, FALSE))
				{
					if ((img + sys_boot_src.u16[1] << BLK_SIZE_BITS)(CKernel *)->compile_time == sys_compile_time)
					{
						" Found\n";
						return TRUE;
					}
					else
						" Read";
				}
				else
					" NoRead";
			}
		}
	}
	" Nope\n";
	Free(img);

	return res;
}

Bool BootDVDProbeAll(CBlkDev *bd)
{
	I64 d1, d2, i, j, k;


	/* AHCI Prototyping */
	CAHCIHba *hba;
	CAHCIPort *port;
	#exe {Option(OPTf_WARN_DUP_TYPES, OFF);};
	I64 bdf = PCIClassFind(PCIC_STORAGE << 16 | PCISC_AHCI << 8 + 1, 0);
	#exe {Option(OPTf_WARN_DUP_TYPES, ON);};

	if (bdf != -1)
	{
		"\nAHCI is not yet supported.\n\n";
		hba = dev.uncached_alias + PCIReadU32(bdf.u8[2], bdf.u8[1], bdf.u8[0], PCIR_BASE5) & ~0x1F;
		Bts(&hba->ghc, AHCI_GHCf_HBA_RESET);
		while (Bt(&hba->ghc, AHCI_GHCf_HBA_RESET));
		Bts(&hba->ghc, AHCI_GHCf_AHCI_ENABLE);
		for (i = 0; i < AHCI_MAX_PORTS; i++)
		{
			if (Bt(&hba->ports_implemented, i))
			{
				port = &hba->ports[i];
				if (port->signature == AHCI_PxSIG_ATAPI)
					"ATAPI drive detected on AHCI Port %d\n", i;
				else if (port->signature == AHCI_PxSIG_ATA)
					"ATA   drive detected on AHCI Port %d\n", i;
			}
		}
		"\n\nReboot with IDE Compatibility mode set in the BIOS.\n";
		SysHlt;
	}
	/********************/


	bd->base1 = 0;
	for (k = 0; k < 256; k++)
	{
		i = -1;
		while (TRUE)
		{
			j = PCIClassFind(0x010100 + k, ++i);
			if (j < 0)
				break;
			"Subcode:0x%X Bus:0x%X Dev:0x%X Fun:0x%X\n", k, j.u8[2], j.u8[1], j.u8[0];
			d1 = PCIReadU32(j.u8[2], j.u8[1], j.u8[0], 0x10);
			d2 = PCIReadU32(j.u8[2], j.u8[1], j.u8[0], 0x14);
			if (d1 & 1 && d2 & 1)
			{
				if (bd->base0 = d1 & ~7)
				{
					bd->unit = 0;
					if (BootDVDProbe(bd))
						return TRUE;
					bd->unit = 1;
					if (BootDVDProbe(bd))
						return TRUE;
				}
			}
			d1 = PCIReadU32(j.u8[2], j.u8[1], j.u8[0], 0x18);
			d2 = PCIReadU32(j.u8[2], j.u8[1], j.u8[0], 0x1C);
			if (d1 & 1 && d2 & 1)
			{
				if (bd->base0 = d1 & ~7)
				{
					bd->unit = 0;
					if (BootDVDProbe(bd))
						return TRUE;
					bd->unit = 1;
					if (BootDVDProbe(bd))
						return TRUE;
				}
			}
		}
	}

	d1 = 0x1F0;
	d2 = 0x3F6;
	if (bd->base0 = d1 & ~7)
	{
		bd->unit = 0;
		if (BootDVDProbe(bd))
			return TRUE;
		bd->unit = 1;
		if (BootDVDProbe(bd))
			return TRUE;
	}

	d1 = 0x170;
	d2 = 0x376;
	if (bd->base0 = d1 & ~7)
	{
		bd->unit = 0;
		if (BootDVDProbe(bd))
			return TRUE;
		bd->unit = 1;
		if (BootDVDProbe(bd))
			return TRUE;
	}
}

U0 ATARepEntry(I64 base0, I64 base1, I64 unit, U8 *message, CATARep **_head, I64 *num_hints)
{
	I64		 type;
	base0 &= -8;
	base1 &= -4;
	CATARep	*tmpha;

	if (type = ATAProbe(base0,base1,unit))
	{
		*num_hints += 1;
		"\n$$PURPLE$$ $$BT+X,\"%d\",LM=\"%d\\n\"$$$$FG$$$$LM,4$$", *num_hints, *num_hints;
		if (type == BDT_ATA)
			"$$RED$$Hard Drive   $$LTBLUE$$ATA   ";
		else
			"$$RED$$CD/DVD Drive $$LTBLUE$$ATAPI ";
		"%s$$FG$$\n", message;
		if (base0 == blkdev.ins_base0 && unit == blkdev.ins_unit)
			"$$PURPLE$$(Drive originally installed from.)$$FG$$\n";
		"Base0:0x%04X Base1:0x%04X Unit:%d$$LM,0$$\n", base0, base1, unit;
		if (_head)
		{
			tmpha = CAlloc(sizeof(CATARep));
			tmpha->next = *_head;
			*_head = tmpha;
			tmpha->num = *num_hints;
			tmpha->type = type;
			tmpha->base0 = base0;
			tmpha->base1 = base1;
			tmpha->unit = unit;
		}
	}
}

Bool ATARepExitAllApplications()
{
	"\nWe're going to probe hardware.\n"
				"$$RED$$Exit all other applications.$$FG$$\n"
				"Press '$$PURPLE$$p$$FG$$' to probe or '$$PURPLE$$s$$FG$$' to skip.\n";
	if (ToUpper(CharGet(, FALSE)) == 'S')
		return TRUE;
	else
		return FALSE;
}

public I64 ATARep(Bool prompt=TRUE, Bool just_ide=FALSE, CATARep **_head=NULL)
{//Report possible ATA devices by probing.	Hard disks and CD/DVDs.
	I64 d1, d2, i, j, k, count = 0, unlock_flags = 0, num_hints = 0;

#assert BLKDEVS_NUM <= 64
	if (_head)
		*_head = NULL;

	if (prompt && ATARepExitAllApplications)
		return 0;

	for (i = 0; i < BLKDEVS_NUM; i++)
		if (blkdev.blkdevs[i].bd_signature == BD_SIGNATURE_VAL)
			BEqual(&unlock_flags, i, BlkDevLock(&blkdev.blkdevs[i]));

	if (!just_ide)
		for (k = 0; k < 256; k++)
		{
			i = -1;
			while (TRUE)
			{
				j = PCIClassFind(0x010100 + k, ++i);
				if (j < 0)
					break;

				"\nSubcode:0x%X Bus:0x%X Dev:0x%X Fun:0x%X\n", k, j.u8[2], j.u8[1], j.u8[0];
				count++;

				d1 = PCIReadU32(j.u8[2], j.u8[1], j.u8[0], 0x10);
				d2 = PCIReadU32(j.u8[2], j.u8[1], j.u8[0], 0x14);
				if (d1 & 1 && d2 & 1)
				{
					ATARepEntry(d1, d2, 0, "Primary IDE", _head, &num_hints);
					ATARepEntry(d1, d2, 1, "Primary IDE", _head, &num_hints);
				}
				else
				{
					d1=0x1F0; d2=0x3F6;
					ATARepEntry(d1, d2, 0, "Primary IDE", _head, &num_hints);
					ATARepEntry(d1, d2, 1, "Primary IDE", _head, &num_hints);
				}
				d1 = PCIReadU32(j.u8[2], j.u8[1], j.u8[0], 0x18);
				d2 = PCIReadU32(j.u8[2], j.u8[1], j.u8[0], 0x1C);
				if (d1&1 && d2&1)
				{
					ATARepEntry(d1, d2, 0, "Secondary IDE", _head, &num_hints);
					ATARepEntry(d1, d2, 1, "Secondary IDE", _head, &num_hints);
				}
				else
				{
					d1 = 0x170;
					d2 = 0x376;
					ATARepEntry(d1, d2, 0, "Secondary IDE", _head, &num_hints);
					ATARepEntry(d1, d2, 1, "Secondary IDE", _head, &num_hints);
				}
			}
		}
	if (!count)
	{
		d1 = 0x1F0;
		d2 = 0x3F6;
		ATARepEntry(d1, d2, 0, "Primary IDE", _head, &num_hints);
		ATARepEntry(d1, d2, 1, "Primary IDE", _head, &num_hints);

		d1 = 0x170;
		d2 = 0x376;
		ATARepEntry(d1, d2, 0, "Secondary IDE", _head, &num_hints);
		ATARepEntry(d1, d2, 1, "Secondary IDE", _head, &num_hints);
	}
	'\n\n';
	for (i = 0; i < BLKDEVS_NUM; i++)
		if (Bt(&unlock_flags, i))
			BlkDevUnlock(&blkdev.blkdevs[i]);
	return num_hints;
}

CATARep *ATARepFind(CATARep *haystack_head, I64 needle_num)
{
	while (haystack_head)
	{
		if (haystack_head->num == needle_num)
			return haystack_head;
		haystack_head = haystack_head->next;
	}
	return NULL;
}

CATARep *ATAIDDrives(CATARep *head, CATARep **_ata_drive, CATARep **_atapi_drive)
{//This is for when trying to sort-out main hard drives and CD/DVD drives.
	CATARep	*res = NULL, *tmpha = head, *ata_drive = NULL, *atapi_drive = NULL;
	CBlkDev	*bd;
	Bool	 was_silent = Silent, ins_found = FALSE;

	bd = Letter2BlkDev(':', FALSE);
	Silent(was_silent);
	while (tmpha)
	{
		if (!res && bd && bd->type == tmpha->type)
		{
			if (bd->type == BDT_ATAPI && bd->base0 == tmpha->base0 && bd->unit == tmpha->unit)
				res = atapi_drive = tmpha;
			else if (bd->type == BDT_ATA &&
					bd->base0 == tmpha->base0 &&
					bd->base1 == tmpha->base1 &&
					bd->unit == tmpha->unit)
				res = ata_drive=tmpha;
		}
		if (!res || res->type != tmpha->type)
		{
			if (tmpha->type == BDT_ATA)
			{
				if (!ata_drive || tmpha->unit<ata_drive->unit ||
						tmpha->unit == ata_drive->unit &&
						tmpha->num < ata_drive->num)
					ata_drive = tmpha;
			}
			else if (tmpha->type == BDT_ATAPI)
			{
				if (!atapi_drive || !ins_found &&
						(tmpha->unit < atapi_drive->unit ||
						tmpha->unit == atapi_drive->unit && tmpha->num < atapi_drive->num))
					atapi_drive = tmpha;
			}
		}
		if (tmpha->type == BDT_ATAPI && bd && bd->type == BDT_ATA &&
			tmpha->base0 == blkdev.ins_base0 && tmpha->unit == blkdev.ins_unit)
		{
			if (!ins_found)
			{
				atapi_drive = tmpha;
				ins_found = TRUE;
			}
		}
		tmpha = tmpha->next;
	}
	if (_ata_drive)
		*_ata_drive = ata_drive;
	if (_atapi_drive)
		*_atapi_drive = atapi_drive;

	return res;
}

CBlkDev *ATAMount(U8 first_drive_let, I64 type, I64 base0, I64 base1, I64 unit)
{
	CBlkDev *res;

	if (0 <= first_drive_let - 'A' < DRIVES_NUM && (type == BDT_ATA || type == BDT_ATAPI) && 0 <= unit <= 1)
	{
		res = BlkDevNextFreeSlot(first_drive_let, type);
		res->unit = unit;
		res->base0 = base0;
		res->base1 = base1;
		if (BlkDevAdd(res,, FALSE, FALSE))
			return res;
	}

	return NULL;
}

I64 MountIDEAuto()
{//Try to mount hard drive and CD/DVD, automatically. (Kernel.Config option).
//It uses 'C' and 'T' as first drive letters or whatever you set
//in config when compiling Kernel.BIN.
	I64		 res  = 0;
	CATARep	*head = NULL, *ata_drive = NULL, *atapi_drive = NULL, *tmpha;

	ATARep(FALSE, TRUE, &head);
	ATAIDDrives(head, &ata_drive, &atapi_drive);
	if (ata_drive && ATAMount(blkdev.first_hd_drive_let, BDT_ATA, ata_drive->base0, ata_drive->base1, ata_drive->unit))
		res++;
	if (atapi_drive && ATAMount(blkdev.first_dvd_drive_let, BDT_ATAPI,
			atapi_drive->base0, atapi_drive->base1, atapi_drive->unit))
		res++;
	tmpha = head;
	while (tmpha)
	{
		if (tmpha != ata_drive && tmpha != atapi_drive)
		{
			if (tmpha->type == BDT_ATA && ATAMount(blkdev.first_hd_drive_let, BDT_ATA,
					tmpha->base0, tmpha->base1, tmpha->unit))
				res++;
			else if (tmpha->type == BDT_ATAPI && ATAMount(blkdev.first_dvd_drive_let, BDT_ATAPI,
						tmpha->base0, tmpha->base1, tmpha->unit))
				res++;
		}
		tmpha = tmpha->next;
	}
	LinkedListDel(head);
	blkdev.mount_ide_auto_count = res;

	return res;
}
