#help_index "Graphics/Color"
public U8 gr_rainbow_10[10] = {BLACK, BROWN, RED, LTRED, YELLOW, GREEN, BLUE, PURPLE, LTGRAY, WHITE};

DefineListLoad("ST_RAINBOW_10", "BLACK\0BROWN\0RED\0LTRED\0YELLOW\0GREEN\0BLUE\0PURPLE\0LTGRAY\0WHITE\0");

public U0 GrPaletteGet(CBGR24 *bgr24)
{//16 colors
	MemCopy(bgr24, &gr_palette, sizeof(CBGR24) * 16);
}

public U0 GrPaletteSet(CBGR24 *bgr24)
{//16 colors
	MemCopy(&gr_palette, bgr24, sizeof(CBGR24) * 16);
}

//legacy
public CBGR48 gr_palette_std[COLORS_NUM] = {
	0x000000000000, 0x00000000AAAA, 0x0000AAAA0000, 0x0000AAAAAAAA,
	0xAAAA00000000, 0xAAAA0000AAAA, 0xAAAA55550000, 0xAAAAAAAAAAAA,
	0x555555555555, 0x55555555FFFF, 0x5555FFFF5555, 0x5555FFFFFFFF,
	0xFFFF55555555, 0xFFFF5555FFFF, 0xFFFFFFFF5555, 0xFFFFFFFFFFFF};

//********************************************************************************
public CBGR24 gr32_palette_std[COLORS_NUM] = {
	0x000000, 0x0000AA, 0x00AA00, 0x00AAAA, 0xAA0000, 0xAA00AA, 0xAA5500, 0xAAAAAA,
	0x555555, 0x5555FF, 0x55FF55, 0x55FFFF, 0xFF5555, 0xFF55FF, 0xFFFF55, 0xFFFFFF
};

public U0 PaletteSetStd(Bool persistent=TRUE)
{//Activate std palette.
	GrPaletteSet(gr32_palette_std);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetStd;
}
//********************************************************************************
public CBGR24 gr_palette_gray[COLORS_NUM] = {
	0x000000, 0x111111, 0x222222, 0x333333, 0x444444, 0x555555, 0x666666, 0x777777,
	0x888888, 0x999999, 0xAAAAAA, 0xBBBBBB, 0xCCCCCC, 0xDDDDDD, 0xEEEEEE, 0xFFFFFF
};

public U0 PaletteSetGray(Bool persistent=TRUE)
{//Activate gray palette.
	GrPaletteSet(gr_palette_gray);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetGray;
}

//********************************************************************************
public CBGR24 gr_palette_gruvbox_light[COLORS_NUM] = {
	0x3C3836, 0x076678, 0x79740E, 0x427B58, 0x9D0006, 0x8F3F71, 0xB57614, 0x928374,
	0x7C6F64, 0x458588, 0x98971A, 0x689D6A, 0xCC241D, 0xB16286, 0xD79921, 0xFBF1C7
};

public U0 PaletteSetGruvboxLight(Bool persistent=TRUE)
{//Activate gruvbox light palette.
	GrPaletteSet(gr_palette_gruvbox_light);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetGruvboxLight;
}

//********************************************************************************
public CBGR24 gr_palette_gruvbox_dark[COLORS_NUM] = {
	0xEBDBB2, 0x458588, 0x98971A, 0x689D6A, 0xCC241D, 0xB16286, 0xD79921, 0x504945,
	0x928374, 0x83A598, 0xB8BB26, 0x8EC07C, 0xFB4934, 0xD3869B, 0xFABD2F, 0x282828
};

public U0 PaletteSetGruvboxDark(Bool persistent=TRUE)
{//Activate gruvbox light palette.
	GrPaletteSet(gr_palette_gruvbox_dark);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetGruvboxDark;
}

//********************************************************************************
public CBGR24 gr_palette_pastel[COLORS_NUM] = {
	0xE8E8D3, 0x8197BF, 0x19CB00, 0x668799, 0xCF6A4C, 0x8787AF, 0xFAD07A, 0x525252,
	0x888888, 0xACCAFF, 0x23FD00, 0x80BFAF, 0xFF9D80, 0xC4C4FF, 0xFFEFBF, 0x151515
};


public U0 PaletteSetPastel(Bool persistent=TRUE)
{//Activate pastel palette.
	GrPaletteSet(gr_palette_pastel);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetPastel;
}

//********************************************************************************
public CBGR24 gr_palette_monokai[COLORS_NUM] = {
	0x272822, 0x01549E, 0x74AA04, 0x1A83A6, 0xA70334, 0x89569C, 0xB6B649, 0xCACACA,
	0x7C7C7C, 0x0373F5, 0x8DD006, 0x58C2E5, 0xF3044B, 0xA87DB8, 0xCCCC81, 0xFFFFFF
};

public U0 PaletteSetMonokai(Bool persistent=TRUE)
{//Activate monokai palette.
	GrPaletteSet(gr_palette_monokai);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetMonokai;
}

//********************************************************************************
public CBGR24 gr_palette_dark[COLORS_NUM] = {
	0xFFFFFF, 0x6095C5, 0x6D9E3F, 0x3BA275, 0xD370A3, 0xAC7BDE, 0xB58858, 0x686868,
	0x404040, 0x98CBFE, 0xA3D572, 0x75DAA5, 0xFFA7DA, 0xE5B0FF, 0xEFBD8B, 0x232323
};

public U0 PaletteSetDark(Bool persistent=TRUE)
{//Activate dark palette.
	GrPaletteSet(gr_palette_dark);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetDark;
}

//********************************************************************************
public CBGR24 gr_palette_smooth[COLORS_NUM] = {
	0xDDDDDD, 0x4E9FB1, 0xA0CF5D, 0x42717B, 0xD23D3D, 0x8542FF, 0xF39D21, 0x404040,
	0x707070, 0x7DC1CF, 0xB8D68C, 0x6D878D, 0xE84F4F, 0x9B64FB, 0xE1AA5D, 0x151515
};

public U0 PaletteSetSmooth(Bool persistent=TRUE)
{//Activate smooth palette.
	GrPaletteSet(gr_palette_smooth);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetSmooth;
}

//********************************************************************************
public CBGR24 gr_palette_dorado[COLORS_NUM] = {
	0xFFFFFF, 0x5879AF, 0x468459, 0x008592, 0xA9635D, 0x9C6594, 0x84763D, 0x4E4E4E,
	0x777777, 0xB3D1FF, 0x9DDEAF, 0x79E0ED, 0xFFBBB2, 0xFABDF0, 0xE0CE91, 0x292929
};

public U0 PaletteSetDorado(Bool persistent=TRUE)
{//Activate dorado palette.
	GrPaletteSet(gr_palette_dorado);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetDorado;
}

//********************************************************************************
public CBGR24 gr_palette_night[COLORS_NUM] = {
	0xDDDDDD, 0xAAAAFF, 0xAAAA00, 0x0000AA, 0xAA5555, 0xAA55AA, 0xAA5500, 0x444444,
	0x555555, 0x5555FF, 0x55FF55, 0x55FFFF, 0xFF5555, 0xFF55FF, 0xFFFF55, 0x111111
};

public U0 PaletteSetNight(Bool persistent=TRUE)
{//Activate night palette.
	GrPaletteSet(gr_palette_night);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetNight;
}
//********************************************************************************
public CBGR24 gr_palette_tom[COLORS_NUM] = {
	0xFFFFFF, 0x3465A4, 0x4E9A06, 0x06989A, 0xA24444, 0x75507B, 0xCE982F, 0xBCC0B9,
	0x555753, 0x729FCF, 0x82BC49, 0x34E2E2, 0xAC3535, 0xAD7FA8, 0xFCE94F, 0x000000
};

public U0 PaletteSetTom(Bool persistent=TRUE)
{//Activate tom's palette.
	GrPaletteSet(gr_palette_tom);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetTom;
	//*(drv_text_attr(U8 *) + 1) = BROWN;
}
//********************************************************************************
public CBGR24 gr_palette_tom_light[COLORS_NUM] = {
	0x000000, 0x3465A4, 0x4E9A06, 0x06989A, 0xA24444, 0x75507B, 0xBF8718, 0xB2B6AF,
	0x555753, 0x729FCF, 0x82BC49, 0x00BBC8, 0xAC3535, 0xAD7FA8, 0xC7AB00, 0xFEF1F0
};

public U0 PaletteSetTomLight(Bool persistent=TRUE)
{//Activate tom's light palette.
	GrPaletteSet(gr_palette_tom_light);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetTomLight;
}
//********************************************************************************
