/* This demo shows how to draw primitives to textures. */

Cd(__DIR__);;

I64 wWC = 64;	// Window width in columns (512px)
I64 wHC = 48;	// Window height in rows (384px)
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

// Draw Rectangles
DrawRectFill(&frameBuf, 32, 32, 128, 96, gr_palette[CYAN]);

DrawRectVertGradient(&frameBuf, 64, 128, 96, 256, gr_palette[CYAN],
	gr_palette[BLUE]);

// Gradient's starting transition points can also be modified:
DrawRectVertGradient(&frameBuf, 160, 32, 224, 96, gr_palette[BLACK],
	gr_palette[WHITE], 0.65, 0.7);

DrawRectOutline(&frameBuf, 55, 300, 75, 310, gr_palette[LTGRAY]);

// You can also define a second color for adding button-like shading
DrawRectSoftOutline(&frameBuf, 100, 200, 130, 210, gr_palette[LTGRAY],
	gr_palette[DKGRAY]);

// Drawing text
DrawChar(&frameBuf, 48, 48, '!', gr_palette[WHITE]);
DrawString(&frameBuf, 16, 104, "When I wrote this, God said:
calls singing moist days excellence.", gr_palette[GREEN]);

while (CharScan() == 0)
{
	Tex2DDebugDisp(&frameBuf, wX, wY);
	Sleep(1);
}

Tex2DFree(&frameBuf);
SettingsPop;
Exit;
