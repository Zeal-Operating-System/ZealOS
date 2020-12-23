U0 SysGlobalsInit()
{
	I64				i, j;
	CRAXRBXRCXRDX	regs;

	CPUId(0x1, &regs);
	sys_cache_line_width = regs.rbx.u8[1] * 8;

	sys_focus_task = Fs;
	QueueInit(&sys_macro_head);

	blkdev.default_iso_filename		= ZStrNew(DEFAULT_ISO_FILENAME);
	blkdev.default_iso_c_filename	= ZStrNew(DEFAULT_ISO_C_FILENAME);
	blkdev.tmp_filename				= ZStrNew("~/Tmp.DD");
	blkdev.dvd_boot_is_good			= TRUE;

	#exe
	{
		if (!kernel_config->mount_ide_auto_hd_let)
			kernel_config->mount_ide_auto_hd_let = 'C';

		if (!kernel_config->mount_ide_auto_cd_let)
			kernel_config->mount_ide_auto_cd_let = 'T';

		StreamPrint("blkdev.first_hd_drive_let  = %d;", kernel_config->mount_ide_auto_hd_let);
		StreamPrint("blkdev.first_dvd_drive_let = %d;", kernel_config->mount_ide_auto_cd_let);
	}

	DebugMode(ON);

	rev_bits_table = CAlloc(256);

	for (i = 0; i < 256; i++)
		for (j = 0; j < 8; j++) 
			if (Bt(&i, 7 - j))
				Bts(rev_bits_table + i, j);

	ext = CAlloc(EXT_EXTS_NUM * sizeof(U8 *));
	fp_getstr2 = &SysGetStr2;
	KeyDevInit;

	#exe
	{
		StreamPrint("blkdev.boot_drive_let = '%C';", kernel_config->boot_drive_let);

		StreamPrint("#exe{ Option(OPTf_WARN_PAREN, OFF); }");

		StreamPrint("DiskCacheInit(%s);", kernel_config->disk_cache_size_exp);

		StreamPrint("#exe{ Option(OPTf_WARN_PAREN, ON); }");
	};

	pow10_I64 = CAlloc(sizeof(F64) * (308 + 308 + 1));
	for (i = -308; i < 309; i++)
		pow10_I64[i + 309] = Pow10(i);

	QueueInit(&screencast.sound_head);
	screencast.t0_now	= Now;
	screencast.t0_tS	= tS;
	screencast.ona = screencast.sound_head.ona = 0;

	ProgressBarsReset;

	QueueInit(&dev.pci_head);
	dev.mem64_ptr = mem_mapped_space;

	if (sys_boot_src.u8[0] != BOOT_SRC_RAM)
	{//framebuffer pointer is already linear
		Seg2Linear(&sys_vbe_info.video_modes);
		Seg2Linear(&sys_vbe_info.oem);
		Seg2Linear(&sys_vbe_info.vendor);
		Seg2Linear(&sys_vbe_info.product_name);
		Seg2Linear(&sys_vbe_info.product_revision);
		Seg2Linear(SYS_FONT_PTR);
		sys_vbe_info.software_revision = Bcd2Binary(sys_vbe_info.software_revision);
	}

	debug.fun_seg_cache  = CAlloc(FUN_SEG_CACHE_SIZE * sizeof(CFunSegCache));
	debug.int_fault_code = IntFaultHandlersNew;
}

U0 SysGrInit()
{
	I64 i, j;
	text.aux_font = MAlloc(256 * 8); //256 U64s
	MemCopy(text.aux_font, *SYS_FONT_PTR(U32), 256 * 8);

	for (i = 0; i < 256; i++)
		for (j = 0; j < 8; j++)
			text.aux_font[i].u8[j] = rev_bits_table[text.aux_font[i].u8[j]];

    text.font = sys_font_std;

	//patch some chars
	text.aux_font[10]  = text.font[10]; //"Return" symbol 
	text.aux_font[255] = text.font[255]; //Block symbol ÿ

	text.border_chars[2] (I64) = 'ÄÍ³ºÚÉ¿»';
	text.border_chars[10](U32) = 'ÀÈÙ¼';

	text.cols = sys_vbe_mode.width  / FONT_WIDTH;
	text.rows = sys_vbe_mode.height / FONT_HEIGHT;

	text.screen_size	= sys_vbe_mode.width * sys_vbe_mode.height;
	text.buffer_size	= text.screen_size * 4; //buffer for 32-bit, but only 16 colors now.
	text.raw_screen		= CAlloc(text.buffer_size);
	text.fb_alias		= sys_vbe_mode.framebuffer;

	MemSetU32(text.fb_alias, BLACK32, text.screen_size);
	text.vga_alias = CAlloc(text.rows * text.cols * 8);
}

U0 TimerInit()
{//See $LK,"::/Doc/PIT.DD",A="FI:::/Doc/PIT.DD"$.
	OutU8(PIT_CMD, PIT_CMDF_CHANNEL0 | PIT_CMDF_OPMODE_RATE_GEN | PIT_CMDF_ACCESS_WORD);
	OutU8(PIT_0, SYS_TIMER0_PERIOD);
	OutU8(PIT_0, SYS_TIMER0_PERIOD >> 8);
}

U0 Reboot(Bool format_ramdisks=FALSE)
{//Hardware reset.
	if (format_ramdisks)
	{
		if (DriveIsWritable('A'))
			Format('A',, FALSE, FSt_REDSEA);
		if (DriveIsWritable('B'))
			Format('B',, FALSE, FSt_REDSEA);
	}
	CLI
	if (mp_count > 1)
		MPHalt;
	*0x472(U16 *) = 0;
	OutU8(0x70, 0x8F);
	OutU8(0x71, 0x00);
	OutU8(0x70, 0x00);
	OutU8(0x92, InU8(0x92) | 1);
	SysHlt;
}

U0 KMain()
{//Continued from $LK,"KStart64.CC",A="FF:::/Kernel/KStart64.CC,I32 &KMain"$
	CBlkDev *bd;

	OutU8(PCSPKR, InU8(PCSPKR) & ~3); //Sound;
	zenith_task = Fs;
	BlkPoolsInit;
	SysGlobalsInit;
	Mem32DevInit;
	UncachedAliasAlloc;
	LoadKernel;
	SysGrInit;
	StrCopy(Fs->task_name, "Zenith Task CPU00");
	StrCopy(Fs->task_title, Fs->task_name);
	Fs->title_src = TTS_TASK_NAME;
	Fs->win_right = text.cols - 2;
	Fs->win_top++;
	TaskDerivedValsUpdate;

	SysDefinesLoad;
	Core0Init;
	IntInit1;

	//Before this point use $LK,"Sound",A="MN:Sound"$() and $LK,"Busy",A="MN:Busy"$()
	//to debug.  After this point, use $LK,"RawPrint",A="MN:RawPrint"$()
	LBts(&sys_run_level, RLf_RAW);
	"ZenithOS V%0.2f\t%D %T\n\n", sys_os_version, sys_compile_time, sys_compile_time;

	TimerInit;
	if (MemBIOSTotal < ToI64 (0.95 * MEM_MIN_MEG * 0x100000) )
		RawPrint(4000, "!!! Requires $TX,"256Meg",D="DD_MEM_MIN_MEG"$ of RAM Memory !!!");

	IntPICInit;
	"Enable IRQs\n";
	RFlagsSet(RFLAGG_NORMAL);
	Busy(2000);
	IntInit2;
	LBts(&sys_run_level, RLf_INTERRUPTS);

	TimeCal;
	"BlkDevsInitAll;\n";
	BlkDevsInitAll;
	"DiskChange(':');\n";
	DiskChange(':');

	#exe
	{
		StreamPrint("HomeSet(\"%s\");\n"
					"blkdev.ins_base0  = %d;"
					"blkdev.ins_base1  = %d;"
					"blkdev.ins_unit   = %d;\n",
					kernel_config->home_dir,
					blkdev.ins_base0, blkdev.ins_base1, blkdev.ins_unit);
	}

	Gs->idle_task->cur_dv = blkdev.let_to_drive[*blkdev.home_dir - 'A'];
	DriveRep;
	if (blkdev.dvd_boot_is_good)
	{
		bd = Letter2BlkDev(':');
		if (bd->type == BDT_ATAPI) {
			blkdev.ins_base0 = bd->base0;
			blkdev.ins_base1 = bd->base1;
			blkdev.ins_unit  = bd->unit;
		}
	}
	LBts(&sys_run_level, RLf_BLKDEV);

	#exe
	{
		if (!kernel_config->opts[CONFIG_NO_MP])
			StreamPrint("\"MultiCore Start\\n\\n\";"
						"Core0StartMP;"
						"LBts(&sys_run_level, RLf_MP);");
	};

	KbdMouseInit;
	MouseInit;
	KbdInit;
	Spawn(&MouseHardDriverInstall);

	"Loading Compiler\n";
	Cd("/Compiler");
	Load("Compiler", LDF_SILENT);
	LBts(&sys_run_level, RLf_COMPILER);

	DebugMode(OFF);
	counts.time_stamp_freq_initial = TimeCal;
	Cd("/");
	try
		ExeFile("StartOS"); //Continues $LK,"/StartOS.CC",A="FL:/StartOS.CC,1"$
	catch
	{
		Raw(ON);
		Silent(OFF);
		GetOutOfDollar;
		PutExcept;
		Debug;
	}

	LBts(&sys_run_level, RLf_ZENITH_SERVER);
	ServerTaskCont; //Never to return
}

asm
{

 	ALIGN 	16, OC_NOP
SYS_KERNEL_END::
#exe {
	if (kernel_config->opts[CONFIG_DEBUG_DISTRO])
		StreamPrint("DU8 0x%X - (SYS_KERNEL_END-SYS_KERNEL + BOOT_RAM_BASE + sizeof(CBinFile)) DUP (0);"
					"BINFILE \"%s\";",
					kernel_config->debug_distro_start, kernel_config->debug_distro_file);
};

}
