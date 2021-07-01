
/**
	@internal
	@ingroup GLWAD
	@brief Hash table type for lump hash.
*/
#define HTT_LUMP		69

/**
	@internal
	@ingroup GLWAD
	@brief Hash for quick access of lump pointer and index by name.
*/
class CHashGLWADLump : CHash
{
	CGLWADFileLump *lump;
	I64 lumpIndex;
};

/**
	@ingroup GLWAD
	@brief Class for WAD currently in memory.

	Has easy access handles and a hash table to quickly find lumps.
*/
class CGLWAD
{
	U8 *name;
	U8 *fileBuf;
	CGLWADInfo *info;			// WAD info header handle
	CGLWADFileLump *lumps;		// File lumps array handle
	CHashTable *lumpTable;		// Hash table for quick access of
								// lumps by name.
	CHashGLWADLump *hashLumps;	// Hashes for lumpTable.
};

/**
	@ingroup GLWAD
	@brief Finds lump with name and returns it's index in the WAD. Also 
	points input lump pointer to it if found.

	@param[in]     wad	WAD to search.
	@param[in]     name	Lump name to find.
	@param[in,out] lump	Points to lump if found.
	@return				Lump index in WAD. -1 if not found.
*/
I64 GLWADFindLump(CGLWAD *wad, U8 *name, CGLWADFileLump **lump = NULL)
{
	CHashGLWADLump *lumpHash;
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
	@ingroup GLWAD
	@brief Loads Half-Life WAD file.

	@param[in,out] wad		Uninitialized WAD to load into.
	@param[in]     fname	File name of WAD.
*/
U0 GLWADLoad(CGLWAD *wad, U8 *fname)
{
	I64 i;
	U32 *type;
	
	wad->fileBuf = FileRead(fname);
	wad->name = StrNew(fname);

	// Map info handle to buffer
	wad->info = wad->fileBuf;
	
	// Allocate hash table
	wad->lumpTable = HashTableNew(wad->info->nLumps);	// Table
	wad->hashLumps = CAlloc(wad->info->nLumps *			// Hashes
		sizeof(CHashGLWADLump));

	// Check version
	type = wad->info->type;	// Cast to U32

	//           'WAD3': Half Life      'WAD2': Quake
	if (*type == 0x33444157 || *type == 0x32444157)
	{
		// Map lumps to buffer
		wad->lumps = wad->fileBuf + wad->info->lumpOffset;
			
		for (i = 0; i < wad->info->nLumps; i++)
		{
			// Copy name to hash
			wad->hashLumps[i].str = CAlloc(17);
			MemCopy(wad->hashLumps[i].str, wad->lumps[i].name, 16);

			// Set hash type
			wad->hashLumps[i].type = HTT_LUMP;

			// Link lump to hash
			wad->hashLumps[i].lump = &wad->lumps[i];

			// Set lump index in hash to this index
			wad->hashLumps[i].lumpIndex = i;

			// Add hash to table
			HashAdd(&wad->hashLumps[i], wad->lumpTable);
		}
		return;
	}

	"[ERROR] %s WAD TYPE NOT RECOGNIZED: %4ts\n", fname, type;
}

/**
	@ingroup GLWAD
	@brief Free WAD.

	@param[in,out] wad WAD to free.
*/
U0 GLWADFree(CGLWAD *wad)
{
	I64 i;
	Free(wad->name);
	Free(wad->lumpTable->body);
	Free(wad->lumpTable);

	for (i = 0; i < wad->info->nLumps; i++)
	{
		Free(wad->hashLumps[i].str);
	}
	Free(wad->hashLumps);

	Free(wad->fileBuf);
}