/**
	@ingroup Tex2D
	@brief Loads Half-Life texture from WAD file.

	@param[in,out] tex		Unitialized texture to load into.
	@param[in]     wad		WAD file to load from.
	@param[in]     texName	Name of texture lump in WAD file to load.
*/
U0 Tex2DLoadWAD(CTex2D *tex, CWAD *wad, U8 *texName)
{
	if (wad->type != WAD_TYPE_HL)
	{
		"[ERROR] CAN NOT LOAD %s TEXTURE FROM NON-HALF-LIFE WAD %s. USE LOAD
		SPRITE/FLAT/WALL FOR DOOM WADS.\n", texName, wad->name;
		return;
	}

	// Get lump handle
	CWADFileLumpHL *lump;
	I64 texIndex = WADFindLump(wad, texName, &lump);
	
	if (texIndex < 0)
	{
		"[ERROR] CAN NOT FIND %s TEXTURE IN WAD %s\n", texName, wad->name;
		return;
	}

	// Map texture class to WAD file buffer
	CWADTexHL *wadTex = wad->fileBuf + lump->filePos;

	Tex2DInit(tex, TEX2D_RAW, wadTex->w, wadTex->h);

	// Map pixel array
	U8 *pixel = wad->fileBuf + lump->filePos + wadTex->offsets[0];
	
	// After the last byte of the fourth mipmap, there are two padding bytes,
	// then a palette of 24-bit color (R, G, B).
	U8 *palette = wad->fileBuf + lump->filePos + wadTex->offsets[3] +
		((wadTex->w * wadTex->h) / 64) + 2;	
		// 1/64 here is the relative size of 4th mip map

	I64 i;
	CBGR24 color;
	color.pad = 255;	// Alpha

	for (i = 0; i < wadTex->w * wadTex->h; i++)
	{
		color.r = palette[pixel[i] * 3];
		color.g = palette[(pixel[i] * 3) + 1];
		color.b = palette[(pixel[i] * 3) + 2];
		
		tex->rawBuf[i] = color;

		// Full blue pixels are transparent
		if (color == 0xFF0000FF)
			tex->rawBuf[i].pad = 0;
	}
}

/**
	@internal
	@ingroup Tex2D
	@brief Loads DOOM patch at memory location into position on texture.

	Relevant locations on texture should be initialized with a transparent
	alpha byte.

	@param[in,out] tex		Initialized texture to load into.
	@param[in]     patch	Memory location of patch to load from.
	@param[in]     palette	Array of 256 colors.
	@param[in]     l		Left (x) offset.
	@param[in]     t		Top (y) offset.
*/
U0 Tex2DLoadWADPatch(CTex2D *tex, CWADPatch *patch, CBGR24 *palette, 
	I64 l, I64 t)
{
	I64 x, y;
	CWADPost *post;			// Current post being parsed.

	// Direct pointer addition gives wierd results so these are
	// intermediate pointers:
	I64 patchAddr = patch;
	I64 cursor;

	// Iterate through every column in patch
	for (x = 0; x < patch->w; x++)
	{
		// Point post to first post in current column
		cursor = patchAddr + patch->columnOffsets[x];
		post = cursor;

		// Post with offset 255 is last post in column and is empty
		while (post->yOffset != 255)
		{
			// Draw every pixel in post to texture buffer
			for (y = 0; y < post->length; y++)
			{
				tex->rawBuf[(x + l) + (y + t + post->yOffset) * tex->w]
					= palette[post->pixels[y]];
			}

			// Point post to next post in column
			cursor += post->length + 4;	// 3 starting bytes + last pad byte
			post = cursor;
		}
	}
}

/**
	@ingroup Tex2D
	@brief Loads DOOM sprite from WAD file.

	@param[in,out] tex		Unitialized texture to load into.
	@param[in]     wad		WAD file to load from.
	@param[in]     sprName	Name of sprite in WAD file to load.
*/
U0 Tex2DLoadWADSprite(CTex2D *tex, CWAD *wad, U8 *sprName)
{
	if (wad->type != WAD_TYPE_DOOM)
	{
		"[ERROR] CAN NOT LOAD %s SPRITE FROM NON-DOOM %s\n", sprName, wad->name;
		return;
	}

	// Get lump handle
	CWADFileLumpDoom *lump;
	I64 sprIndex = WADFindLump(wad, sprName, &lump);

	if (sprIndex < 0)
	{
		"[ERROR] CAN NOT FIND %s SPRITE IN %s\n", sprName, wad->name;
		return;
	} 

	// Map patch class to sprite lump (which is in patch format)
	CWADPatch *patch = wad->fileBuf + lump->filePos;

	Tex2DInit(tex, TEX2D_RAW, patch->w, patch->h, patch->l, patch->t);
	Tex2DColorFill(tex, 0);	// To set alpha to 0 since patch's don't draw
							// the transparent pixels, only opaque ones.
	Tex2DLoadWADPatch(tex, patch, wad->paletteBuf, 0, 0);
}

/** 
	@ingroup Tex2D
	@brief Loads DOOM wall texture from WAD file.

	@param[in,out] tex		Uninitialized texture to load into.
	@param[in]     wad		WAD file to load from.
	@param[in]     wallName	Name of wall in WAD file to load.
*/
U0 Tex2DLoadWADWall(CTex2D *tex, CWAD *wad, U8 *wallName)
{

}

/**
	@internal
	@ingroup Tex2D
	@brief BMP file header.
*/
class CBMPHeader
{
	U8 szVersion[2];	// Should have 'BM' signature
	U32 nSize;			// File size in bytes
	U32 pad;			// Unused
	U32 nOffset;		// Offset from beginning of file to data;

	/* Info header is right after first header, so it is merged into this class */
	U32 nInfoSize;		// Size of this info part of the header (=40)
	U32 nWidth;			// Image width in pixels
	U32 nHeight;		// Image height in pixels
	U16 nPlanes;		// Number of planes (=1)
	U16 nPxBits;		// Number of bits per pixel. This also indicates palette method:
						// 1-bit:	Monochrome
						// 4-bit:	16-color palette
						// 8-bit:	256-color palette
						// 16-bit:	65565 colors
						// 24-bit:	16M colors
	U32 nCompression;	// Type of compression:
						// 0: BI_RGB	no-compression
						// 1: BI_RLE8	8-bit RLE encoding
						// 2: BI_RLE4 	4-bit RLE encoding
	U32 nImageSize;		// Size of image if compressed, (can =0 if not compressed)
	U32 nXPxPerM;		// Horizontal resolution, pixels per meter
	U32 nYPxPerM;		// Vertical resolution, pixels per meter
	U32 nColors;		// Number of actually used colors (ie. 256 for 8-bit color)
	U32 nImptColors;	// Number of important colors (=0 for all) 
};

/**
	@ingroup Tex2D
	@brief Loads BMP image.

	Supports standard uncompressed 24-bit color BMP images.

	@param[in,out] tex		Uninitialized texture to load into.
	@param[in]     fname	File name of BMP.
*/
U0 Tex2DLoadBMP(CTex2D *tex, U8 *fname, Bool mask = FALSE, 
	Bool invert = TRUE)
{
	U8 *bmp = FileRead(fname);

	// Map locations in buffer;
	CBMPHeader *info = bmp;

	//if (StrMatch(bmp->szVersion, "BM") == 0)
	if (info->szVersion[0] != 'B' && info->szVersion[1] != 'M')
	{
		"[ERROR] %s IS NOT A VALID BMP FILE!\n", fname;
		return;
	}

	if (info->nPxBits != 24 || info->nCompression != 0)
	{
		"[ERROR] %s IS NOT A 24-BIT UNCOMPRESSED BMP!\n", fname;
		return;
	}
	
	// Each pixel is 3 bytes in 24-bit BMP, however CTex2D uses CBGR24
	// which contains a final padding bit (32-bits per pixel). The rows
	// also increment in the opposite direction.
	I64 imgPointer = bmp + info->nOffset;
	I64 xPx, yPx;
	
	// For checking if a color channel is greater than 0 for masks
	U8 channel;

	if (mask)
	{
		/*
		// Initialize with MASK format for 1-bit non-compressed color
		Tex2DInit(tex, TEX2D_MASK, info->nWidth, info->nHeight);

		for (yPx = 0; yPx < info->nHeight; yPx++)
		{
			for (xPx = 0; xPx < info->nWidth; xPx++)
			{
				channel = *(imgPointer + (xPx + info->nWidth * 
					(info->nHeight - yPx)) * 3);

				if ((channel == 0 && invert = TRUE) ||
					(channel > 0 && invert = FALSE))
				{
					tex->maskBuf[(xPx + info->nWidth * yPx) / 8] | (1 << (xPx % 8));
				}
			}
		}
		*/
	}
	else
	{
		// Initialize with RAW format for 24-bit non-compressed color
		Tex2DInit(tex, TEX2D_RAW, info->nWidth, info->nHeight);
	
		for (yPx = 0; yPx < info->nHeight; yPx++)
		{
			for (xPx = 0; xPx < info->nWidth; xPx++)
			{
				MemCopy(&tex->rawBuf[xPx + info->nWidth * yPx], 
					imgPointer + (xPx + info->nWidth * (info->nHeight - yPx)) 
					* 3, 3);
			}
		}
	}
}

