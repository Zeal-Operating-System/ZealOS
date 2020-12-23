U0 InstallDrive(U8 drv_let)
{
	U8 *st;

	ExePrint("CopyTree(\"::/\",\"%C:/\");",			drv_let);
	ExePrint("DirMake(\"%C:/Tmp\");",				drv_let);
	ExePrint("DirMake(\"%C:/Tmp/ScreenShots\");",	drv_let);
	ExePrint("DirMake(\"%C:/Home\");",				drv_let);

	st = MStrPrint("%C:/Home/DoDistro.CC", drv_let);
	if (!FileFind(st))
		Copy("::/Misc/DoDistro.CC", st);
	Free(st);

	st = MStrPrint("%C:/Home/MakeHome.CC", drv_let);
	if (!FileFind(st))
		Copy("::/MakeHome.CC", st);
	Free(st);
}

Bool VMPartDisk(CTask *task, CATARep *ata_drive)
{
	if (ata_drive)
	{
		XTalkWait(task, "DiskPart(,0.5,0.5);\nC\np%d\nY", ata_drive->num);
		return TRUE;
	}
	else
		return FALSE;
}

U0 VMInstallDrive(CTask *task, U8 drv_let, CATARep *ata_drive, CATARep *atapi_drive)
{
	InstallDrive(drv_let);
	XTalkWait(task, "BootHDIns('%C');\n\nB\n0x20000\n", drv_let);
	if (ata_drive)
		XTalkWait(task, "C\np%d\n", ata_drive->num);
	if (atapi_drive)
		XTalkWait(task, "Tp%d\n", atapi_drive->num);
	XTalkWait(task, "\n1024\n768\n\n\n"); //Exit Drives,  set Screen Resolution, skip Disk Cache and Options
}

U0 VMInstallWiz()
{
	CATARep *head = NULL, *ata_drive = NULL, *atapi_drive = NULL;
	CTask	*task;

	task = User;
	TaskWait(task);
	task->border_src	= BDS_CONST;
	task->border_attr	= LTGRAY << 4 + DriveTextAttrGet(':') & 15;
	task->text_attr		= LTGRAY << 4 + BLUE;
	task->win_inhibit	= WIG_TASK_DEFAULT - WIF_SELF_BORDER;
	WinHorz(Fs->win_left, Fs->win_right, task);
	WinVert(Fs->win_top,  (Fs->win_top + Fs->win_bottom) >> 2 - 1, task);
	WinVert(task->win_bottom + 3, Fs->win_bottom);
	WinToTop(Fs);

	ATARep(FALSE, TRUE, &head);
	ATAIDDrives(head, &ata_drive, &atapi_drive);
	if (VMPartDisk(task, ata_drive))
	{
		VMInstallDrive(task, 'C', ata_drive, atapi_drive);
		VMInstallDrive(task, 'D', ata_drive, atapi_drive);
		BootMHDIns('C');
	}
	LinkedListDel(head);
	WinVert(task->win_top, Fs->win_bottom);
	Kill(task);
}

U0 RegularInstallWiz()
{
	I64		 unit, drv_let;
	U8		*st, *base0, *base1;
	CATARep	*head = NULL, *tmpha;
	I64		 ch, num_hints, res_num;
	CTask	*task;

	task = User;
	TaskWait(task);
	task->border_src	= BDS_CONST;
	task->border_attr	= LTGRAY << 4 + DriveTextAttrGet(':') & 15;
	task->text_attr		= LTGRAY << 4 + BLUE;
	task->win_inhibit	= WIG_TASK_DEFAULT - WIF_SELF_BORDER;
	WinHorz(Fs->win_left, Fs->win_right, task);
	WinVert(Fs->win_top,  (Fs->win_top + Fs->win_bottom) >> 2 - 1, task);
	WinVert(task->win_bottom + 3, Fs->win_bottom);
	WinToTop(Fs);
	XTalk(task, "Mount;\nC\np");

	num_hints = ATARep(FALSE,, &head);
	"\nInclude '$$PURPLE$$0x$$FG$$' for hexidecimal numbers.\n\n";
	while (TRUE)
	{
		base0 = StrGet("Hard Drive I/O Port Base0  : ");
		if (0 < Str2I64(base0) <= 0xFFFF)
			break;
		Free(base0);
	}
	if (1 <= Str2I64(base0) <= num_hints)
	{
		tmpha = ATARepFind(&head, Str2I64(base0));
		Free(base0);
		base0 = MStrPrint("0x%X", tmpha->base0);
		base1 = MStrPrint("0x%X", tmpha->base1);
		st	  = MStrPrint("0x%X", tmpha->unit);
		unit = Str2I64(st);
		Free(st);
	}
	else
	{
		while (TRUE)
		{
			base1 = StrGet("Hard Drive I/O Port Base1  : ");
			if (0 < Str2I64(base1) <= 0xFFFF)
				break;
			Free(base1);
		}
		do
		{
			st = StrGet("Unit--$$PURPLE$$0$$FG$$=Master or $$PURPLE$$1$$FG$$=Slave: ", "0");
			unit = Str2I64(st);
			Free(st);
		}
		while (!(0 <= unit <= 1));
	}
	LinkedListDel(head);
	XTalkWait(task, "%s\n%s\n%C\n", base0, base1, '0' + unit);
	DriveRep;
	do
	{
		st = StrGet("\nDestination Partition Letter: ");
		if (*st)
			drv_let = Letter2Letter(*st);
		else
			drv_let = 0;
		Free(st);
	}
	while (!('A' <= drv_let <= 'Z'));

	'\n';

	"$$RED$$Format %C Partition?$$FG$$\n", drv_let;
	if (YorN)
	{
		'\n';
		do
		{
			"$$PURPLE$$1$$FG$$) Use FAT32\n"
			"$$PURPLE$$2$$FG$$) Use RedSea\n"
			"\nFile System Type: ";
			ch = CharGet;
			'\n';
		}
		while (!('1' <= ch <= '2'));

		if (ch == '1')
			Format(drv_let,, FALSE, FSt_FAT32);
		else
			Format(drv_let,, FALSE, FSt_REDSEA);
	}
	InstallDrive(drv_let);
	XTalkWait(task, "BootHDIns('%C');\n\nB\n0x20000\nC\ns%s\n%s\n%C\n", drv_let, base0, base1, '0' + unit);
	VideoRep;
	res_num = I64Get("Enter desired list num ($$PURPLE$$<ENTER>$$FG$$ for max res): ",, 1);
	XTalkWait(task, "%d\n\n\n", res_num); //skip through Disk Cache, Options
	"$$RED$$Install Master Boot loader?$$FG$$";
	if (YorN)
	{
		'\n';
		BootMHDIns(drv_let);
	}
	Free(base0);
	Free(base1);

	WinVert(task->win_top, Fs->win_bottom);
	Kill(task);
}

U0 DoInstructions()
{
	CTask *task = User;

	AutoComplete;
	WinToTop(Fs);
	WinTileVert;
	XTalk(task, "Ed(\"::/Doc/Install.DD\");\n");
}

Bool DoInstall(Bool prompt_reboot)
{
	I64					 res = FALSE, vm_install = TRUE;
	CSMBIOSSystemInfo	*sys_info = SMBIOSStructGet(SMBIOSt_SYSTEM);
	U8					*company = SMBIOSStr(sys_info, sys_info->manufacturer);
	
	if (StrCompare(company, "VMware, Inc.") && StrCompare(company, "innotek GmbH") && StrCompare(company, "QEMU"))
	{
		"\n\n\n\n\nAre you installing inside VMware, QEMU, VirtualBox or a similar virtual machine? ";
		vm_install = YorN;
	}
	DocBottom;
	if (vm_install)
	{
		VMInstallWiz();
		res = TRUE;
	}
	else
	{
		"\n\nThis wizard works if you have a partition ready. You can partition the drive or BootHDIns() "
				"with more options if you do it by hand, not using this wizard.\n\n"
				"Continue Install Wizard ";
		if (YorN)
		{
			RegularInstallWiz();
			res = TRUE;
		}
		else
			prompt_reboot = FALSE;
	}
	if (prompt_reboot)
	{
		"Reboot Now ";
		if (YorN)
			Reboot;
	}
	return res;
}

Bool OSInstall(Bool prompt_reboot=TRUE)
{
	DoInstructions;

	return DoInstall(prompt_reboot);
}

#if __CMD_LINE__
OSInstall(TRUE);
#endif
