/*This was done with <CTRL-SHIFT-L> template code.
It's conceptually easy to do a ctrl,
but tedious.  You have complete freedom.

See $LK,"CCtrl",A="MN:CCtrl"$.
*/

//Start of autocreated Code
#define SLIDER_RANGE	255
#define SLIDER_SPACING	28
#define SLIDER_BORDER	2

I64 SELECTED_COLOR = 0;

class CSliderState
{
	I64 left_pos;
	I64 middle_pos;
	I64 right_pos;
	I64 preview;
	CBGR24 color;
} sld;

I0 DrawPixel(I64 x, I64 y, CBGR24 color)
{
	text.fb_alias[x + y * GR_WIDTH] = color;
}

U0 DrawCtrlSlider(CDC *dc,CCtrl *c)
{

	CSliderState *s=c->state;


	//box

	dc->color=LTRED;
	GrRect(dc,	c->left,
				c->top,
				SLIDER_SPACING*4+2,
				SLIDER_SPACING*2+SLIDER_RANGE);
	dc->color=BLUE;
	GrRect(dc,	c->left+SLIDER_BORDER,
				c->top+SLIDER_BORDER,
				SLIDER_SPACING*4+2-2*SLIDER_BORDER,
				SLIDER_SPACING*2+SLIDER_RANGE-2*SLIDER_BORDER);

	//slider

	dc->color=BLACK;

	I64 SLIDER_AMOUNT=3;
	I64 i,k,j,l;
	for(i=1; i<=3; i++){
		GrLine(dc,	c->left+i*SLIDER_SPACING+i-1,
					c->top+SLIDER_SPACING,
					c->left+i*SLIDER_SPACING+i-1,
					c->top+SLIDER_SPACING+SLIDER_RANGE-1);
	}

	//values

	dc->color=LTRED;
	I64 pos,col;

	for(i=1; i<=3; i++){

		if (i==1) { pos=s->left_pos;  col="B";}
		if (i==2) { pos=s->middle_pos;col="G";}
		if (i==3) { pos=s->right_pos; col="R";}

		//values
		GrPrint(dc,	c->left+i*SLIDER_SPACING+i-FONT_WIDTH/2,
					c->top+SLIDER_SPACING+SLIDER_RANGE+8,
					"%d",pos);
		//RGB label
		GrPrint(dc,	c->left+i*SLIDER_SPACING+3-FONT_WIDTH/2,
					c->top+14,
					"%s", col);
		//knobs
		GrRect(dc,	c->left+i*SLIDER_SPACING+i-4,
					c->top+SLIDER_SPACING+SLIDER_RANGE-1-pos-2,
					7,5);
	}


	//color preview
	I64 size=20;

	for(i=0;i<16;i++){
		for (j = 0; j <= size; j++){
			for (k = 0; k <= size; k++){
				CBGR24 tempColor=gr_palette[i];
				// black borders
				if(k==0 || k==size || j==0 || j==size) tempColor=0x000000;
				// color preview
				DrawPixel(size+j+(i*size), c->top + k, tempColor);
			}
		}
		// label
		GrPrint(dc,(size/2)+4+(i*size),c->top - 180, "%d", i+1);
	}

	// current color box preview
	GrPrint(dc,size,c->top,"Current Color in RGB: %u,%u,%u", gr_palette[SELECTED_COLOR].r,
														   	 gr_palette[SELECTED_COLOR].g,
													   		 gr_palette[SELECTED_COLOR].b);
	// pixel loop for current color preview
	for(i=0; i <=size; i++)
		for(j=0; j<=size; j++){			
			tempColor = gr_palette[SELECTED_COLOR];
			if(i==0 || i==size || j==0 || j==size) tempColor = 0x000000;	
			DrawPixel(300 + i, c->top + 160 + j, tempColor);
		}

}


U0 FESave(Bool prompt)
{
	//U8		 old_draw_it = Fs->draw_it;
	CDoc	*doc = DocNew;
	I64		 i;
	U8		 tmp_name= doc->filename.name;
	U8		 name;
	//StrLastRemove(tmp_name,".", name);
	//StrFirstRemove(tmp_name,"/", name);
	
	DocPrint(doc, "public CBGR24 gr_palette_%s[COLORS_NUM] = {\n	", name);
	
	for (i = 0; i < 16; i++)
	{
		if (i == 15) DocPrint(doc, "0x%X", gr_palette[i]);
		else DocPrint(doc, "0x%X, ", gr_palette[i]);

		if (i == 7) {
			DocPrint(doc, "\n	");
		}
	}
	
	DocPrint(doc,"\n};
				\n\n
				public U0 PaletteSet%s(Bool persistent=TRUE)\n
				{\n	GrPaletteSet(gr_palette_%s);\n
					LFBFlush;\n
					if (persistent)\n
						fp_set_std_palette = &PaletteSet%s\n
				}",name,name,name);
	DocWrite(doc, prompt);
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
	for(i=0; i<16; i++){
		"%d: #%X\n",i,gr_palette[i];
	}
}

U0 SelectColor(I64 color_number, CCtrl *c){
	SELECTED_COLOR = color_number;
	CSliderState *s=c->state;

	s->left_pos  = gr_palette[SELECTED_COLOR].r;
	s->middle_pos= gr_palette[SELECTED_COLOR].g;
	s->right_pos = gr_palette[SELECTED_COLOR].b;
}

U0 UpdateDerivedCtrlSlider(CCtrl *c)
{
	CSliderState *s=c->state;

//	c->left=c->win_task->pix_width/2-(SLIDER_SPACING*3+2)/2;
//	c->right=c->left+3*SLIDER_SPACING+2;
//	c->top=c->win_task->pix_height/2-(SLIDER_SPACING*2+SLIDER_RANGE)/2;
//	c->bottom=c->top+SLIDER_SPACING*2+SLIDER_RANGE;

	c->left=c->win_task->pix_width/2;
	c->right=c->left+3*SLIDER_SPACING+2;
	c->top=c->win_task->pix_height/3;
	c->bottom=c->top+SLIDER_SPACING*2+SLIDER_RANGE;

	// I used to clamp between 0 and 127 and do math but i changed it to 256 for now.
	s->left_pos=ClampI64(s->left_pos,0,SLIDER_RANGE);
	s->middle_pos=ClampI64(s->middle_pos,0,SLIDER_RANGE);
	s->right_pos=ClampI64(s->right_pos,0,SLIDER_RANGE);

	// add the slider's BGR value to s->preview
	s->preview = s->left_pos + s->middle_pos << 8 + s->right_pos << 16;
}


U0 LeftClickSlider(CCtrl *c,I64 x,I64 y,Bool)
{
	CSliderState *s=c->state;

	if (x<c->left+1*SLIDER_SPACING+0+SLIDER_SPACING/3)
		s->left_pos=SLIDER_RANGE-1-(y-(c->top+SLIDER_SPACING));

	else if(x<c->left+2*SLIDER_SPACING+1+SLIDER_SPACING/3)
			s->middle_pos=SLIDER_RANGE-1-(y-(c->top+SLIDER_SPACING));
	else
		s->right_pos=SLIDER_RANGE-1-(y-(c->top+SLIDER_SPACING));

	if (c->update_derived_vals)
		(*c->update_derived_vals)(c);

	// set palette
	gr_palette[SELECTED_COLOR] = s->preview;
	PaletteSetTemp(FALSE);
}

CCtrl *SliderNew()
{
	CCtrl *c=CAlloc(sizeof(CCtrl));
	c->win_task=Fs;
	c->flags=CTRLF_SHOW|CTRLF_CAPTURE_LEFT_MS;
	c->type=CTRLT_GENERIC;
	c->state=&sld;
	MemSet(&sld,0,sizeof(CSliderState));
	c->draw_it=&DrawCtrlSlider;
	c->left_click=&LeftClickSlider;
	c->update_derived_vals=&UpdateDerivedCtrlSlider;
	QueueInsert(c,Fs->last_ctrl);
	TaskDerivedValsUpdate;
	return c;
}

U0 SliderDel(CCtrl *c)
{
	QueueRemove(c);
	Free(c);
}

//End of autocreated Code

U0 Main()
{

	SettingsPush;
	WinBorder;
	WinMax;
	WinHorz(0, 50, Fs);
	MenuPush(
		"File {"
		"	New(,'.');"
		//"	ChangeDir(MESSAGE_CMD,PSMF_CD);"
		"	Open(,CH_CTRLO);"
		"	SaveAs(,CH_CTRLA);"
		"	Abort(,CH_SHIFT_ESC);"
		"	Exit(,CH_ESC);"
		"}"
		"Help {"
		"	Help(,,SC_F1);"
		"}"
		);

	//AutoComplete;
	//WinBorder;
	//WinMax;
	//WinTileVert;
	//	WinHorz(50,Fs->win_right);
	//	WinVert(3, Fs->win_bottom);
	//dirname=StrNew("~/Palettes");

	MenuPop;
	DocClear;
	SettingsPop;

	CCtrl *c=SliderNew;

	I64 arg1,arg2,ch=0,sc=0;
	
	"Change colors 1 to 16 using: 1,2,3,4,5,6,7,8,9,0, -, =, q, w, e, r \n";
	//"Current Palette: %s \n";
	//gr_palette;

	try {
		while(TRUE) {
			switch(MessageScan(&arg1,&arg2,1<<MESSAGE_KEY_DOWN|1<<MESSAGE_KEY_UP)) {
				case MESSAGE_KEY_DOWN:
					ch=arg1;
					switch(ch){
						case '1': SelectColor(0,c); break;
						case '2': SelectColor(1,c); break;
						case '3': SelectColor(2,c); break;
						case '4': SelectColor(3,c); break;	
						case '5': SelectColor(4,c); break;
						case '6': SelectColor(5,c); break;
						case '7': SelectColor(6,c); break;
						case '8': SelectColor(7,c); break;
						case '9': SelectColor(8,c); break;
						case '0': SelectColor(9,c); break;
						case '-': SelectColor(10,c);break;
						case '=': SelectColor(11,c);break;
						case 'q': SelectColor(12,c);break;
						case 'w': SelectColor(13,c);break;
						case 'e': SelectColor(14,c);break;
						case 'r': SelectColor(15,c);break;
						case 's': PalettePrint(); break;
						case CH_CTRLA: FESave(TRUE); break;
						case CH_ESC:
						case CH_SHIFT_ESC:
							throw;
					}
					break;
				}
			Refresh;
		}
	}
	catch
		PutExcept;

	
	//SliderDel(c);
	DocBottom;
}

Main;
