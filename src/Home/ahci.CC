//AHCI driver, by V0x3L. (AHCI spec 1.3.1)

I64 AHCILBA48CapacityGet(U16 *id_record)
{//Get capacity of drive, in LBA blocks.
	return *&id_record[ATA_IDENT_LBA48_CAPACITY](U64 *) - 1;
}

I64 AHCIPortCmdSlotGet(CAHCIPort *port)
{//Get next free command slot in port; if none, return -1.
	I64 i;
	U32 slots = port->sata_active | port->cmd_issue;

	for (i = 0; i < blkdev.cmd_slot_count; i++)
	{
		if (!(slots & 1))
			return i;
		slots >>= 1;
	}
	return -1;
}

Bool AHCIPortIsIdle(CAHCIPort *port)
{//Check if the command engine is running on port.
	return !(port->command & (AHCI_PxCMDF_ST | AHCI_PxCMDF_CR | AHCI_PxCMDF_FR | AHCI_PxCMDF_FRE));
}

U0 AHCIPortCmdStop(CAHCIPort *port)
{//Stop command engine on port.
	Btr(&port->command, AHCI_PxCMDf_ST);
	Btr(&port->command, AHCI_PxCMDf_FRE);
//	while (port->command & (AHCI_PxCMDF_CR | AHCI_PxCMDF_FR));
	while (Bt(&port->command, AHCI_PxCMDf_CR) || Bt(&port->command, AHCI_PxCMDf_FR));
}

U0 AHCIPortCmdStart(CAHCIPort *port)
{//Start command engine on port.
	while (Bt(&port->command, AHCI_PxCMDf_CR));
	Bts(&port->command, AHCI_PxCMDf_FRE);
	Bts(&port->command, AHCI_PxCMDf_ST);
}

Bool AHCIPortWait(CAHCIPort *port, F64 timeout)
{//Wait until DRQ & BSY are clear in port task file.
	do
	{
		if (!(port->task_file_data & (ATAS_DRQ | ATAS_BSY)))
			return TRUE;
	}
	while (timeout > tS);
	return FALSE;
}

U0 AHCIPortReset(CAHCIPort *port)
{//Software reset of port. Port command engine must be started after this.
 //If port is not responsive we do a full reset.
	AHCIPortCmdStop(port);
	port->interrupt_status = port->interrupt_status; //Acknowledge all interrupt statuses.

	if (!AHCIPortWait(port, tS + 1))
	{//Perform 'more intrusive' HBA<->Port comm reset (sec. 10.4.2 of spec).
		port->sata_ctrl = AHCI_PxSCTLF_DET_INIT;
		Sleep(2); //Spec says 1 millisecond
		port->sata_ctrl = 0;
	}
	while (port->sata_status & 0xF != AHCI_PxSSTSF_DET_PRESENT);
	port->sata_error = ~0; //Write all 1s to sata error register.
}

U0 AHCIPortIdentify(CBlkDev *bd)
{
	CHBACmdHeader *cmd_header;
	CHBACmdTable  *cmd_table;
	CFisH2D		  *cmd_fis;
	U16			  *dev_id_record;
	CAHCIPort 	  *port = bd->ahci_port;
	I64			  *slot = AHCIPortCmdSlotGet(port);

	if (slot < 0)
	{
		ZenithErr("No empty command slots.");
		throw('AHCI');
	}

	//Sticking with code heap for this alloc because we don't want to deal with 64 bit buffer address shit.
	dev_id_record = CAlloc(512, Fs->code_heap);

	port->interrupt_status = port->interrupt_status; //Ackowledge all interrupt statuses???? is this needed?

	cmd_header = *&port->cmd_list_base(I64 *); //Read full 64-bit cmd_list_base value.
	cmd_header += slot; //Move up pointer to the slot we have in the command list.

	//Setting Command FIS Length, bits 4:0, takes size in U32s.
	cmd_header->desc = (cmd_header->desc & ~0x1F) + sizeof(CFisH2D) / sizeof(U32);
	Btr(&cmd_header->desc, AHCI_CH_DESCf_W); //Disable 'write' bit.

	cmd_table = *&cmd_header->cmd_table_base(I64 *); //Read full 64-bit cmd_table_base value.
	MemSet(cmd_table, 0, sizeof(CHBACmdTable));
	cmd_table->prdt[0].data_base	   = dev_id_record;
	cmd_table->prdt[0].data_base_upper = 0;
	cmd_table->prdt[0].data_byte_count = 512 - 1;
	cmd_header->prdt_len = 1; //1 PRD, descrived above, which contains the address to put the ID record.

	cmd_fis = &cmd_table->command_fis;
	MemSet(cmd_fis, 0, sizeof(CFisH2D));
	cmd_fis->type	 = FISt_H2D;
	cmd_fis->command = ATA_IDENTIFY;
	cmd_fis->device  = 0; //No bits need to be set in the device register.
	Bts(&cmd_fis->desc, AHCI_CF_DESCf_C); //Set cmd_fis->c to 1 (Command bit).

	if (!AHCIPortWait(port, tS + 2))
	{
		ZenithErr("AHCI: Port %d hung!\n", bd->port_num);
		throw('AHCI');
	}

	Bts(&port->cmd_issue, slot);

	while (TRUE)
	{
		if (!Bt(&port->cmd_issue, slot))
			break;

		if (Bt(&port->interrupt_status, AHCI_PxIf_TFE)) //tfe = task file error
		{
oof:
			ZenithErr("AHCI: Port %d: Identify command failed!\n", bd->port_num);
			throw('AHCI');
		}
	}

	if (Bt(&port->interrupt_status, AHCI_PxIf_TFE)) //Second safety check
		goto oof;

	bd->max_blk = AHCILBA48CapacityGet(dev_id_record);
	"%X\n", bd->max_blk;
	Free(bd->dev_id_record);
	bd->dev_id_record = dev_id_record;
}

U0 AHCIPortInit(CBlkDev *bd, CAHCIPort *port, I64 port_num)
{
	CHBACmdHeader *cmd_header;
	I64 i, addr = 0;

	bd->ahci_port = port;
	bd->port_num = port_num;

	AHCIPortReset(port);
	AHCIPortCmdStart(port);

	//Spin up, power on device. If the capability isn't suppport the bits will be read-only and this won't do anything.
	port->command |= AHCI_PxCMDF_POD | AHCI_PxCMDF_SUD;
	Sleep(100);//Why?
	AHCIPortCmdStop(port);

	if (blkdev.ahci64)
	{
		//'1K-byte' align as per SATA spec.
		addr = CAllocAligned(sizeof(CHBACmdHeader) * blkdev.cmd_slot_count, 1024);
		port->cmd_list_base		  = addr.u32[0];
		port->cmd_list_base_upper = addr.u32[1];

		//Alloc where received FISes will be copied to. '256-byte' align as per spec.
		addr = CAllocAligned(sizeof(CFisReceived), 256);
		port->fis_base		 = addr.u32[0];
		port->fis_base_upper = addr.u32[1];
	}
	else
	{//Code Heap is always under 4 GB in address space, so we can use that instead.
		port->cmd_list_base		  = CAllocAligned(sizeof(CHBACmdHeader) * blkdev.cmd_slot_count, 1024, Fs->code_heap);
		port->cmd_list_base_upper = 0;

		port->fis_base		 = CAllocAligned(sizeof(CFisReceived), 256, Fs->code_heap);
		port->fis_base_upper = 0;
	}

	for (i = 0; i < blkdev.cmd_slot_count; i++)
	{
		cmd_header = &port->cmd_list_base(CHBACmdHeader *)[i];
		cmd_header->prdt_len = 8; //TODO: reason

		if (blkdev.ahci64)
		{
			//'128-byte' align as per SATA spec, minus 1 since length is 1-based.
			addr = CAllocAligned(sizeof(CHBACmdTable) + sizeof(CPrdtEntry) * (cmd_header->prdt_len - 1), 128);
			cmd_header->cmd_table_base		 = addr.u32[0];
			cmd_header->cmd_table_base_upper = addr.u32[1];
		}
		else
		{
			cmd_header->cmd_table_base		 = CAllocAligned(sizeof(CHBACmdTable) + sizeof(CPrdtEntry) * 
																(cmd_header->prdt_len - 1), 128, Fs->code_heap);
			cmd_header->cmd_table_base_upper = 0;

		}
	}
	AHCIPortCmdStart(port);
	AHCIPortIdentify(bd);
}

U0 AHCIInit()
{
	CAHCIHba *hba;
	CAHCIPort *port;
	I64 i, bdf = PCIClassFind(PCIC_STORAGE << 16 | PCISC_AHCI << 8 + 1, 0); //0x010601, last byte prog_if, AHCI version 1.0

	if (bdf == -1)
	{
		"No AHCI controller found.\n";
		return;
	}

	hba = dev.uncached_alias + PCIReadU32(bdf.u8[2], bdf.u8[1], bdf.u8[0], PCIR_BASE5) & ~0x1F; //Last 4 bits not part of addr.

	Bts(&hba->ghc, AHCI_GHCf_HBA_RESET);
	while (Bt(&hba->ghc, AHCI_GHCf_HBA_RESET));

	Bts(&hba->ghc, AHCI_GHCf_AHCI_ENABLE);

	//Transferring ownership from BIOS if supported.
	if (Bt(&hba->caps_ext, AHCI_CAPSEXTf_BOH))
	{
		Bt(&hba->bohc, AHCI_BOHCf_OOS);
		while (Bt(&hba->bohc, AHCI_BOHCf_BOS));
		Sleep(25);
		if (Bt(&hba->bohc, AHCI_BOHCf_BB)) //if Bios Busy is still set after 25 mS, wait 2 seconds.
			Sleep(2000);
	}

	blkdev.ahci64		  = Bt(&hba->caps, AHCI_CAPSf_S64A);
	blkdev.cmd_slot_count = (hba->caps & 0x1F00) >> 8;
	blkdev.ahci_hba		  = hba;
//	blkdev.ahci64 = 0;

	"ahci64: %Z\n", blkdev.ahci64, "ST_FALSE_TRUE";

	for (i = 0; i < AHCI_MAX_PORTS; i++)
	{
		if (Bt(&hba->ports_implemented, i))
		{
			port = &hba->ports[i];
			if (port->signature == AHCI_PxSIG_ATA || port->signature == AHCI_PxSIG_ATAPI)
			{
				"Port on %d\n", i;
				if (port->signature == AHCI_PxSIG_ATAPI)
					Bts(&port->command, AHCI_PxCMDf_ATAPI);

				if (!AHCIPortIsIdle(port))
				{
					"Port not idle\n";
					AHCIPortCmdStop(port);
				}
				AHCIPortInit(BlkDevNextFreeSlot('G', BDT_ATA), port, i); //gay
			}
		}
	}
}

AHCIInit;