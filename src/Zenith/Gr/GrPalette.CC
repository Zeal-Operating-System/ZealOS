#help_index "Graphics/Color"
public U8 gr_rainbow_10[10] = {BLACK,BROWN,RED,LTRED,YELLOW,GREEN,BLUE,PURPLE,LTGRAY,WHITE};

DefineListLoad("ST_RAINBOW_10","BLACK\0BROWN\0RED\0LTRED\0YELLOW\0GREEN\0BLUE\0PURPLE\0LTGRAY\0WHITE\0");

public CBGR48 gr_palette_std[COLORS_NUM]={
0x000000000000,0x00000000AAAA,0x0000AAAA0000,0x0000AAAAAAAA,
0xAAAA00000000,0xAAAA0000AAAA,0xAAAA55550000,0xAAAAAAAAAAAA,
0x555555555555,0x55555555FFFF,0x5555FFFF5555,0x5555FFFFFFFF,
0xFFFF55555555,0xFFFF5555FFFF,0xFFFFFFFF5555,0xFFFFFFFFFFFF};

public CBGR24 gr_palette_gruvbox_light[COLORS_NUM] = {
  0x3C3836, 0x076678, 0x79740E, 0x427B58, 0x9D0006, 0x8F3F71, 0xB57614, 0x928374,
  0x7C6F64, 0x458588, 0x98971A, 0x689D6A, 0xCC241D, 0xB16286, 0xD79921, 0xFBF1C7
};

public CBGR24 gr_palette_pastel[COLORS_NUM]={
  0xE8E8D3, 0x8197BF, 0x19CB00, 0x668799, 0xCF6A4C, 0x8787AF, 0xFAD07A, 0x525252,
  0x888888, 0xACCAFF, 0x23FD00, 0x80BFAF, 0xFF9D80, 0xC4C4FF, 0xFFEFBF, 0x151515
};

public CBGR24 gr_palette_gray[COLORS_NUM] = {
  0x000000, 0x111111, 0x222222, 0x333333, 0x444444, 0x555555, 0x666666, 0x777777,
  0x888888, 0x999999, 0xAAAAAA, 0xBBBBBB, 0xCCCCCC, 0xDDDDDD, 0xEEEEEE, 0xFFFFFF
};

public U0 GrPaletteGet(CBGR24 *bgr24)
{//16 colors
  MemCopy(bgr24, &gr_palette, sizeof(CBGR24) * 16);
}

public U0 GrPaletteSet(CBGR48 *bgr24)
{//16 colors
  MemCopy(&gr_palette, bgr24, sizeof(CBGR24) * 16);
}

public U0 PaletteSetGray(Bool persistent=TRUE)
{//Activate gray palette.
  GrPaletteSet(gr_palette_gray);
  VGAFlush;
  if (persistent)
    fp_set_std_palette = &PaletteSetGray;
}


public U0 PaletteSetGruvboxLight(Bool persistent=TRUE)
{//Activate std palette.
  GrPaletteSet(gr_palette_gruvbox_light);
  VGAFlush;
  if (persistent)
    fp_set_std_palette = &PaletteSetGruvboxLight;
}


public U0 PaletteSetPastel(Bool persistent=TRUE)
{//Activate std palette.
  GrPaletteSet(gr_palette_pastel);
  VGAFlush;
  if (persistent)
    fp_set_std_palette = &PaletteSetPastel;
}

