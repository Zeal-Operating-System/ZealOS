#define SQUARE_SIZE 20
#define SQUARE_GAP	5

I0 DrawPixel(I64 x, I64 y, CBGR24 color)
{
	text.fb_alias[x + y * GR_WIDTH] = color;
}

I0 Color32Demo()
{
	I64		i, j, x, y;
	CBGR24	color;

	while (TRUE)
	{
		x = FloorI64(RandU16 % GR_WIDTH, SQUARE_SIZE + SQUARE_GAP);
		y = FloorI64(RandU16 % GR_WIDTH, SQUARE_SIZE + SQUARE_GAP);
		color = RandU32;

		for (i = 0; i < SQUARE_SIZE; i++)
			for (j = 0; j < SQUARE_SIZE; j++)
				DrawPixel(x + i, y + j, color);

		Busy(1000);
	}
}

Color32Demo;