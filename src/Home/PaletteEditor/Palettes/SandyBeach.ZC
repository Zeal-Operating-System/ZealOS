public CBGR24 gr_palette_sandy_beach[COLORS_NUM] = {
0x000000, 0x000088, 0x008800, 0x006060, 0x002288, 0x4B0082, 0xA52A2A, 0xAAAAAA, 0x444444, 0x4169E1, 0xADFF2F, 0x00AAAA, 0xFF8888, 0x9932CC, 0xC09020, 0xFFF8DF
};
public U0 PaletteSetSandyBeach(Bool persistent=TRUE)
{
	GrPaletteSet(gr_palette_sandy_beach);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetSandyBeach;
}
