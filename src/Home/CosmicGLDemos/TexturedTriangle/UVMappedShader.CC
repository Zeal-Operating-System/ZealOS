/* This demo shows how to create a custom model format, import a texture, and
program a shader to render a triangle. */

Cd(__DIR__);;

I64 wWC = 32;  		// Window width in columns (512px)
I64 wHC = 32; 		// Window height in rows (512px)
I64 wW = wWC * 8;
I64 wH = wHC * 8; 
I64 wXC = 1;       		// Window x in columns
I64 wYC = 2;       		// Window y in rows
I64 wX = wXC * 8;
I64 wY = (wYC + 4) * 8;

SettingsPush;
WinHorz(wXC, wXC + wWC - 1);
WinVert(wYC, wYC + wHC + 3);
DocClear;

// Framebuffer Initialization
CTex2D frameBuf;
CTex2D depthBuf;

Tex2DInit(&frameBuf, TEX2D_RAW, wW, wH);
Tex2DInit(&depthBuf, TEX2D_DEPTH, wW, wH);

// Clear framebuffer texture with black background
CBGR24 cBlack;
cBlack.r = 0; cBlack.g = 0; cBlack.b = 0;
Tex2DColorFill(&frameBuf, cBlack);

// Importing BMP texture
CTex2D texture;
Tex2DLoadBMP(&texture, "MrGod.bmp");

// Create custom model format that is quite straightforward
class MDL
{
	I64 nTris;
	CTri *tri;
	CVec2 *uv;
};

// Load it with a texture mapped triangle. 
MDL model;
model.nTris = 1;
model.tri = MAlloc(sizeof(CTri));
model.tri[0].p[0].x = 0.0;
model.tri[0].p[0].y = 0.8;
model.tri[0].p[0].z = 0.0;
model.tri[0].p[1].x = -0.8;
model.tri[0].p[1].y = -0.4;
model.tri[0].p[1].z = 0.0;
model.tri[0].p[2].x = 0.8;
model.tri[0].p[2].y = -0.4;
model.tri[0].p[2].z = 0.0;
model.uv = MAlloc(sizeof(CVec2)*3);
// UVs commonly use coordinates of 0.0-1.0, although you can use direct pixel
// coordinates if you use the pixel coordinate sampler in the shader.
model.uv[0].x = 0.5;
model.uv[0].y = 0.0898;
model.uv[1].x = 0.07421875;
model.uv[1].y = 0.73046875;
model.uv[2].x = 0.9375;
model.uv[2].y = 0.7305;

// In this example a class is not needed for the uniforms (unchanging
// parameters), we only feed the pointer for the texture we want to sample.
// to the shader.

// Generate a shader. Each vertex has a UV coordinate (coordinate that
// maps to the texture), so we only need to pass one CVEC2 attribute
// from the vertex shader to the fragment shader.
CShader shd, shdB;
shd.vertValues = MAlloc(sizeof(I64));
shd.vertValues[0] = SHD_CVEC2; // UV coordinate
shd.nVertValues = 1;

// The vertex shader gives the normalized device coordinates (screen coordinates
// from -1.0 to 1.0) of each vertex of a specified triangle. Normally you would
// do translations and perspective transforms, but here our model is already in
// NDC. It also passes the UV coordinates of each vertex to the vertOutBuf to
// be interpolated for the fragment shader.
U0 vShader(CTri *tri, F64 *vertOutBuf, U8 *mdlPtr, U8 *uniforms, I64 iTri, I64 nTris)
{
	MDL *mdl = mdlPtr;
	MemCopy(tri, &mdl->tri[iTri], sizeof(CTri));
	MemCopy(vertOutBuf, &mdl->uv[iTri*3], sizeof(CVec2)*3);
}

// The fragment shader calculates what color an individual fragment (pixel)
// should be. Here we use the interpolated UV coordinate from the fragInBuf to
// sample the color from the texture.
U0 fShader(CBGR24 *color, F64 *fragInBuf, U8 *uniforms)
{
	// We will pass in the texture pointer through the uniform later
	// when we render.
	Tex2DSampleNorm(color, uniforms, fragInBuf[0], fragInBuf[1]);
}

// Attach vertex and fragment shader
shd.FragShd = &fShader;
shd.VertShd = &vShader;

while (CharScan() == 0)
{
	// Where &texture is you would usually feed in a pointer to uniforms, 
	// however since the texture is the only value the shader needs, 
	// we simply pass in that pointer.
	RenderTris(&shd, &frameBuf, &depthBuf, &model, &texture, 1);
	Tex2DDebugDisp(&frameBuf, wX, wY);
	Sleep(1);
}

Tex2DFree(&frameBuf);
Tex2DFree(&depthBuf);
Tex2DFree(&texture);
SettingsPop;
Exit;
