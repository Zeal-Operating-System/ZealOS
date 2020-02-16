#define ZERO_BUF_SIZE	2048
U0 BlkWriteZero(CDrive *dv,I64 blk,I64 count)
{//Fill blk count with zeros in Drive.
  I64 n;
  U8 *z=CAlloc(ZERO_BUF_SIZE<<BLK_SIZE_BITS);
  Bool show_progress;
  if (count>ZERO_BUF_SIZE && dv->bd->type!=BDT_RAM) {
    progress1=0; progress1_max=count;
    StrCpy(progress1_desc,"Zeroing");
    show_progress=TRUE;
  } else
    show_progress=FALSE;
  while (count>0) {
    n=count;
    if (n>ZERO_BUF_SIZE)
      n=ZERO_BUF_SIZE;
    BlkWrite(dv,z,blk,n);
    blk+=n;
    count-=n;
    if (show_progress)
      progress1+=n;
    Yield;  //Prevent locking
  }
  Free(z);
  if (show_progress) {
    *progress1_desc=0;
    progress1=progress1_max=0;
  }
}

Bool BlkRead(CDrive *dv,U8 *buf, I64 blk, I64 count)
{//Read blk count from Drive to buf.
  Bool res=TRUE,unlock;
  CBlkDev *bd=dv->bd;
  if (count<=0) return TRUE;
  DriveCheck(dv);
  try {
    unlock=DriveLock(dv);
    BlkDevInit(bd);
    if (dv->drv_offset && blk<dv->drv_offset ||
	  blk+count>dv->drv_offset+dv->size)
      throw('Drive');
    if (bd->flags & BDF_READ_CACHE)
      RCache(dv,&buf,&blk,&count);
    if (count>0) {
      switch (bd->type) {
	case BDT_RAM:
	  MemCpy(buf,bd->RAM_dsk+blk<<BLK_SIZE_BITS,count<<BLK_SIZE_BITS);
	  break;
	case BDT_ISO_FILE_READ:
	case BDT_ISO_FILE_WRITE:
	  FBlkRead(bd->file_dsk,buf,blk,count);
	  break;
	case BDT_ATA:
	case BDT_ATAPI:
	  res=ATARBlks(dv,buf,blk,count);
	  break;
      }
      bd->last_time=tS;
      if (bd->flags & BDF_READ_CACHE)
	DiskCacheAdd(dv,buf,blk,count);
    }
    if (unlock)
      DriveUnlock(dv);
  } catch
    if (unlock)
      DriveUnlock(dv);
  return res;
}

Bool BlkWrite(CDrive *dv,U8 *buf, I64 blk, I64 count)
{//Write blk count from buf to Drive.
  Bool res=TRUE,unlock;
  CBlkDev *bd=dv->bd;
  if (count<=0) return TRUE;
  DriveCheck(dv);
  try {
    unlock=DriveLock(dv);
    BlkDevInit(bd);
    if (bd->flags&BDF_READ_ONLY && !(bd->flags & BDF_READ_ONLY_OVERRIDE))
      throw('BlkDev');
    if (dv->drv_offset && blk<dv->drv_offset ||
	  blk+count>dv->drv_offset+dv->size)
      throw('Drive');
    if (count>0) {
      switch (bd->type) {
	case BDT_RAM:
	  MemCpy(bd->RAM_dsk+blk<<BLK_SIZE_BITS,buf,count<<BLK_SIZE_BITS);
	  break;
	case BDT_ISO_FILE_READ:
	case BDT_ISO_FILE_WRITE:
	  FBlkWrite(bd->file_dsk,buf,blk,count);
	  break;
	case BDT_ATA:
	case BDT_ATAPI:
	  res=ATAWBlks(dv,buf,blk,count);
	  break;
      }
      bd->last_time=tS;
      if (bd->flags & BDF_READ_CACHE)
	DiskCacheAdd(dv,buf,blk,count);
    }
    if (unlock)
      DriveUnlock(dv);
  } catch
    if (unlock)
      DriveUnlock(dv);
  return res;
}
