/**
	@ingroup GLDraw
	@brief Draw a single color character to color texture.

	Will not draw character if partially off-screen.

	@param[in,out] tex	Texture to draw to.
	@param[in]     x	X position to draw character at.
	@param[in]     y	Y position to draw character at.
*/
U0 GLDrawChar(CGLTex2D *tex, I64 x, I64 y, U8 char, CBGR24 color, 
	U64 *font = text.font)
{
	// Check if off-screen
	if (x >= tex->w || x <= -FONT_WIDTH)
		return;

	I64 i, j;
	for (j = 0; j < FONT_HEIGHT; j++)
	{
		for (i = 0; i < FONT_WIDTH; i++)
		{
			if (font[char].u8[j] & 1 << i)
				tex->rawBuf[x + i + (y + j) * tex->w] = color;
		}
	}
}

/**
	@ingroup GLDraw
	@brief Draw a single color string to color texture.

	Escape sequences are not working correctly.

	@param[in,out] tex		Texture to draw to.
	@param[in]     x		X position to draw text at.
	@param[in]     y		Y position to draw text at.
	@param[in]     color	Color of text.
	@param[in]     font		Pointer to font buffer. System font by default.
*/
U0 GLDrawString(CGLTex2D *tex, I64 x, I64 y, U8 *str, CBGR24 color,
	U64 *font = text.font)
{
	I64 cur = 0,	// String cursor
		xCur, yCur;	// Screen cursors 

	xCur = x;
	yCur = y;

	while (str[cur] != NULL)
	{
		switch (str[cur])
		{
			// Escape sequence
			case '\\':
				switch (str[cur + 1])
				{
					case 'n':
						xCur = x;
						yCur += FONT_HEIGHT;
						"NEWLINE\n";
						break;

					// Not a real tab, but what mong uses tabs in labels?
					case 't':
						xCur += FONT_WIDTH * 4;
						break;
					
					case '\\':
						GLDrawChar(tex, xCur, yCur, '\\', color, font);
						xCur += FONT_WIDTH;
						break;
						
				}
				cur += 2;
				break;

			case ' ':
				cur++;
				xCur += FONT_WIDTH;
				break;

			default:
				GLDrawChar(tex, xCur, yCur, str[cur], color, font);
				cur++;
				xCur += FONT_WIDTH;
				break;
		}
	}
}