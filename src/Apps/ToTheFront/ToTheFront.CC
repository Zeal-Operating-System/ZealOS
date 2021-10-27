U0 AnimationDelaySet()
{
	animation_delay = PopUpRangeF64(0, 100, 25, "%3f% %%", "Animation Delay\n")/100;
}

U0 TurnNew()
{
	I64 i, j;
	for (j = 0; j < 2; j++)
		for (i = 0; i < UNITS_NUM; i++)
		{
			units[j][i].remaining_movement = units[j][i].movement;
			units[j][i].fired = FALSE;
		}
	phase = PHASE_START;
	moving_unit = NULL;

	SleepUntil(message_off_timeout);
	message_off_timeout = counts.jiffies + JIFFY_FREQ * 2 * animation_delay + 1;
	Sound(74);
	StrPrint(message_buf, "Turn %d", ++turn);
	VRSetUp(0);
	VRSetUp(1);
	VisRecalc(VR_ALL_UNITS);
	cur_player = (turn & 1) ^ 1;
	enemy_player = cur_player ^ 1;
}

U0 PhaseNew()
{
	cur_player ^= 1;
	enemy_player = cur_player ^ 1;
	if (++phase >= PHASE_END)
	{
		IndirectResolveAll;
		TurnNew;
	}

	SleepUntil(message_off_timeout);
	message_off_timeout = counts.jiffies + JIFFY_FREQ * 2 * animation_delay + 1;
	Sound(74);
	switch (phase)
	{
		case PHASE_INDIRECT0:
		case PHASE_INDIRECT1:
			StrPrint(message_buf, "Player %d Artillery Plot", cur_player + 1);
			break;

		case PHASE_MOVE0:
		case PHASE_MOVE1:
			StrPrint(message_buf, "Player %d Move", cur_player + 1);
			break;

		case PHASE_DIRECT0:
		case PHASE_DIRECT1:
			StrPrint(message_buf, "Player %d Fire", cur_player + 1);
			break;
	}
}

U0 CharDo(U8 ch)
{
	I64  old_inhibit, old_draw_it;
	Bool old_cursor;

	switch (ch)
	{
		case CH_ESC:
		case CH_SHIFT_ESC:
			throw('ExitGame', TRUE);

		case CH_SPACE:
			throw('PhaseOvr', TRUE);

		case '\n':
			throw('NewGame', TRUE);

		case '1':
			ViewPlayerSet(0);
			break;

		case '2':
			ViewPlayerSet(1);
			break;

		case 'c':
			old_draw_it = Fs->draw_it;
			old_inhibit = Fs->win_inhibit;
			Fs->draw_it = Fs->next_settings->draw_it;
			Fs->win_inhibit = WIG_USER_TASK_DEFAULT;
			old_cursor = DocCursor(ON);
			DocBottom;
			"\n$$GREEN$$<SHIFT-ESC>$$FG$$ to return to game.\n";
			View;
			DocBottom;
			DocCursor(old_cursor);
			Fs->win_inhibit = old_inhibit;
			Fs->draw_it = old_draw_it;
			break;

		case 'd':
			AnimationDelaySet;
			break;
	}
}

U0 UserCheck()
{
	I64 ch;

	if (!alive_count[0] || !alive_count[1])
		throw('GameOver', TRUE);
	if (ch = CharScan)
		CharDo(ch);
}

U0 TaskEndCB()
{
	Sound;
	progress4 = progress4_max = progress1 = progress1_max = 0;
	Exit;
}

I64 PhaseDo()
{
	I64 res = 'ExitGame';

	PhaseNew;
	try
	{
		if (phase & ~1 == PHASE_INDIRECT)
			Call(player_indirect[cur_player]);
		else if (phase & ~1 == PHASE_MOVE)
			Call(player_move[cur_player]);
		else
			Call(player_direct[cur_player]);
	}
	catch
	{
		res = Fs->except_ch;
		Fs->catch_except = TRUE;
	}
	return res;
}

U0 ToTheFront()
{
	I64 res, ch;

	map_dc = DCNew(MAP_WIDTH, MAP_HEIGHT);

	SettingsPush; //See $LK,"SettingsPush",A="MN:SettingsPush"$
	Cd(__DIR__);
	Fs->win_inhibit |= WIF_SELF_MS_L | WIF_SELF_MS_R | WIG_DBL_CLICK;

	MenuPush(	"File {"
				"  Abort(,CH_SHIFT_ESC);"
				"  Exit(,CH_ESC);"
				"}"
				"Play {"
				"  EndPhase(,CH_SPACE);"
				"  Restart(,'\n');"
				"}"
				"View {"
				"  Player1(,'1');"
				"  Player2(,'2');"
				"  OddsCalculations(,'c');"
				"  LOS(,0,SCF_SHIFT);"
				"}"
				"Settings {"
				"  AnimationDelay(,'d');"
				"}"
				);

	AutoComplete;
	WinBorder;
	WinMax;
	DocCursor;
	DocMax;
	Init;
	PlayerPick("AIs", 0);
	PlayerPick("AIs", 1);

	PopUpOk(	"$$PURPLE$$$$TX+CX,\"ToTheFront\"$$$$FG$$\n\n"
				"$$GREEN$${Left-click and drag}$$FG$$ to move or fire units.\n"
				"$$GREEN$$<SPACE>$$FG$$\tor $$GREEN$${Right-click}$$FG$$ to end phase.\n"
				"$$GREEN$$<SHIFT>$$FG$$\tto show line-of-sight.\n"
				"$$GREEN$$<ENTER>$$FG$$\tto start new game.\n"
				"$$GREEN$$  1$$FG$$\tPlayer 1 view.\n"
				"$$GREEN$$  2$$FG$$\tPlayer 2 view.\n"
				"$$GREEN$$  c$$FG$$\tView odds calculations.\n"
				"$$GREEN$$  d$$FG$$\tSet animation delay.\n\n"
				"Squares are infantry. Cones are artillery.\n"
				"Units move faster on enemy roads,\n"
				"slower on friendly roads, forests, or mountains.\n"
				"Forests and mountains hide units,\n"
				"mountain units get high-ground bonus.");
	PaletteSetLight(FALSE);
	Fs->task_end_cb = &TaskEndCB; //<CTRL-ALT-x>
	Fs->draw_it = &DrawIt;
	try
	{
		do
		{
			res = PhaseDo;
			if (res == 'GameOver')
			{
				while (TRUE)
				{
					message_off_timeout = 0;
					StrCopy(message_buf, "Game Over");
					Sound;
					ch = CharGet(, FALSE);
					if (ch == '\n')
					{
						CleanUp;
						Init;
						break;
					}
					else if (ch == CH_ESC || ch == CH_SHIFT_ESC)
					{
						res = 'ExitGame';
						break;
					}
					else if (ch == '1')
						ViewPlayerSet(0);
					else if (ch == '2')
						ViewPlayerSet(1);
					else if (ch == 'd')
						AnimationDelaySet;
				}
			}
			else if (res == 'NewGame')
			{
				CleanUp;
				Init;
			}
		}
		while (res != 'ExitGame');
	}
	catch
		PutExcept;
	ProgressBarsReset;

	SettingsPop;
	DCDel(map_dc);
	CleanUp;
	MenuPop;
	Seed;
}
