U0 UnusedSpaceRep()
{
  I64 i;
  CDrive *dv;
  for (i=0;i<26;i++)
    if ((dv=Letter2Drive(i+'A',FALSE)) &&
	  (dv->fs_type==FSt_FAT32 || dv->fs_type==FSt_REDSEA))
      "%C: %7.3f%% Free\n",
	    Drive2Letter(dv),DriveUnused(Drive2Letter(dv))*100.0/(dv->size*BLK_SIZE);
}

UnusedSpaceRep;
