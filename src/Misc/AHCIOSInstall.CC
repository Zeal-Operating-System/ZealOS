U0 InstallDrive(U8 drv_let)
{
	U8 *st;

	while (!DriveCheck(blkdev.let_to_drive[drv_let - 'A'], FALSE))
		Yield;
	Sleep(500);

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

Bool VMPartDisk(CTask *task, I64 ata_port)
{
	if (ata_port > -1)
	{
		XTalkWait(task, "DiskPart(,0.5,0.5);\nC\n%d\nY", ata_port); // DOUBLE CHECK INFILE
		return TRUE;
	}
	else
		return FALSE;
}

U0 VMInstallDrive(CTask *task, U8 drv_let, I64 ata_port, I64 atapi_port)
{// DOUBLE CHECK INFILE
	InstallDrive(drv_let);
	XTalkWait(task, "BootHDIns('%C');\n\nB\n0x20000\n", drv_let);
	if (ata_port > -1)
		XTalkWait(task, "C\n%d\n", ata_port);
	if (atapi_port > -1)
		XTalkWait(task, "T%d\n", atapi_port);
	XTalkWait(task, "\n1024\n768\n\n\n"); //Exit Drives,  set Screen Resolution, skip Disk Cache and Options
}

U0 VMInstallWiz()
{
	CTask		*task;
	I64			 i, atapi_port = -1, ata_port = -1;
	CAHCIPort	*port;

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


	////////////////////////////////////
	SATARep;
	for (i = 0; i < AHCI_MAX_PORTS; i++)
	{
		if (Bt(&blkdev.ahci_hba->ports_implemented, i))
		{
			port = &blkdev.ahci_hba->ports[i];
			if (port->signature == AHCI_PxSIG_ATA)
			{
				ata_port = i;
				break;
			}
		}
	}
	for (i = 0; i < AHCI_MAX_PORTS; i++)
	{
		if (Bt(&blkdev.ahci_hba->ports_implemented, i))
		{
			port = &blkdev.ahci_hba->ports[i];
			if (port->signature == AHCI_PxSIG_ATAPI)
			{
				atapi_port = i;
				break;
			}
		}
	}

	if (VMPartDisk(task, ata_port))
	{
		VMInstallDrive(task, 'C', ata_port, atapi_port);
		VMInstallDrive(task, 'D', ata_port, atapi_port);
		BootMHDIns('C');
	}

	////////////////////////////////////

	WinVert(task->win_top, Fs->win_bottom);
	Kill(task);
}

U0 RegularInstallWiz()
{
	I64		 drv_let;
	U8		*st;
	I64		 ch, res_num;
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

	XTalk(task, "Mount;\nC\n");

	"\nSelect the port of the ATA drive to install on.\n";

	"Hard Drive Port: ";
	while (TRUE)
	{
		st = StrGet;
		if ((0 <= Str2I64(st) < AHCI_MAX_PORTS) &&
			((&blkdev.ahci_hba->ports[Str2I64(st)])->signature == AHCI_PxSIG_ATA))
		{
			break;
		}
		Free(st);
	}

	XTalkWait(task, "%s\n\n", st);

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


	XTalkWait(task, "BootHDIns('%C');\n\nB\n0x20000\nC\n%s\n\n", drv_let, st);
	VideoRep;
	res_num = I64Get("Enter desired list num ($$PURPLE$$<ENTER>$$FG$$ for max res): ",, 1);
	XTalkWait(task, "%d\n\n\n", res_num); //skip through Disk Cache, Options
	"$$RED$$Install Master Boot loader?$$FG$$";
	if (YorN)
	{
		'\n';
		BootMHDIns(drv_let);
	}

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
