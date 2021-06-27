/**
	@defgroup WAD WAD
	@brief WAD file format management and parsing. Supports DOOM and
	Half-Life WADs.
*/

/**
	@internal
	@ingroup WAD
	@brief WAD file header.
*/
class CWADInfo
{
	U8 type[4];		// Type of WAD, like IWAD/PWAD/WAD3
	I32 nLumps;		// Number of lumps
	I32 lumpOffset;	// Offset to lump
};

/**
	@ingroup WAD
	@brief DOOM file lump. These point to "lumps" or directories in the WAD.
*/
class CWADFileLumpDoom
{
	I32 filePos;		// Relative offset
	I32 size;
	U8 name[8];
};

/**
	@ingroup WAD
	@brief Half-Life file lump. These point to "lumps" or directories in the
	WAD.
*/
class CWADFileLumpHL
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
	@ingroup WAD
	@brief Union of Half-Life and DOOM lump classes to return as a pointer
	from general purpose WAD functions like WADFindLump.
*/
union CWADFileLump
{
	CWADFileLumpDoom doom;
	CWADFileLumpHL hl;
};


/**
	@internal
	@ingroup WAD
	@brief Thing element from a DOOM WAD THINGS lump.

	Describes an entity.
*/
class CWADThing
{
	I16 x;
	I64 y;
	I16 angle;
	I16 type;
	I16 flags;
};

/**
	@internal
	@ingroup WAD
	@brief Linedef element from a DOOM WAD LINEDEFS lump.

	Describes a line that makes up a wall/sector boundary on the map.
*/
class CWADLinedef
{
	I16 v1;				// Vertex 1
	I16 v2;				// Vertex 2
	I16 flags;
	I16 type;
	I16 sectorTag;
	I16 frontSidedef;	// Sidedefs hold texture data for each side of linedef
	I16 backSidedef;
};

/**
	@internal
	@ingroup WAD
	@brief Sidedef element from a DOOM WAD SIDEDEFS lump.

	Describes a side of a line (wall) and what textures it uses as well as
	what sector it faces.
*/
class CWADSidedef
{
	I16 xOffset;		// Texture x offset
	I16 yOffset;		// Texture y offset
	U8 upperTex[8];		// These are found in TEXTUREx lumps
	U8 lowerTex[8];
	U8 middleTex[8];
	I16 sectorFaces;	// Sector this sidedef faces
};

/**
	@internal
	@ingroup WAD
	@brief Vertex element from a DOOM WAD VERTEXES lump.
*/
class CWADVertex
{
	I16 x;
	I16 y;
};

/**
	@internal
	@ingroup WAD
	@brief Segment element from a DOOM WAD SEGS lump.

	Describes a segment of a line that makes up the outline of a subsector
	(convex BSP leaf).
*/
class CWADSeg
{
	I16 v1;
	I16 v2;
	I16 angle;
	I16 linedef;
	I16 direction;
	I16 offset;
};

/**
	@internal
	@ingroup WAD
	@brief Sector element from a DOOM WAD SECTORS lump.
	
	Describes a 2D region of the map.
*/
class CWADSector
{
	I16 floorHeight;
	I16 ceilingHeight;
	U8 floorTex[8];
	U8 ceilingTex[8];
	I16 lightLevel;
	I16 flags;
	I16 tag;
};

/**
	@internal
	@ingroup WAD
	@brief Sub-sector element from a DOOM WAD SSECTORS lump. 

	Describes a convex BSP leaf, meaning a convex sub section of a sector.
*/
class CWADSubSector
{
	I16 nLinedefs;
	I16 firstLinedef;
};

/**
	@internal
	@ingroup WAD
	@brief Node element from a DOOM WAD NODES lump

	Describes a node on a BSP tree. Each node splits a region of the map into
	two along a line, with a left/right side child which can either be another
	node or a subsector.
*/
class CWADNode
{
	I16 x;
	I16 y;
};

/**
	@internal
	@ingroup WAD
	@brief DOOM Patch texture header.

	Points to columns which are variable size arrays of CWADPost. This is a
	variable length class.
*/
class CWADPatch
{
	U16 w;
	U16 h;
	I16 l;					// Offsets to shift origin point when drawing
	I16 t;
	U32 columnOffsets[1];	// Array of offsets (relative to header) of size
							// width. If columns are identical they may point 
							// to the same column in the file.
};

/**
	@internal
	@ingroup WAD
	@brief DOOM Post.

	A post is a vertical segment of opaque pixels in the column of a patch
	texture. There may be multiple of these posts in a column, one after the
	other, with the end of a column being signifiged by a post with an offset
	of 255. This is a variable length class.
*/
class CWADPost
{
	U8 yOffset;		// Offset from start of column. This is 255 if
					// signaling end of column.
	U8 length;		// Length is bytes/pixels
	U8 pad;
	U8 pixels[1];	// Size is equal to length. Each pixel points to a color
					// in the color palette.
	// Technically another U8 pad comes here but pixels is variable length
};

/**
	@internal
	@ingroup WAD
	@brief Header to DOOM TEXTUREx lumps.
*/
class CWADTexHeader
{
	I32 nTextures;	// Number of textures in TEXTUREx lump
	I32 offsets[1];	// Offsets to CWADMapTex's from start of this class
};

/**
	@internal
	@ingroup WAD
	@brief Information about DOOM patch and where to find it in the PNAMES
	lump.
*/
class CWADMapPatch
{
	I16 l;			// Left offset (x origin)
	I16 t;			// Top offset (y origin)
	I16 patch;		// Patch number listed in PNAMES lump
	I16 stepdir;	// Obsolete, ignored by all DOOM versions
	I16 colormap;	// Obsolete, ignored by all DOOM versions
};

/**
	@internal
	@ingroup WAD
	@brief Texture in a DOOM TEXTUREx lump.

	A texture is composed of multiple patches. However it would have been
	too simple for this to point to these patches directly, instead it points
	to CWADMapPatch  which describes where the patch is found in the PNAMES 
	lump.
*/
class CWADMapTex
{
	U8 name[8];
	I32 masked;					// Boolean
	I16 width;
	U16 height;
	U8 columnDir[4];			// Obsolete, ignored by all DOOM versions
	I16 patchCount;				// Number of patches that make up texture
	CWADMapPatch patches[1];	// Size dependent on patchCount
};

/**
	@internal
	@ingroup WAD
	@brief Header to a Half-Life texture lump.
*/
class CWADTexHL
{
	U8 name[16];
	U32 w;
	U32 h;
	U32 offsets[4];	// Relative offset to each mip map
};