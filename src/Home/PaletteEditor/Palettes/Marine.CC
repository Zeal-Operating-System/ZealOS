public CBGR24 gr_palette_marine[COLORS_NUM] = {
	0xE2E8EB, 0x5BD2D4, 0x47515D, 0xB46D29, 0xB34F4B, 0xCB711F, 0xFFEF2F, 0x3D272F, 
	0xA161C, 0xE24594, 0xA1CE97, 0x6DB4BE, 0xFF575B, 0xB1AA9E, 0xD4B475, 0xE2331
};

public U0 PaletteSetMarine(Bool persistent=TRUE)
{
	GrPaletteSet(gr_palette_marine);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetMarine;
}