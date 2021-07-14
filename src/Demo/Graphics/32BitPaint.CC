//#define SQUARE_SIZE		20
//#define SQUARE_GAP		5
//#define SQUARE_DELAY	5 // mS

// paint program globals
class CPaint
{
	// Image Framebuffer
	U32		*fb;

	// Brush
	CBGR24	 color;
	U64		 thick;
	U64		 last_x;
	U64		 last_y;
	U64		 last_thick;

} paint;

U0 PaintGlobalsInit()
{
	paint.fb			= CAlloc(text.buffer_size);
	paint.thick			= 8;
	paint.color			= BLACK32;

	// last cursor position and size
	paint.last_x		= mouse.pos.x;
	paint.last_y		= mouse.pos.y;
	paint.last_thick	= paint.thick;
}


I0 DrawImagePixel(I64 x, I64 y, CBGR24 color)
{
	paint.fb[x + y * GR_WIDTH] = color;
}

I0 DrawScreenPixel(I64 x, I64 y, CBGR24 color)
{
	text.fb_alias[x + y * GR_WIDTH] = color;
}

I0 DrawScreenChar(I64 x, I64 y, I64 char)
{
	I64 i, j;

	for (i = 0; i < FONT_HEIGHT; i++)
		for (j = 0; j < FONT_WIDTH; j++)
			if ((text.font[char] >> (i * 8)) & (1 << j))
				DrawScreenPixel(x + j, y + i, BLACK32);
}

I0 DrawScreenStr(I64 x, I64 y, U8 *str)
{
	I64 c, i = 0;

	while (c = *str++)
	{
		DrawScreenChar(x + (FONT_WIDTH * i++), y, c);
	}
}

I0 DrawImageBrush(I64 x, I64 y, CBGR24 color, I64 thick)
{
	I64 i, j;

	for (i = x; i < x + thick; i++)
		for (j = y; j < y + thick; j++)
			DrawImagePixel(i, j, color);
}

I0 DrawScreenBrush(I64 x, I64 y, CBGR24 color, I64 thick)
{
	I64 i, j;

	for (i = x; i < x + thick; i++)
		for (j = y; j < y + thick; j++)
			DrawScreenPixel(i, j, color);

	paint.last_x		= x;
	paint.last_y		= y;
	paint.last_thick	= thick;

}

I0 Paint32()
{
	I64		 sc, ch, i, j;
	U8		*str_r[STR_LEN],
			*str_g[STR_LEN],
			*str_b[STR_LEN];

	SettingsPush; //See $LK,"SettingsPush",A="MN:SettingsPush"$
	AutoComplete;
	WinBorder;
	WinMax;
	DocCursor;
	DocClear;
	MenuPush("");

	PopUpOk("Press $$GREEN$$0-9$$FG$$ to get colors from current palette.\n"
			"Press $$GREEN$$R, G, or B$$FG$$ to increase color values.\n"
			"Press $$GREEN$$Ctrl-R, Ctrl-G, or Ctrl-B$$FG$$ to decrease.\n"
			"Press $$GREEN$$+ or -$$FG$$ to change brush size.\n"
			"Left-click to draw.");

	text.is_fb_busy = TRUE;
	MemSet(text.fb_alias, WHITE32, text.buffer_size);
	MemSet(paint.fb, WHITE32, text.buffer_size);
	while (TRUE)
	{
		for (i = paint.last_x; i < paint.last_x + paint.last_thick; i++)
			for (j = paint.last_y; j < paint.last_y + paint.last_thick; j++)
				DrawScreenPixel(i, j, paint.fb[i + j * GR_WIDTH]);

		DrawScreenBrush(mouse.pos.x, mouse.pos.y, paint.color, paint.thick);

		if (mouse.lb)
			DrawImageBrush(mouse.pos.x, mouse.pos.y, paint.color, paint.thick);

		StrPrint(str_r, "Red:   %d", paint.color.r);
		StrPrint(str_g, "Green: %d", paint.color.g);
		StrPrint(str_b, "Blue:  %d", paint.color.b);

		for (i = 0; i < 3 * FONT_HEIGHT; i++)
			for (j = 0; j < 12 * FONT_WIDTH; j++)
				DrawScreenPixel(j, i, paint.fb[j + i * GR_WIDTH]);

		DrawScreenStr(0, 0 * FONT_HEIGHT, str_r);
		DrawScreenStr(0, 1 * FONT_HEIGHT, str_g);
		DrawScreenStr(0, 2 * FONT_HEIGHT, str_b);

		Refresh;

		// Get key, process
		KeyScan(&ch, &sc);
		switch (ch)
		{
			case 0:
				switch (sc.u8[0])
				{
					case SC_CURSOR_LEFT:
						break;

					case SC_CURSOR_RIGHT:
						break;

					case SC_CURSOR_UP:
						break;

					case SC_CURSOR_DOWN:
						break;
				}
				break;

			case '+':
				paint.thick++;
				break;
			case '-':
				paint.thick--;
				break;

			case 'r':
				paint.color.r++;
				break;
			case 'g':
				paint.color.g++;
				break;
			case 'b':
				paint.color.b++;
				break;

			case CH_CTRLR:
				paint.color.r--;
				break;
			case CH_CTRLG:
				paint.color.g--;
				break;
			case CH_CTRLB:
				paint.color.b--;
				break;

			case '0'...'9':
				paint.color = gr_palette[ch - '0'];
				break;


			case '\n':
				MemSet(paint.fb, WHITE32, text.buffer_size);
				MemSet(text.fb_alias, WHITE32, text.buffer_size);
				break;

			case CH_SHIFT_ESC:
			case CH_ESC:
				goto paint_done;
		}
	}

paint_done:
	text.is_fb_busy = FALSE;
	LFBFlush;
	SettingsPop;
	MenuPop;
}

PaintGlobalsInit;
Paint32;