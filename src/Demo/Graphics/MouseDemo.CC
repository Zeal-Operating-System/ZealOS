U0 Mouse()
{
	"Press left mouse bttn to exit.\n";
	while (!mouse.lb)
	{ //Left bttn to exit.
		GrPlot(, mouse.pos.x, mouse.pos.y);
		Refresh;
	}
	DCFill;
}

Mouse;
