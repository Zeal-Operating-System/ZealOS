public CBGR24 gr_palette_vapor[COLORS_NUM] = {
0xE3E3E3, 0x3284F0, 0x55587C, 0xBF3584, 0xB34F4B, 0x9EE9EF, 0xD2865B, 0x444444, 0x6D6D6D, 0x8BD2B7, 0xA1CE97, 0xCB99CD, 0xE88E88, 0xFDBEA4, 0xFF8F9D, 0x2A1B39
};
public U0 PaletteSetVapor(Bool persistent=TRUE)
{
	GrPaletteSet(gr_palette_vapor);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetVapor;
}