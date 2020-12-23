U0 InSetMouseDemo()
{
	I64 t, l;

	WinBorder(ON);
	l = Fs->pix_left + Fs->scroll_x;
	t = Fs->pix_top  + Fs->scroll_y;
	MouseSet(,,, FALSE,FALSE); //Mouse unclicked
	InSetMouse(,l - 4, t - 4);
	InSetMouse(20, l + 20, t + 20,, TRUE);
	MouseSet(,,, FALSE, FALSE);
}

InSetMouseDemo;
