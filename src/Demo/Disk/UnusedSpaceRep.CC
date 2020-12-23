U0 UnusedSpaceRep()
{
	I64		i;
	CDrive *drive;

	for (i = 0; i < 26; i++)
		if ((drive = Letter2Drive(i + 'A', FALSE)) && (drive->fs_type == FSt_FAT32 || drive->fs_type == FSt_REDSEA))
			"%C: %7.3f%% Free\n", Drive2Letter(drive), DriveUnused(Drive2Letter(drive)) * 100.0 / (drive->size * BLK_SIZE);
}

UnusedSpaceRep;
