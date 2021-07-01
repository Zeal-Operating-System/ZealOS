/**
	@defgroup GLWAD WAD File Loading
	@brief Half-Life WAD file format management and parsing.
*/

/**
	@internal
	@ingroup GLWAD
	@brief WAD file header.
*/
class CGLWADInfo
{
	U8 type[4];		// Type of WAD, like IWAD/PWAD/WAD3
	I32 nLumps;		// Number of lumps
	I32 lumpOffset;	// Offset to lump
};

/**
	@ingroup GLWAD
	@brief Half-Life WAD file lump. These point to "lumps" or directories in
	the WAD.
*/
class CGLWADFileLump
{
	I32 filePos;		// Relative offset
	I32 diskSize;		// Size of lump (compressed)
	I32 size;			// Uncompressed lump size
	I8 type;
	I8 compression;		// 0 if none
	I16 pad;
	U8 name[16];
};

/**
	@internal
	@ingroup GLWAD
	@brief Header to a Half-Life texture lump.
*/
class CGLWADTex
{
	U8 name[16];
	U32 w;
	U32 h;
	U32 offsets[4];	// Relative offset to each mip map
};