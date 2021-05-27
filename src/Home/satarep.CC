I64 SATARep()
{
	I64 bdf;
	CAHCIPort *port;
	CPCIDev *pci;
	"AHCI version %X.%1X%1X\n", blkdev.ahci_hba->version >> 16, (blkdev.ahci_hba->version & 0xFF00) >> 8, blkdev.ahci_hba->version & 0xFF;
	if (dev.pci_head)
	{
		pci = PCIDevFind(PCIC_STORAGE, PCISC_AHCI);
		ClassRep(pci);
		"Bus:0x%02X, Dev:0x%02X, Fun:0x%02X\n\n", pci->bus, pci->dev, pci->fun;
		"$$PURPLE$$Vendor$$FG$$: $$BLACK$$%s$$FG$$\n", pci->vendor_str;
		"$$PURPLE$$Device$$FG$$: $$BLACK$$%s$$FG$$\n", pci->dev_id_str;
	}	
	else
	{
		bdf = PCIClassFind(PCIC_STORAGE << 16 | PCISC_AHCI << 8 + 1, 0);
		"Bus:%02X, Dev:%02X, Fun:%02X", bdf.u8[2], bdf.u8[1], bdf.u8[0];
		"HBA Base Address: 0x%X", PCIReadU32(bdf.u8[2], bdf.u8[1], bdf.u8[0], PCIR_BASE5) & ~0x1F;
	}
	return 0;
}

SATARep;