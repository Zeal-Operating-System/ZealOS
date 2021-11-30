//Place this file in /Home and change
//anything you want.

//This file is executed by the
//first terminal window upon start-up.
//See $LK,"Once",A="FF:~/HomeSys.CC,Once"$ and $LK,"Home Files",A="FF:::/Doc/GuideLines.DD,/Home Files"$.

//Delete the rest from this file.

U0 Tmp()
{
	OnceExe;
	// 8x16 hack
	text.font[256] = -1;
	text.font[257] = -1;
	text.font[258] = text.font[259] = 0xFFFF0000FFFF0000 & 0x9999999999999999;
	text.border_chars[2] (I64) = 'ÅÄÅÄÅÄÅÄ';
	text.border_chars[10](U32) = 'ÅÄÅÄ';
	////////////

	switch (sys_boot_src.u16[0])
	{
		case BOOT_SRC_ROM:
			"Continue booting hard drive ";
			if (YorN)
			{
				DocBottom;
				ExeFile("C:/Home/Once");
			}
			break;
		case BOOT_SRC_DVD:
			"\nIf you answer 'No' you can play with\n"
			"the live CD without installing.\n\n"
			"Install onto hard drive ";

			if (YorN)
			{
				DocBottom;
				RunFile("::/Misc/OSInstall",, TRUE);
			}
			if (FileFind("::/Misc/Tour"))
			{
				"\nTake Tour";
				if (YorN) {
					DocBottom;
					Cd("::/Misc/Tour");
					InFile("Tour");
				}
			}
			break;
		case BOOT_SRC_HARDDRIVE:
		case BOOT_SRC_RAM:
			"\n$$PURPLE$$$$TX+CX,\"Tips of the Day\"$$$$FG$$\n";
			TipOfDay;Yield;
			TipOfDay;
			Type("::/Doc/Customize.DD");
			break;
	}
}
Tmp;
