/*
	You "System Include" this because you want the wallpaper
	routine to stay in mem even if this task is killed.
*/

#define NUM_STARS	GR_WIDTH * GR_HEIGHT / 2160
// Derived from ratio for 600 for 1440x900

class Star
{
	U16 x, y;

} wall_stars[NUM_STARS];

U0 (*old_wall_paper)(CTask *task);

U0 WallPaperStars(CTask *task)
{
	I64  i;
	CDC *dc = DCAlias(gr.dc2, task);

	dc->color = YELLOW;

	for (i = 0; i < NUM_STARS; i++)
	{
		GrPlot(dc, wall_stars[i].x, wall_stars[i].y);

		if (++wall_stars[i].y > GR_HEIGHT)
		{
			wall_stars[i].y = 0;
			wall_stars[i].x = RandU16 % GR_WIDTH;
		}
	}

	DCDel(dc);

	//Uncomment the following if you wish. Will draw the old wallpaper over this one.
	//old_wall_paper(task);

	if (gr_palette[0] > gr_palette[15])
		task->text_attr = WHITE << 4 + WHITE;
	else
		task->text_attr = BLACK << 4 + BLACK;

}

U0 WallInit()
{
	I64 i;

	if (Fs != sys_task)
	{
		"\nMust be System Included. (SHIFT-F5 / RightClick->System Include) \n";
		return;
	}
	old_wall_paper = gr.fp_wall_paper;

	for (i = 0; i < NUM_STARS; i++)
	{
		wall_stars[i].x = RandU16 % GR_WIDTH;
		wall_stars[i].y = RandU16 % GR_HEIGHT;
	}

	gr.fp_wall_paper = &WallPaperStars;
}

WallInit;
