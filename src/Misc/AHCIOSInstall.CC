U0 InstallDrive(U8 drv_let)
{
	U8 *st;

	Sleep(3000);

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
			//RegularInstallWiz(); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
