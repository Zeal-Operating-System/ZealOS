//See $LK,"::/Demo/Games/Stadium/StadiumGen.HC"$.

U0 Main()
{
  "Capture scrn...\n";
  PressAKey;
  GRScreenCaptureWrite("~/DemoScreenShot");
  "View captured scrn...\n";
  PressAKey;
  GRScreenCaptureRead("~/DemoScreenShot");
  PressAKey;
  DCFill;
}

Main;
