//This is run in a $LK,"#exe",A="FF:::/Kernel/Kernel.PRJ,KConfig"${}.

U8 *kernel_config_options = "MemInit\0"
							"HeapInit\0"
							"VarInit\0"
							"HomeDir\0"
							"NoMP\0"
							"DontProbe\0"
							"MountIDEAuto\0"
							"DebugDistro\0"
							"Help";

#define CONFIG_MEM_INIT 		0
#define CONFIG_HEAP_INIT		1
#define CONFIG_VAR_INIT 		2
#define CONFIG_HOME_DIR 		3
#define CONFIG_NO_MP			4
#define CONFIG_DONT_PROBE 		5
#define CONFIG_MOUNT_IDE_AUTO 	6
#define CONFIG_DEBUG_DISTRO 	7
#define CONFIG_OPTIONS_NUM		8

#define CONFIG_HELP				8

class CKConfig
{
	U8		*disk_cache_size_exp;
	CDoc	*add_dev;
	U8		*debug_distro_file, *debug_distro_start;
	U8		*home_dir;
	U16		screen_width, screen_height;
	Bool	opts[CONFIG_OPTIONS_NUM];
	U8		mem_init_val, heap_init_val, var_init_val, boot_drive_let, mount_ide_auto_hd_let, mount_ide_auto_cd_let;
};

CDoc *KConfigAddDev(CKConfig *c)
{
	I64   ch;
	CDoc *doc = DocNew;

	"\n\nIn anticipation of the drives you will define shortly, enter the drive letter\n"
	"of the drive with your Home directory. ($$PURPLE$$<ENTER>$$FG$$ for current drive) Boot Drive:";

	ch = Letter2Letter(CharGet);
	if ('A' <= ch <= 'Z')
		c->boot_drive_let = ch;
	else
		c->boot_drive_let = Drive2Letter(Fs->cur_dv);

	"\n\n$$BK,1$$$$PURPLE$$Mount drives so they will be present when you boot.$$FG$$$$BK,0$$\n";

	Mount2(c->boot_drive_let, doc, FALSE);

	return doc;
}

U0 KConfigOptions(CKConfig *c)
{
	I64  i;
	U8  *st = NULL, *st2, *st3;
	Bool state;
	do
	{
		Free(st);
		for (i = 0; i < CONFIG_OPTIONS_NUM; i++)
			if (i == CONFIG_HOME_DIR)
				"$$PURPLE$$%13tz$$FG$$:\"%s\"\n", i, kernel_config_options, c->home_dir;
			else
				"$$PURPLE$$%13tz$$FG$$:%Z\n", i, kernel_config_options, c->opts[i], "ST_OFF_ON";
		"\nType '$$PURPLE$$Help$$FG$$' for help.\n";
		st = StrGet("Option ($$PURPLE$$<ENTER>$$FG$$ when done):", "");
		i = ListMatch(st, kernel_config_options, LMF_IGNORE_CASE);
		if (i == CONFIG_HELP)
			"\n"
			"$$PURPLE$$MemInit$$FG$$ Initializes memory above 0x100000 "
			"to a val at boot.\n"
			"$$PURPLE$$HeapInit$$FG$$ Initializes MAlloc() memory to a val.\n"
			"$$PURPLE$$VarInit$$FG$$ Initializes global var memory to a val.\n"
			"$$PURPLE$$HomeDir$$FG$$ Set home dir.\n"
			"$$PURPLE$$NoMP$$FG$$ No multicore.\n"
			"$$PURPLE$$DontProbe$$FG$$ Just prompt CD/DVD ports, don't probe.\n"
			"$$PURPLE$$MountIDEAuto$$FG$$ Auto Mount IDE drives to 'C' and 'T'.\n"
			"$$PURPLE$$DebugDistro$$FG$$ Include RAM Drive in Kernel.BIN.\n"
			"\n";
		else
			if (0 <= i < CONFIG_OPTIONS_NUM)
			{
				state = c->opts[i] = !c->opts[i];
				switch (i)
				{
					case CONFIG_MEM_INIT:
						if (state)
							c->mem_init_val = I64Get("Val (0-255):", 255, 0, 255);
						break;

					case CONFIG_HEAP_INIT:
						if (state)
							c->heap_init_val = I64Get("Val (0-255):", 255, 0, 255);
						break;

					case CONFIG_VAR_INIT:
						if (state)
							c->var_init_val = I64Get("Val (0-255):", 255, 0, 255);
						break;

					case CONFIG_HOME_DIR:
						st2 = StrGet("Home Dir(\"%s\"):", c->home_dir);
						if (!*st2)
							st2 = StrNew("::/Home");
						else if (st2[1] != ':')
						{
							st3 = MStrPrint("::%s", st2);
							Free(st2);
							st2 = st3;
						}
						Free(c->home_dir);
						c->home_dir = st2;
						if (StrCompare(c->home_dir, "::/Home"))
							c->opts[i] = TRUE;
						else
							c->opts[i] = FALSE;
						break;

					case CONFIG_MOUNT_IDE_AUTO:
						if (state)
						{
							"First HD Drive Let:";
							c->mount_ide_auto_hd_let = Letter2Letter(CharGet);
							if (!('A' <= c->mount_ide_auto_hd_let <= 'Z'))
								c->mount_ide_auto_hd_let = 0;
							'\n';
							if (c->mount_ide_auto_hd_let)
								"First HD Drive:%C\n", c->mount_ide_auto_hd_let;
							else
								"First HD Drive:%C\n", 'C';

							"First CD Drive Let:";
							c->mount_ide_auto_cd_let = Letter2Letter(CharGet);
							if (!('A' <= c->mount_ide_auto_cd_let <= 'Z'))
								c->mount_ide_auto_cd_let = 0;
							'\n';
							if (c->mount_ide_auto_cd_let)
								"First CD Drive:%C\n", c->mount_ide_auto_cd_let;
							else
								"First CD Drive:%C\n", 'T';
						}
						else
						{
							c->mount_ide_auto_hd_let = 0;
							c->mount_ide_auto_cd_let = 0;
						}
						break;

					case CONFIG_DEBUG_DISTRO:
						Free(c->debug_distro_file);
						c->debug_distro_file  = 0;
						c->debug_distro_start = 0;
						if (state)
						{
							c->debug_distro_file  = StrGet("Debug Distro File:");
							c->debug_distro_start = I64Get("Debug Distro Start:");
						}
						break;
				}
			}
	}
	while (*st);

	Free(st);
}

CKConfig *KConfigNew()
{
	I64		  resolution_num;
	CKConfig *c = CAlloc(sizeof(CKConfig));

	c->add_dev = KConfigAddDev(c);
	c->home_dir = StrNew("::/Home");

	VideoRep(FALSE);
	resolution_num = I64Get("Enter list number of desired resolution, "
							"or desired width. ($$PURPLE$$<ENTER>$$FG$$ for auto maximum): ",, 1);
	if (resolution_num <= VBE_MODES_NUM)
	{
		c->screen_width  = sys_vbe_modes[resolution_num - 1].width;
		c->screen_height = sys_vbe_modes[resolution_num - 1].height;
	}
	else
	{
		c->screen_width  = resolution_num;
		c->screen_height = I64Get("Enter Height: ",, 0);
	}
 

	c->disk_cache_size_exp = StrGet("\nDisk Cache Size in Bytes, gets rounded-up funny, "
									"($$PURPLE$$<ENTER>$$FG$$ will use default.):",
									"Scale2Mem(0x80000,0x8000000)");
	KConfigOptions(c);

	return c;
}
 
U0 KConfigDel(CKConfig *c)
{
	DocDel(c->add_dev);
	Free(c->debug_distro_file);
	Free(c->home_dir);
	Free(c->disk_cache_size_exp);
	Free(c);
}
