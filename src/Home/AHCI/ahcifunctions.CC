#define BLKS 40

U0 Test()
{
	CBlkDev *ata_bd = CAlloc(sizeof(CBlkDev));
	CBlkDev *atapi_bd = CAlloc(sizeof(CBlkDev));
	AHCIPortInit(ata_bd, &blkdev.ahci_hba->ports[0], 0);
	AHCIPortInit(atapi_bd, &blkdev.ahci_hba->ports[1], 1);
}

Test;