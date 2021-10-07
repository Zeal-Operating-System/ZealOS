U0 Mouse()
{
	"Press left mouse button to exit.\n";
	while (!mouse.lb)
	{ //Left button to exit.
		GrPlot(, mouse.pos.x, mouse.pos.y);
		Refresh;
	}
	DCFill;
}

Mouse;
