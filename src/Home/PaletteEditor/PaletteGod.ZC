
public U0 PaletteGodGenerate()
{
	I64		i;
	CBGR24	palette;

	for (i = 0; i < 16; i++)
	{
		palette = GodPick & 0xFFFFFF;
		gr_palette[i] = palette;
		LFBFlush;
	}
}

PaletteGodGenerate;