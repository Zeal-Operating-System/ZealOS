public CBGR24 gr_palette_temple[COLORS_NUM] = {
0x0, 0xAA, 0xAA00, 0xAAAA, 0xAA0000, 0xAA00AA, 0xAA5500, 0xAAAAAA, 0x555555, 0x5555FF, 0x55FF55, 0x55FFFF, 0xFF5555, 0xFF55FF, 0xFFFF55, 0xFFFFFF
};
public U0 PaletteSetTemple(Bool persistent=TRUE)
{
	GrPaletteSet(gr_palette_temple);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetTemple;
}