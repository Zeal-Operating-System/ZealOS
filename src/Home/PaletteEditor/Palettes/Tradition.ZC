public CBGR24 gr_palette_tradition[COLORS_NUM] = {
0xE8E8E9, 0x374B88, 0x4FBC2C, 0x29CACE, 0xDD0000, 0x8C33FF, 0x875721, 0x7F7A7C, 0x15171C, 0x2EA1FF, 0x4FFF00, 0xFFBB, 0x690000, 0x6E3FFC, 0xFFCC00, 0xC0F14
};
public U0 PaletteSetTradition(Bool persistent=TRUE)
{
	GrPaletteSet(gr_palette_tradition);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetTradition;
}