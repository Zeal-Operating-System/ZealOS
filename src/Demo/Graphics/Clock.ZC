#define USE_JIFFIES		FALSE // Set FALSE for less smooth but more accurate time.

#define CLOCK_CENTER	70
#define CLOCK_RADIUS	(CLOCK_CENTER-2)

#define SECOND_HAND_LEN	CLOCK_RADIUS
#define MINUTE_HAND_LEN	8 * CLOCK_RADIUS / 10
#define HOUR_HAND_LEN	CLOCK_RADIUS / 2

#define CLOCK_BASE_COLOR	BLACK
#define SECOND_HAND_COLOR	DKGRAY
#define MINUTE_HAND_COLOR	DKGRAY
#define HOUR_HAND_COLOR		BLACK

// set this either 24 or 12
#define HOUR_MAX	12

#define ç	2*ã


//EST NY -> India:		  9.5
//EST NY -> China:		  12
CDate clock_time_offset = 0 * 60 * 60 * CDATE_FREQ;

CDateStruct *ds = CAlloc(sizeof(CDateStruct));
CDate d = Now + clock_time_offset;
Date2Struct(ds, d);
I64 init_jiff = counts.jiffies;
I64 cur_jiff;
F64 sec, min, hr;

U0 ClockDrawIt(CTask *, CDC *dc)
{
	if (USE_JIFFIES)
	{
		cur_jiff = counts.jiffies - init_jiff;
		sec = ds->sec + cur_jiff/1000.0;
		min = ds->min + cur_jiff/1000.0/60;
		hr  = (ds->hour % HOUR_MAX) + cur_jiff/1000.0/60/60;
	}
	else
	{
		d = Now + clock_time_offset;
		Date2Struct(ds, d);
		sec = ds->sec;
		min = ds->min;
		hr  = ds->hour % HOUR_MAX;
	}
/*

public Bool GrLine3(CDC *dc=gr.dc,I64 x1,I64 y1,I64 z1,
								  I64 x2,
								  I64 y2,
								  I64 z2, I64 step=1,I64 start=0)
*/
	//draw second hand
	dc->thick = 1;
	dc->color = SECOND_HAND_COLOR;
	GrLine3(dc, CLOCK_CENTER, CLOCK_CENTER, GR_Z_ALL,
			  (CLOCK_CENTER + SECOND_HAND_LEN * Cos(3*ç/4 + sec * ç/60)),
			  (CLOCK_CENTER + SECOND_HAND_LEN * Sin(3*ç/4 + sec * ç/60)),
			   GR_Z_ALL);

	// draw minute hand
	dc->thick = 2;
	dc->color = MINUTE_HAND_COLOR;
	GrLine3(dc, CLOCK_CENTER, CLOCK_CENTER, GR_Z_ALL,
			  (CLOCK_CENTER + MINUTE_HAND_LEN * Cos(3*ç/4 + min * ç/60)),
			  (CLOCK_CENTER + MINUTE_HAND_LEN * Sin(3*ç/4 + min * ç/60)),
			   GR_Z_ALL);

	// draw hour hand
	dc->thick = 3;
	dc->color = HOUR_HAND_COLOR;
	GrLine3(dc, CLOCK_CENTER, CLOCK_CENTER, GR_Z_ALL,
			  (CLOCK_CENTER + HOUR_HAND_LEN * Cos(3*ç/4 + hr * ç/HOUR_MAX)),
			  (CLOCK_CENTER + HOUR_HAND_LEN * Sin(3*ç/4 + hr * ç/HOUR_MAX)),
			   GR_Z_ALL);


	dc->color = CLOCK_BASE_COLOR;
	//GrPrint(dc, 0, 0, "%d", ds->sec);
	
	//draw clock base
	GrCircle(dc, CLOCK_CENTER, CLOCK_CENTER, CLOCK_RADIUS);

}

U0 ClockDemo()
{
	SettingsPush;
	DocClear;
	DocCursor;
	Fs->draw_it = &ClockDrawIt;
	StrCopy(Fs->task_title, "Time");

	while (CharGet(,FALSE) != CH_SHIFT_ESC) {};

	SettingsPop;
};

ClockDemo;
