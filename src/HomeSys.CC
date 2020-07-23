//Place this file in /Home and change
//anything you want.

U0 UserStartUp()
{//Run each time a user a spawned
	DocTermNew;
	Type("::/Doc/Start.DD");
	LBts(&Fs->display_flags, DISPLAYf_SHOW);
	WinToTop;
	WinZBufUpdate;
	Dir;
}

U0 ServerStartUp()
{//Run each time a server task is spawned.
	DocTermNew;
	LBts(&Fs->display_flags, DISPLAYf_SHOW);
	WinToTop;
	WinZBufUpdate;
}

U0 StartUpTasks()
{
	if (sys_boot_src.u16[0] != BOOT_SRC_RAM)
		PopUpRunFile("::/Zenith/ZSplash.CC");
	CTask *user = User;
	WinToTop(user);
	WinTileVert;
	"Boot Time:%7.3fs\n", tS;
	XTalk(user, "Cd;#include \"Once\";\n");
	Silent; //no output to screen
	ACInit("/*");
	Silent(OFF); //no output to screen
}

StartUpTasks;

"\nZenithOS V%0.2f\t%D %T\n\n", sys_os_version, sys_compile_time, sys_compile_time;
