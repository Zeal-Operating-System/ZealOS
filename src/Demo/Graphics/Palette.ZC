U0 PaletteDemo()
{
	I64		i, j;
	CBGR24  bgr;

	for (i = 0; i < COLORS_NUM; i++)
		"$$BLACK$$$$BG,%d$$__%-8Z__$$FG$$$$BG$$\n", i, i, "ST_COLORS";

	SettingsPush; //See $LK,"SettingsPush",A="MN:SettingsPush"$
	//Alternatively, use $LK,"GrPaletteSet",A="MN:GrPaletteSet"$(gr_palette_gray);
	for (i = 0; i < COLORS_NUM; i++)
	{
		j = 0xFF * i / (COLORS_NUM - 1);
		bgr.b = j;
		bgr.g = j;
		bgr.r = j;
		gr_palette[i] = bgr;
	}
	PressAKey;

	//You can do it this way, too.
	gr_palette[WHITE] = 0xFFFF00;
	PressAKey;
	LFBFlush;

	//$LK,"SettingsPop",A="MN:SettingsPop"$() restores original palette
	SettingsPop;
}

PaletteDemo;
