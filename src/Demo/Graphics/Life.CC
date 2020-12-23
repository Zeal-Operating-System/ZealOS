//Conway's Game of Life

CDC *dc[2]; //double buf
I64  cur_dc, ;
Bool restart;

U0 DrawIt(CTask *, CDC *dc2)
{
	dc[cur_dc]->flags |= DCF_NO_TRANSPARENTS;
	GrBlot(dc2, 0, 0, dc[cur_dc]);
}

U0 AnimateTask(I64)
{
	I64 x, y, x1, y1, count, next_dc;

	while (TRUE)
	{
		next_dc = cur_dc ^ 1;
start_over:
		restart = FALSE;
		DCClear(dc[next_dc]);
		for (y = 1; y < Fs->parent_task->pix_height - 1; y++)
		{
			for (x = 1; x < Fs->parent_task->pix_width - 1; x++)
			{
				count = 0;
				for (y1 = y - 1; y1 <= y + 1; y1++)
					for (x1 = x - 1; x1 <= x + 1; x1++)
						if (GrPeek(dc[cur_dc], x1, y1) == GREEN)
							count++;
				if (restart)
					goto start_over;
				if (GrPeek(dc[cur_dc], x, y) == GREEN)
				{
					if (count == 3)
					{
						dc[next_dc]->color = GREEN;
						GrPlot(dc[next_dc], x, y);
					}
				}
				else
				{
//					if (count == 3) //Use this for the classic rules
					if (count == 2)
					{
						dc[next_dc]->color = GREEN;
						GrPlot(dc[next_dc], x, y);
					}
				}
			}
			Yield;
		}
		Sleep(50);
		cur_dc = next_dc;
	}
}

public U0 Life()
{
	I64 message_code, count, x1, y1, x2, y2, arg1, arg2;

	dc[0] = DCNew(GR_WIDTH, GR_HEIGHT);
	dc[1] = DCNew(GR_WIDTH, GR_HEIGHT);
	cur_dc = 0;
	restart = FALSE;

	SettingsPush; //See $LK,"SettingsPush",A="MN:SettingsPush"$
	AutoComplete;
	WinBorder;
	WinMax;
	DocClear;
	DCFill;

	Fs->animate_task = Spawn(&AnimateTask, NULL, "Animate",, Fs);
	Fs->draw_it		 = &DrawIt;
	Fs->win_inhibit	 = WIG_TASK_DEFAULT - WIF_SELF_FOCUS - WIF_SELF_BORDER;
	do
	{
		message_code = MessageGet(&arg1, &arg2, 1 << MESSAGE_KEY_DOWN + 1 << MESSAGE_MS_L_DOWN);
		switch (message_code)
		{
			case MESSAGE_MS_L_DOWN:
				x1 = arg1;
				y1 = arg2;
				x2 = arg1;
				y2 = arg2;
				count = 0;
				while (message_code != MESSAGE_MS_L_UP)
				{
					restart = TRUE;
					dc[cur_dc]->color = GREEN;
					dc[cur_dc]->thick = 0.04 * mouse.speed;
					GrLine3(dc[cur_dc], x1, y1, 0, x2, y2, 0);
					restart = TRUE;
					message_code = MessageGet(&arg1, &arg2, 1 << MESSAGE_MS_L_UP + 1 << MESSAGE_MS_MOVE);
					x1 = x2;
					y1 = y2;
					x2 = arg1;
					y2 = arg2;
				}
				GrLine3(dc[cur_dc], x1, y1, 0, x2, y2, 0);
				break;

			case MESSAGE_KEY_DOWN:
				break;
		}
	}
	while (message_code != MESSAGE_KEY_DOWN || !arg1);

	MessageGet(,, 1 << MESSAGE_KEY_UP);
	SettingsPop;
	DCFill;
	DCDel(dc[0]);
	DCDel(dc[1]);
}

Life;
