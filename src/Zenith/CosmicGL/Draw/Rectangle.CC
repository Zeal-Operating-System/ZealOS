
/**
	@ingroup Draw
	@brief Draw single color rectangle.

	@param[in,out] tex		Texture to draw to.
	@param[in]     x0		Start corner x.
	@param[in]     y0		Start corner y.
	@param[in]     x1		End corner x.
	@param[in]     y1		End corner y.
	@param[in]     color	Color of rectangle.
*/
U0 DrawRectFill(CTex2D *tex, I64 x0, I64 y0, I64 x1, I64 y1, CBGR24 color)
{
	I64 xMaxIndex = tex->w - 1;
	I64 yMaxIndex = tex->h - 1;
	I64 xMin = Clamp(Min(x0, x1), 0, xMaxIndex);
	I64 xMax = Clamp(Max(x0, x1), 0, xMaxIndex);
	I64 yMin = Clamp(Min(y0, y1), 0, yMaxIndex);
	I64 yMax = Clamp(Max(y0, y1), 0, yMaxIndex);
	I64 xLen = xMax - xMin;

	I64 y;
	for (y = yMin; y < yMax; y++)
	{
		MemSetU32(&tex->rawBuf[xMin + y * tex->w], color, xLen); 
	}
}

/**
	@ingroup Draw
	@brief  Draw 1px soft rectangle outline (corners not filled).

	@param[in,out] tex			Texture to draw to.
	@param[in]     x0			Start corner x.
	@param[in]     y0			Start corner y.
	@param[in]     x1			End corner x.
	@param[in]     y1			End corner y.
	@param[in]     color		Color of rectangle.
	@param[in]     shadeColor	(Optional) color of bottom right corner
								for shading effect.
*/
U0 DrawRectSoftOutline(CTex2D *tex, I64 x0, I64 y0, I64 x1, I64 y1, 
	CBGR24 color, CBGR24 shadeColor = 0x7FFFFFFF)
{
	if (shadeColor == 0x7FFFFFFF)
		shadeColor = color;

	I64 xMaxIndex = tex->w - 1;
	I64 yMaxIndex = tex->w - 1;
	I64 xMin = Clamp(Min(x0, x1), 0, xMaxIndex);
	I64 xMax = Clamp(Max(x0, x1), 0, xMaxIndex);
	I64 yMin = Clamp(Min(y0, y1), 0, yMaxIndex);
	I64 yMax = Clamp(Max(y0, y1), 0, yMaxIndex);
	I64 xLen = xMax - xMin - 1;

	// Top border
	MemSetU32(&tex->rawBuf[xMin + 1 + yMin * tex->w], color, xLen);

	// Bottom border
	MemSetU32(&tex->rawBuf[xMin + 1 + yMax * tex->w], shadeColor, xLen);

	// Left/Right border
	I64 y;
	for (y = yMin + 1; y < yMax; y++)
	{
		tex->rawBuf[xMin + y * tex->w] = color;
		tex->rawBuf[xMax + y * tex->w] = shadeColor;
	}
}

/**
	@ingroup Draw
	@brief Draw 1px rectangle outline.

	@param[in,out] tex			Texture to draw to.
	@param[in]     x0			Start corner x.
	@param[in]     y0			Start corner y.
	@param[in]     x1			End corner x.
	@param[in]     y1			End corner y.
	@param[in]     color		Color of rectangle.
	@param[in]     shadeColor	(Optional) color of bottom right corner
								for shading effect.
*/
U0 DrawRectOutline(CTex2D *tex, I64 x0, I64 y0, I64 x1, I64 y1,
	CBGR24 color, CBGR24 shadeColor = 0x7FFFFFFF)
{
	if (shadeColor == 0x7FFFFFFF)
		shadeColor = color;

	I64 xMaxIndex = tex->w - 1;
	I64 yMaxIndex = tex->w - 1;
	I64 xMin = Clamp(Min(x0, x1), 0, xMaxIndex);
	I64 xMax = Clamp(Max(x0, x1), 0, xMaxIndex);
	I64 yMin = Clamp(Min(y0, y1), 0, yMaxIndex);
	I64 yMax = Clamp(Max(y0, y1), 0, yMaxIndex);
	I64 xLen = xMax - xMin + 1;

	// Top border
	MemSetU32(&tex->rawBuf[xMin + yMin * tex->w], color, xLen);

	// Bottom border
	MemSetU32(&tex->rawBuf[xMin + yMax * tex->w], shadeColor, xLen);

	// Left/Right border
	I64 y;
	for (y = yMin + 1; y < yMax; y++)
	{
		tex->rawBuf[xMin + y * tex->w] = color;
		tex->rawBuf[xMax + y * tex->w] = shadeColor;
	}
}

/**
	@ingroup Draw
	@brief Draw two color vertical gradient rectangle.

	@param[in,out] tex			Texture to draw to.
	@param[in]     x0			Start corner x.
	@param[in]     y0			Start corner y.
	@param[in]     x1			End corner x.
	@param[in]     y1			End corner y.
	@param[in]     colorTop		Top color of gradient.
	@param[in]     colorBottom	Bottom color of gradient.
	@param[in]     shadeColor	(Optional) color of bottom right corner
								for shading effect.
	@param[in]     tStart		(Optional) start of gradient.
	@param[in]     tEnd			(Optional) end of gradient.
*/
U0 DrawRectVertGradient(CTex2D *tex, I64 x0, I64 y0, I64 x1, I64 y1,
	CBGR24 colorTop, CBGR24 colorBottom, F64 tStart = 0.0, F64 tEnd = 1.0)
{
	I64 xMaxIndex = tex->w - 1;
	I64 yMaxIndex = tex->h - 1;
	I64 xMin = Clamp(Min(x0, x1), 0, xMaxIndex);
	I64 xMax = Clamp(Max(x0, x1), 0, xMaxIndex);
	I64 yMinReal = Min(y0, y1);
	I64 yMin = Clamp(yMinReal, 0, yMaxIndex);
	I64 yMaxReal = Max(y0, y1);
	I64 yMax = Clamp(yMaxReal, 0, yMaxIndex);
	I64 xLen = xMax - xMin;

	F64 yHeight = yMaxReal - yMinReal + 1;
	F64 t;

	F64 rDiff = colorBottom.r - colorTop.r;
	F64 gDiff = colorBottom.g - colorTop.g;
	F64 bDiff = colorBottom.b - colorTop.b;

	F64 r, g, b;
	
	I64 y;
	CBGR24 color;
	for (y = yMin; y < yMax; y++)
	{
		t = Clamp((y - yMinReal) / yHeight, tStart, tEnd);
		r = t * rDiff;
		g = t * gDiff;
		b = t * bDiff;
		color.r = colorTop.r + r;
		color.g = colorTop.g + g;
		color.b = colorTop.b + b;
		MemSetU32(&tex->rawBuf[xMin + y * tex->w], color, xLen);
	}
}