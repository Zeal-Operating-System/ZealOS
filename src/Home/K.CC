//Ed("/Doc/ChangeLog.DD");

CAHCIPort	*port;
I64			 i, ata_drive = -1;

// Find first-available ATA drive for BootHDIns.
for (i = 0; i < AHCI_MAX_PORTS; i++)
{
	if (Bt(&blkdev.ahci_hba->ports_implemented, i))
	{
		port = &blkdev.ahci_hba->ports[i];
		if (port->signature == AHCI_PxSIG_ATA)
		{
			ata_drive = i;
			break;
		}
	}
}

if (ata_drive < 0)
	throw('No ATA');

In("CC\n%d\n\n1024\n768\n\n\n", ata_drive);
BootHDIns;

"\n\nSuccessful? ";
if (YorN)
{
	Once(	"CursorRemove(\"/*\");;;"
			"PopUp(\"#include \\\"DoDistro\\\";;"
			"if (DriveIsWritable)"
			"{"
				"Del(\\\"~/Registry.CC\\\");"
				"OutU16(0x4004, 0x3400);"
			"}\");");

	BootRAM;
}
