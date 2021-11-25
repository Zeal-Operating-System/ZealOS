public CBGR24 gr_palette_zsnes[COLORS_NUM] = {
0xE8E8E9, 0x374B88, 0x6C84FC, 0x297582, 0x63D64E, 0x397AFF, 0xB7822F, 0x25256E, 0x712, 0xFF2A76, 0xA1CE97, 0x6DB4BE, 0x9FA6FF, 0xCA94E8, 0xFFCC00, 0x132C
};
public U0 PaletteSetZsnes(Bool persistent=TRUE)
{
	GrPaletteSet(gr_palette_zsnes);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetZsnes;
}