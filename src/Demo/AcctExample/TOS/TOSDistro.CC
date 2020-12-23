//The CONFIG defines are $LK,"~/TOS/TOSConfig.CC",A="FI:::/Demo/AcctExample/TOS/TOSConfig.CC"$.

#help_index "Misc/TOS/Distro"

#define MAKE_LITE 			1
#define MAKE_DEBUG			0
#define MAKE_STAFF			1

public U8 TOSGetDrive()
{//Prompt for drv let.
	I64 res;

	"Drive (%s):", TOS_HDS;
	res = Letter2Letter(CharGet);
	'\n';

	return res;
}

public U0 TOSBootHDIns(U8 drv_let=0)
{//Make Compiler and Kernel. Reinstall Kernel.
	drv_let = Letter2Letter(drv_let);
	In(TOS_CONFIG);
	BootHDIns(drv_let);
	if (StrOcc(TOS_MASTER_BOOT_DRIVES, drv_let))
		BootMHDIns(drv_let);
}

public U0 TOSCopyDrive(U8 src, U8 dst)
{//Format dst and copy entire drv.
	U8 buf_s[STR_LEN], buf_d[STR_LEN];

	src = Letter2Letter(src);
	dst = Letter2Letter(dst);

	if (dst == 'D')
		Format(dst,, FALSE, FSt_FAT32);
	else
		Format(dst,, FALSE, FSt_REDSEA);

	StrPrint(buf_s, "%c:/", src);
	StrPrint(buf_d, "%c:/", dst);
	CopyTree(buf_s, buf_d);

	DocClear;
	Drive(dst);
	TOSBootHDIns(dst);
}

public U0 TOSPromptAndCopyDrive()
{//Prompt for drv lets. Then, Format dst and copy entire drv.
	I64 src, dst;

	"$$RED$$\nCopy Src Drive:\n$$FG$$";
	src = TOSGetDrive;
	"$$RED$$\nCopy Dst Drive:\n$$FG$$";
	dst = TOSGetDrive;
	TOSCopyDrive(src, dst);
}

U0 DistroPrep()
{
	ZOnceFlush; //Don't want in Registry
	OnceFlush;

	Del("/Home/Demo*");
	DelTree("/Home/*Tmp.DD");

	DelTree("/Tmp");
	DirMake("/Tmp");
	DirMake("/Tmp/ScreenShots");

	Touch("/PersonalMenu.DD", "+T");
	Touch("/Home/PersonalMenu.DD", "+T");

	DelTree("/Demo/AcctExample");
	CopyTree("/Home", "/Demo/AcctExample");
	DelTree("/Demo/AcctExample/TAD");
	DelTree("/Demo/AcctExample/Sup1");
	DelTree("/Demo/AcctExample/Sup2");
	DelTree("/Demo/AcctExample/Sup3");
	Del("/Demo/AcctExample/Test*");
	if (FileFind("~/Sup1/Sup1Utils/SortHeaders.CC"))
		ExeFile("~/Sup1/Sup1Utils/SortHeaders.CC");

	CursorRemove("/*");
	DelTree("/Demo/*.BI*");
	S2T("/*", "+r+S");
	DocOpt("/*", "+R");
	Move(ACD_DEF_FILENAME, ACD_DEF_FILENAME_Z);
}

U0 DebugDistroFilePrep()
{
	CBlkDev *bd;

	if (!Letter2Drive('A', FALSE))
	{
		In(CONFIG_DEBUG_DISTRO "\n");
		Mount;
	}
	bd = Letter2BlkDev('A');
	Format('A',, FALSE, FSt_REDSEA);

	DirMake("A:/Compiler");
	Copy("C:/Compiler/Compiler.BIN",	"A:/Compiler");
	Copy("C:/Compiler/OpCodes.DD",		"A:/Compiler");
	Copy("C:/Compiler/CompilerA.HH",	"A:/Compiler");
	Copy("C:/Compiler/CompilerB.HH",	"A:/Compiler");

	DirMake("A:/Kernel");
	Copy("C:/Kernel/*.HH*",			"A:/Kernel");
	CopyTree("C:/Kernel/BlkDev",	"A:/Kernel/BlkDev");

	Copy("C:/Home/Sup1/Sup1Distro/DebugStartOS.CC", "A:/StartOS.CC");

	DirMake("A:/Zenith");
	Copy("C:/Home/Sup1/Sup1Distro/DebugMakeZenith.CC", "A:/Zenith/MakeZenith.CC");
	Copy("C:/Home/Sup1/Sup1Distro/DebugMount.CC", "A:/Zenith");
	Copy("C:/Zenith/AExts.CC",		"A:/Zenith");
	Copy("C:/Zenith/AMath.CC",		"A:/Zenith");
	Copy("C:/Zenith/Training.CC",	"A:/Zenith");
	Copy("C:/Zenith/AMem.CC", 		"A:/Zenith");
	Copy("C:/Zenith/TaskRep.CC",	"A:/Zenith");

	FileWrite("C:" CONFIG_DEBUG_DISTRO_FILE, bd->RAM_disk, (bd->max_blk + 1) << BLK_SIZE_BITS);
}


U0 StdDistroPrep()
{
	Drive('C');
	DistroPrep;
	In(STD_DISTRO_DVD_CONFIG);
	BootDVDIns('C');
	Format('B',, FALSE, FSt_REDSEA);
	DelTree(TOS_DISTRO_DIR);
	CopyTree("C:/", TOS_DISTRO_DIR "/");
	DelTree(TOS_DISTRO_DIR "/Home");
	DirMake(TOS_DISTRO_DIR "/Home");
	Del(TOS_DISTRO_DIR "/" KERNEL_BIN_C);
	Del(TOS_DISTRO_DIR BOOT_DIR "/OldMBR.BIN.C");
	Del(TOS_DISTRO_DIR BOOT_DIR "/BootMHD2.BIN.C");
}
U0 MakeStdDistro()
{
	StdDistroPrep;
	RedSeaISO(TOS_ISO_NAME, TOS_DISTRO_DIR, TOS_DISTRO_DIR BOOT_DIR_KERNEL_BIN_C);
	DefinePrint("DD_TEMPLEOSCD_SIZE", "Download $TX,"ZenithOS V1.13",D="DD_OS_NAME_VERSION"$ - Standard Distro (%0.1fMB)",
				0.1 * (10 * Size(TOS_ISO_NAME, "+s") / 1024 / 1024));
	Drive('C');
}

U0 LiteDistroPrep()
{
	Drive('C');
	DistroPrep;
	In(STD_DISTRO_DVD_CONFIG);
	BootDVDIns('C');
	Format('B',, FALSE, FSt_REDSEA);
	DelTree(TOS_DISTRO_DIR);
	CopyTree("C:/", TOS_DISTRO_DIR "/");
	DelTree(TOS_DISTRO_DIR "/Home");
	DirMake(TOS_DISTRO_DIR "/Home");
	DelTree(TOS_DISTRO_DIR "/Apps");
	DelTree(TOS_DISTRO_DIR "/Demo");
	Copy(TOS_DISTRO_DIR "/Demo/Games/Talons.CC", TOS_DISTRO_DIR "/Home");
	Del(TOS_DISTRO_DIR "/" KERNEL_BIN_C);
	Del(TOS_DISTRO_DIR BOOT_DIR "/OldMBR.BIN.C");
	Del(TOS_DISTRO_DIR BOOT_DIR "/BootMHD2.BIN.C");
	Del(TOS_DISTRO_DIR "/Zenith/AutoComplete/ACDefs.DATA");
	Del(TOS_DISTRO_DIR "/Zenith/AutoComplete/ACWords.DATA");
	Del(TOS_DISTRO_DIR "/Misc/Bible.TXT");
}
U0 MakeLiteDistro()
{
	LiteDistroPrep;
	RedSeaISO(TOS_ISO_NAME, TOS_DISTRO_DIR, TOS_DISTRO_DIR BOOT_DIR_KERNEL_BIN_C);
	DefinePrint("DD_TEMPLEOSCD_SIZE", "Download $TX,"ZenithOS V1.13",D="DD_OS_NAME_VERSION"$ - Standard Distro (%0.1fMB)", 
				0.1 * (10 * Size(TOS_ISO_NAME, "+s") / 1024 / 1024));
	Drive('C');
}

U0 DebugDistroPrep()
{
	Drive('C');
	DistroPrep;
	DebugDistroFilePrep;
	In(TOS_DVD_DEBUG_CONFIG);
	BootDVDIns('C');
	Format('B',, FALSE, FSt_REDSEA);
	DelTree(TOS_DISTRO_DIR);
	CopyTree("C:/", TOS_DISTRO_DIR "/");
	DelTree(TOS_DISTRO_DIR "/Home");
	DirMake(TOS_DISTRO_DIR "/Home");
	Del(TOS_DISTRO_DIR "/" KERNEL_BIN_C);
	Del(TOS_DISTRO_DIR BOOT_DIR "/OldMBR.BIN.C");
	Del(TOS_DISTRO_DIR BOOT_DIR "/BootMHD2.BIN.C");
}
U0 MakeDebugDistro()
{
	DebugDistroPrep;
	RedSeaISO(TOS_ISO_NAME, TOS_DISTRO_DIR, TOS_DISTRO_DIR BOOT_DIR_KERNEL_BIN_C);
	DefinePrint("DD_TEMPLEOS_DEBUG_SIZE", "Download $TX,"ZenithOS V1.13",D="DD_OS_NAME_VERSION"$ - Debug Distro (%0.1fMB)", 
				0.1 * (10 * Size(TOS_ISO_NAME, "+s") / 1024 / 1024));
	Drive('C');
}

U0 StaffDistroPrep()
{
	Drive('C');
	DistroPrep;
	In(TOS_DVD_CONFIG);
	BootDVDIns('C');
	Format('B',, FALSE, FSt_REDSEA);
	DelTree(TOS_DISTRO_DIR);
	CopyTree("C:/", TOS_DISTRO_DIR "/");
	DelTree(TOS_DISTRO_DIR "/Home/Sup1");
	DelTree(TOS_DISTRO_DIR "/Home/Sup2");
	DelTree(TOS_DISTRO_DIR "/Home/Sup3");
	Del(TOS_DISTRO_DIR "/" KERNEL_BIN_C);
}
U0 MakeStaffDistro()
{
	StaffDistroPrep;
	RedSeaISO(TOS_ISO_NAME, TOS_DISTRO_DIR, TOS_DISTRO_DIR BOOT_DIR_KERNEL_BIN_C);
	DefinePrint("DD_TEMPLEOS_STAFF_SIZE", "Download $TX,"ZenithOS V1.13",D="DD_OS_NAME_VERSION"$ - T.S. Company Internal Distro (%0.1fMB)", 
				0.1 * (10 * Size(TOS_ISO_NAME, "+s") / 1024 / 1024));
	Drive('C');
}

I64 UpdateLineCounts()
{
	I64 res;

	DocClear;
	Drive('C');
	DistroPrep;

	Cd("C:/");
	DelTree("B:/TOS/TOS");
	CopyTree("C:/Home", "B:/TOS/TOS");
	DelTree("C:/Home");

	DocMax;
	DocClear;
	res = LineRep("C:/*", "-r") + LineRep("C:/Zenith/*") + LineRep("C:/Compiler/*", "-S+$$") + LineRep("C:/Kernel/*");
	CopyTree("B:/TOS/TOS", "C:/Home");
	DelTree("B:/TOS/TOS");

	DocTreeFWrite("C:/Zenith/ZDefine.CC", "LineRep", "DefinePrint(\"DD_TEMPLEOS_LOC\",\"%,d\");\n", res);
	DefinePrint("DD_TEMPLEOS_LOC", "%,d", res);

	"Total LOC:%12,d\n\n", res;

	return res;
}

U0 UpdateISODocDefines()
{
	try
	{
		DefinePrint("DD_TEMPLEOSCD_SIZE", "Download $TX,"ZenithOS V1.13",D="DD_OS_NAME_VERSION"$ - Standard Distro (%0.1fMB)", 
					0.1 * (10 * Size("D:/Downloads/TOS_Distro.ISO", "+s") / 1024 / 1024));
		DefinePrint("DD_TEMPLEOSCD_K_SIZE", "%dKB", Size("D:/Downloads/TOS_Distro.ISO", "+s") / 1024);
	}
	catch
		Fs->catch_except = TRUE;
}
UpdateISODocDefines;


I64 tos_progress;
F64 tos_progress_t0;

U0 TOSProgress(U8 *st)
{
	U8 buf[STR_LEN];

	progress4		= tos_progress;
	progress3_max	= 1;
	*progress4_desc	= 0;
	progress4_max	= 9 + MAKE_LITE + MAKE_DEBUG + MAKE_STAFF;
	progress4_t0	= tos_progress_t0;
	StrPrint(buf, "%d. %s", ++progress4, st);
	"$$PURPLE$$$$TX+CX,\"%s\"$$$$FG$$\n", buf;
	StrCopy(progress3_desc, buf);
	tos_progress = progress4;
}

U0 TOSRegen2()
{
	I64 slash_home = 0;

	SettingsPush; //See $LK,"SettingsPush",A="MN:SettingsPush"$
	tos_progress = -1;
	tos_progress_t0 = tS;
	RegExe("ZenithOS/TOSRegen");

	TOSProgress("DiskCheck All");
	AutoComplete;
	WinBorder;
	WinMax;
	DiskCheckAll;

	TOSProgress("Update Line Counts");
	UpdateLineCounts;

	TOSProgress("Copy C to D");
	TOSCopyDrive('C', 'D');

	TOSProgress("Make Standard Distro ISO");
	MakeStdDistro;
	DocClear;
	Move(TOS_ISO_NAME, "D:/Downloads/TOS_Distro.ISO");

	TOSProgress("Make Supplemental1 ISO");
	RedSeaISO("D:/Downloads/TOS_Supplemental1", "C:/Home/Sup1");

	TOSProgress("Make Supplemental2 ISO");
	RedSeaISO("D:/Downloads/TOS_Supplemental2", "C:/Home/Sup2");

	TOSProgress("Make Supplemental3 ISO");
	RedSeaISO("D:/Downloads/TOS_Supplemental3", "C:/Home/Sup3");

#if MAKE_LITE
	TOSProgress("Make Lite Distro ISO");
	MakeLiteDistro;
	DocClear;
	Move(TOS_ISO_NAME, "D:/Downloads/TOS_Lite.ISO");
#endif
#if MAKE_DEBUG
	TOSProgress("Make Debug Distro ISO");
	MakeDebugDistro;
	DocClear;
	Move(TOS_ISO_NAME, "D:/Downloads/TOS_Debug.ISO");
#endif
#if MAKE_STAFF
	TOSProgress("Make Staff Distro ISO");
	MakeStaffDistro;
	DocClear;
	Move(TOS_ISO_NAME, "D:/Downloads/TOS_Staff.ISO");
#endif

	UpdateISODocDefines;
	Cd("C:/");
	DocClear;

	TOSProgress("Check for Long Lines");
	if (LongLines)
		throw;

	DocClear;
	TOSProgress("Check for Broken DolDoc Links");
	if (LinkCheck)
		throw;

	TOSProgress("Find /Home");
	slash_home = F2("/Home", "-i+la");

	TOSProgress("DiskCheck All");
	Drive('C');
	DiskCheckAll;

	TOSProgress("Done");
	SettingsPop;
	"F2(\"/Home\") Count\t:%d\n", slash_home;
	"Elapsed Time\t:%5.3fs\n", tS - progress4_t0;
	ProgressBarsReset("ZenithOS/TOSRegen");
}

public U0 TOSPreRegen()
{//Copy bins from D:/Home/Sup1 to C:/Home/Sup1
	Copy("D:/Home/" INS_REG_PERSONAL_INITIALS "/*", "C:/Home/" INS_REG_PERSONAL_INITIALS);
	DelTree("C:/Home/Sup1/Sup1Bin");
	CopyTree("D:/Home/Sup1/Sup1Bin", "C:/Home/Sup1/Sup1Bin");
	Copy("D:/Home/Sup1/Sup1CodeScraps/Comm/TOSSocket*", "C:/Home/Sup1/Sup1CodeScraps/Comm");
	DelTree("C:/Downloads/Linux");
	CopyTree("D:/Downloads/Linux", "C:/Downloads/Linux");
}

public U0 TOSRegen()
{//Generate distro ISO's
	TOSBootHDIns('C');
	Once("TOSRegen2;");
	BootRAM("C:/Kernel/" KERNEL_BIN_C); //Boot to load $LK,"TOS_CONFIG",A="PF:::/Demo/AcctExample/TOS/TOSConfig.CC,TOS_CONFIG"$.
}
