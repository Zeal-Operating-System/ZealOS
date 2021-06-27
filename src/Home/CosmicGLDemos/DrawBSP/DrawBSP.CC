/* This demo renders a BSP. Put DOOM1.WAD in the directory to try this. */

Cd(__DIR__);;

"\n\n\n\n";		// Seperate from annoying warnings

I64 wWC = 90;	// Window width in columns
I64 wHC = 90;	// Window height in rows
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

// Prepare framebuffer
CTex2D frameBuf;
Tex2DInit(&frameBuf, TEX2D_RAW, wW, wH);
Tex2DColorFill(&frameBuf, gr_palette[WHITE]);

// Load BSP and render
CWAD doom1;
WADLoad(&doom1, "DOOM1.WAD");

CDoomMap map;
DoomMapLoad(&map, &doom1, "E1M1");

// Sprite loading
CTex2D sprite;
Tex2DLoadWADSprite(&sprite, &doom1, "POSSF2F8");

WADFree(&doom1);

CBGR24 cRed;
cRed.r = 255; cRed.b = cRed.g = 0;

I64 i, a, b, c, d;
for (i = 0; i < map.nLines; i++)
{
	a = map.lines[i].v1->x >> 32;
	b = map.lines[i].v1->y >> 32;
	c = map.lines[i].v2->x >> 32;
	d = map.lines[i].v2->y >> 32;

	a /= 8;
	b /= 8;
	c /= 8;
	d /= 8;

	a += 200;
	b += 650;
	c += 200;
	d += 650;

	if (a < 0 || b < 0 || c < 0 || d < 0 ||
		a >= wW || b >= wH || c >= wW || d >= wH)
	{
		// One coordinate outside window
	}
	else
	{
		DrawLine(&frameBuf, a, b, c, d, cRed);
	}
}

DrawTexture(&frameBuf, &sprite, 200, 200, TRUE);

while (CharScan() == 0)
{
	Tex2DDebugDisp(&frameBuf, wX, wY);
	Sleep(1);
}

DoomMapFree(&doom1);
Tex2DFree(&sprite);
Tex2DFree(&framebuf);
SettingsPop;
Exit;
