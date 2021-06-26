
// Color palette indexing
#define C_BCKGND		0
#define C_BCKGNDLIGHT	1	// Light for highlights
#define C_BCKGNDSHD		2	// Shade for shadows
#define C_TEXT			3

CBGR24 palette[4] = 
{
	0x282828,	// C_BCKGND
	0x383838,	// C_BCKGNDLIGHT
	0x101010,	// C_BCKGNDSHD
	0xFFFFFF	// C_TEXT
};


/* Draws text button, returns col/row for next button in nCol/nRow. */
U0 DrawTextButton(CTex2D *tex, I64 col, I64 row, U8 *str, I64 size = 0,
	I64 *nCol = NULL, I64 *nRow = NULL)
{
	if (size == 0)
		size = StrLen(str);

	I64 x = col * FONT_WIDTH;
	I64 y = row * FONT_HEIGHT;

	CBGR24 blue = 0x0000FF;
	DrawRectSoftOutline(tex, x - 3, y - 3, x + 1 + size * FONT_WIDTH,
		y + FONT_HEIGHT + 1, palette[C_BCKGNDLIGHT]);

	DrawRectVertGradient(tex, x - 2, y - 2, x + 1 + size * FONT_WIDTH,
		y + FONT_HEIGHT + 1, palette[C_BCKGNDLIGHT], palette[C_BCKGND]);

	DrawString(tex, x, y, str, palette[C_TEXT]);

	if (nCol != NULL)
		*nCol += size + 1;

	if (nRow != NULL)
		*nRow += 2;
}

