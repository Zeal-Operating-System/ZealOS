
/**
	@ingroup Draw
	@brief Draw non-transformed color texture with blit operation.

	Does not yet check if texture being drawn is entirely inside the texture
	being drawn to.

	@param[in,out] dst			Destination texture to draw to.
	@param[in]     src			Source texture to draw.
	@param[in]     x			X location to draw texture.
	@param[in]     y			Y location to draw texture.
	@param[in]     transparent	(optional) use alpha as mask. False by default.
*/
U0 DrawTexture(CTex2D *dst, CTex2D *src, I64 x, I64 y, 
	Bool transparent = FALSE)
{
	I64 xC, yC; // Current width/height position being copied from

	I64 srcW = src->w;	// Don't think the compiler is optimizing this so I am
	I64 srcH = src->h;
	I64 dstW = dst->w;

	if (transparent)
	{
		for (yC = 0; yC < srcH; yC++)
		{
			for (xC = 0; xC < srcW; xC++)
			{
				if (src->rawBuf[xC + yC * srcW].pad == 255)
				{
					// Assume target doesn't care about alpha byte being copied
					dst->rawBuf[(x + xC) + (y + yC) * dstW] =
						src->rawBuf[xC + yC * srcW];
				}
			} 
		}
	}
	else
	{
		for (yC = 0; yC < srcH; yC++)
		{
			MemCopy(&dst->rawBuf[x + (y + yC) * dstW],
				&src->rawBuf[yC * srcW], sizeof(CBGR24) * srcW);
		}
	}
}