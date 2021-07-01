/**
	@defgroup GLDraw Draw
	@brief Functions for drawing to textures.
*/

/**
	@ingroup GLDraw
	@brief Draw pixel on color texture. Does not check boundaries, point
	must be fully inside texture.

	@param[in,out] tex		Color texture to draw to.
	@param[in]     x		X position.
	@param[in]     y		Y position.
	@param[in]     color	Color of point.
*/
U0 GLDrawPixel(CGLTex2D *tex, I64 x, I64 y, CBGR24 color)
{
    tex->rawBuf[x + y * tex->w] = color;
}


/**
	@ingroup GLDraw
	@brief Draw line on color texture. Does not check boundaries, line must
	be fully inside texture.

	@param[in,out] tex		Color texture to draw to.
	@param[in]     x0		Start x.
	@param[in]     y0		Start y.
	@param[in]     x1		End x.
	@param[in]     y1		End y.
	@param[in]     color	Color of line.
*/
U0 GLDrawLine(CGLTex2D *tex, I64 x0, I64 y0, I64 x1, I64 y1, CBGR24 color)
{
	Bool steep;
	I64 temp,
		delta_x, delta_y, error,
		step_y, x, y;

	steep = Abs(y1 - y0) > Abs(x1 - x0);

	if (steep == TRUE)
    {
		temp = x0;
		x0 = y0;
		y0 = temp;
		temp = x1;
		x1 = y1;
		y1 = temp;
    }

	if (x0 > x1)
	{
		temp = x0;
		x0 = x1;
		x1 = temp;
		temp = y0;
		y0 = y1;
		y1 = temp;	
	}

	delta_x = x1 - x0;
	delta_y = Abs(y1 - y0);
	error = delta_x / 2;

	step_y;
	
	if (y0 < y1)
	{
		step_y = 1;
	}
	else
	{
		step_y = -1;
	}

	y = y0;
	
	for (x = x0; x < x1 + 1; x++)
	{
		if (steep == TRUE)
		{
			tex->rawBuf[y + x * tex->w] = color;
		}
		else
		{
			tex->rawBuf[x + y * tex->w] = color;
		}

		error -= delta_y;

		if (error < 0)
		{
			y += step_y;
			error += delta_x;
		}
	}
}

/**
	@ingroup GLDraw
	@brief Draw single color triangle to color texture. Does not check
	boundaries, triangle must be fully inside texture.

	@param[in,out] tex		Color texture to draw to.
	@param[in]     x0		First vertex x.
	@param[in]     y0		First vertex y.
	@param[in]     x1		Second vertex x.
	@param[in]     y1		Second vertex y.
	@param[in]     x2		Third vertex x.
	@param[in]     y2		Third vertex y.
	@param[in]     color	Color of triangle.
*/
U0 GLDrawTriangle(CGLTex2D *tex, I64 x0, I64 y0, I64 x1, I64 y1, I64 x2, I64 y2,
	CBGR24 color)
{
	Bool middle_line_drawn;
	I64 temp;
	F64 ftemp,
		x_delta, y_delta,
		left_delta, right_delta,
		left_x, right_x,
		y, lX, rX,
		left_index, right_index,
		width;
	
	if (y0 > y1)
	{
		temp = x0;
		x0 = x1;
		x1 = temp;
		temp = y0;
		y0 = y1;
		y1 = temp;
	}

	if (y0 > y2)
	{
		temp = x0;
		x0 = x2;
		x2 = temp;
		temp = y0;
		y0 = y2;
		y2 = temp;
	}

	if (y1 > y2)
	{
		temp = x1;
		x1 = x2;
		x2 = temp;
		temp = y1;
		y1 = y2;
		y2 = temp;
	}

	middle_line_drawn = FALSE;

	// Bottom Half
	if (y0 != y1)
	{
		x_delta = x1 - x0;
		y_delta = y1 - y0;
		left_delta = x_delta / y_delta;
		x_delta = x2 - x0;
		y_delta = y2 - y0;
		right_delta = x_delta / y_delta;

		if (left_delta > right_delta)
		{
			ftemp = left_delta;
			left_delta = right_delta;
			right_delta = ftemp;
		}

		left_x = x0;
		right_x = x0;

		middle_line_drawn = TRUE;

		for (y = y0; y < y1 + 1; y++)
		{
			lX = left_x + 0.5;
			rX = right_x + 0.5;
			left_index = y * tex->w + lX;
			right_index = y * tex->w + rX;
			width = right_index - left_index;
			MemSetU32(tex->rawBuf + left_index, color, width);
			left_x += left_delta;
			right_x += right_delta;
		}
	}

	// Top Half
	if (y1 != y2)
	{
		x_delta = -x1 - x2;
		y_delta = y1 - y2;
		left_delta = x_delta / y_delta;
		x_delta = -x0 - x2;
		y_delta = y0 - y2;
		right_delta = x_delta / y_delta;

		if (left_delta > right_delta)
		{
			ftemp = left_delta;
			left_delta = right_delta;
			right_delta = ftemp;
		}

		left_x = x2;
		right_x = x2;

		if (middle_line_drawn == TRUE)
		{
			y1 += 1;
		}

		for (y = y2; y > y1 - 1; y--)
		{
			lX = left_x + 0.5;
			rX = right_x + 0.5;
			left_index = y * tex->w + lX;
			right_index = y * tex->w + rX;
			width = right_index - left_index;
			MemSetU32(tex->rawBuf + left_index, color, width);
			left_x += left_delta;
			right_x += right_delta;
		}
	}
}