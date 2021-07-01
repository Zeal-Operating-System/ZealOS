//See $LK,"Install Documentation",A="FI:::/Doc/Install.DD"$.
//Study my account examples: $LK,"Config Strs",A="FL:::/Demo/AcctExample/TOS/TOSConfig.CC,1"$, $LK,"Update Funs",A="FL:::/Demo/AcctExample/TOS/TOSDistro.CC,1"$

#include "BootDVD"
#include "DiskISORedSea"

#help_index "Install"

#define KERNEL_BIN_C			"Kernel.BIN.C"
#define BOOT_DIR				"/0000Boot"
#define BOOT_DIR_KERNEL_BIN_C	BOOT_DIR "/0000" KERNEL_BIN_C

U0 MakeAll()
{
	if (Comp("/Compiler/Compiler", "Compiler",, ':'))
		throw;
	if (Comp("/Kernel/Kernel", "Kernel",, ':'))
		throw;
}

public U0 BootDVDIns(U8 drv_let=0)
{//See $LK,"::/Misc/DoDistro.CC"$.
	try
	{
		if (!Drive(drv_let))
			throw;
		MakeAll;
		Move("/Kernel/Kernel.BIN", BOOT_DIR_KERNEL_BIN_C);
	}
	catch
	{
		PutExcept;
		Beep;
	}
}
