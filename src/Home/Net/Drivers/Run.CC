// Must be in same directory as driver files. (Uses __DIR__)
// Throws if stack has no driver for the PC's hardware.

#define PCIV_PCNET		0x1022
#define PCID_PCNET		0x2000

#define	PCIV_E1000		0x8086
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
	Bool	 found = FALSE;

	switch (net_driver_pci->vendor_id)
	{
		case PCIV_PCNET:
			switch (net_driver_pci->device_id)
			{
				case PCID_PCNET:
					NetDriverInclude("PCNet");
					found = TRUE;
					break;
			}
			break;

		case PCIV_E1000:
			switch (net_driver_pci->device_id)
			{
				case PCID_82545EM:
					NetDriverInclude("E1000");
					found = TRUE;
					break;
			}
			break;
	}

	if (!found)
		throw('NET');
}

NetDriverInit;
