Bool DriveLock(CDrive *dv)
{//Make this task have exclusive access to drv & BlkDev.
  DriveCheck(dv);
  BlkDevLock(dv->bd);
  if (!Bt(&dv->locked_flags,DVlf_LOCKED) || dv->owning_task!=Fs) {
    while (LBts(&dv->locked_flags,DVlf_LOCKED))
      Yield;
    dv->owning_task=Fs;
    return TRUE;
  } else
    return FALSE;
}

Bool DriveUnlock(CDrive *dv,Bool rst=FALSE)
{//Release exclusive lock on access to drv & BlkDev.
  DriveCheck(dv);
  if (Bt(&dv->locked_flags,DVlf_LOCKED) && dv->owning_task==Fs) {
    BlkDevUnlock(dv->bd,rst);
    dv->owning_task=NULL;
    LBtr(&dv->locked_flags,DVlf_LOCKED);
    Yield; //Prevent deadlock
    return TRUE;
  } else
    return FALSE;
}

U0 DrivesRelease()
{//When task dies, release all owned drvs.
  I64 i;
  CDrive *dv;
  for (i=0;i<DRVS_NUM;i++) {
    dv=&blkdev.drvs[i];
    if (dv->owning_task==Fs && dv->dv_signature==DRV_SIGNATURE_VAL)
      DriveUnlock(dv,TRUE);
  }
}

CDrive *DriveMakeFreeSlot(U8 drv_let)
{//Make a slot free for a new drv, like during $LK,"Mount",A="MN:Mount"$().
//!!! drv_let is not a $LK,"remapped",A="MN:DriveMap"$ drv.
  I64 i=Letter2Letter(drv_let)-'A';
  CDrive *res;
  if (!(0<=i<DRVS_NUM))
    throw('Drive');
  res=&blkdev.drvs[i];
  MemSet(res,0,sizeof(CDrive));
  res->drv_let='A'+i;
  return res;
}

U8 DriveNextFreeLet(U8 first_drv_let='C')
{//Locate free slot for new drv, like during $LK,"Mount",A="MN:Mount"$().
//!!! first_drv_let is not a $LK,"remapped",A="MN:DriveMap"$ drv.
  I64 i=Letter2Letter(first_drv_let)-'A',type=Letter2BlkDevType(first_drv_let);
  if (!(0<=i<DRVS_NUM))
    throw('Drive');
  do
    if (blkdev.drvs[i].dv_signature!=DRV_SIGNATURE_VAL) {
      if (Letter2BlkDevType(i+'A')!=type)
	throw('Drive');
      else
	return i+'A';
    }
  while (++i<DRVS_NUM);
  throw('Drive');
  return 0; //Never gets here.
}

U0 DriveDel(CDrive *dv)
{//Delete drv
  if (dv->fs_type==FSt_REDSEA && dv->next_free)
    RedSeaFreeFreeLst(dv);
  Free(dv->cur_fat_blk);
  Free(dv->fis);
  MemSet(dv,0,sizeof(CDrive));
}

U0 DriveBlkDevDel(CBlkDev *bd)
{//Delete drv's of BlkDev
  I64 i;
  CDrive *dv;
  for (i=0;i<DRVS_NUM;i++) {
    dv=&blkdev.drvs[i];
    if (dv->bd==bd)
      DriveDel(dv);
  }
}

U0 DriveFATBlkAlloc(CDrive *dv)
{
  DriveCheck(dv);
  Free(dv->cur_fat_blk);
  dv->cur_fat_blk=AMAlloc(BLK_SIZE);
  dv->cur_fat_blk_num=0;
  dv->fat_blk_dirty=0;
  BlkRead(dv,dv->cur_fat_blk,dv->fat1,1);
}

U0 DriveFATBlkClean(CDrive *dv,I64 fat_sel=3)
{
  if ((dv->fs_type==FSt_FAT32 || dv->fs_type==FSt_REDSEA) &&
       Bt(&dv->fat_blk_dirty,0)) {
    if (dv->fat1==dv->fat2) {
      BlkWrite(dv,dv->cur_fat_blk,dv->fat1+dv->cur_fat_blk_num,1);
      LBtr(&dv->fat_blk_dirty,0);
    } else {
      if (fat_sel==3 || !fat_sel)
	BlkWrite(dv,dv->cur_fat_blk,dv->fat1+dv->cur_fat_blk_num,1);
      if (fat_sel==3 || fat_sel==1) {
	BlkWrite(dv,dv->cur_fat_blk,dv->fat2+dv->cur_fat_blk_num,1);
	LBtr(&dv->fat_blk_dirty,0);
      }
    }
  }
}

U0 DriveFATBlkSet(CDrive *dv,I64 c,I64 fat_sel=3)
{
  I64 fat_blk_num;
  if (c==INVALID_CLUS)
    throw('Drive');
  switch (dv->fs_type) {
    case FSt_FAT32:
      fat_blk_num=c>>(BLK_SIZE_BITS-2);
      break;
    case FSt_REDSEA:
      fat_blk_num=(c-dv->data_area)>>(BLK_SIZE_BITS+3);
      break;
    default:
      throw('Drive');
  }
  if (fat_blk_num!=dv->cur_fat_blk_num) {
    DriveFATBlkClean(dv,fat_sel);
    dv->cur_fat_blk_num=fat_blk_num;
    if (fat_sel==3 || !fat_sel)
      BlkRead(dv,dv->cur_fat_blk,dv->fat1+dv->cur_fat_blk_num,1);
    else
      BlkRead(dv,dv->cur_fat_blk,dv->fat2+dv->cur_fat_blk_num,1);
  }
}

CDrive *DriveCheck(CDrive *dv,Bool except=TRUE)
{//Check for valid drv. Throw exception.
  if (!dv || dv->dv_signature!=DRV_SIGNATURE_VAL) {
    if (except)
      throw('Drive');
    else
      return NULL;
  } else
    return dv;
}

U8 Drive2Letter(CDrive *dv=NULL)
{//Drive ptr to Drive letter.
  if (!dv)
    dv=Fs->cur_dv;
  DriveCheck(dv);
  return dv->drv_let;
}

U8 Letter2Letter(U8 drv_let=0)
{//Drive letter to Drive letter.
  if (!drv_let)
    drv_let=Drive2Letter(Fs->cur_dv);
  else if (drv_let==':')
    drv_let=blkdev.boot_drv_let;
  else if (drv_let=='~')
    drv_let=*blkdev.home_dir;
  return ToUpper(drv_let);
}

I64 Letter2BlkDevType(U8 drv_let)
{//Drive letter to BlkDev Type. drv_let=0 not allowed. See $LK,"BDT_NULL",A="MN:BDT_NULL"$.
  drv_let=Letter2Letter(drv_let);
  if ('A'<=drv_let<='B')
    return BDT_RAM;
  if ('C'<=drv_let<='L')
    return BDT_ATA;
  if ('M'<=drv_let<='P')
    return BDT_ISO_FILE_READ;
  if ('Q'<=drv_let<='S')
    return BDT_ISO_FILE_WRITE;
  if ('T'<=drv_let<='Z')
    return BDT_ATAPI;
  return BDT_NULL;
}

CDrive *Letter2Drive(U8 drv_let=0,Bool except=TRUE)
{//Drive letter to Drive ptr.
  CDrive *dv;
  if (!drv_let)
    dv=Fs->cur_dv;
  else {
    drv_let=Letter2Letter(drv_let);
    if (!('A'<=drv_let<='Z')) {
      if (except)
	throw('Drive');
      else
	return NULL;
    }
    dv=blkdev.let_to_drv[drv_let-'A'];
  }
  return DriveCheck(dv,except);
}

CBlkDev *DriveIsWritable(U8 drv_let=0,Bool except=FALSE)
{//Is drive writable?
  CBlkDev *bd;
  if (!(bd=Letter2BlkDev(drv_let,except)) || bd->flags & BDF_READ_ONLY) {
    if (except)
      throw('Drive');
    else
      return NULL;
  } else
    return bd;
}

U0 DiskCacheInvalidate(CDrive *dv)
{//Needed for removable media. Called by $LK,"DiskChg",A="MN:DiskChg"$().
  Bool unlock;
  CBlkDev *bd=dv->bd;
  DriveCheck(dv);
  try {
    unlock=DriveLock(dv);
    BlkDevInit(bd);
    if (bd->flags & BDF_READ_CACHE)
      DiskCacheInvalidate2(dv);
    if (bd->type==BDT_ATAPI && !(bd->flags & BDF_READ_ONLY_OVERRIDE))
      ISOInit(dv,(32767/bd->blk_size+1)*bd->blk_size>>BLK_SIZE_BITS);
    if (unlock)
      DriveUnlock(dv);
  } catch
    if (unlock)
      DriveUnlock(dv);
}

U0 DiskChg(U8 drv_let=0)
{//Change disk. (Needed for removable media.)
  CDrive *dv=Letter2Drive(drv_let);
  CBlkDev *bd=dv->bd;
  if (!(bd->flags&BDF_INITIALIZED))
    BlkDevInit(bd);
  else if (bd->flags&BDF_REMOVABLE) {
    if (bd->type==BDT_ATAPI)
      ATAInit(bd); //TODO: This is a kludge for QEMU?
    DiskCacheInvalidate(dv);
  }
  Drive(drv_let);
  RedSeaFreeFreeLst(dv);
}

Bool DriveMap(U8 drv_let,CDrive *dv)
{//Make drive letter map to another.
  drv_let=Letter2Letter(drv_let);
  if ('A'<=drv_let<='Z') {
    blkdev.let_to_drv[drv_let-'A']=dv;
    dv->drv_let=drv_let;
    return TRUE;
  } else
    return FALSE;
}

Bool Drive(U8 drv_let)
{//Change drive.  You can set drive with $LK,"Cd",A="MN:Cd"$() as well.
  CDrive *dv=Letter2Drive(drv_let);
  CBlkDev *bd;
  bd=BlkDevCheck(dv->bd);
  if (dv!=Fs->cur_dv) {
    if (bd->flags & BDF_REMOVABLE && !(bd->flags & BDF_INITIALIZED))
      DiskChg(Drive2Letter(dv));
    if (bd->type==BDT_RAM ||
	bd->type==BDT_ISO_FILE_READ || bd->type==BDT_ISO_FILE_WRITE)
      BlkDevInit(bd);
  }
  Fs->cur_dv=dv;
  Free(Fs->cur_dir);
  Fs->cur_dir=StrNew("/");
  switch (dv->fs_type) {
    case FSt_REDSEA:
    case FSt_FAT32:
      return TRUE;
    default:
      PrintErr("File System Not Supported\n");
      return FALSE;
  }
}

U8 *DriveSerialNum(U8 drv_let=0)
{//20 bytes max.
  CBlkDev *bd=Letter2BlkDev(drv_let);
  U16 *st,*res=NULL;
  I64 i;
  if (bd->dev_id_record) {
    st=CAlloc(20+1);
    for (i=0;i<10;i++)
      st[i]=EndianU16(bd->dev_id_record[10+i]);
    res=MStrUtil(st,SUF_REM_LEADING|SUF_REM_TRAILING);
    Free(st);
  }
  return res;
}

U8 *DriveModelNum(U8 drv_let=0)
{//40 bytes max.
  CBlkDev *bd=Letter2BlkDev(drv_let);
  U16 *st,*res=NULL;
  I64 i;
  if (bd->dev_id_record) {
    st=CAlloc(40+1);
    for (i=0;i<20;i++)
      st[i]=EndianU16(bd->dev_id_record[27+i]);
    res=MStrUtil(st,SUF_REM_LEADING|SUF_REM_TRAILING);
    Free(st);
  }
  return res;
}

U8 blkdev_text_attr[BDT_TYPES_NUM]={BLACK,LTCYAN,WHITE,LTGREEN,LTRED,LTBLUE};
U8 drv_text_attr[3]={BLACK,BLUE,RED};

U8 DriveTextAttrGet(U8 drv_let=0)
{//Get color of drive.
  drv_let=Letter2Letter(drv_let);
  if ('A'<=drv_let<='Z')
    return blkdev_text_attr[Letter2BlkDevType(drv_let)]<<4|
	  drv_text_attr[drv_let%sizeof(drv_text_attr)];
  else
    return BLACK<<4|WHITE;
}

U0 DriveRep()
{//Drive report.
  CDrive *dv;
  CBlkDev *bd;
  I64 ch,i,drv_let,attr;
  U8 *st;
  "\nDefined Drives:\n";
  for (i=0,dv=blkdev.drvs;i<DRVS_NUM;i++,dv++) {
    if (dv->dv_signature==DRV_SIGNATURE_VAL) {
      bd=dv->bd;
      drv_let=Drive2Letter(dv);
      if (Bt(&dv->fs_type,FStf_DISABLE))
	ch='-';
      else if (drv_let==blkdev.boot_drv_let)
	ch=':';
      else
	ch='+';
      attr=DriveTextAttrGet(drv_let);
      "$$FG,%d$$$$BG,%d$$%C %-8Z %-10Z %04X %04X %02X\n",
	    attr&15,attr>>4,drv_let,dv->fs_type&FSG_TYPE_MASK,"ST_DRV_TYPES",
	    bd->type,"ST_BLKDEV_TYPES",bd->base0,bd->base1,bd->unit;
      if (st=DriveModelNum(drv_let)) {
	"Model#:%s\n",st;
	Free(st);
      }
      if (st=DriveSerialNum(drv_let)) {
	"Serial#:%s\n",st;
	Free(st);
      }
      if (bd->type==BDT_ISO_FILE_READ || bd->type==BDT_ISO_FILE_WRITE)
	"File=\"%s\"\n",bd->file_dsk_name;
      "%016X-%016X\n$$FG$$$$BG$$",dv->drv_offset,dv->drv_offset+dv->size-1;
    }
  }
  "Home Dir:\"%s\"\n",blkdev.home_dir;
}
