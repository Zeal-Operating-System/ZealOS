#define PTS_NUM 16

U0 BSplineDemo()
{
	CDC		*dc = DCAlias;
	I64		 arg1, arg2, i = 0, message_code;
	CD3I32	 c[PTS_NUM];

	SettingsPush;
	Fs->win_inhibit = WIG_TASK_DEFAULT - WIF_SELF_FOCUS - WIF_SELF_BORDER;

	DocClear;
	"Sel ctrl points with left mouse.  Right when finished.\n";
	DCFill;
	do
	{
		message_code  = MessageGet(&arg1, &arg2, 1 << MESSAGE_MS_L_UP + 1 << MESSAGE_MS_R_UP);
		if (message_code == MESSAGE_MS_L_UP)
		{
			c[i].x = arg1;
			c[i].y = arg2;
			c[i].z = 0;
			dc->color = GREEN;
			GrCircle(dc, arg1, arg2, 10);
			i++;
		}
	}
	while (i < PTS_NUM && message_code != MESSAGE_MS_R_UP);

	dc->color = RED;
	Gr2BSpline(dc, c, i, TRUE);
	dc->color = BLUE;
	Gr3BSpline(dc, c, i, TRUE);
	DCDel(dc);
	SettingsPop;

	PressAKey;
	DCFill;
}

BSplineDemo;
