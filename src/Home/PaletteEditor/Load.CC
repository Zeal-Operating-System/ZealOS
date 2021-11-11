#define SLIDER_RANGE	255
#define SLIDER_SPACING	28
#define SLIDER_BORDER	2


#define PALETTES_PATH	"~/PaletteEditor/Palettes/"


#include "~/PaletteEditor/PaletteSelect"

I64 current_palette = "temp";

I64 SELECTED_COLOR = 0;
I64 l,r,t,b;


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


	//GrPrint(dc,0,50,"%s", current_palette);

	I64 size=(c->win_task->pix_width/16);
	I64 border=size/16;
	I64 SLIDER_AMOUNT=3;
	I64 i,k,j,l;
	I64 pos,col;
	CBGR24 tempColor;

	///////////////////////
	// CURRENT SELECTION //
	///////////////////////

	// current color box preview
	dc->color=BLACK;
	GrPrint(dc,10,10,"Preview:");

	// pixel loop for current color preview
	for(i=0; i<=12; i++)
		for(j=0; j<=12; j++)
		{
			tempColor = gr_palette[SELECTED_COLOR];
			if(i<border || i>12-border || j<border || j>12-border) tempColor = 0x000000;	
			DrawPixel(c->win_task->pix_left + 78 + i, t + 7 + j, tempColor);
		}
	GrPrint(dc,10,26,"Current Color: #%d", SELECTED_COLOR+1);
	if(SELECTED_COLOR == 15) dc->color = LTGRAY;	
	else if(gr_palette[SELECTED_COLOR] > 0xCCCCCC) dc->color=DKGRAY;
	else dc->color=15;
	GrRect(dc,94,8,58,12);

	dc->color=SELECTED_COLOR;
	GrPrint(dc,95,10,"#%x%x%x",	gr_palette[SELECTED_COLOR].r,
								gr_palette[SELECTED_COLOR].g,
								gr_palette[SELECTED_COLOR].b);


	////////////
	// SLIDER //
	////////////

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

	for(i=1; i<=3; i++)
	{
		GrLine(dc,	c->left+i*SLIDER_SPACING+i-1,
					c->top+SLIDER_SPACING,
					c->left+i*SLIDER_SPACING+i-1,
					c->top+SLIDER_SPACING+SLIDER_RANGE-1);
	}

	//values
	dc->color=LTRED;

	for(i=1; i<=3; i++)
	{

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

	////////////////////
	// COLORS PREVIEW //
	////////////////////

	dc->color=8;
	GrRect(dc,0,c->win_task->pix_height + size*1.5 - size*2 ,c->win_task->pix_width,size*0.75);

	for(i=0;i<16;i++){
		for (j = 0; j <= size; j++){
			for (k = 0; k <= size; k++){
				tempColor=gr_palette[i];
				// black borders
				if(k<border || k>size-border || j < border || j>size-border-1)
				{
					if(SELECTED_COLOR==i) tempColor=0xFFFFFF;
					else tempColor=0x000000;
				}
				// color preview
				DrawPixel(c->win_task->pix_left + j + (size*i), c->win_task->pix_bottom - size*1.5 + k, tempColor);
			}
		}
		// color label and text preview
		// TODO: THIS LOGIC DOESNT WORK ON LIGHT THEMES		
		// if color too light or too dark add bg

		if(i==15) dc->color = LTGRAY;
		else if(gr_palette[i] < gr_palette[15]) dc->color=LTGRAY;
		else if(gr_palette[i] > gr_palette[0]) dc->color=DKGRAY;
		//else if(i == 7) dc->color=LTRED;	
		else dc->color=15;
		if(i == SELECTED_COLOR)	dc->color=0; GrRect(dc,6,(size*2)+65+16*i,80,18);
		GrRect(dc,(size*i),c->win_task->pix_height-(size-size/2),size,size*1.5);
		
		GrRect(dc,6,(size*2)+65+16*i,80,18);
	
	
		if(i == SELECTED_COLOR)	dc->color=15;
		else dc->color=i;
		I64 bias=(size/2)-4;
		if(i >= 9) bias = (size/2)-8;
		//	if(i == SELECTED_COLOR){
		//	blink selected color coroutine?	
		//}
		GrPrint(dc,bias+(i*size),c->win_task->pix_height-(size*.6)+(size/4), "%d", i+1);
		GrPrint(dc,10,(size*2)+70+16*i,"#%d: Test",i+1);
	}


	// Add Save/Load button?	
	
}



U0 PESave(Bool prompt, CCtrl *c)
{
	//U8		 old_draw_it = c->draw_it;
	CDoc	*doc = DocNew(PALETTES_PATH);
	I64		 i;
//	U8		 tmp_name= doc->filename.name;
//	I64		 file_name;
//	FileExtRemove(tmp_name);
//	StrLastRemove(tmp_name, "/", file_name);

	
//	DocPrint(doc, "public CBGR24 gr_palette_%s[COLORS_NUM] = {\n	", file_name);
	
	for (i = 0; i < COLORS_NUM; i++)
	{
		if (i == COLORS_NUM-1) DocPrint(doc, "0x%X", gr_palette[i]);
		else DocPrint(doc, "0x%X, ", gr_palette[i]);

//		if (i == 7) {
//			DocPrint(doc, "\n	");
//		}
	}
	
//	StrCopy	
//	StrFirstRemove(file_name+1, StrLen(file_name));

//	DocPrint(doc,"\n};
//				\n\npublic U0 PaletteSet%s(Bool persistent=TRUE)\n{\n\tGrPaletteSet(gr_palette_%s);\n\tLFBFlush;\n\tif (persistent)\n\t\tfp_set_std_palette = &PaletteSet%s\n}",
//				file_name,file_name,file_name);
	// TODO: supposed to make draw_it null and put it back to blank the window when saving...
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

	s->left_pos  = gr_palette[SELECTED_COLOR].b;
	s->middle_pos= gr_palette[SELECTED_COLOR].g;
	s->right_pos = gr_palette[SELECTED_COLOR].r;
}

U0 UpdateDerivedCtrlSlider(CCtrl *c)
{
	CSliderState *s=c->state;


	c->left=(c->win_task->pix_width/2)-(SLIDER_SPACING*3+2)/2;
	c->right=c->left+3*SLIDER_SPACING+2;
	c->top=c->win_task->pix_height/2-(SLIDER_SPACING*2+SLIDER_RANGE)/2;
	c->bottom=c->top+SLIDER_SPACING*2+SLIDER_RANGE;

	// I used to clamp between 0 and 127 and do math but i changed it to 256 for now.
	s->left_pos=ClampI64(s->left_pos,0,SLIDER_RANGE);
	s->middle_pos=ClampI64(s->middle_pos,0,SLIDER_RANGE);
	s->right_pos=ClampI64(s->right_pos,0,SLIDER_RANGE);

	// add the slider's BGR value to s->preview
	s->preview = s->left_pos + s->middle_pos << 8 + s->right_pos << 16;

	// cheap way to force redraw 32bit colors
	// TODO: make this not stupid
	// can I use *last_task?
	if (c->win_task->pix_left	!= l	||
		c->win_task->pix_right	!= r	||
		c->win_task->pix_bottom != b	||
		c->win_task->pix_top	!= t){
		l=c->win_task->pix_left;
		r=c->win_task->pix_right;
		t=c->win_task->pix_top;
		b=c->win_task->pix_bottom;
		LFBFlush;
	}
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
		"About {"
		"	Info(,CH_CTRLI);"
		"}"
		);
	DocClear;

	CCtrl *c=SliderNew;

	I64 arg1,arg2,sc=0;
	I64 original_left, original_right, original_top, original_bottom;
	
	original_left	= c->win_task->win_left;
	original_right	= c->win_task->win_right;
	original_top	= c->win_task->win_top;
	original_bottom	= c->win_task->win_bottom;
	
	// windowed	
	c->win_task->win_left = (GR_WIDTH/23);
	c->win_task->win_right = (GR_WIDTH/13);
	
	// c->win_task->win_right = c->win_task->win_width - 85;
	c->win_task->win_top = GR_HEIGHT/80;
	c->win_task->win_bottom = GR_HEIGHT/10;//c->win_task->win_height;


	// init pos for 32bit redraw
	l=c->win_task->pix_left;
	r=c->win_task->pix_right;
	t=c->win_task->pix_top;
	b=c->win_task->pix_bottom;


	SelectColor(0,c);

	try
	{
		while(TRUE)
		{
			switch(KeyGet(&sc))
			{
				case 0:
					switch (sc.u8[0])
					{
						case SC_CURSOR_LEFT:
							if(SELECTED_COLOR==0) SELECTED_COLOR=16;
							SelectColor(SELECTED_COLOR-1,c);
							break;
						case SC_CURSOR_RIGHT:
							if(SELECTED_COLOR==15) SELECTED_COLOR=-1;
							SelectColor(SELECTED_COLOR+1,c);
							break;		
					}
				break;
				case CH_CTRLO: current_palette = PaletteSelect; break;
				case CH_CTRLI: PopUpOk("\n\n Use Left and Right arrows to select color\n\n\n\t\t\tMade by y4my4m"); break;$ID,2$
				case CH_CTRLA: PESave(TRUE,c);break;
				case CH_ESC: // should make it keep palette on ESC and discard on SHIFT_ESC
				case CH_SHIFT_ESC:
					LFBFlush;
					DocClear;
					throw;
			}
			Refresh;
		}
	
	}
	catch
		PutExcept;

	MenuPop;
	SettingsPop;
	
	SliderDel(c);
	DocBottom;


	c->win_task->win_left	= original_left;
	c->win_task->win_right	= original_right;
	c->win_task->win_top 	= original_top;
	c->win_task->win_bottom = original_bottom;
}