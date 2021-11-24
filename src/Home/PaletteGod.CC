
public U0 PaletteGodGenerate()
{

	I64 i;
	for(i=0; i<16; i++)
	{
		CBGR24 palette = GodPick & 0xFFFFFF;
		gr_palette[i] = palette;
		GrPaletteSet(gr_palette);
		LFBFlush;
	}
}
PaletteGodGenerate;