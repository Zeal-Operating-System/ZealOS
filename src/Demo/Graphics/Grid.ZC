#define GRID		5

U0 DrawMyMouse(CDC *dc, I64 x, I64 y)
{
	dc->thick = 1;
	dc->flags &= ~(DCF_TRANSFORMATION | DCF_SYMMETRY);
	GrRect(dc, x, y, GRID, GRID);
}

U0 GridDemo()
{
	CGridGlobals old_grid;
	U0 (*old_draw_mouse)(CDC *dc, I64 x, I64 y); //Can't init this type of variable.

	MemCopy(&old_grid, &mouse_grid, sizeof(CGridGlobals));
	GridInit;
	mouse_grid.snap	= TRUE; //You can set other $LK,"stuff",A="MN:CGridGlobals"$.
	mouse_grid.x	= GRID;
	mouse_grid.y	= GRID;
	old_draw_mouse = gr.fp_draw_mouse;
	gr.fp_draw_mouse = &DrawMyMouse;
	while (!mouse.lb) 
	{//Left button to exit.
		GrPlot(, mouse.pos.x, mouse.pos.y);
		Yield;
	}
	DCFill;
	gr.fp_draw_mouse = old_draw_mouse;
	MemCopy(&mouse_grid, &old_grid, sizeof(CGridGlobals));
}

GridDemo;
