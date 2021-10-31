
// Custom DoDistro file that generates an AUTO.ISO.
// Used by host OS to create a full Distro ISO synced with GitHub repo.

#define STD_DISTRO_DVD_CONFIG 	"TB\nScale2Mem(2048,0x40000)\nT\n\n1024\n768\n\n\n"

U0 MakeMyISO(U8 *_out_iso_filename)
{//Does everything with current drive.
//If you have not recompiled $FG,2$Kernel$FG$ and defined your CD/DVD drive, use $LK,"Mount",A="MN:Mount"$.
	U8 *out_iso_filename = FileNameAbs(_out_iso_filename);
	if (!DriveIsWritable)
	{
		"Drive must be writable.	Install on Hard drive, first.\n";
		return;
	}
	DelTree("/Distro");
	Del(out_iso_filename);

	DirMake("/Distro");
	In(STD_DISTRO_DVD_CONFIG);
	BootDVDIns;

	Copy("/*","/Distro");
	DirMake("/Distro" BOOT_DIR);
	Move(BOOT_DIR_DVD_KERNEL_BIN_C, "/Distro" BOOT_DIR_KERNEL_BIN_C);

	CopyTree("/Home", 		"/Distro/Home");
	Del("/Distro/Home/Registry.CC");
	CopyTree("/System", 	"/Distro/System");
	Del("/Distro/System/AutoComplete/ACDefs.DATA");
	CopyTree("/Compiler",	"/Distro/Compiler");
	CopyTree("/Kernel", 	"/Distro/Kernel");
	CopyTree("/Misc", 		"/Distro/Misc");
	DirMake("/Distro/Doc");
	Copy("/Doc/EdPullDown.DD", "/Distro/Doc/EdPullDown.DD");
	Copy("/Doc/Tips.DD", "/Distro/Doc/Tips.DD");
	Copy("/Misc/Auto/Once.CC", "/Distro/Once.CC");
	Copy("/Misc/Auto/HomeSys.CC", "/Distro/HomeSys.CC");
	Del("/Distro/Misc/PCIDevices.DD");
	Del("/Distro/Misc/Bible.TXT");
	Del("/Distro/Misc/Clementine.TXT");

	RedSeaISO(out_iso_filename, "/Distro", "/Distro" BOOT_DIR_KERNEL_BIN_C);

	DelTree("/Distro");
	Free(out_iso_filename);
}

MakeMyISO("/Tmp/AUTO.ISO.C");

// Study the account examples $LK,"Config Strs",A="FL:::/Demo/AcctExample/TOS/TOSConfig.CC,1"$, $LK,"Update Funs",A="FL:::/Demo/AcctExample/TOS/TOSDistro.CC,1"$.
