/**
    @defgroup Tex2D Texture
    @brief The core of the library, almost all functions either read from
    or write to textures.
*/


/**
	@ingroup Tex2D 
	@brief Raw format is a CBGR24 rawBuf array of size w * h in row-major 
	order. 
*/
#define TEX2D_RAW	1

/** 
	@ingroup Tex2D
	@brief Depth format is a F64 depthBuf array of size w * h in row-major 
	order. 
*/
#define TEX2D_DEPTH	2

/**
    @ingroup Tex2D
    @brief The CTex2D class
*/
class CTex2D
{
	I64 type;			// Type, see TEX2D_ macros above
	I64 w;				// Width
	I64 h;				// Height
	I64 l;				// Left offset if applicable (for use with sprite textures)
	I64 t;				// Top offset if applicable (for use with sprite textures)
	I64 mipmaps;		// Mipmaps, not currently being used
	CBGR24 *rawBuf;		// Raw color buffer. Size: w * h
	F64 *depthBuf;		// Depth buffer. Size: w * h, pixels are depth.
};

/**
	@ingroup Tex2D
    @brief Initialize texture.

    @param[in,out] tex	Uninitialized texture to initialize.
    @param[in]     type	Type of texture. See TEX2D_ macros for options.
    @param[in]     w	Width
    @param[in]     h	Height
    @param[in]     l	(Optional) left offset for use with sprite textures.
    @param[in]     t	(Optional) top offset for use with sprite textures.
*/
U0 Tex2DInit(CTex2D *tex, I64 type, I64 w, I64 h, I64 l = 0, I64 t = 0)
{
	tex->w = w;
	tex->h = h;
	tex->l = l;
	tex->t = t;
	tex->type = type;

	switch (type)
	{
		case (TEX2D_RAW):
			tex->rawBuf = MAlloc(4 * tex->w * tex->h);
		break;

		case (TEX2D_DEPTH):
			tex->depthBuf = MAlloc(sizeof(F64) * tex->w * tex->h);
		break;
	}
}

/**
	@ingroup Tex2D
	@brief Free texture.
	
	@param[in,out] tex	Texture to free.
*/
U0 Tex2DFree(CTex2D *tex)
{
	switch (tex->type)
	{
		case TEX2D_RAW:
			Free(tex->rawBuf);
		break;

		case TEX2D_DEPTH:
			Free(tex->depthBuf);
		break;
	}
}

/**
	@ingroup Tex2D
	@brief Fill texture with color. Only works with raw textures.

	@param[in,out] tex		Texture to color fill.
	@param[in]     color	Color to fill texture with.
*/
U0 Tex2DColorFill(CTex2D *tex, CBGR24 color)
{
	MemSetU32(tex->rawBuf, color, tex->w * tex->h);
}

/**
	@ingroup Tex2D
	@brief Reset depth texture. Set all pixels to far depth.

	@param[in,out] tex	Depth texture to reset.
*/
U0 Tex2DDepthReset(CTex2D *tex)
{
	F64 depth = 2.0;
	I64 *iDepth = &depth;
	MemSetI64(tex->depthBuf, *iDepth, tex->w * tex->h);
} 

/**
	@ingroup Tex2D
	@brief Draw texture directly to display buffer. Maps non-visible textures
	like depth to a visible palette when drawing for visual debugging.

	This may cause fighting with the operating system and flashing/text or
	other visual updates might show through. If using this for an application,
	be sure to disable the operating system from drawing to the display buffer
	in GrWinUpdate32.

	@param[in] tex	Texture to draw to display buffer.
	@param[in] x	X position on screen to draw texture.
	@param[in] y	Y position on screen to draw texture. 
*/
U0 Tex2DDebugDisp(CTex2D *tex, I64 x, I64 y)
{
	// i, j = sampling x, y position on texture
	I64 i, j;
	
	// For scaling depth buffer to 8 bit color
	F64 scaled;
	CBGR24 color;

	for (j = 0; j < tex->h; j++)
	{
		for (i = 0; i < tex->w; i++)
		{
			switch (tex->type)
			{
				case TEX2D_RAW:
					text.fb_alias[(x + i) + (y + j) * GR_WIDTH] 
						= tex->rawBuf[i + j * tex->w];
				break;

				case TEX2D_DEPTH:
					// Scaled to display 0-1024 depth
					scaled = tex->depthBuf[i + j * tex->w] / 4;
					color.r = scaled;
					color.g = scaled;
					color.b = scaled;
					text.fb_alias[(x + i) + (y + j) * GR_WIDTH] = color;
				break;
			}
		}
	}
}

/**
	@ingroup Tex2D
	@brief Sample color from color textures at normalized UV coordinate 
	(0.0-1.0). Coordinates over 1.0 loop causing a repeating texture effect. 

	Does not handle filtering or mip maps (yet).

	@param[in,out] col	Sets color at this address to sampled color.
	@param[in]     tex	Texture to sample from.
	@param[in]     u	Normalized (0.0-1.0) x coordinate to sample from.
	@param[in]     v	Normalized (0.0-1.0) y coordinate to sample from.
*/
U0 Tex2DSampleNorm(CBGR24 *col, CTex2D *tex, F64 u, F64 v)
{
	I64 x = u * tex->w;
	I64 y = v * tex->h;
	x %= tex->w;
	y %= tex->h;

	*col = tex->rawBuf[x + y * tex->w];
}

/**
	@ingroup Tex2D
	@brief Sample color from color textures at UV coordinate. Coordinates
	over texture dimensions loop causing a repeating texture effect.

	@param[in,out] col	Sets color at this address to sampled color.
	@param[in]     u	X coordinate to sample from.
	@param[in]     v	Y coordinate to sample from.
*/
U0 Tex2DSampleCoord(CBGR24 *col, CTex2D *tex, I64 u, I64 v)
{
	u %= tex->w;
	v %= tex->h;

	*col = tex->rawBuf[u + v * tex->w];
}
