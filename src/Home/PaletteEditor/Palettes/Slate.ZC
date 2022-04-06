public CBGR24 gr_palette_slate[COLORS_NUM] = {
0xE3E3E3, 0x4F84A6, 0x73A255, 0x297582, 0xB34F4B, 0x8A52C3, 0xB7822F, 0x444444, 0x6D6D6D, 0x94BFDE, 0xA1CE97, 0x6DB4BE, 0xE88E88, 0xCA94E8, 0xD4B475, 0x1F1F1F
};
public U0 PaletteSetSlate(Bool persistent=TRUE)
{
	GrPaletteSet(gr_palette_slate);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetSlate;
}