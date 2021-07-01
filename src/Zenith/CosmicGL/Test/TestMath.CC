Cd(__DIR__);;
#include "../Math/Types"
#include "../Math/Vec4"
#include "../Math/Vec3"

CVec4 *a = MAllocAligned(sizeof(CVec4), 16);
CVec4 *b = MAllocAligned(sizeof(CVec4), 16);
CVec4 *dest = MAllocAligned(sizeof(CVec4), 16);
CVec4 *trueRes = MAllocAligned(sizeof(CVec4), 16);

// Note that some smaller vector functions are identical to larger vector
// functions so they do not get tested. 

//-----------------------------------------------------------------------------
// Vec4Copy

Vec4(1.25, 2.5, 3.75, 5.0, a);
Vec4(0.0, 0.0, 0.0, 0.0, dest);
Vec4Copy(a, dest);
if (!Vec4IsEqual(a, dest))
{
	"[WARNING] Vec4Copy NOT WORKING CORRECTLY! RESULT VECTOR:\n";
	Vec4Print(dest);
}
//-----------------------------------------------------------------------------
// Vec4Add

Vec4(1.25, -2.5, 3.75, -5.0, a);
Vec4(-1.0, 2.0, -3.0, 4.0, b);
Vec4(0.25, -0.5, 0.75, -1.0, trueRes);
Vec4Add(a, b, dest);
// Looks like I have to use actual float compare and not direct
// equal compare. I'll fix Vec4IsEqual to do this.
if (!Vec3IsEqual(dest, trueRes))
{
	"[WARNING] Vec4Add NOT WORKING CORRECTLY! RESULT VECTOR:\n";
	Vec3Print(dest);
}
//-----------------------------------------------------------------------------

Free(a);
Free(b);
Free(dest);

