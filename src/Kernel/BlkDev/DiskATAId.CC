/* // TODO: use this for reference in SATARep when fixing AHCI's lack of blkdev.ins_unit, etc
U0 ATARepEntry(I64 base0, I64 base1, I64 unit, U8 *message, CATARep **_head, I64 *num_hints)
{
	I64		 type;
	base0 &= -8;
	base1 &= -4;
	CATARep	*tmpha;

	if (type = IDEATAProbe(base0,base1,unit))
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
*/

CBlkDev *ATAMount(U8 first_drive_let, I64 type, I64 port_num)
{
	CBlkDev *res;

	if (0 <= first_drive_let - 'A' < DRIVES_NUM && (type == BDT_ATA || type == BDT_ATAPI) && 0 <= port_num <= AHCI_MAX_PORTS)
	{
		res = BlkDevNextFreeSlot(first_drive_let, type);
		res->port_num = port_num;
		res->ahci_port = &blkdev.ahci_hba->ports[port_num];
		res->ahci_port->cmd_list_base = NULL; // See $LK+PU,"AHCIAtaInit",A="FF:::/Kernel/BlkDev/DiskAHCI.CC,if (bd->ahci_port->cmd_list_base)"$ ...
		if (BlkDevAdd(res,, FALSE, FALSE))
			return res;
	}

	return NULL;
}

I64 MountAHCIAuto()
{//Try to mount hard drives and CD/DVD drives automatically. (Kernel.Config option).
//It uses 'C' and 'T' as first drive letters or whatever you set
//in config when compiling Kernel.BIN.
	CBlkDev		*bd		= Letter2BlkDev(':', FALSE);
	I64			 res	= 0, i, ata_port = -1, atapi_port = -1;
	CAHCIPort	*port;

	"MountAHCIAuto;\n";
	if (bd)
	{
		// if boot-drive blkdev exists, do a SATA port iteration to mount it first
		"( ':' BlkDev at 0x%0X )\n", bd;
		for (i = 0; i < AHCI_MAX_PORTS; i++)
			if (Bt(&blkdev.ahci_hba->ports_implemented, i))
			{
				port = &blkdev.ahci_hba->ports[i];

				if (bd->port_num == i)
				{
					if (ata_port == -1 && bd->type == BDT_ATA && port->signature == AHCI_PxSIG_ATA)
					{
						"ATAMount('%C', BDT_ATA, %d);\n", blkdev.first_hd_drive_let, i;
						ATAMount(blkdev.first_hd_drive_let, BDT_ATA, i);
						ata_port = i;
						res++;
					}
					else if (atapi_port == -1 && bd->type == BDT_ATAPI && port->signature == AHCI_PxSIG_ATAPI)
					{
						"ATAMount('%C', BDT_ATAPI, %d);\n", blkdev.first_dvd_drive_let, i;
						ATAMount(blkdev.first_dvd_drive_let, BDT_ATAPI, i);
						atapi_port = i;
						res++;
					}
				}
			}
	}
	// do a 2nd iteration to mount remaining drives
	// (we will end up trying to boot off whichever drive/partition ends up at chosen letter)
	for (i = 0; i < AHCI_MAX_PORTS; i++)
		if (i != ata_port && i != atapi_port && Bt(&blkdev.ahci_hba->ports_implemented, i))
		{
			port = &blkdev.ahci_hba->ports[i];

			if (port->signature == AHCI_PxSIG_ATA)
			{
				"ATAMount('%C', BDT_ATA, %d);\n", blkdev.first_hd_drive_let, i;
				if (ATAMount(blkdev.first_hd_drive_let, BDT_ATA, i))
					res++;
			}
			else if (port->signature == AHCI_PxSIG_ATAPI)
			{
				"ATAMount('%C', BDT_ATAPI, %d);\n", blkdev.first_dvd_drive_let, i;
				if (ATAMount(blkdev.first_dvd_drive_let, BDT_ATAPI, i))
					res++;
			}
		}
	"\n";
	blkdev.mount_ide_auto_count = res;

	return res;
}
