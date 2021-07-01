
/**
	@ingroup GLDraw
	@brief Draw single color rectangle.

	@param[in,out] tex		Texture to draw to.
	@param[in]     x0		Start corner x.
	@param[in]     y0		Start corner y.
	@param[in]     x1		End corner x.
	@param[in]     y1		End corner y.
	@param[in]     color	Color of rectangle.
*/
U0 GLDrawRectFill(CGLTex2D *tex, I64 x0, I64 y0, I64 x1, I64 y1, CBGR24 color)
{
	I64 xMaxIndex, yMaxIndex,
		xMin, xMax,
		yMin, yMax,
		xLen, y;

	xMaxIndex = tex->w - 1;
	yMaxIndex = tex->h - 1;
	xMin = Clamp(Min(x0, x1), 0, xMaxIndex);
	xMax = Clamp(Max(x0, x1), 0, xMaxIndex);
	yMin = Clamp(Min(y0, y1), 0, yMaxIndex);
	yMax = Clamp(Max(y0, y1), 0, yMaxIndex);
	xLen = xMax - xMin;

	for (y = yMin; y < yMax; y++)
	{
		MemSetU32(&tex->rawBuf[xMin + y * tex->w], color, xLen); 
	}
}

/**
	@ingroup GLDraw
	@brief Draw 1px soft rectangle outline (corners not filled).

	@param[in,out] tex			Texture to draw to.
	@param[in]     x0			Start corner x.
	@param[in]     y0			Start corner y.
	@param[in]     x1			End corner x.
	@param[in]     y1			End corner y.
	@param[in]     color		Color of rectangle.
	@param[in]     shadeColor	(Optional) color of bottom right corner
								for shading effect.
*/
U0 GLDrawRectSoftOutline(CGLTex2D *tex, I64 x0, I64 y0, I64 x1, I64 y1, 
	CBGR24 color, CBGR24 shadeColor = 0x7FFFFFFF)
{
	I64 xMaxIndex, yMaxIndex,
		xMin, xMax,
		yMin, yMax,
		xLen, y;

	if (shadeColor == 0x7FFFFFFF)
		shadeColor = color;

	xMaxIndex = tex->w - 1;
	yMaxIndex = tex->w - 1;
	xMin = Clamp(Min(x0, x1), 0, xMaxIndex);
	xMax = Clamp(Max(x0, x1), 0, xMaxIndex);
	yMin = Clamp(Min(y0, y1), 0, yMaxIndex);
	yMax = Clamp(Max(y0, y1), 0, yMaxIndex);
	xLen = xMax - xMin - 1;

	// Top border
	MemSetU32(&tex->rawBuf[xMin + 1 + yMin * tex->w], color, xLen);

	// Bottom border
	MemSetU32(&tex->rawBuf[xMin + 1 + yMax * tex->w], shadeColor, xLen);

	// Left/Right border
	for (y = yMin + 1; y < yMax; y++)
	{
		tex->rawBuf[xMin + y * tex->w] = color;
		tex->rawBuf[xMax + y * tex->w] = shadeColor;
	}
}

/**
	@ingroup GLDraw
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
U0 GLDrawRectOutline(CGLTex2D *tex, I64 x0, I64 y0, I64 x1, I64 y1,
	CBGR24 color, CBGR24 shadeColor = 0x7FFFFFFF)
{
	I64 xMaxIndex, yMaxIndex,
		xMin, xMax,
		yMin, yMax,
		xLen, y;

	if (shadeColor == 0x7FFFFFFF)
		shadeColor = color;

	xMaxIndex = tex->w - 1;
	yMaxIndex = tex->w - 1;
	xMin = Clamp(Min(x0, x1), 0, xMaxIndex);
	xMax = Clamp(Max(x0, x1), 0, xMaxIndex);
	yMin = Clamp(Min(y0, y1), 0, yMaxIndex);
	yMax = Clamp(Max(y0, y1), 0, yMaxIndex);
	xLen = xMax - xMin + 1;

	// Top border
	MemSetU32(&tex->rawBuf[xMin + yMin * tex->w], color, xLen);

	// Bottom border
	MemSetU32(&tex->rawBuf[xMin + yMax * tex->w], shadeColor, xLen);

	// Left/Right border
	for (y = yMin + 1; y < yMax; y++)
	{
		tex->rawBuf[xMin + y * tex->w] = color;
		tex->rawBuf[xMax + y * tex->w] = shadeColor;
	}
}

/**
	@ingroup GLDraw
	@brief Draw two color vertical gradient rectangle.

	Should be optimized to avoid such heavy use of F64's.

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
U0 GLDrawRectVertGradient(CGLTex2D *tex, I64 x0, I64 y0, I64 x1, I64 y1,
	CBGR24 colorTop, CBGR24 colorBottom, F64 tStart = 0.0, F64 tEnd = 1.0)
{
	CBGR24 color;
	I64 xMaxIndex, yMaxIndex,
		xMin, xMax,
		yMin, yMax,
		yMinReal, yMaxReal,
		xLen, y;
	F64 yHeight, t,
		rDiff, gDiff, bDiff,
		r, g, b;

	xMaxIndex = tex->w - 1;
	yMaxIndex = tex->h - 1;
	xMin = Clamp(Min(x0, x1), 0, xMaxIndex);
	xMax = Clamp(Max(x0, x1), 0, xMaxIndex);
	yMinReal = Min(y0, y1);
	yMin = Clamp(yMinReal, 0, yMaxIndex);
	yMaxReal = Max(y0, y1);
	yMax = Clamp(yMaxReal, 0, yMaxIndex);
	xLen = xMax - xMin;

	yHeight = yMaxReal - yMinReal + 1;

	rDiff = colorBottom.r - colorTop.r;
	gDiff = colorBottom.g - colorTop.g;
	bDiff = colorBottom.b - colorTop.b;

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