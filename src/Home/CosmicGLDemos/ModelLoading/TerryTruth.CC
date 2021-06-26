/* This demo shows how to load a custom model (created based on the .obj format
using a converstion script). It uses WAD textures rather than BMP textures 
unlike most of the other demos. The model is not transformed in any way and 
is rendered directly, so scaling the window will also scale the resulting 
render. */

Cd(__DIR__);;

I64 wWC = 80;  		// Window width in columns (Drop to under 80 for 640x480 displays)
I64 wHC = 45; 		// Window height in rows (Drop to under 60 for 640x480 displays)
I64 wW = wWC * 8;
I64 wH = wHC * 8; 
I64 wXC = 1;       		// Window x in columns
I64 wYC = 2;       		// Window y in rows
I64 wX = wXC * 8;
I64 wY = (wYC + 0) * 8;

SettingsPush;
WinHorz(wXC, wXC + wWC - 1);
WinVert(wYC, wYC + wHC - 1);
DocClear;

// Framebuffer Initialization
CTex2D frameBuf;
CTex2D depthBuf;

Tex2DInit(&frameBuf, TEX2D_RAW, wW, wH);
Tex2DInit(&depthBuf, TEX2D_DEPTH, wW, wH);

// Colors
CBGR24 cBlack;
cBlack.r = 0; cBlack.g = 0; cBlack.b = 0;
CBGR24 cRed;
cRed.r = 255; cRed.g = 20; cRed.b = 20;
CBGR24 cWhite;
cWhite.r = 255; cWhite.g = 255; cWhite.b = 255;

Tex2DColorFill(&frameBuf, cBlack);

// Texture Intitalization
CWAD wad;
WADLoad(&wad, "KingTerry.wad");

CTex2D TexRevelation;
Tex2DLoadWAD(&TexRevelation, &wad, "Revelation");

CTex2D TexKingTerrySkin;
Tex2DLoadWAD(&TexKingTerrySkin, &wad, "KingTerry_Skin");

CTex2D TexKingTerryBody;
Tex2DLoadWAD(&TexKingTerryBody, &wad, "KingTerry_Body");

CTex2D TexNebula;
Tex2DLoadWAD(&TexNebula, &wad, "Nebula");

WADFree(&wad);

// Generate our own page texture
CTex2D TexPages;
Tex2DInit(&TexPages, TEX2D_RAW, 256, 256);
Tex2DColorFill(&TexPages, cWhite);
DrawString(&TexPages, 16, 20, "I should fix", cBlack);
DrawString(&TexPages, 16, 35, "the UVs on this", cBlack);
DrawString(&TexPages, 16, 50, "book model.", cBlack);

class CMat
{
	U8 name[32];
	U32 nOffset;	// Offset to first triangle
	U32 nTris;		// Number of triangles
};

class CZMHeader
{
	I32 nMats;			// Number of materials
	U32 nTriOffset;		// Triangle array offset
	U32 nVertOffset;	// Vertex array offset
	U32 nUVOffset;		// UV array offset
	U32 nNormOffset;	// Normal array offset
};

class CZMTri
{
	U32 iV1;	// Vertices
	U32 iV2;
	U32 iV3;
	U32 iN1;	// Normals
	U32 iN2;
	U32 iN3;
	U32 iT1;	// UVs
	U32 iT2;
	U32 iT3;
};

class CZModel
{
	CMat *mat;
	CZMTri *tri;
	CVec3 *vert;
	CVec2 *uv;
	CVec3 *norm;
};

class UniformTex
{
	I64 mat;		// Material index of model to render
	CTex2D *tex;
};

class UniformCol
{
	I64 mat;
	CBGR24 col;
};

// Load model
U8 *MdlHandle = FileRead("TerryTruth.ZM");
CZMHeader *header = MdlHandle;
CZModel MdlTerry;

MdlTerry.mat = MdlHandle + 20;
MdlTerry.tri = MdlHandle + header->nTriOffset;
MdlTerry.vert = MdlHandle + header->nVertOffset;
MdlTerry.uv = MdlHandle + header->nUVOffset;
MdlTerry.norm = MdlHandle + header->nNormOffset;

// Prepare uniforms (unchanging parameters) to feed into shader

// Book cover is red
UniformCol UniCover;
UniCover.col.r = 150;
UniCover.col.g = 0;
UniCover.col.b = 0;
UniCover.mat = 0;

// Skin uses skin texture
UniformTex UniKingTerry_Skin;
UniKingTerry_Skin.tex = &TexKingTerrySkin;
UniKingTerry_Skin.mat = 1;

// Body uses body texture
UniformTex UniKingTerry_Body;
UniKingTerry_Body.tex = &TexKingTerryBody;
UniKingTerry_Body.mat = 2;

// Hat is black (dark gray)
UniformCol UniHat;
UniHat.col.r = 20;
UniHat.col.g = 20;
UniHat.col.b = 20;
UniHat.mat = 3;

// Pages uses WAD texture
UniformTex UniPages;
UniPages.tex = &TexPages;	// Set this to &TexRevelation for original.
UniPages.mat = 4;

// Nebula uses WAD texture
UniformTex UniNebula;
UniNebula.tex = &TexNebula;
UniNebula.mat = 5;

// Generate a texure and color shader
CShader ShdTex, ShdCol;
ShdTex.vertValues = MAlloc(2 * sizeof(I64));
ShdTex.vertValues[0] = SHD_CVEC2; // UV
ShdTex.vertValues[1] = SHD_CVEC3; // Normal

ShdCol.vertValues = MAlloc(2 * sizeof(I64));
ShdCol.vertValues[0] = SHD_CVEC2; // UV
ShdCol.vertValues[1] = SHD_CVEC3; // Normal

ShdTex.nVertValues = 2;
ShdCol.nVertValues = 2;

U0 vShaderTex(CTri *tri, F64 *vertOutBuf, U8 *mdlPtr, U8 *uniforms, I64 iTri, I64 nTris)
{
	CZModel *mdl = mdlPtr;
	UniformTex *uni = uniforms;

	nTris++; // So I don't have to see the unused warning.
	
	I64 t = mdl->mat[uni->mat].nOffset + iTri;	// Triangle index in triangle array

	// Copy model directly into the triangle, I won't even transform for this demo.
	MemCopy(&tri->p[0], &mdl->vert[mdl->tri[t].iV1 - 1], sizeof(CVec3));
	MemCopy(&tri->p[1], &mdl->vert[mdl->tri[t].iV2 - 1], sizeof(CVec3));
	MemCopy(&tri->p[2], &mdl->vert[mdl->tri[t].iV3 - 1], sizeof(CVec3));

	tri->p[0].z = -1 * tri->p[0].z;
	tri->p[1].z = -1 * tri->p[1].z;
	tri->p[2].z = -1 * tri->p[2].z;

	// Copy uv and normals into vertOutBuf to be interpolated for the vertex shader.
	MemCopy(&vertOutBuf[0], &mdl->uv[mdl->tri[t].iT1 - 1], sizeof(CVec2));
	MemCopy(&vertOutBuf[2], &mdl->norm[mdl->tri[t].iN1 - 1], sizeof(CVec3));
	MemCopy(&vertOutBuf[5], &mdl->uv[mdl->tri[t].iT2 - 1], sizeof(CVec2));
	MemCopy(&vertOutBuf[7], &mdl->norm[mdl->tri[t].iN2 - 1], sizeof(CVec3));
	MemCopy(&vertOutBuf[10], &mdl->uv[mdl->tri[t].iT3 - 1], sizeof(CVec2));
	MemCopy(&vertOutBuf[12], &mdl->norm[mdl->tri[t].iN3 - 1], sizeof(CVec3));
}

U0 fShaderTex(CBGR24 *color, F64 *fragInBuf, U8 *uniforms)
{
	UniformTex *uni = uniforms;
	Tex2DSampleNorm(color, uni->tex, fragInBuf[0], 1.0-fragInBuf[1]);
	// Debug, display normals
	// color->r=fragInBuf[2]*255.0; color->g=fragInBuf[3]*255.0; color->b=fragInBuf[4]*255.0;
}

U0 fShaderCol(CBGR24 *color, F64 *fragInBuf, U8 *uniforms)
{
	UniformCol *uni = uniforms;
	color->r = uni->col.r;
	color->g = uni->col.g;
	color->b = uni->col.b;
}

ShdTex.FragShd = &fShaderTex;
ShdTex.VertShd = &vShaderTex;
ShdCol.FragShd = &fShaderCol;
ShdCol.VertShd = &vShaderTex;

Tex2DDepthReset(&depthBuf);
RenderTris(&ShdCol, &frameBuf, &depthBuf, &MdlTerry, &UniCover, MdlTerry.mat[0].nTris);
RenderTris(&ShdTex, &frameBuf, &depthBuf, &MdlTerry, &UniKingTerry_Skin, MdlTerry.mat[1].nTris);
RenderTris(&ShdTex, &frameBuf, &depthBuf, &MdlTerry, &UniKingTerry_Body, MdlTerry.mat[2].nTris);
RenderTris(&ShdCol, &frameBuf, &depthBuf, &MdlTerry, &UniHat, MdlTerry.mat[3].nTris);
RenderTris(&ShdTex, &frameBuf, &depthBuf, &MdlTerry, &UniPages, MdlTerry.mat[4].nTris);
RenderTris(&ShdTex, &frameBuf, $ER$&depthBuf, &MdlTerry, &UniNebula, MdlTerry.mat[5].nTris);

while (CharScan() == 0)
{
	Tex2DDebugDisp(&frameBuf, wX, wY);
	Sleep(1);
}

Tex2DFree(&frameBuf);
Tex2DFree(&depthBuf);
Tex2DFree(&TexPages);
Tex2DFree(&TexRevelation);
Tex2DFree(&TexKingTerrySkin);
Tex2DFree(&TexKingTerryBody);
Tex2DFree(&TexNebula);

SettingsPop;
Exit;
