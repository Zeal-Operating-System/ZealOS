I64 ClusNumNext(CDrive *dv,I64 c,I64 cnt=1)
{//Return next cnt'th clus in chain.
  Bool unlock;
  DriveCheck(dv);
  if (cnt<=0) return c;
  try {
    unlock=DriveLock(dv);
    switch (dv->fs_type) {
      case FSt_REDSEA:
	c+=cnt;
	break;
      case FSt_FAT32:
	while (cnt-->0 && 0<c<0x0FFFFFF8) {
	  DriveFATBlkSet(dv,c);
	  c=dv->cur_fat_blk[c & (BLK_SIZE/4-1)];
	}
	if (!(0<c<0x0FFFFFF8))
	  c=INVALID_CLUS;
	break;
      default:
	throw('Drive');
    }
    if (unlock)
      DriveUnlock(dv);
  } catch
    if (unlock)
      DriveUnlock(dv);
  return c;
}

I64 Clus2Blk(CDrive *dv,I64 c)
{//Drive clus num to blk num.
  DriveCheck(dv);
  switch (dv->fs_type) {
    case FSt_REDSEA:
      return c;
    case FSt_FAT32:
      return dv->data_area+c*dv->spc;
    default:
      throw('Drive');
  }
}

I64 ClusBlkRead(CDrive *dv,U8 *buf,I64 c,I64 blks)
{//Accepts blk count, so padding on last clus is not read.
  I64 i;
  Bool unlock;
  DriveCheck(dv);
  if (blks<=0) return c;
  try {
    unlock=DriveLock(dv);
    switch (dv->fs_type) {
      case FSt_REDSEA:
	BlkRead(dv,buf,c,blks);
	c+=blks;
	break;
      case FSt_FAT32:
	while (blks && 0<c<0x0FFFFFF8) {
	  i=blks;
	  if (i>dv->spc)
	    i=dv->spc;
	  BlkRead(dv,buf,dv->data_area+c*dv->spc,i);
	  buf+=i<<BLK_SIZE_BITS;
	  c=ClusNumNext(dv,c,1);
	  blks-=i;
	}
	if (blks)
	  throw('Drive');
	break;
      default:
	throw('Drive');
    }
    if (unlock)
      DriveUnlock(dv);
  } catch
    if (unlock)
      DriveUnlock(dv);
  return c;
}

I64 ClusRead(CDrive *dv,U8 *buf,I64 c,I64 cnt)
{//Read clus cnt from drv to buf.
  return ClusBlkRead(dv,buf,c,cnt*dv->spc);
}

I64 ClusBlkWrite(CDrive *dv,U8 *buf,I64 c,I64 blks)
{//Accepts blk count, so padding on last clus is not written.
  I64 i;
  Bool unlock;
  DriveCheck(dv);
  if (blks<=0) return c;
  try {
    unlock=DriveLock(dv);
    switch (dv->fs_type) {
      case FSt_REDSEA:
	BlkWrite(dv,buf,c,blks);
	c=0;
	break;
      case FSt_FAT32:
	while (blks) {
	  if (!(0<c<0x0FFFFFF8))
	    throw('Drive');
	  i=blks;
	  if (i>dv->spc)
	    i=dv->spc;
	  BlkWrite(dv,buf,dv->data_area+c*dv->spc,i);
	  buf+=i<<BLK_SIZE_BITS;
	  c=ClusNumNext(dv,c);
	  blks-=i;
	}
	break;
      default:
	throw('Drive');
    }
    if (unlock)
      DriveUnlock(dv);
  } catch
    if (unlock)
      DriveUnlock(dv);
  return c;
}

I64 ClusWrite(CDrive *dv,U8 *buf,I64 c,I64 cnt)
{//Write clus cnt from buf to drv.
  return ClusBlkWrite(dv,buf,c,cnt*dv->spc);
}

I64 ClusAlloc(CDrive *dv,I64 c=0,I64 cnt=1,Bool contiguous=FALSE)
{//Alloc clus cnt into chain.
//c=0 means first clus in chain
  DriveCheck(dv);
  if (cnt<=0) return c;
  switch (dv->fs_type) {
    case FSt_REDSEA:
      return RedSeaAllocClus(dv,cnt);
    case FSt_FAT32:
      if (contiguous) {
	if (c) throw('File');
	return FAT32AllocContiguousClus(dv,cnt);
      } else
	return FAT32AllocClus(dv,c,cnt);
    default:
      throw('Drive');
  }
}
