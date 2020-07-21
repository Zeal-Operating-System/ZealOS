//AHCI driver, by V0x3L. (AHCI spec 1.3.1)

I64 AHCILBA48CapacityGet(U16 *id_record)
{//Get capacity of drive, in LBA blocks.
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
{//Perform ATA_IDENTIFY command on ATA/ATAPI drive and store capacity and id record.
	CPortCmdHeader *cmd_header;
	CPortCmdTable  *cmd_table;
	CFisH2D		   *cmd_fis;
	U16			   *dev_id_record;
	CAHCIPort 	   *port = bd->ahci_port;
	I64			   *cmd_slot = AHCIPortCmdSlotGet(port);

	if (cmd_slot < 0)
	{
		ZenithErr("AHCI: No empty command slots on port %d!\n", bd->port_num);
		throw('AHCI');
	}
	//Using the code heap for this alloc to avoid dealing with a missing ahci64 capability.
	dev_id_record = CAlloc(512, Fs->code_heap);

	port->interrupt_status = port->interrupt_status; //TODO: Why?

	cmd_header = *&port->cmd_list_base(I64 *); //Read cmd_list_base and cmd_list_base_upper as one full I64 value.
	cmd_header += cmd_slot; //Move up pointer to the slot we have in the command list.

	//Write Command FIS Length (CFL, a fixed size) in bits 4:0 of the desc. Takes size in U32s.
	cmd_header->desc = (cmd_header->desc & ~0x1F) + sizeof(CFisH2D) / sizeof(U32);
	Btr(&cmd_header->desc, AHCI_CH_DESCf_W); //Disable 'Write' bit.

	cmd_table = *&cmd_header->cmd_table_base(I64 *); //Read cmd_table_base and cmd_table_base_upper as one full I64 value.
	MemSet(cmd_table, 0, sizeof(CPortCmdTable));
	//Set up PRD
	cmd_table->prdt[0].data_base	   = dev_id_record;
	cmd_table->prdt[0].data_base_upper = 0;
	cmd_table->prdt[0].data_byte_count = 512 - 1; //Zero-based value
	cmd_header->prdt_len = 1; //1 PRD, as described above, which contains the address to put the ID record.

	cmd_fis = &cmd_table->cmd_fis;
	MemSet(cmd_fis, 0, sizeof(CFisH2D));
	cmd_fis->type = FISt_H2D;
	Bts(&cmd_fis->desc, AHCI_CF_DESCf_C); //Set Command bit in H2D FIS.

	if (port->signature == AHCI_PxSIG_ATAPI)
		cmd_fis->command = ATA_IDENTIFY_PACKET;
	else
		cmd_fis->command = ATA_IDENTIFY;

	cmd_fis->device  = 0; //No bits need to be set in the device register.

	if (!AHCIPortWait(port, tS + 2))
	{
		ZenithErr("AHCI: Port %d hung while attempting IDENTIFY!\n", bd->port_num);
		throw('AHCI');
	}

	Bts(&port->cmd_issue, cmd_slot); //Issue the command

	while (TRUE)
	{
		if (!Bt(&port->cmd_issue, cmd_slot)) //When command has been processed
			break;

		if (Bt(&port->interrupt_status, AHCI_PxIf_TFE)) //Task File Error ($LK,"ATAS_ERR",A="MN:ATAS_ERR"$)
		{
id_error:
			ZenithErr("AHCI: Port %d: Identify command failed!\n", bd->port_num);
			throw('AHCI');
		}
	}
	if (Bt(&port->interrupt_status, AHCI_PxIf_TFE)) //Second safety check
		goto id_error;

	bd->max_blk = AHCILBA48CapacityGet(dev_id_record);
	"%X\n", bd->max_blk;
	Free(bd->dev_id_record);
	bd->dev_id_record = dev_id_record;
}

U8 *AHCIBufferFix(CBlkDev *bd, U8 *user_buf, I64 buf_size, Bool write)
{//Make sure buffer is accessible by AHCI HBA controller.
//Controller requires a U16-aligned buffer, and, if not 64-bit capable (ahci64),
//it requires the buffer to be in the 32-bit address space.
//MAlloc provides U64-aligned addresses, and can allocate in the code heap ( <4GB ).
//In the case of an inadequate buffer address being passed in, we will use a MAlloced internal buffer.
	if (!blkdev.ahci64 && (user_buf + buf_size > U32_MAX || user_buf & 1))
	{//if the buffer is not within the 32-bit range or not U16-aligned
		"fixing buffer to be aligned and under 32-bit range\n";
		Free(bd->prd_buf);
		bd->prd_buf = MAlloc(buf_size, Fs->code_heap);
		goto fixed;
	}
	if (user_buf & 1)
	{//if buffer is not U16 aligned (ahci64 means buf can be anywhere in normal high memory)
		"64-bit capable buffer not aligned, fixing...\n";
		Free(bd->prd_buf);
		bd->prd_buf = MAlloc(buf_size);
		goto fixed;
	}
	Btr(&bd->flags, BDf_INTERNAL_BUF);
	return user_buf;

fixed:
	"Using internal buffer: 0x%X\n", bd->prd_buf;
	Bts(&bd->flags, BDf_INTERNAL_BUF);
	if (write)
		MemCopy(bd->prd_buf, user_buf, buf_size);
	return bd->prd_buf;
}

I64 AHCIAtaBlksRW(CBlkDev *bd, U8 *buf, I64 blk, I64 count, Bool write)
{//ATA Disk RW Blocks. Returns number of bytes transferred between system and device (should match 'count * BLK_SIZE').
	CPortCmdHeader *cmd_header;
	CPortCmdTable  *cmd_table;
	CFisH2D		   *cmd_fis;
	CAHCIPort	   *port = bd->ahci_port;
	I64			    buf_size, buf_size2, byte_count, prdt_len, i, cmd_slot = AHCIPortCmdSlotGet(port);
	U8			   *internal_buf;

	if (count < 1) return 0;

	if (cmd_slot < 0)
	{
		ZenithErr("AHCI: No empty command slots on port %d!\n", bd->port_num);
		throw('AHCI');
	}
	if (count > AHCI_PRDT_MAX_BLOCKS)
	{//There will be wrappers for reading and writing which will handle block sizes greater than MAX_BLOCKS.
		ZenithErr("AHCI: Blk count %d exceeds max allowed in one command (%d)", count, AHCI_PRDT_MAX_BLOCKS);
		throw('AHCI');
	}
	//Obtain command header and zero it.
	cmd_header = *&port->cmd_list_base(I64 *); //Read cmd_list_base and adjacent cmd_list_base_upper as one full I64 value.
	cmd_header += cmd_slot; //Move up pointer to the slot we have in the command list.
	MemSet(cmd_header, 0, sizeof(CPortCmdHeader));

	//Write Command FIS Length (CFL, a fixed size) in bits 4:0 of the desc. Takes size in U32s.
	cmd_header->desc = (cmd_header->desc & ~0x1F) + sizeof(CFisH2D) / sizeof(U32);
	//Set 'Write' depending on 'write' parameter.
	BEqual(cmd_header->desc, AHCI_CH_DESCf_W, write);

	//Obtain command table and zero it.
	cmd_table = *&cmd_header->cmd_table_base(I64 *); //Read cmd_table_base and adjacent cmd_table_base_upper as one full I64 value.
	MemSet(cmd_table, 0, sizeof(CPortCmdTable));

	//Determine buffer size and PRDT length.
	buf_size = buf_size2 = count * BLK_SIZE;
	prdt_len = (buf_size - 1) / AHCI_PRD_MAX_BYTES + 1;

	"PRDT Length:\t%d\n", prdt_len;
	"Count:\t\t\t%d\n", count;
	"Buffer size:\t%X\n", buf_size;

	cmd_header->prdt_len = prdt_len; //Set PRDTL in cmd header.

	internal_buf = AHCIBufferFix(bd, buf, buf_size, write); 
	"Buffer:\t\t\t0x%X\n", internal_buf;

	if (!buf) throw('AHCI'); //Will probably never happen.

	//Create 'prdt_len' amount of PRD entries
	for (i = 0; i < prdt_len; i++)
	{//Use max PRD size until the remaining buffer is smaller than max size.
		if (buf_size2 > AHCI_PRD_MAX_BYTES) 
			byte_count = AHCI_PRD_MAX_BYTES;
		else
			byte_count = buf_size2;

		"prdt[%d].data_base_addr  = 0x%X\n"  , i, internal_buf;
		"prdt[%d].data_byte_count = 0x%X\n\n", i, byte_count;

		cmd_table->prdt[i].data_base	   = internal_buf(I64).u32[0];
		cmd_table->prdt[i].data_base_upper = internal_buf(I64).u32[1];
		cmd_table->prdt[i].data_byte_count = byte_count - 1; //Zero-based value
		buf_size2 -= byte_count;
		internal_buf += byte_count;		
	}
	//Obtain address of command FIS (CFIS) and zero it.
	cmd_fis = &cmd_table->cmd_fis;
	MemSet(cmd_fis, 0, sizeof(CFisH2D));

	cmd_fis->type = FISt_H2D; 
	Bts(&cmd_fis->desc, AHCI_CF_DESCf_C); //Set Command bit in H2D FIS 

	if (write) //Assume support for LBA48. This is 2020.
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
	cmd_fis->count = count;

	if (!AHCIPortWait(port, tS + 2))
	{//2 second timeout for last command to complete.
		ZenithErr("AHCI: Port %d hung during %z!\n", bd->port_num, write, "read\0write");
		throw('AHCI');
	}

	Bts(&port->cmd_issue, cmd_slot); //Issue the command

	while (TRUE)
	{
		if (!Bt(&port->cmd_issue, cmd_slot)) //when command has been processed
			break;

		if (Bt(&port->interrupt_status, AHCI_PxIf_TFE)) //Task File Error ($LK,"ATAS_ERR",A="MN:ATAS_ERR"$)
		{
rw_error:	ZenithErr("AHCI: Disk %z error on port %d!\n", write, "read\0write", bd->port_num);
			throw('AHCI');
		}
	}
	//Second check for safety
	if (Bt(&port->interrupt_status, AHCI_PxIf_TFE))
		goto rw_error;

	if (!write) //writeback internal_buf to parameter buf if one was created
		if (bd->flags & BDF_INTERNAL_BUF)
		{
			"Writeback internal buffer\n";
			//internal_buf was consumed while creating PRD entries so we push it back
			MemCopy(buf, internal_buf - buf_size, buf_size); 
		}
	return cmd_header->prd_byte_count;
}

U0 AHCIPortInit(CBlkDev *bd, CAHCIPort *port, I64 port_num)
{
	CPortCmdHeader *cmd_header;
	I64 i, addr = 0;

	bd->ahci_port = port;
	bd->port_num = port_num;

	AHCIPortReset(port);
	AHCIPortCmdStart(port);

	//Spin up, power on device. If the capability isn't suppport the bits will be read-only and this won't do anything.
	port->command |= AHCI_PxCMDF_POD | AHCI_PxCMDF_SUD;
	Sleep(100); //Why?
	AHCIPortCmdStop(port);

	if (blkdev.ahci64)
	{
		//'1K-byte' align as per SATA spec.
		addr = CAllocAligned(sizeof(CPortCmdHeader) * blkdev.cmd_slot_count, 1024);
		port->cmd_list_base		  = addr.u32[0];
		port->cmd_list_base_upper = addr.u32[1];

		//Alloc where received FISes will be copied to. '256-byte' align as per spec.
		addr = CAllocAligned(sizeof(CFisReceived), 256);
		port->fis_base		 = addr.u32[0];
		port->fis_base_upper = addr.u32[1];
	}
	else
	{//Code Heap is always under 4 GB in address space, so we can use that instead.
		port->cmd_list_base		  = CAllocAligned(sizeof(CPortCmdHeader) * blkdev.cmd_slot_count, 1024, Fs->code_heap);
		port->cmd_list_base_upper = 0;

		port->fis_base		 = CAllocAligned(sizeof(CFisReceived), 256, Fs->code_heap);
		port->fis_base_upper = 0;
	}

	for (i = 0; i < blkdev.cmd_slot_count; i++)
	{
		cmd_header = &port->cmd_list_base(CPortCmdHeader *)[i];

		if (blkdev.ahci64)
		{
			//'128-byte' align as per SATA spec, minus 1 since length is 1-based.
			addr = CAllocAligned(sizeof(CPortCmdTable) + sizeof(CPrdtEntry) * (AHCI_PRDT_MAX_LEN - 1), 128);
			cmd_header->cmd_table_base		 = addr.u32[0];
			cmd_header->cmd_table_base_upper = addr.u32[1];
		}
		else
		{
			cmd_header->cmd_table_base		 = CAllocAligned(sizeof(CPortCmdTable) + sizeof(CPrdtEntry) * 
																(AHCI_PRDT_MAX_LEN - 1), 128, Fs->code_heap);
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

	hba = dev.uncached_alias + PCIReadU32(bdf.u8[2], bdf.u8[1], bdf.u8[0], PCIR_BASE5) & ~0x1F; //Last 4 bits not part of address.

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
#define BLKS 20000

U0 Test()
{
	U8 *buf = MAlloc(BLKS * BLK_SIZE);
	U8 *buf2 = MAlloc(BLKS * BLK_SIZE);

	MemSet(buf, 0xFF, BLKS * BLK_SIZE);

	CBlkDev *bd = CAlloc(sizeof(CBlkDev));
	bd->ahci_port = &blkdev.ahci_hba->ports[0];

	"$$PURPLE$$Byte count: %X$$FG$$\n", AHCIAtaBlksRW(bd, buf,  0, BLKS, TRUE); //write
	"$$PURPLE$$Byte count: %X$$FG$$\n", AHCIAtaBlksRW(bd, buf2, 0, BLKS, FALSE);//read

	D(buf2 + (BLKS - 5) * BLK_SIZE, 5 * BLK_SIZE); //Dump last 5 blocks
	Free(buf);
	Free(buf2);
}
DocMax;
Test;