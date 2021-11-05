U0 UserStartUp()
{
	DocTermNew;
	Type("::/Doc/Start.DD");
	LBts(&Fs->display_flags, DISPLAYf_SHOW);
	WinToTop;
	WinZBufUpdate;
	Dir;
}

U0 ServerStartUp()
{
	DocTermNew;
	LBts(&Fs->display_flags, DISPLAYf_SHOW);
	WinToTop;
	WinZBufUpdate;
}

U0 StartUpTasks()
{
	CTask *user = User;

	if (sys_boot_src.u16[0] != BOOT_SRC_DVD)
		User;

	WinToTop(user);
	WinTileVert;
	"Boot Time:%7.3fs\n", tS;
	XTalk(user, "Cd; #include \"Once\";\n");
	Silent;
	Silent(OFF);
}

StartUpTasks;

"\nZealOS V%0.2f\t%D %T\n\n", sys_os_version, sys_compile_time, sys_compile_time;
