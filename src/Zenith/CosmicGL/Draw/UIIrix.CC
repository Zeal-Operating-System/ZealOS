
/* Draws text button, returns col/row for next button in nCol/nRow. */
U0 DrawTextButton(CTex2D *tex, I64 col, I64 row, U8 *str, I64 size = 0,
	I64 *nCol = NULL, I64 *nRow = NULL)
{
	if (size == 0)
		size = StrLen(str);

	I64 x = col * FONT_WIDTH;
	I64 y = row * FONT_HEIGHT;

	DrawRectSoftOutline(tex, x - 3, y - 3, x + 1 + size * FONT_WIDTH,
		y + FONT_HEIGHT + 1, gr_palette[DKGRAY]);

	DrawRectVertGradient(tex, x - 2, y - 2, x + 1 + size * FONT_WIDTH,
		y + FONT_HEIGHT + 1, gr_palette[DKGRAY], gr_palette[WHITE]);

	DrawString(tex, x, y, str, gr_palette[BLACK ]);

	if (nCol != NULL)
		*nCol += size + 1;

	if (nRow != NULL)
		*nRow += 2;
}
