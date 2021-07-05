// Must be in same directory as driver files.
// (Uses __DIR__)

#define PCIV_PCNET		0x1022
#define PCID_PCNET		0x2000

#define	PCIV_82545EM	0x8086
#define	PCID_82545EM	0x100F

U0 NetDriverInclude(U8 *driver)
{
	U8 *filename = MStrPrint(__DIR__ "/%s", driver);

	ExeFile(filename);
	Free(filename);
}

U0 NetDriverInit()
{
	CPCIDev *net_driver_pci = PCIDevFind(PCIC_NETWORK);

	switch (net_driver_pci->vendor_id)
	{
		case PCIV_PCNET:
			switch (net_driver_pci->device_id)
			{
				case PCID_PCNET:
					NetDriverInclude("PCNet");
					break;
			}
			break;

		case PCIV_82545EM:
			switch (net_driver_pci->device_id)
			{
				case PCID_82545EM:
					NetDriverInclude("82545EM");
					break;
			}
			break;

	} 
}

NetDriverInit;
