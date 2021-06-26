/**
	@internal
	@ingroup WAD
	@brief Half-Life WAD type.
*/
#define WAD_TYPE_HL		1

/**
	@internal
	@ingroup WAD
	@brief Doom WAD type.
*/
#define WAD_TYPE_DOOM	2

/**
	@internal
	@ingroup WAD
	@brief Hash table type for lump hash.
*/
#define HTT_LUMP		69

/**
	@internal
	@ingroup WAD
	@brief Hash for quick access of lump pointer and index by name.
*/
class CHashLump : CHash
{
	CWADFileLump *lump;		// Pointer to lump
							// Access with lump->doom/lump->hl
	I64 lumpIndex;			// Index of lump in WAD
};

/**
	@ingroup WAD
	@brief Class for WAD currently in memory.

	Has easy access handles and a hash table to quickly find lumps.
*/
class CWAD
{
	U8 *name;
	U8 *fileBuf;
	CWADInfo *info;				// Type, size, pointer to lumps
	CWADFileLumpDoom *doomLumps;// Quick access doom lumps
	CWADFileLumpHL	*hlLumps;	// Quick access half life lumps
	I64 type;					// WAD type
	CHashTable *lumpTable;		// Hash table for quick access of
								// lumps by name.
	CHashLump *hashLumps;		// Hashes for lumpTable.
	CBGR24 *paletteBuf;			// Color palette 0 for texture loading if doom
};

/**
	@ingroup WAD
	@brief Finds lump with name and returns it's index in the WAD. Also 
	points input lump pointer to it if found.

	@param[in]     wad	WAD to search.
	@param[in]     name	Lump name to find.
	@param[in,out] lump	Points to lump if found.
	@return				Lump index in WAD. -1 if not found.
*/
I64 WADFindLump(CWAD *wad, U8 *name, CWADFileLump **lump = NULL)
{
	CHashLump *lumpHash;
	lumpHash = HashFind(name, wad->lumpTable, HTT_LUMP);

	if (lumpHash != NULL)
	{
		if (lump != NULL)
			*lump = lumpHash->lump;

		return lumpHash->lumpIndex;
	}
	else
	{
		return -1;
	}
}

/**
	@ingroup WAD
	@brief Loads WAD file.

	@param[in,out] wad		Uninitialized WAD to initialize.
	@param[in]     fname	File name of WAD.
*/
U0 WADLoad(CWAD *wad, U8 *fname)
{
	wad->fileBuf = FileRead(fname);
	wad->name = StrNew(fname);

	// For palette loading if doom WAD
	CWADFileLumpDoom *paletteLump;
	U8 *paletteColor;

	// Map locations in buffer
	wad->info = wad->fileBuf;
	
	// Allocate hash table
	wad->lumpTable = HashTableNew(wad->info->nLumps);	// Table
	wad->hashLumps = CAlloc(wad->info->nLumps *			// Hashes
		sizeof(CHashLump));

	I64 i;

	// Check version and proceed accordingly
	U32 *type = wad->info->type;	// Cast to U32

	//           'WAD3': Half Life      'WAD2': Quake
	if (*type == 0x33444157 || *type == 0x32444157)
	{
		wad->type = WAD_TYPE_HL;

		// Map lumps to buffer
		wad->hlLumps = wad->fileBuf + wad->info->lumpOffset;
			
		for (i = 0; i < wad->info->nLumps; i++)
		{
			// Copy name to hash
			wad->hashLumps[i].str = CAlloc(17); // 16 + NULL
			MemCopy(wad->hashLumps[i].str, 
				wad->hlLumps[i].name, 16);

			// Set hash type
			wad->hashLumps[i].type = HTT_LUMP;

			// Link lump to hash
			wad->hashLumps[i].lump = &wad->hlLumps[i];

			// Set lump index in hash to this index
			wad->hashLumps[i].lumpIndex = i;

			// Add hash to table
			HashAdd(&wad->hashLumps[i], wad->lumpTable);
		}
		return;
	}
	
	//           'IWAD': Doom Internal  'PWAD': Doom Patch
	if (*type == 0x44415749 || *type == 0x44415750)
	{
		wad->type = WAD_TYPE_DOOM;

		// Map lumps to buffer
		wad->doomLumps = wad->fileBuf + wad->info->lumpOffset;

		for (i = 0; i < wad->info->nLumps - 10; i++)
		{
			// Copy name to hash
			wad->hashLumps[i].str = CAlloc(9); // 8 + NULL
			MemCopy(wad->hashLumps[i].str, 
				wad->doomLumps[i].name, 8);

			// Set hash type
			wad->hashLumps[i].type = HTT_LUMP;

			// Link lump to hash
			wad->hashLumps[i].lump = &wad->doomLumps[i];

			// Set lump index in hash to this index
			wad->hashLumps[i].lumpIndex = i;

			// Add hash to table
			HashAdd(&wad->hashLumps[i], wad->lumpTable);
		}

		// Load palette 0 for texture loading later if it exists
		if (WADFindLump(wad, "PLAYPAL", &paletteLump) != -1)
		{
			wad->paletteBuf = MAlloc(sizeof(CBGR24) * 256);
			paletteColor = wad->fileBuf + paletteLump->filePos;
			
			// Load each 3-byte RGB color into 4 byte BGRA palette
			for (i = 0; i < 256; i++)
			{
				wad->paletteBuf[i].r = paletteColor[i * 3];
				wad->paletteBuf[i].g = paletteColor[i * 3 + 1];
				wad->paletteBuf[i].b = paletteColor[i * 3 + 2];
				wad->paletteBuf[i].pad = 255;	// Alpha
			}
		}
 
		return;
	}

	// Type not recognized
	U64 typeStr = 0;
	MemCopy(&typeStr, wad->type, 4);
	"[ERROR] %s WAD TYPE NOT RECOGNIZED: %s\n", typeStr;
}

/**
	@ingroup WAD
	@brief Free WAD.

	@param[in,out] wad WAD to free.
*/
U0 WADFree(CWAD *wad)
{
	Free(wad->lumpTable->body);
	Free(wad->lumpTable);
	Free(wad->hashLumps);
	Free(wad->fileBuf);
}

