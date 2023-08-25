#ifndef PALETTES_PATH
Cd(__DIR__);;
#include "Load"
#endif

// FIXME: $BK,1$bug where holding CTRL for 5-ish seconds crashes program!$BK,0$
// TODO: move to Demo/Graphics, make sprite link in Menu

#define SLIDER_RANGE	255
#define SLIDER_SPACING	28
#define SLIDER_BORDER	2

I64 current_palette = "*New Palette";
I64 selected_color = 0;
I64 l, r, t, b;

U8 *manual_value;

CBGR24 gr_temp_palette[COLORS_NUM];

class CSliderState
{
	I64		left_pos;
	I64		middle_pos;
	I64		right_pos;
	I64		preview;
	CBGR24	color;

} sld;

I0 DrawPixel(I64 x, I64 y, CBGR24 color)
{
	text.fb_alias[x + y * GR_WIDTH] = color;
}

U0 DrawCtrlSlider(CDC *dc, CCtrl *c)
{

	CSliderState *s = c->state;
	I64	size = (c->win_task->pix_width / 16),
		size2 = (c->win_task->pix_height / 32),
		i,
		pos, col,
		bias;

	///////////////////////
	// CURRENT SELECTION //
	///////////////////////

	// current color box preview
	dc->color = BLACK;
	GrPrint(dc, 10, 10, "Preview:");
	GrPrint(dc, 10, 26, "Current Color: #%d", selected_color);

	if (selected_color == 15)
		dc->color = LTGRAY;	
	else if (gr_palette[selected_color] > 0xCCCCCC)
		dc->color = DKGRAY;
	else
		dc->color = 15;
	GrRect(dc, 94, 8, 58, 12);

	// #Hex value
	dc->color = selected_color;
	GrRect(dc, 78, 8, 12, 12);
	GrPrint(dc, 95, 10, "#%x%x%x",	gr_palette[selected_color].r,
									gr_palette[selected_color].g,
									gr_palette[selected_color].b);

	// palette name
	dc->color = BLACK;
	GrPrint(dc, 10, 43, "Palette: %s", current_palette);

	////////////
	// SLIDER //
	////////////

	//box
	dc->color = LTRED;
	GrRect(dc,	c->left,
				c->top,
				SLIDER_SPACING * 4 + 2,
				SLIDER_SPACING * 2 + SLIDER_RANGE);
	dc->color = BLUE;
	GrRect(dc,	c->left + SLIDER_BORDER,
				c->top + SLIDER_BORDER,
				SLIDER_SPACING * 4 + 2 - 2 * SLIDER_BORDER,
				SLIDER_SPACING * 2 + SLIDER_RANGE - 2 * SLIDER_BORDER);

	//slider
	dc->color = BLACK;

	for (i = 1; i <= 3; i++)
	{
		GrLine(dc,	c->left + i * SLIDER_SPACING + i - 1,
					c->top + SLIDER_SPACING,
					c->left + i * SLIDER_SPACING + i - 1,
					c->top + SLIDER_SPACING + SLIDER_RANGE - 1);
	}

	//values
	dc->color = LTRED;

	for (i = 1; i <= 3; i++)
	{
		switch (i)
		{
			case 1:
				pos = s->left_pos;
				col = "R";
				break;
			case 2:
				pos = s->middle_pos;
 				col = "G";
				break;
			case 3:
				pos = s->right_pos;
				col = "B";
				break;
		}

		//values
		GrPrint(dc,	c->left + i * SLIDER_SPACING + i - FONT_WIDTH / 2,
					c->top + SLIDER_SPACING + SLIDER_RANGE + 8,
					"%d", pos);
		//RGB label
		GrPrint(dc,	c->left + i * SLIDER_SPACING + 3 - FONT_WIDTH / 2,
					c->top + 14,
					"%s", col);
		//knobs
		GrRect(dc,	c->left + i * SLIDER_SPACING + i - 4,
					c->top + SLIDER_SPACING + SLIDER_RANGE - 1 - pos - 2,
					7, 5);
	}

	////////////////////
	// COLORS PREVIEW //
	////////////////////

	dc->color = 8;
	GrRect(dc, 0, c->win_task->pix_height + size * 1.5 - size * 2, c->win_task->pix_width, size * 0.75);

	for (i = 0; i < COLORS_NUM; i++)
	{
		// color label and text preview
		// TODO: THIS LOGIC DOESNT WORK ON LIGHT THEMES		
		// if color too light or too dark add bg
		
		if (i == 15)
			dc->color = LTGRAY;
		else if (gr_palette[i] < gr_palette[15])
			dc->color = LTGRAY;
		else if (gr_palette[i] > gr_palette[0])
			dc->color = DKGRAY;
		/*else if (i == 7)
			dc->color = LTRED;*/
		else
			dc->color = 15;
	
		if (i == selected_color)
			dc->color = 0;
		GrRect(dc, 6, (size2 * 2) + 65 + 16 * i, 80, 18);
		GrRect(dc, (size * i), c->win_task->pix_height - (size - size / 2), size, size * 1.5);
		
		GrRect(dc, 6, (size2 * 2) + 65 + 16 * i, 80, 18);

	
		if (i == selected_color)
			dc->color = 15;
		else
			dc->color = i;

		bias = (size / 2) - 4;
		if (i >= 9)
			bias = (size / 2) - 8;

		GrPrint(dc, bias + (i * size), c->win_task->pix_height - (size * .6) + (size / 4), "%d", i);
		GrPrint(dc, 10, (size2 * 2) + 70 + 16 * i, "#%d: Test", i);
		// Border for preview box
		GrRect(dc, (size * i)-2, c->win_task->pix_height - (size*1.5)-1, size+2, size+1);
		// preview box
		dc->color = i;
		GrRect(dc, (size * i), c->win_task->pix_height - (size*1.5), size, size);
	}


	// Add Save/Load button?	
	
}



U0 PESave(Bool prompt, CCtrl *c)
{
	CDoc	*doc = DocNew(PALETTES_PATH);
	I64		 i;
	no_warn c; // TODO remove param if not needed
	U8		*tmp1, *tmp2; // 1: lower, 2: Capital

	if (prompt)
		DocForm(&doc->filename);

	tmp1 = StrNew(&doc->filename.name);
	StrLastRemove(tmp1, "/", tmp1);
	StrReplace(tmp1, ".ZC", "");
	for (i = 0; i < StrLen(tmp1); i++)
		if ('A' <= tmp1[i] <= 'Z')
			tmp1[i] = tmp1[i] + 32;

	tmp2 = StrNew(tmp1);
	tmp2[0] = ToUpper(tmp2[0]);

	DocPrint(doc, "public CBGR24 gr_palette_%s[COLORS_NUM] = {\n", tmp1);

	for (i = 0; i < COLORS_NUM; i++)
	{
		if (i == COLORS_NUM - 1)
			DocPrint(doc, "0x%X", gr_palette[i]);
		else
			DocPrint(doc, "0x%X, ", gr_palette[i]);
	}

	DocPrint(doc,	"\n};\npublic U0 PaletteSet%s(Bool persistent=TRUE)\n{\n"
					"\tGrPaletteSet(gr_palette_%s);\n"
					"\tLFBFlush;\n"
					"\tif (persistent)\n"
					"\t\tfp_set_std_palette = &PaletteSet%s;\n}", tmp2, tmp1, tmp2);

	DocWrite(doc);
	DocDel(doc);
}


U0 PaletteSetTemp(Bool persistent=TRUE)
{//Activate temp palette.
	GrPaletteSet(gr_palette);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetTemp;
}

U0 PalettePrint(){
	I64 i;

	for (i = 0; i < COLORS_NUM; i++)
	{
		"%d: #%X\n", i, gr_palette[i];
	}
}

U0 SelectColor(I64 color_number, CCtrl *c)
{
	selected_color = color_number;
	CSliderState *s = c->state;

	s->left_pos  = gr_palette[selected_color].r;
	s->middle_pos= gr_palette[selected_color].g;
	s->right_pos = gr_palette[selected_color].b;
}

U0 UpdateDerivedCtrlSlider(CCtrl *c)
{
	CSliderState *s = c->state;


	c->left		= (c->win_task->pix_width / 2) - (SLIDER_SPACING * 3 + 2) / 2;
	c->right	= c->left + 3 * SLIDER_SPACING + 2;
	c->top		= c->win_task->pix_height / 2 - (SLIDER_SPACING * 2 + SLIDER_RANGE) / 2;
	c->bottom	= c->top + SLIDER_SPACING * 2 + SLIDER_RANGE;

	// I used to clamp between 0 and 127 and do math but i changed it to 256 for now.
	s->left_pos		= ClampI64(s->left_pos, 0, SLIDER_RANGE);
	s->middle_pos	= ClampI64(s->middle_pos, 0, SLIDER_RANGE);
	s->right_pos	= ClampI64(s->right_pos, 0, SLIDER_RANGE);

	// add the slider's RGB value to s->preview 						// opposite for BGR
	s->preview = s->right_pos + s->middle_pos << 8 + s->left_pos << 16; //s->left_pos + s->middle_pos << 8 + s->right_pos << 16;

	// cheap way to force redraw 32bit colors
	// TODO: make this not stupid
	// can I use *last_task?
	if (c->win_task->pix_left	!= l	||
		c->win_task->pix_right	!= r	||
		c->win_task->pix_bottom != b	||
		c->win_task->pix_top	!= t)
	{
		l = c->win_task->pix_left;
		r = c->win_task->pix_right;
		t = c->win_task->pix_top;
		b = c->win_task->pix_bottom;
		LFBFlush;
	}
}


U0 LeftClickSlider(CCtrl *c, I64 x, I64 y, Bool)
{
	CSliderState *s = c->state;

	if (x < c->left + 1 * SLIDER_SPACING + 0 + SLIDER_SPACING / 3)
		s->left_pos = SLIDER_RANGE - 1 - (y - (c->top + SLIDER_SPACING));

	else if (x < c->left + 2 * SLIDER_SPACING + 1 + SLIDER_SPACING / 3)
		s->middle_pos = SLIDER_RANGE - 1 - (y - (c->top + SLIDER_SPACING));
	else
		s->right_pos = SLIDER_RANGE - 1 - (y - (c->top + SLIDER_SPACING));

	if (c->update_derived_vals)
		(*c->update_derived_vals)(c);

	// set palette
	gr_palette[selected_color] = s->preview;
	PaletteSetTemp(FALSE);

	current_palette = "*New Palette";
}

CCtrl *SliderNew()
{
	CCtrl *c = CAlloc(sizeof(CCtrl));
	c->win_task = Fs;
	c->flags				= CTRLF_SHOW | CTRLF_CAPTURE_LEFT_MS;
	c->type					= CTRLT_GENERIC;
	c->state				= &sld;
	MemSet(&sld,0,sizeof(CSliderState));
	c->draw_it				= &DrawCtrlSlider;
	c->left_click			= &LeftClickSlider;
	c->update_derived_vals	= &UpdateDerivedCtrlSlider;
	QueueInsert(c, Fs->last_ctrl);
	TaskDerivedValsUpdate;
	return c;
}

U0 SliderDel(CCtrl *c)
{
	QueueRemove(c);
	Free(c);
}

public U0 PaletteEditor()
{

	SettingsPush;
	MenuPush(
		"File {"
		"	Open(,CH_CTRLO);"
		"	SaveAs(,CH_CTRLA);"
		"	Abort(,CH_SHIFT_ESC);"
		"	Exit(,CH_ESC);"
		"}"
		"Edit {"
		"	Hex(,'#');"
		"	PreviousColor(,,SC_CURSOR_LEFT);"
		"	PreviousColor(,,SC_CURSOR_UP);"
		"	NextColor(,,SC_CURSOR_RIGHT);"
		"	NextColor(,,SC_CURSOR_DOWN);"
		"	RandomColor(,'r');"
		"	RandomPalette(,'R');"
		"}"
		"About {"
		"	Info(,CH_CTRLI);"
		"}"
		);
	DocClear;
	DocCursor(OFF);
	WinBorder(ON);

	CCtrl *c = SliderNew;
	I64 /*arg1, arg2,*/ sc = 0,
		original_left, original_right, original_top, original_bottom;
	Bool is_done = FALSE, keep_palette = FALSE;
	
	original_left	= c->win_task->win_left;
	original_right	= c->win_task->win_right;
	original_top	= c->win_task->win_top;
	original_bottom	= c->win_task->win_bottom;
	
	// windowed	
	c->win_task->win_left = (GR_WIDTH / 23);
	c->win_task->win_right = (GR_WIDTH / 13);
	c->win_task->win_top = GR_HEIGHT / 80;
	c->win_task->win_bottom = GR_HEIGHT / 10;


	// init pos for 32bit redraw
	l = c->win_task->pix_left;
	r = c->win_task->pix_right;
	t = c->win_task->pix_top;
	b = c->win_task->pix_bottom;


	SelectColor(0, c);

	try
	{
		while (!is_done)
		{
			switch (KeyGet(&sc))
			{
				case '#':
					manual_value = StrGet(" Hex Value: #");
					gr_palette[selected_color] = Str2I64(manual_value, 16);
					Free(manual_value);
					SelectColor(selected_color, c);
					LFBFlush;
					DocClear;
					break;					
				case 0:
					switch (sc.u8[0])
					{
						case SC_CURSOR_UP:
						case SC_CURSOR_LEFT:
							if (selected_color == 0)
								selected_color = 16;
							SelectColor(selected_color - 1, c);
							break;
						case SC_CURSOR_DOWN:
						case SC_CURSOR_RIGHT:
							if (selected_color == 15)
								selected_color = -1;
							SelectColor(selected_color + 1, c);
							break;
					}
					break;
				case CH_CTRLO:
					current_palette = "";
					current_palette = PaletteSelect;
					break;
				case 'r':
					gr_palette[selected_color] = ColorGod;
					LFBFlush;
					break;
				case 'R':	
					PaletteGod;
					break;
				case CH_CTRLI:
					PopUpOk("\n\n  Use the arrows to select color\n\n  # to manually input hex value","\n\n\n\t\tMade by y4my4m\n\n");
					break;
				case CH_CTRLA:
					PESave(TRUE, c);
					break;
				case CH_ESC:
					MemCopy(&gr_temp_palette, gr_palette, sizeof(CBGR24) * COLORS_NUM);
					keep_palette = TRUE;
				case CH_SHIFT_ESC:
					LFBFlush;
					DocClear;
					is_done = TRUE;
			}
			Refresh;
		}
	
	}
	catch
		PutExcept;

	MenuPop;
	SettingsPop;

	if (keep_palette)
		GrPaletteSet(gr_temp_palette);
	
	SliderDel(c);
	DocBottom;


	c->win_task->win_left	= original_left;
	c->win_task->win_right	= original_right;
	c->win_task->win_top 	= original_top;
	c->win_task->win_bottom = original_bottom;
}
