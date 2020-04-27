//TODO: Test
I64 AHCILBA48CapacityGet(U16 *id_record)
{//Get capacity of drive.
	return *&id_record[ATA_IDENT_LBA48_CAPACITY](U64 *) - 1;
	//return (id_record)(U64 *)[ATA_IDENT_LBA48_CAPACITY / 4] - 1;
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
{//Check if command engine is running on port.
	return !(port->cmd & (AHCI_PxCMDF_ST | AHCI_PxCMDF_CR | AHCI_PxCMDF_FR | AHCI_PxCMDF_FRE));
}

U0 AHCIPortCmdStop(CAHCIPort *port)
{//Stop command engine on port.
	//Btr(&port->cmd, AHCI_PxCMDf_ST);
	//Btr(&port->cmd, AHCI_PxCMDf_FRE);
	port->cmd &= ~(AHCI_PxCMDF_ST | AHCI_PxCMDF_FRE);
	//while (port->cmd & (AHCI_PxCMDF_CR | AHCI_PxCMDF_FR));
	while (Bt(&port->cmd, AHCI_PxCMDf_CR) || Bt(&port->cmd, AHCI_PxCMDf_FR));
}

U0 AHCIPortCmdStart(CAHCIPort *port)
{//Start command engine on port.
	while (Bt(&port->cmd, AHCI_PxCMDf_CR))
	Bts(&port->cmd, AHCI_PxCMDf_FRE);
	Bts(&port->cmd, AHCI_PxCMDf_ST);
	//port->command |= AHCI_PxCMDF_FRE | AHCI_PxCMDF_ST;
}

Bool AHCIPortWait(CAHCIPort *port, F64 timeout)
{//Wait until DRQ and BSY are clear in the port task file.
	do
		if (!(port->task_file_data & (ATAS_DRQ | ATAS_BSY)))
			return TRUE;
	while (timeout > tS);
	return FALSE;
}

//TODO: explain&comment statements in this function
U0 AHCIPortReset(CAHCIPort *port)
{//Software reset of port. Port cmd engine must be started after this.
//If port is not responsive, then perform a full port reset.
	AHCIPortCmdStop(port);
	port->interrupt_status = port->interrupt_status; //Acknowledge all interrupt statuses.

	if (!AHCIPortWait(port, tS + 1))
	{//Perform a 'more intrusive' HBA<->Port comm reset (sec. 10.4.2 of spec).
		port->sata_ctrl = AHCI_PxSCTLF_DET_INIT;
		Sleep(1);
		port->sata_ctrl = 0;
	}
	while (port->sata_status & 0xF != AHCI_PxSSTSF_DET_PRESENT);
	port->sata_error = 0;
}

U0 AHCIPortIdentify(CBlkDev *bd)
{//Perform the ATA_IDENTIFY command and set bd.dev_id_record to result.

}

U0 AHCIInit()
{
	CAHCIHba *hba;
	CAHCIPort *port;
	I64 i, bdf = PCIClassFind(PCIC_STORAGE << 16 | PCISC_AHCI << 8 + 1, 0); //0x010601, last byte = prog_if, AHCI 1.0 support.

	if (bdf == -1)
	{
		"No AHCI controller found.\n";
		return;
	}
	hba = dev.uncached_alias + PCIReadU32(bdf.u8[2], bdf.u8[1], bdf.u8[0], PCIR_BASE5) & ~0x1F; //Last 5 bits not part of addr.


	Bts(&hba->ghc, AHCI_GHCf_HBA_RESET);
	while (Bt(&hba->ghc, AHCI_GHCf_HBA_RESET));

	Bts(&hba->ghc, AHCI_GHCf_AHCI_ENABLE);
}