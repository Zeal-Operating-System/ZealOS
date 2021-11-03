/*This was done with <CTRL-SHIFT-L> template code.
It's conceptually easy to do a ctrl,
but tedious.  You have complete freedom.

See $LK,"CCtrl",A="MN:CCtrl"$.
*/

//Start of autocreated Code
#define SLIDER_RANGE	128
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
	GrRect(dc, c->left,c->top,SLIDER_SPACING*4+2,SLIDER_SPACING*2+SLIDER_RANGE);
	dc->color=BLUE;
	GrRect(dc, c->left+SLIDER_BORDER,c->top+SLIDER_BORDER,
				SLIDER_SPACING*4+2-2*SLIDER_BORDER,
				SLIDER_SPACING*2+SLIDER_RANGE-2*SLIDER_BORDER);
	//slider
	dc->color=BLACK;
	GrLine(dc,c->left+1*SLIDER_SPACING+0,c->top+SLIDER_SPACING,
				c->left+1*SLIDER_SPACING+0,c->top+SLIDER_SPACING+SLIDER_RANGE-1);
	GrLine(dc,c->left+2*SLIDER_SPACING+1,c->top+SLIDER_SPACING,
				c->left+2*SLIDER_SPACING+1,c->top+SLIDER_SPACING+SLIDER_RANGE-1);
	GrLine(dc,c->left+3*SLIDER_SPACING+2,c->top+SLIDER_SPACING,
				c->left+3*SLIDER_SPACING+2,c->top+SLIDER_SPACING+SLIDER_RANGE-1);
	//values
	dc->color=LTRED;
	GrPrint(dc,c->left+1*SLIDER_SPACING+2-FONT_WIDTH/2,
				c->top+SLIDER_SPACING+SLIDER_RANGE+8,
				"%d",s->left_pos*259/SLIDER_RANGE);
	GrPrint(dc,c->left+2*SLIDER_SPACING+2-FONT_WIDTH/2,
				c->top+SLIDER_SPACING+SLIDER_RANGE+8,
				"%d",s->middle_pos*259/SLIDER_RANGE);
	GrPrint(dc,c->left+3*SLIDER_SPACING+3-FONT_WIDTH/2,
				c->top+SLIDER_SPACING+SLIDER_RANGE+8,
				"%d",s->right_pos*259/SLIDER_RANGE);

	GrPrint(dc,c->left+1*SLIDER_SPACING+3-FONT_WIDTH/2,
				c->top+14,"%s","B");
	GrPrint(dc,c->left+2*SLIDER_SPACING+3-FONT_WIDTH/2,
				c->top+14,"%s","G");
	GrPrint(dc,c->left+3*SLIDER_SPACING+4-FONT_WIDTH/2,
				c->top+14,"%s","R");

	//knobs
	GrRect(dc,c->left+1*SLIDER_SPACING+0-3,
				c->top+SLIDER_SPACING+SLIDER_RANGE-1-s->left_pos-2,7,5);
	GrRect(dc,c->left+2*SLIDER_SPACING+1-3,
				c->top+SLIDER_SPACING+SLIDER_RANGE-1-s->middle_pos-2,7,5);
	GrRect(dc,c->left+3*SLIDER_SPACING+2-3,
				c->top+SLIDER_SPACING+SLIDER_RANGE-1-s->right_pos-2,7,5);

	dc->color=YELLOW;
	GrRect(dc,c->left+1*SLIDER_SPACING+0-2,
				c->top+SLIDER_SPACING+SLIDER_RANGE-1-s->left_pos-1,5,3);
	GrRect(dc,c->left+2*SLIDER_SPACING+1-2,
				c->top+SLIDER_SPACING+SLIDER_RANGE-1-s->middle_pos-1,5,3);
	GrRect(dc,c->left+3*SLIDER_SPACING+2-2,
				c->top+SLIDER_SPACING+SLIDER_RANGE-1-s->right_pos-1,5,3);


	//color preview
	I64 i, j, k;
	// sizeof shows more colors?...probably cause im retarded
    //    for (i = 0; i < sizeof(gr_palette); i++)
	for(i=0;i<16;i++){
		for (j = 0; j <= 20; j++){
			for (k = 0; k <= 20; k++){
					if(k==0 || k==20 || j==0 || j==20) DrawPixel(20+j+(i*30), c->top + k, 0x000000);
					else DrawPixel(20+j+(i*30), c->top + k, gr_palette[i]);
			}
		}
		GrPrint(dc,15+(i*30),240, "%d", i+1);

	}
	GrPrint(dc,20,c->top,"Current Color in RGB:%u,%u,%u", gr_palette[SELECTED_COLOR] & 0xFF,
													   gr_palette[SELECTED_COLOR] >> 8 & 0xFF,
													   gr_palette[SELECTED_COLOR] >> 16 & 0xFF);
	for(i=0; i <=20; i++)
		for(j=0; j<=20; j++){			
			if(i==0 || i==20 || j==0 || j==20) DrawPixel(300+i, c->top + 160 + j, 0x000000);	
			else DrawPixel(300 + i, c->top + 160 + j, gr_palette[SELECTED_COLOR]);
		}

}

//public CBGR24 gr_palette_temp[16] = {
//	0xFFFFFF, 0x3465A4, 0x4E9A06, 0x06989A, 0xA24444, 0x75507B, 0xCE982F, 0xBCC0B9,
//	0x555753, 0x729FCF, 0x82BC49, 0x34E2E2, 0xAC3535, 0xAD7FA8, 0xFCE94F, 0x000000
//};

public U0 PaletteSetTemp(Bool persistent=TRUE)
{//Activate temp palette.
	GrPaletteSet(gr_palette);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetTemp;
}

U0 UpdateDerivedCtrlSlider(CCtrl *c)
{
	CSliderState *s=c->state;
	c->left=c->win_task->pix_width/2-(SLIDER_SPACING*3+2)/2;
	c->right=c->left+3*SLIDER_SPACING+2;
	c->top=c->win_task->pix_height/2-(SLIDER_SPACING*2+SLIDER_RANGE)/2;
	c->bottom=c->top+SLIDER_SPACING*2+SLIDER_RANGE;
//	s->left_pos=ClampI64(s->left_pos,0,SLIDER_RANGE-1);
//	s->middle_pos=ClampI64(s->middle_pos,0,SLIDER_RANGE-1);
//	s->right_pos=ClampI64(s->right_pos,0,SLIDER_RANGE-1);

//	s->left_pos  = gr_palette[SELECTED_COLOR] & 0xFF;
//	s->middle_pos= gr_palette[SELECTED_COLOR] >> 8 & 0xFF;
//	s->right_pos = gr_palette[SELECTED_COLOR] >> 16 & 0xFF;

	s->left_pos=ClampI64(s->left_pos,gr_palette[SELECTED_COLOR] & 0xFF,SLIDER_RANGE-1);
	s->middle_pos=ClampI64(s->middle_pos,gr_palette[SELECTED_COLOR] >> 8 & 0xFF,SLIDER_RANGE-1);
	s->right_pos=ClampI64(s->right_pos,gr_palette[SELECTED_COLOR] >> 16 & 0xFF,SLIDER_RANGE-1);

	
	I64 previewB = ClampI64(s->left_pos,0,255);	
	I64 previewG = ClampI64(s->middle_pos,0,255);
	I64 previewR = ClampI64(s->right_pos,0,255);

	s->preview = previewB + previewG << 8 + previewR << 16;
	
	//gr_palette_temp = GrPaletteGet;	
	//gr_palette_temp[2] = preview*2;
	//PaletteSetTemp;
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
	gr_palette[SELECTED_COLOR] = s->preview*2;
	PaletteSetTemp;
	LFBFlush; //why is this used?
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

	AutoComplete;
	//WinBorder;
	//WinMax;

	//dirname=StrNew("~/Palettes");

	MenuPop;
	DocClear;
	SettingsPop;

	//"This is to demo ctrls.\n";
	CCtrl *c=SliderNew;
	//PressAKey;
	//"Left: %d Middle:%d Right: %d\n",

	sld.left_pos*10/SLIDER_RANGE,
	sld.middle_pos*10/SLIDER_RANGE,
	sld.right_pos*10/SLIDER_RANGE;

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
						case '1': "1";	sld.left_pos=0;sld.middle_pos=0;sld.right_pos=0; SELECTED_COLOR=0;	break;
						case '2': "2";	sld.left_pos=0;sld.middle_pos=0;sld.right_pos=0; SELECTED_COLOR=1;	break;
						case '3': "3";	sld.left_pos=0;sld.middle_pos=0;sld.right_pos=0; SELECTED_COLOR=2;	break;
						case '4': "4";	sld.left_pos=0;sld.middle_pos=0;sld.right_pos=0; SELECTED_COLOR=3;	break;	
						case '5': "5";	sld.left_pos=0;sld.middle_pos=0;sld.right_pos=0; SELECTED_COLOR=4;	break;
						case '6': "6";	sld.left_pos=0;sld.middle_pos=0;sld.right_pos=0; SELECTED_COLOR=5;	break;
						case '7': "7";	sld.left_pos=0;sld.middle_pos=0;sld.right_pos=0; SELECTED_COLOR=6;	break;
						case '8': "8";	sld.left_pos=0;sld.middle_pos=0;sld.right_pos=0; SELECTED_COLOR=7;	break;
						case '9': "9";	sld.left_pos=0;sld.middle_pos=0;sld.right_pos=0; SELECTED_COLOR=8;	break;
						case '0': "10";	sld.left_pos=0;sld.middle_pos=0;sld.right_pos=0; SELECTED_COLOR=9;	break;
						case '-': "11";	sld.left_pos=0;sld.middle_pos=0;sld.right_pos=0; SELECTED_COLOR=10;	break;
						case '=': "12";	sld.left_pos=0;sld.middle_pos=0;sld.right_pos=0; SELECTED_COLOR=11;	break;
						case 'q': "13";	sld.left_pos=0;sld.middle_pos=0;sld.right_pos=0; SELECTED_COLOR=12;	break;
						case 'w': "14";	sld.left_pos=0;sld.middle_pos=0;sld.right_pos=0; SELECTED_COLOR=13;	break;
						case 'e': "15";	sld.left_pos=0;sld.middle_pos=0;sld.right_pos=0; SELECTED_COLOR=14;	break;
						case 'r': "16";	sld.left_pos=0;sld.middle_pos=0;sld.right_pos=0; SELECTED_COLOR=15;	break;

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