I64 AHCILBA48CapacityGet(U16 *id_record)
{//Get capacity of drive, in LBA blocks.
//Capacity is stored in a U64, so we take the shortcut
//and access the U16-indexed ID record as U64 indexed. Zero-based value.
	return (id_record)(U64 *)[ATA_IDENT_LBA48_CAPACITY / 4] - 1;
}

I64 AHCIPortCmdSlotGet(I64 port_num)
{//Get next free command slot in port; if none, throw error.
	I64			 i;
	CAHCIPort	*port	= &blkdev.ahci_hba->ports[port_num];
	U32			 slots	= port->sata_active | port->cmd_issue;

	for (i = 0; i < blkdev.cmd_slot_count; i++)
	{
		if (!(slots & 1))
			return i;

		slots >>= 1;
	}

	ZenithErr("AHCI: No empty command slots on port %d!\n", port_num);
	throw('AHCI');
}

Bool AHCIPortIsIdle(I64 port_num)
{//Check if the command engine is running on port.
	return !(blkdev.ahci_hba->ports[port_num].command & (AHCI_PxCMDF_ST | AHCI_PxCMDF_CR | AHCI_PxCMDF_FR | AHCI_PxCMDF_FRE));
}

U0 AHCIPortCmdStop(I64 port_num)
{//Stop command engine on port.
	CAHCIPort *port = &blkdev.ahci_hba->ports[port_num];

	Btr(&port->command, AHCI_PxCMDf_ST);
	Btr(&port->command, AHCI_PxCMDf_FRE);

	while (Bt(&port->command, AHCI_PxCMDf_CR) || Bt(&port->command, AHCI_PxCMDf_FR));
}

U0 AHCIPortCmdStart(I64 port_num)
{//Start command engine on port.
	CAHCIPort *port = &blkdev.ahci_hba->ports[port_num];

	while (Bt(&port->command, AHCI_PxCMDf_CR));

	Bts(&port->command, AHCI_PxCMDf_FRE);
	Bts(&port->command, AHCI_PxCMDf_ST);
}

Bool AHCIPortWait(I64 port_num, F64 timeout, Bool throwing=TRUE)
{//Wait until DRQ & BSY are clear in port task file.
	CAHCIPort *port = &blkdev.ahci_hba->ports[port_num];

	do
	{
		if (!(port->task_file_data & (ATAS_DRQ | ATAS_BSY)))
			return TRUE;
		Yield; // don't hang OS
	}
	while (timeout > tS);

	if (throwing)
	{	ZenithErr("AHCI: Port %d hung.\n", port_num);
		throw('AHCI');
	}

	return FALSE;
}

U0 AHCIPortReset(I64 port_num)
{//Software reset of port. Port command engine must be started after this.
 //If port is not responsive we do a full reset.
	CAHCIPort *port = &blkdev.ahci_hba->ports[port_num];

	AHCIPortCmdStop(port_num);

	port->interrupt_status = port->interrupt_status; //Acknowledge all interrupt statuses.

	if (!AHCIPortWait(port_num, tS + 1))
	{//Perform 'more intrusive' HBA<->Port comm reset (sec. 10.4.2 of spec).
		port->sata_ctrl = AHCI_PxSCTLF_DET_INIT;
		Sleep(2); //Spec says 1 millisecond
		port->sata_ctrl = 0;
	}

	while (port->sata_status & 0xF != AHCI_PxSSTSF_DET_PRESENT);

	port->sata_error = ~0; //Write all 1s to sata error register.
}

CPortCmdHeader *AHCIPortActiveHeaderGet(I64 port_num, I64 cmd_slot)
{//Get current command slot header on port.
	CAHCIPort		*port = &blkdev.ahci_hba->ports[port_num];
	CPortCmdHeader	*cmd_header = port->cmd_list_base;

	return cmd_header + cmd_slot; //Move up pointer to the slot we have in the command list.
}

U0 AHCIPortCmdWait(I64 port_num, I64 cmd_slot)
{//Wait on command completion after command issue, and double check any error.
	CAHCIPort *port = &blkdev.ahci_hba->ports[port_num];

	while (TRUE)
	{
		if (!Bt(&port->cmd_issue, cmd_slot)) //When command has been processed
			break;

		if (Bt(&port->interrupt_status, AHCI_PxIf_TFE)) //Task File Error ($LK,"ATAS_ERR",A="MN:ATAS_ERR"$)
		{
error:
			ZenithErr("AHCI: Port %d: Command failed!\n", port_num);
			throw('AHCI');
		}

		Yield; // don't hang OS
	}

	if (Bt(&port->interrupt_status, AHCI_PxIf_TFE)) //Second safety check
		goto error;
}

I64 AHCIAtapiCapacityGet(CBlkDev *bd)
{
	CPortCmdTable	*cmd_table;
	CFisH2D			*cmd_fis;
	CAHCIPort		*port		= bd->ahci_port;
	I64				 cmd_slot	= AHCIPortCmdSlotGet(bd->port_num);
	CPortCmdHeader	*cmd_header	= AHCIPortActiveHeaderGet(bd->port_num, cmd_slot);
	U32				*buf;

	if (port->signature != AHCI_PxSIG_ATAPI)
	{
		ZenithErr("AHCI: Drive is not an ATAPI drive!\n");
		throw('AHCI');	
	}

	buf = CAlloc(8, Fs->code_heap);

	Bts(&cmd_header->desc, AHCI_CH_DESCf_A);

	cmd_table = cmd_header->cmd_table_base;
	MemSet(cmd_table, 0, sizeof(CPortCmdTable));

	//Set up single PRD
	cmd_table->prdt[0].data_base	   = buf;
	cmd_table->prdt[0].data_byte_count = DVD_BLK_SIZE - 1; //Zero-based value
	cmd_header->prdt_len = 1;

	cmd_fis	= &cmd_table->cmd_fis;

	cmd_fis->type		= FISt_H2D;
	Bts(&cmd_fis->desc, AHCI_CF_DESCf_C); //Set Command bit in H2D FIS.
	cmd_fis->command	= ATA_PACKET;
	cmd_table->acmd[0]	= ATAPI_READ_CAPACITY >> 8;

	AHCIPortWait(bd->port_num, tS + 2);
	Bts(&port->cmd_issue, cmd_slot); //Issue the command.

	try
		AHCIPortCmdWait(bd->port_num, cmd_slot);
	catch
	{
		Fs->catch_except = TRUE;
		return 0;
	}

	return EndianU32(buf[0]);
}

Bool AHCIAtapiSeek(CBlkDev *bd, I64 blk)
{
	CPortCmdTable	*cmd_table;
	CFisH2D			*cmd_fis;
	CAHCIPort		*port		= bd->ahci_port;
	I64				 cmd_slot	= AHCIPortCmdSlotGet(bd->port_num);
	CPortCmdHeader	*cmd_header	= AHCIPortActiveHeaderGet(bd->port_num, cmd_slot);

	if (port->signature != AHCI_PxSIG_ATAPI)
	{
		ZenithErr("AHCI: Drive is not an ATAPI drive!\n");
		throw('AHCI');	
	}

	Bts(&cmd_header->desc, AHCI_CH_DESCf_A);

	cmd_table = cmd_header->cmd_table_base;
	MemSet(cmd_table, 0, sizeof(CPortCmdTable));

	cmd_fis	= &cmd_table->cmd_fis;

	cmd_fis->type		= FISt_H2D;
	Bts(&cmd_fis->desc, AHCI_CF_DESCf_C); //Set Command bit in H2D FIS.
	cmd_fis->command	= ATA_PACKET;
	cmd_table->acmd[0]	= ATAPI_SEEK >> 8;
	cmd_table->acmd[2]	= blk.u8[4];
	cmd_table->acmd[3]	= blk.u8[3];
	cmd_table->acmd[4]	= blk.u8[2];
	cmd_table->acmd[5]	= blk.u8[1];

	AHCIPortWait(bd->port_num, tS + 2);
	Bts(&port->cmd_issue, cmd_slot); //Issue the command.

	try
		AHCIPortCmdWait(bd->port_num, cmd_slot);
	catch
	{
		Fs->catch_except = TRUE;
		return FALSE;
	}

	return TRUE;
}

Bool AHCIAtapiStartStop(CBlkDev *bd, Bool start)
{
	CPortCmdTable	*cmd_table;
	CFisH2D			*cmd_fis;
	CAHCIPort		*port		= bd->ahci_port;
	I64				 cmd_slot	= AHCIPortCmdSlotGet(bd->port_num);
	CPortCmdHeader	*cmd_header	= AHCIPortActiveHeaderGet(bd->port_num, cmd_slot);

	if (port->signature != AHCI_PxSIG_ATAPI)
	{
		ZenithErr("AHCI: Drive is not an ATAPI drive!\n");
		throw('AHCI');	
	}

	Bts(&cmd_header->desc, AHCI_CH_DESCf_A);

	cmd_table = cmd_header->cmd_table_base;
	MemSet(cmd_table, 0, sizeof(CPortCmdTable));

	cmd_fis	= &cmd_table->cmd_fis;

	cmd_fis->type		= FISt_H2D;
	Bts(&cmd_fis->desc, AHCI_CF_DESCf_C); //Set Command bit in H2D FIS.
	cmd_fis->command	= ATA_PACKET;
	cmd_table->acmd[0]	= ATAPI_START_STOP_UNIT >> 8;
	cmd_table->acmd[4]	= start;

	AHCIPortWait(bd->port_num, tS + 2);
	Bts(&port->cmd_issue, cmd_slot); //Issue the command.

	try
		AHCIPortCmdWait(bd->port_num, cmd_slot);
	catch
	{
		Fs->catch_except = TRUE;
		return FALSE;
	}

	return TRUE;
}

U0 AHCIPortIdentify(CBlkDev *bd)
{//Perform ATA_IDENTIFY command on ATA/ATAPI drive and store capacity and id record.
	CPortCmdTable	*cmd_table;
	CFisH2D			*cmd_fis;
	CAHCIPort		*port		= bd->ahci_port;
	I64				 cmd_slot	= AHCIPortCmdSlotGet(bd->port_num);
	CPortCmdHeader	*cmd_header	= AHCIPortActiveHeaderGet(bd->port_num, cmd_slot);
	U16				*dev_id_record;

	port->interrupt_status = port->interrupt_status; //TODO: Why?

	//Using the code heap for this alloc to stay under 32-bit address space.
	dev_id_record = CAlloc(512, Fs->code_heap);

	cmd_table = cmd_header->cmd_table_base;
	MemSet(cmd_table, 0, sizeof(CPortCmdTable));

	//Set up single PRD
	cmd_table->prdt[0].data_base	   = dev_id_record;
	cmd_table->prdt[0].data_base_upper = 0;
	cmd_table->prdt[0].data_byte_count = 512 - 1; //Zero-based value
	cmd_header->prdt_len = 1; //1 PRD, as described above, which contains the address to put the ID record.

	//Setup command FIS
	cmd_fis = &cmd_table->cmd_fis;

	cmd_fis->type = FISt_H2D;
	Bts(&cmd_fis->desc, AHCI_CF_DESCf_C); //Set Command bit in H2D FIS.

	if (port->signature == AHCI_PxSIG_ATAPI)
		cmd_fis->command = ATA_IDENTIFY_PACKET;
	else
		cmd_fis->command = ATA_IDENTIFY;

	cmd_fis->device  = 0; //No bits need to be set in the device register.

	//Wait on previous command to complete.
	AHCIPortWait(bd->port_num, tS + 2);

	Bts(&port->cmd_issue, cmd_slot); //Issue the command.
	AHCIPortCmdWait(bd->port_num, cmd_slot);

	Free(bd->dev_id_record);
	bd->dev_id_record = dev_id_record;

	if (port->signature == AHCI_PxSIG_ATA)
	{
		bd->max_blk = AHCILBA48CapacityGet(dev_id_record);
		"MAX BLOCK %d, disk size %d MiB\n", bd->max_blk, bd->max_blk * BLK_SIZE / 1024 / 1024; 
	}
	else
	{
		bd->max_blk = AHCIAtapiCapacityGet(bd);
		"MAX BLOCK %d, disk size %d MiB\n", bd->max_blk, bd->max_blk * DVD_BLK_SIZE / 1024 / 1024; 
	}
}

U8 *AHCIBufferAlign(CBlkDev *bd, U8 *user_buf, I64 buf_size, Bool write)
{//Make sure buffer is accessible by HBA controller.
//Controller requires a U16 aligned buffer and in 32-bit address space (We are not using 64-bit capabilities).
//MAlloc provides U64-aligned addresses, and can allocate in the code heap ( <4GB ).
//In the case of an inadequate buffer address being passed in, we will use a MAlloced internal buffer.
	if(user_buf + buf_size > U32_MAX || user_buf & 1)
	{//if the buffer is not within 32-bit address space or not U16-aligned
//		"Aligning buffer under 32-bit range\n";

		Free(bd->prd_buf);
		bd->prd_buf = MAlloc(buf_size, zenith_task->code_heap);

		Bts(&bd->flags, BDf_INTERNAL_BUF);

		if (write)
			MemCopy(bd->prd_buf, user_buf, buf_size);

		return bd->prd_buf;
	}
	Btr(&bd->flags, BDF_INTERNAL_BUF);

	return user_buf;
}

I64 AHCIAtaBlksRW(CBlkDev *bd, U8 *buf, I64 blk, I64 count, Bool write)
{//Read/Write ATA disk blocks. Returns number of bytes transferred between system and disk.
//Don't use this, use the AHCIAtaBlksRead and AHCIAtaBlksWrite functions.
	CPortCmdTable  *cmd_table;
	CFisH2D		   *cmd_fis;
	CAHCIPort      *port = bd->ahci_port;
	I64 i, buf_size, buf_size_tmp, byte_count, prdt_len, cmd_slot = AHCIPortCmdSlotGet(bd->port_num);
	CPortCmdHeader *cmd_header = AHCIPortActiveHeaderGet(bd->port_num, cmd_slot);
	U8             *internal_buf_tmp, *internal_buf;
	Bool			unlock;

	if (port->signature != AHCI_PxSIG_ATA)
	{
		ZenithErr("AHCI: Drive is not an ATA drive!\n");
		throw('AHCI');
	}

	if (count < 1) return 0;
	if (count > AHCI_PRDT_MAX_BLOCKS)
	{
		ZenithErr("AHCI: Block count %d max allowed in one command (%d)", count, AHCI_PRDT_MAX_BLOCKS);
		throw('AHCI');
	}

	unlock = BlkDevLock(bd);

	//Determine buffer size and PRDT length.
	buf_size = buf_size_tmp = count * BLK_SIZE;
	prdt_len = (buf_size - 1) / AHCI_PRD_MAX_BYTES + 1;

//	"PRDT Length:\t%d\n", prdt_len;
//	"Count:\t\t\t%d\n", count;
//	"Buffer size:\t%X\n", buf_size;

	cmd_header->prdt_len = prdt_len; //Set PRD table length in cmd header.
	//Set 'write' bit depending on 'write' argument.
	BEqual(&cmd_header->desc, AHCI_CH_DESCf_W, write);

	internal_buf = internal_buf_tmp = AHCIBufferAlign(bd, buf, buf_size, write);
//	"Buffer:\t\t\t0x%X\n", internal_buf;

	if (!internal_buf) throw('AHCI'); //Will probably never happen.

	//Obtain command table and zero it. This contains the command FIS and the PRDT.
	cmd_table = cmd_header->cmd_table_base;
	MemSet(cmd_table, 0, sizeof(CPortCmdTable));
	
	//Create 'prdt_len' amount of PRD entries in the command table
	for (i = 0; i < prdt_len; i++)
	{//Use max PRD size until the remaining buffer is smaller than max size.
		if (buf_size_tmp > AHCI_PRD_MAX_BYTES)
			byte_count = AHCI_PRD_MAX_BYTES;
		else
			byte_count = buf_size_tmp;

//		"prdt[%d].data_base_addr  = 0x%X\n"  , i, internal_buf_tmp;
//		"prdt[%d].data_byte_count = 0x%X\n\n", i, byte_count;

		cmd_table->prdt[i].data_base = internal_buf_tmp;
		cmd_table->prdt[i].data_byte_count = byte_count - 1; //Zero-based value
		buf_size_tmp -= byte_count;
		internal_buf_tmp += byte_count;
	}
	//Setup the command FIS.
	cmd_fis = &cmd_table->cmd_fis;

	cmd_fis->type = FISt_H2D;
	Bts(&cmd_fis->desc, AHCI_CF_DESCf_C); //Set Command bit in H2D FIS

	if (write) //Assumed support for LBA48.
		cmd_fis->command = ATA_WRITE_DMA_EXT;
	else
		cmd_fis->command = ATA_READ_DMA_EXT;

	//Fill in the rest of the command FIS.
	cmd_fis->lba0	= blk.u8[0];
	cmd_fis->lba1	= blk.u8[1];
	cmd_fis->lba2	= blk.u8[2];
	cmd_fis->device	= 1 << 6; //Required as per ATA8-ACS section 7.25.3
	cmd_fis->lba3	= blk.u8[3];
	cmd_fis->lba4	= blk.u8[4];
	cmd_fis->lba5	= blk.u8[5];
	cmd_fis->count	= count;

	//Wait on previous command to complete.
	AHCIPortWait(bd->port_num, tS + 2);
	//Issue the command.
	Bts(&port->cmd_issue, cmd_slot);
	//Wait on command to finish.
	AHCIPortCmdWait(bd->port_num, cmd_slot);

	if (!write) //If internal_buf was created it back to argument buf.
		if (bd->flags & BDF_INTERNAL_BUF)
		{
//			"Writing back internal buffer\n";
			MemCopy(buf, internal_buf, buf_size);
		}

	if (unlock)
		BlkDevUnlock(bd);

	return cmd_header->prd_byte_count;
}

I64 AHCIAtaBlksRead(CBlkDev *bd, U8 *buf, I64 blk, I64 count)
{//Read 'blk' amount of blocks from AHCI disk device. Returns num of bytes transferred between disk and memory.
	I64 byte_count = 0;
	if (!count)
		return 0;
	if (count <= AHCI_PRDT_MAX_BLOCKS)
	{
//		"$$GREEN$$READ less than MAX_BLOCKS$$FG$$\n";
		return AHCIAtaBlksRW(bd, buf, blk, count, FALSE);
	}
	else
	{
//		"$$GREEN$$READ greater than MAX_BLOCKS\n";
//		"read count: %d\n$$FG$$", count;
		while (count > AHCI_PRDT_MAX_BLOCKS)
		{
			byte_count += AHCIAtaBlksRW(bd, buf, blk, AHCI_PRDT_MAX_BLOCKS, FALSE);
			count -= AHCI_PRDT_MAX_BLOCKS;
			blk += AHCI_PRDT_MAX_BLOCKS;
			buf += AHCI_PRDT_MAX_BLOCKS * BLK_SIZE;
//			"$$GREEN$$read count: %d\n$$FG$$", count;
		}$ER$
		byte_count += AHCIAtaBlksRW(bd, buf, blk, count, FALSE);
	}

	blkdev.read_count += (count * bd->blk_size) >> BLK_SIZE_BITS;

	return byte_count;
}

I64 AHCIAtaBlksWrite(CBlkDev *bd, U8 *buf, I64 blk, I64 count)
{//Write 'blk' amount of blocks to AHCI disk device. Returns num of bytes transferred between memory and disk.
	I64  byte_count = 0;

	if (!count)
		return 0;
	if (count <= AHCI_PRDT_MAX_BLOCKS)
	{
//		"$$GREEN$$WRITE less than MAX_BLOCKS$$FG$$\n";
		return AHCIAtaBlksRW(bd, buf, blk, count, TRUE);
	}
	else
	{
//		"$$GREEN$$WRITE greater than MAX_BLOCKS\n";
//		"write count: %d$$FG$$\n", count;
		while (count > AHCI_PRDT_MAX_BLOCKS)
		{
			byte_count += AHCIAtaBlksRW(bd, buf, blk, AHCI_PRDT_MAX_BLOCKS, TRUE);
			count -= AHCI_PRDT_MAX_BLOCKS;
			blk += AHCI_PRDT_MAX_BLOCKS;
			buf += AHCI_PRDT_MAX_BLOCKS * BLK_SIZE;
//			"$$GREEN$$write count: %d\n$$FG$$\n", count;
		}
		byte_count += AHCIAtaBlksRW(bd, buf, blk, count, TRUE);
	}

	return byte_count;
}

I64 AHCIAtapiBlksRead(CBlkDev *bd, U8 *buf, I64 blk, I64 count, Bool lock=TRUE)
{//Read 'blk' amount of blocks from from AHCI ATAPI device. Returns num of bytes transferred.
	CPortCmdTable	*cmd_table;
	CFisH2D			*cmd_fis;
	CAHCIPort		*port = bd->ahci_port;
	I64				 i, byte_count, buf_size, buf_size_tmp, prdt_len, cmd_slot = AHCIPortCmdSlotGet(bd->port_num);
	CPortCmdHeader	*cmd_header = AHCIPortActiveHeaderGet(bd->port_num, cmd_slot);
	U8				*internal_buf, *internal_buf_tmp;
	CAtapiReadCmd	 read_cmd;
	Bool			 unlock;

	if (port->signature != AHCI_PxSIG_ATAPI)
	{
		ZenithErr("AHCI: Drive is not an ATAPI drive!\n");
		throw('AHCI');
	}
	if (count < 1)
		return 0;

	if (lock)
		unlock = BlkDevLock(bd);

	buf_size = buf_size_tmp = count * DVD_BLK_SIZE;
	prdt_len = (buf_size - 1) / AHCI_PRD_MAX_BYTES + 1;

//	"PRDT Length:\t%d\n", prdt_len;
//	"Count:\t\t\t%d\n", count;
//	"Buffer size:\t%X\n", buf_size;

	cmd_header->prdt_len = prdt_len;

	internal_buf = internal_buf_tmp = AHCIBufferAlign(bd, buf, buf_size, FALSE);
//	"Buffer:\t\t\t0x%X\n", internal_buf;

	if (!internal_buf) throw('AHCI');

	Bts(&cmd_header->desc, AHCI_CH_DESCf_A); //Set ATAPI flag in command header

	cmd_table = cmd_header->cmd_table_base;
	MemSet(cmd_table, 0, sizeof(CPortCmdTable));

	for (i = 0; i < prdt_len; i++)
	{
		if (buf_size_tmp > AHCI_PRD_MAX_BYTES) //$BK,1$SHOULD PROBABLY BE ATAPI MAX BYTES$BK,0$
			byte_count = AHCI_PRD_MAX_BYTES;
		else
			byte_count = buf_size_tmp;

//		"prdt[%d].data_base_addr  = 0x%X\n"  , i, internal_buf_tmp;
//		"prdt[%d].data_byte_count = 0x%X\n\n", i, byte_count;
		cmd_table->prdt[i].data_base = internal_buf_tmp;
		cmd_table->prdt[i].data_byte_count = byte_count - 1; //Zero-based value

		buf_size_tmp	 -= byte_count;
		internal_buf_tmp += byte_count;
	}

	cmd_fis = &cmd_table->cmd_fis;
	MemSet(cmd_fis, 0, sizeof(CFisH2D));

	cmd_fis->type = FISt_H2D;
	Bts(&cmd_fis->desc, AHCI_CF_DESCf_C); //Set Command bit in H2D FIS 

	cmd_fis->feature_low = 1; //Necessary?
	cmd_fis->command	 = ATA_PACKET;

	MemSet(&read_cmd, 0, sizeof(CAtapiReadCmd));
	read_cmd.command = ATAPI_READ >> 8; //$BK,1$FIX$BK,0$
	read_cmd.lba	 = EndianU32(blk);
	read_cmd.count	 = EndianU32(count);
	MemCopy(&cmd_table->acmd, &read_cmd, 16);
	
	cmd_fis->count = count; //Necessary?

	AHCIPortWait(bd->port_num, tS + 2);
	
	Bts(&port->cmd_issue, cmd_slot);
//	Sleep(1000);
	AHCIPortCmdWait(bd->port_num, cmd_slot);
	
	if (bd->flags & BDF_INTERNAL_BUF)
	{
//		"Writing back internal buffer\n";
		MemCopy(buf, internal_buf, buf_size);
	}

	if (lock && unlock)
		BlkDevUnlock(bd);

	return cmd_header->prd_byte_count;
}

U0 AHCIPortInit(CBlkDev *bd, CAHCIPort *port, I64 port_num)
{//Initialize base addresses for command list and FIS receive area and start command execution on port.
	CPortCmdHeader *cmd_header;
	I64				i;

	bd->ahci_port = port;
	bd->port_num  = port_num;

	AHCIPortReset(port_num);
	AHCIPortCmdStart(port_num);

	//Spin up, power on device. If the capability isn't suppport the bits will be read-only and this won't do anything.
	port->command |= AHCI_PxCMDF_POD | AHCI_PxCMDF_SUD;
	Sleep(100); //Why?
	AHCIPortCmdStop(port_num);

	//'1K-byte' align as per SATA spec.
	port->cmd_list_base = CAllocAligned(sizeof(CPortCmdHeader) * blkdev.cmd_slot_count, 1024, Fs->code_heap);
	port->cmd_list_base_upper = 0;

	//Alloc where received FISes will be copied to. '256-byte' align as per spec.
	port->fis_base = CAllocAligned(sizeof(CFisReceived), 256, Fs->code_heap);
	port->fis_base_upper = 0;

	for (i = 0; i < blkdev.cmd_slot_count; i++)
	{
		cmd_header = &port->cmd_list_base(CPortCmdHeader *)[i];
		//Write Command FIS Length (CFL, a fixed size) in bits 4:0 of the desc. Takes size in U32s.
		cmd_header->desc = sizeof(CFisH2D) / sizeof(U32);

		//'128-byte' align as per SATA spec, minus 1 since length is 1-based.
		cmd_header->cmd_table_base = CAllocAligned(sizeof(CPortCmdTable) + sizeof(CPrdtEntry) * (AHCI_PRDT_MAX_LEN - 1), 128, Fs->code_heap);
		cmd_header->cmd_table_base_upper = 0;
	}
	AHCIPortCmdStart(port_num);
	AHCIPortIdentify(bd);
}

U0 AHCIHbaReset()
{
	Bts(&blkdev.ahci_hba->ghc, AHCI_GHCf_HBA_RESET);
	while (Bt(&blkdev.ahci_hba->ghc, AHCI_GHCf_HBA_RESET));
	Bts(&blkdev.ahci_hba->ghc, AHCI_GHCf_AHCI_ENABLE);
}

U0 AHCIInit()
{
	CAHCIHba	*hba;
	CAHCIPort	*port;
	I64			 i, bdf = PCIClassFind(PCIC_STORAGE << 16 | PCISC_AHCI << 8 + 1, 0); //0x010601, last byte prog_if, AHCI version 1.0

	if (bdf == -1)
	{
		"No AHCI controller found.\n";
		return;
	}

	"AHCI: controller found\n";
	hba = dev.uncached_alias + PCIReadU32(bdf.u8[2], bdf.u8[1], bdf.u8[0], PCIR_BASE5) & ~0x1F; //Last 4 bits not part of address.
	blkdev.ahci_hba = hba;


	Bts(&blkdev.ahci_hba->ghc, AHCI_GHCf_AHCI_ENABLE);
	"AHCI: GHC.AE\n";

//	AHCIHbaReset;
//	"AHCI: HBA reset\n";

	//Transferring ownership from BIOS if supported.
	if (Bt(&hba->caps_ext, AHCI_CAPSEXTf_BOH))
	{
		Bt(&hba->bohc, AHCI_BOHCf_OOS);
		"AHCI: Transferring ownership from BIOS\n";

		while (Bt(&hba->bohc, AHCI_BOHCf_BOS));

		Sleep(25);
		if (Bt(&hba->bohc, AHCI_BOHCf_BB)) //if Bios Busy is still set after 25 mS, wait 2 seconds.
			Sleep(2000);
	}

	blkdev.cmd_slot_count = (hba->caps & 0x1F00) >> 8;
	"AHCI: cmd slot count: %d\n", blkdev.cmd_slot_count;

	for (i = 0; i < AHCI_MAX_PORTS; i++)
	{
		if (Bt(&hba->ports_implemented, i))
		{//$BK,1$Make ports idle?$BK,0$
			port = &hba->ports[i];
			"AHCI: port on %d, signature 0x%0X\n", i, port->signature;
			if (port->signature == AHCI_PxSIG_ATA || port->signature == AHCI_PxSIG_ATAPI)
			{
				if (port->signature == AHCI_PxSIG_ATAPI)
				{
					Bts(&port->command, AHCI_PxCMDf_ATAPI);
					"      ATAPI drive\n";
				}
				else
					"      ATAPI drive\n";

				if (!AHCIPortIsIdle(i))
				{
					"AHCI: Port not idle\n";
					AHCIPortCmdStop(i);
				}
			}
		}
	}
}

Bool AHCIBootDVDProbeAll(CBlkDev *bd)
{
	I64			 i;
	CAHCIPort	*port;
	U8			*buf = CAlloc(DVD_BLK_SIZE);
	CKernel 	*kernel;

	for (i = 0; i < AHCI_MAX_PORTS; i++)
	{
		if (Bt(&blkdev.ahci_hba->ports_implemented, i))
		{
			port = &blkdev.ahci_hba->ports[i];
			"AHCI: BootDVDProbeAll: Saw port at %d with signature 0x%0X\n", i, port->signature;

			if (port->signature == AHCI_PxSIG_ATAPI)
			{
				"AHCI: Probing ATAPI drive at port %d\n", i;

				AHCIPortInit(bd, port, i);

				AHCIAtapiBlksRead(bd, buf, sys_boot_blk, 1, FALSE);

				kernel = buf + sys_boot_src.u16[1] << BLK_SIZE_BITS;

				if (kernel->compile_time == sys_compile_time)
				{
					"Found sys_compile_time at BLK %d on Port %d\n", sys_boot_blk, i;
					return TRUE;
				}
				else
					"Did not find matching sys_compile_time on Port %d\n", i;
			}
		}
	}

	return FALSE;
}

Bool AHCIAtapiRBlks(CDrive *drive, U8 *buf, I64 blk, I64 count)
{
	CBlkDev	*bd			= drive->bd;
	I64		 spc		= bd->blk_size >> BLK_SIZE_BITS, n, blk2,
			 l2			= bd->max_reads << 1 + spc << 1;
	U8		*dvd_buf;//	= MAlloc(l2 << BLK_SIZE_BITS);

	if (bd->type == BDT_ATAPI)
	{
		dvd_buf	= MAlloc(l2 << BLK_SIZE_BITS);

		if (blk <= bd->max_reads)
			blk2 = 0;
		else
			blk2 = FloorU64(blk - bd->max_reads, spc);

		if (blk2 + l2 > drive->size + drive->drv_offset)
			l2 = drive->size + drive->drv_offset - blk2;

		n = (l2 + spc - 1) / spc;

//		"AHCIAtapiBlksRead(bd, dvd_buf, %d, %d);", blk2 / spc, n;
		AHCIAtapiBlksRead(bd, dvd_buf, blk2 / spc, n);

		if (bd->flags & BDF_READ_CACHE)
			DiskCacheAdd(drive, dvd_buf, blk2, n * spc);

		MemCopy(buf, dvd_buf + (blk - blk2) << BLK_SIZE_BITS, count << BLK_SIZE_BITS);
		Free(dvd_buf);

	}
	else
		return FALSE;

	return TRUE;
}
//IDEATARBlks

Bool AHCIAtaRBlks(CDrive *drive, U8 *buf, I64 blk, I64 count)
{
	CBlkDev	*bd = drive->bd;

	if (bd->type == BDT_ATA)
		AHCIAtaBlksRead(bd, buf, blk, count);
	else
		return FALSE;

	return TRUE;
}

Bool AHCIAtaWBlks(CDrive *drive, U8 *buf, I64 blk, I64 count)
{
	CBlkDev	*bd = drive->bd;

	AHCIAtaBlksWrite(bd, buf, blk, count);

	blkdev.write_count += count;

	return TRUE;
}

/*
AHCIInit;

#define BLKS 65537

U0 rw()
{
	U8 *buf = MAlloc(BLKS * BLK_SIZE);
	U8 *buf2 = MAlloc(BLKS * DVD_BLK_SIZE);
	U8 *buf3 = CAlloc(BLKS * DVD_BLK_SIZE);

	MemSet(buf, 0xFF, BLKS * BLK_SIZE);

	CBlkDev *bd = CAlloc(sizeof(CBlkDev));
	CBlkDev *bd2 = CAlloc(sizeof(CBlkDev));
//	AHCIPortInit(bd, &blkdev.ahci_hba->ports[0], 0);
	AHCIPortInit(bd2, &blkdev.ahci_hba->ports[1], 1);
	
//	"$$PURPLE$$Byte count: %X$$FG$$\n", AHCIAtaBlksWrite(bd, buf,  0, BLKS); //write
//	"$$PURPLE$$Byte count: %X$$FG$$\n", AHCIAtaBlksRead(bd, buf2, 0, BLKS);//read

//	"$$PURPLE$$Byte count: %X$$FG$$\n", AHCIAtapiBlksRead(bd2, buf3, 0, BLKS);//read
	
//	D(buf2 + (BLKS - 5) * BLK_SIZE, 5 * BLK_SIZE);

	"Capacity: %d\n", AHCIAtapiCapacityGet(bd2);
//	D(buf3 + DVD_BLK_SIZE * (BLKS - 5), 5 * DVD_BLK_SIZE);
	Free(buf);
	Free(buf2);
	Free(buf3);
	Free(bd);
	Free(bd2);
}

rw;
*/