//See $LK,"::/Demo/Games/Stadium/StadiumGen.CC"$.

U0 Main()
{
	"Capture screen...\n";
	PressAKey;
	GRScreenCaptureWrite("~/DemoScreenShot");
	"View captured screen...\n";
	PressAKey;
	GRScreenCaptureRead("~/DemoScreenShot");
	PressAKey;
	DCFill;
}

Main;
