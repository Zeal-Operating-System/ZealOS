/* This demo shows how to initialize, import, and render textures. */

Cd(__DIR__);;

I64 wWC = 32;	// Window width in columns (256px)
I64 wHC = 32;	// Window height in rows (256px)
I64 wW = wWC * 8;
I64 wH = wHC * 8;
I64 wXC = 1;	// Window x in columns
I64 wYC = 2;	// Window y in rows
I64 wX = wXC * 8;
I64 wY = wYC * 8;

SettingsPush;
WinHorz(wXC, wXC + wWC - 1);
WinVert(wYC, wYC + wHC - 1);
DocClear;

CGLTex2D texture;
GLTex2DLoadBMP(&texture, "SaintTerry.bmp");

while (CharScan() == 0)
{
	GLTex2DDebugDisp(&texture, wX, wY);
	Sleep(1);
}

GLTex2DFree(&texture);
SettingsPop;
Exit;
