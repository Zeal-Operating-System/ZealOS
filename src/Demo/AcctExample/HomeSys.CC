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
	"\n$TX,"94,710",D="DD_ZEALOS_LOC"$ LOC, ";
	"%d MB RAM, ", MemBIOSTotal / 1024 / 1024;
	CPURep;
	"\n";
}

U0 ServerStartUp()
{//Run each time a server task is spawned.
	DocTermNew;
	LBts(&Fs->display_flags, DISPLAYf_SHOW);
	WinToTop;
	WinZBufUpdate;
}

CTask *user1, *user2;

U0 StartUpTasks()
{
	user1 = User;
	user2 = User;
	WinToTop(user1);
	WinTileVert;
	"Boot     Time:%7.3fs\n", tS;
	XTalk(user1, "Cd;#include \"Once\";\n");
	Silent;
	ACInit("/*;!*/Bible.TXT*;!*.TXT"); //No Bible, no uncompressed DD.
	Silent(OFF);
	"AutoComplete Time:%7.3fs\n", tS;
}

if (DriveIsWritable(':'))
	{
	DelTree("::/Tmp/ScreenShots");
	DirMake("::/Tmp/ScreenShots");
}

StartUpTasks;

"\nZealOS V%5.3f\t%D %T\n\n", sys_os_version, sys_compile_time, sys_compile_time;
