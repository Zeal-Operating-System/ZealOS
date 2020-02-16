//This is run in a $LK,"#exe",A="FF:::/Kernel/Kernel.PRJ,KConfig"${}.

U8 *kernel_config_options="MemInit\0HeapInit\0VarInit\0StaffMode\0"
"HomeDir\0NoMP\0TextMode\0DontProbe\0MountIDEAuto\0DebugDistro\0Help\0";

#define CONFIG_MEM_INIT		0
#define CONFIG_HEAP_INIT		1
#define CONFIG_VAR_INIT		2
#define CONFIG_STAFF_MODE		3
#define CONFIG_HOME_DIR		4
#define CONFIG_NO_MP		5
#define CONFIG_TEXT_MODE		6
#define CONFIG_DONT_PROBE		7
#define CONFIG_MOUNT_IDE_AUTO	8
#define CONFIG_DBG_DISTRO	9
#define CONFIG_OPTIONS_NUM		10

#define CONFIG_HELP		10

class CKConfig
{
  U8 *disk_cache_size_exp;
  CDoc *add_dev;
  U8 *dbg_distro_file,*dbg_distro_start;
  U8 *home_dir;
  Bool opts[CONFIG_OPTIONS_NUM];
  U8 mem_init_val,heap_init_val,var_init_val,
	boot_drive_let,mount_ide_auto_hd_let,mount_ide_auto_cd_let;
};

CDoc *KConfigAddDev(CKConfig *c)
{
  I64 ch;
  CDoc *doc=DocNew;
  "\n\nIn anticipation of the drives you will\n"
	"define shortly, enter the drive letter\n"
	"of the drive with the account directory.\n"
	"\n($$PURPLE$$<ENTER>$$FG$$ for cur drv) Boot Drive:";
  ch=Letter2Letter(GetChar);
  if ('A'<=ch<='Z')
    c->boot_drive_let=ch;
  else
    c->boot_drive_let=Drive2Letter(Fs->cur_dv);
  "\n\n$$BK,1$$$$PURPLE$$Mount drives so they will be present when "
	"you boot.$$FG$$$$BK,0$$\n";
  Mount2(c->boot_drive_let,doc,FALSE);
  return doc;
}

U0 KConfigOptions(CKConfig *c)
{
  I64 i;
  U8 *st=NULL,*st2,*st3;
  Bool state;
  do {
    Free(st);
    for (i=0;i<CONFIG_OPTIONS_NUM;i++)
      if (i==CONFIG_HOME_DIR)
	"$$PURPLE$$%13tz$$FG$$:\"%s\"\n",i,kernel_config_options,c->home_dir;
      else
	"$$PURPLE$$%13tz$$FG$$:%Z\n",i,kernel_config_options,c->opts[i],"ST_OFF_ON";
    "\nType '$$PURPLE$$Help$$FG$$' for help.\n";
    st=GetStr("Option ($$PURPLE$$<ENTER>$$FG$$ when done):","");
    i=ListMatch(st,kernel_config_options,LMF_IGNORE_CASE);
    if (i==CONFIG_HELP)
      "\n"
	    "$$PURPLE$$MemInit$$FG$$ Initializes memory above 0x100000 "
	    "to a val at boot.\n"
	    "$$PURPLE$$HeapInit$$FG$$ Initializes MAlloc() memory to a val.\n"
	    "$$PURPLE$$VarInit$$FG$$ Initializes glbl var memory to a val.\n"
	    "$$PURPLE$$HomeDir$$FG$$ Set home dir.\n"
	    "$$PURPLE$$NoMP$$FG$$ No multicore.\n"
	    "$$PURPLE$$TextMode$$FG$$ Text Mode (requires hard reboot).\n"
	    "$$PURPLE$$DontProbe$$FG$$ Just prompt CD/DVD ports, don't probe.\n"
	    "$$PURPLE$$MountIDEAuto$$FG$$ Auto Mount IDE drives to 'C' and 'T'.\n"
	    "$$PURPLE$$DebugDistro$$FG$$ Include RAM Drive in Kernel.BIN.\n"
	    "\n";
    else
      if (0<=i<CONFIG_OPTIONS_NUM) {
	state=c->opts[i]=!c->opts[i];
	switch (i) {
	  case CONFIG_MEM_INIT:
	    if (state)
	      c->mem_init_val=GetI64("Val (0-255):",255,0,255);
	    break;
	  case CONFIG_HEAP_INIT:
	    if (state)
	      c->heap_init_val=GetI64("Val (0-255):",255,0,255);
	    break;
	  case CONFIG_VAR_INIT:
	    if (state)
	      c->var_init_val=GetI64("Val (0-255):",255,0,255);
	    break;
	  case CONFIG_HOME_DIR:
	    st2=GetStr("Home Dir(\"%s\"):",c->home_dir);
	    if (!*st2)
	      st2=StrNew("::/Home");
	    else if (st2[1]!=':') {
	      st3=MStrPrint("::%s",st2);
	      Free(st2);
	      st2=st3;
	    }
	    Free(c->home_dir);
	    c->home_dir=st2;
	    if (StrCompare(c->home_dir,"::/Home"))
	      c->opts[i]=TRUE;
	    else
	      c->opts[i]=FALSE;
	    break;
	  case CONFIG_MOUNT_IDE_AUTO:
	    if (state) {
	      "First HD Drive Let:";
	      c->mount_ide_auto_hd_let=Letter2Letter(GetChar);
	      if (!('A'<=c->mount_ide_auto_hd_let<='Z'))
		c->mount_ide_auto_hd_let=0;
	      '\n';
	      if (c->mount_ide_auto_hd_let)
		"First HD Drive:%C\n",c->mount_ide_auto_hd_let;
	      else
		"First HD Drive:%C\n",'C';

	      "First CD Drive Let:";
	      c->mount_ide_auto_cd_let=Letter2Letter(GetChar);
	      if (!('A'<=c->mount_ide_auto_cd_let<='Z'))
		c->mount_ide_auto_cd_let=0;
	      '\n';
	      if (c->mount_ide_auto_cd_let)
		"First CD Drive:%C\n",c->mount_ide_auto_cd_let;
	      else
		"First CD Drive:%C\n",'T';
	    } else {
	      c->mount_ide_auto_hd_let=0;
	      c->mount_ide_auto_cd_let=0;
	    }
	    break;
	  case CONFIG_DBG_DISTRO:
	    Free(c->dbg_distro_file);
	    c->dbg_distro_file=0;
	    c->dbg_distro_start=0;
	    if (state) {
	      c->dbg_distro_file=GetStr("Debug Distro File:");
	      c->dbg_distro_start=GetI64("Debug Distro Start:");
	    }
	    break;
	}
      }
  } while (*st);
  Free(st);
}

CKConfig *KConfigNew()
{
  CKConfig *c=CAlloc(sizeof(CKConfig));

  c->add_dev=KConfigAddDev(c);
  c->home_dir=StrNew("::/Home");
  c->disk_cache_size_exp=GetStr(
	"Disk Cache Size in Bytes,\n"
	"gets rounded-up funny,\n"
	"($$PURPLE$$<ENTER>$$FG$$ will use default.):",
	"Scale2Mem(0x80000,0x8000000)");
  KConfigOptions(c);
  return c;
}
 
U0 KConfigDel(CKConfig *c)
{
  DocDel(c->add_dev);
  Free(c->dbg_distro_file);
  Free(c->home_dir);
  Free(c->disk_cache_size_exp);
  Free(c);
}
