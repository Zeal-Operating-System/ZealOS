//AHCI driver, by V0x3L. (AHCI spec 1.3.1)

I64 AHCILBA48CapacityGet(U16 *id_record)
{//Get capacity of drive, in LBA blocks.
	D((id_record + 27));
	return	(id_record)(U64 *)[ATA_IDENT_LBA48_CAPACITY / 4] - 1;
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

	cmd_fis = &cmd_table->cmd_fis;
	MemSet(cmd_fis, 0, sizeof(CFisH2D));
	cmd_fis->type	 = FISt_H2D;
	if (port->signature == AHCI_PxSIG_ATAPI)
		cmd_fis->command = ATA_IDENTIFY_PACKET;
	else
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

U8 *AHCIBufferFix(CBlkDev *bd, U8 *user_buf, I64 buf_size, Bool write)
{
	if (!blkdev.ahci64)
	{
		if (user_buf + buf_size < U32_MAX)
		{	
			"user_buf is less than U32_MAX\n";
			return user_buf;
		}
		"Using internal buffer\n";
		Bts(&bd->flags, BDf_INTERNAL_BUF);
		Free(bd->prd_buf);
		bd->prd_buf = MAlloc(buf_size, Fs->code_heap);
		"Internal buffer: 0x%X\n", bd->prd_buf;
		if (write)
			MemCopy(bd->prd_buf, user_buf, buf_size);
		return bd->prd_buf;
	}
	Btr(&bd->flags, BDf_INTERNAL_BUF);
	return user_buf;
}

U0 AHCIAtaBlksRW(CBlkDev *bd, U8 *_buf, I64 blk, I64 count, Bool write)
{
	CHBACmdHeader *cmd_header;
	CHBACmdTable  *cmd_table;
	CFisH2D		  *cmd_fis;
	CAHCIPort	  *port = bd->ahci_port;
	I64			   buf_size, prdt_len, byte_count, _byte_count, i, slot = AHCIPortCmdSlotGet(port);
	U8			  *buf;

	if (count > AHCI_PRDT_MAX_BLOCKS)
	{
		ZenithErr("AHCI: blk count exceeds maximum of %d", AHCI_PRDT_MAX_BLOCKS);
		throw('AHCI');
	}
	if (slot < 0)
	{
		ZenithErr("No empty command slots!\n");
		throw('AHCI');
	}

	cmd_header = *&port->cmd_list_base(I64 *);
	cmd_header += slot; //Move up pointer to the slot we have in the command list
	MemSet(cmd_header, 0, sizeof(CHBACmdHeader));

	//setting Command FIS length, bits 4:0, takes size in U32s.
	cmd_header->desc = (cmd_header->desc & ~0x1F) + sizeof(CFisH2D) / sizeof(U32);
	//Set 'write' bit depending on 'write' val
	BEqual(&cmd_header->desc, AHCI_CH_DESCf_W, write);

	cmd_table = *&cmd_header->cmd_table_base(I64 *);
	MemSet(cmd_table, 0, sizeof(CHBACmdTable));

	//determine buf_size and prdt_len
	buf_size = count * BLK_SIZE;
	prdt_len = (buf_size - 1) >> AHCI_PRDT_BYTES_BITS + 1;

	if (prdt_len > AHCI_PRDT_MAX_LEN)
	{//This is probably never going to happen because we check the count beforehand.
		ZenithWarn("AHCI: Required PRDT length exceeds max of 32\n");
		prdt_len = AHCI_PRDT_MAX_LEN;
		buf_size = prdt_len * AHCI_PRDT_BYTES;
	}
	"prdt_len: %d\n", prdt_len;
	"bytes to work on: %X\n", buf_size;

	cmd_header->prdt_len = prdt_len;
	buf = AHCIBufferFix(bd, _buf, buf_size, write);
	"buf: %X\n", buf;

	if (!buf)
		throw('AHCI');

	_byte_count = buf_size;
	"count %d\n", _byte_count >> BLK_SIZE_BITS;
	for (i = 0; i < prdt_len; i++)
	{
		if (buf_size > AHCI_PRDT_BYTES)
			byte_count = AHCI_PRDT_BYTES;
		else
			byte_count = buf_size;

		"prdt[%d].data_base = 0x%X\n", i, buf(I64).u32[0];
		"prdt[%d].data_base_upper = 0x%X\n", i, buf(I64).u32[1];
		"prdt[%d].data_byte_count = 0x%X\n\n", i, byte_count - 1;

		cmd_table->prdt[i].data_base	   = buf(I64).u32[0];
		cmd_table->prdt[i].data_base_upper = buf(I64).u32[1];
		cmd_table->prdt[i].data_byte_count = byte_count - 1; //Zero-based value
		buf_size -= byte_count;
		buf += byte_count;
	}
	cmd_fis = &cmd_table->cmd_fis;
	MemSet(cmd_fis, 0, sizeof(CFisH2D));

	cmd_fis->type = FISt_H2D;
	Bts(&cmd_fis->desc, AHCI_CF_DESCf_C); //Set cmd_fis->c to 1 (Command)
	if (write)
		//Assuming support for LBA48. Boomers need need not apply.
		cmd_fis->command = ATA_WRITE_DMA_EXT;
	else
		cmd_fis->command = ATA_READ_DMA_EXT;

	cmd_fis->lba0 = blk.u8[0];
	cmd_fis->lba1 = blk.u8[1];
	cmd_fis->lba2 = blk.u8[2];
	cmd_fis->device = 1 << 6; //Required as per ATA8-ACS section 7.25.3
	cmd_fis->lba3 = blk.u8[3];
	cmd_fis->lba4 = blk.u8[4];
	cmd_fis->lba5 = blk.u8[5];
	cmd_fis->count = byte_count >> BLK_SIZE_BITS;

	if (!AHCIPortWait(port, tS + 2))
	{//2 second timeout for last command to complete.
		ZenithErr("AHCI: Port %d hung during %z!\n", bd->port_num, write, "read\0write");
		throw('AHCI');
	}

	Bts(&port->cmd_issue, slot); //Issue the command

	while (TRUE)
	{
		if (!Bt(&port->cmd_issue, slot))
			break;

		if (Bt(&port->interrupt_status, AHCI_PxIf_TFE)) //Task File Error
		{
oof:
			ZenithErr("AHCI: Disk %z error on port %d!\n", write, "read\0write", bd->port_num);
			throw('AHCI');
		}
	}
	//Second check for safety
	if (Bt(&port->interrupt_status, AHCI_PxIf_TFE))
		goto oof;

	if (!write) //writeback buffer if internal buffer was used.
		if (bd->flags & BDF_INTERNAL_BUF)
		{
			"Writeback internal buffer\n";
			MemCopy(buf, _buf, buf_size);
		}
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
	blkdev.ahci64 = 0;

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
#define BLKS 8195

U0 Test()
{
	U8 *buf = MAlloc(BLKS * BLK_SIZE, Fs->code_heap);
	U8 *buf2 = MAlloc(BLKS * BLK_SIZE);

	MemSet(buf, 0xFF, BLKS * BLK_SIZE);

	CBlkDev *bd = CAlloc(sizeof(CBlkDev));
	bd->ahci_port = &blkdev.ahci_hba->ports[0];

	AHCIAtaBlksRW(bd, buf, 0, BLKS, TRUE);
	AHCIAtaBlksRW(bd, buf2, 0, BLKS, FALSE);

	D(buf2 + (BLKS - 5) * BLK_SIZE, 5 * BLK_SIZE);
}
DocMax;
Test;