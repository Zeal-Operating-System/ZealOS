/* Legacy math library. Is being replaced, however the few functions
still used will remain until SIMD math library is finished. */

/**
	@defgroup math Math
	@brief Legacy math stuff that is still being used.
*/

class CVec4
{
	F64 x;
	F64 y;
	F64 z;
	F64 w;
};

class CVec3
{
	F64 x;
	F64 y;
	F64 z;
};

class CVec2
{
	F64 x;
	F64 y;
};

class CIVec2
{
	I64 x;
	I64 y;
};

class CTri
{
	CVec3 p[3];
};

/**
	@ingroup math
	@brief Subtract vector b from a.

	@param[in]     a	Vector 1
	@param[in]     b	Vector 2
	@param[in,out] dest	Destination vector.
*/
U0 Vec2Sub(CVec2 *a, CVec2 *b, CVec2 *dest)
{
	dest->x = a->x - b->x;
	dest->y = a->y - b->y;
}

/**
	@ingroup math
	@brief Dot product of two vectors.

	@param[in] a	Vector 1
	@param[in] b	Vector 2
	@return         Dot product.
*/
F64 Vec2Dot(CVec2 *a, CVec2 *b)
{
	return a->x * b->x + a->y * b->y;
}

/**
	@ingroup math
	@brief Calculates barycentric coordinates for point p from triangle
	vertices a, b, and c.

	@param[in]     p	Point
	@param[in]     a	Vertex 1
	@param[in]     b	Vertex 2
	@param[in]     c	Vertex 3
	@param[in,out] u	U coordinate.
	@param[in,out] b	V coordinate.
	@param[in,out] w	W coordinate.
*/
U0 Vec2Barycentric(CVec2 *p, CVec2 *a, CVec2 *b, CVec2 *c, F64 *u, F64 *v, F64 *w)
{
	CVec2 v0, v1, v2;
	Vec2Sub(b, a, &v0);
	Vec2Sub(c, a, &v1);
	Vec2Sub(p, a, &v2);
	
	F64 d00 = Vec2Dot(&v0, &v0);	
	F64 d01 = Vec2Dot(&v0, &v1);
	F64 d11 = Vec2Dot(&v1, &v1);
	F64 d20 = Vec2Dot(&v2, &v0);
	F64 d21 = Vec2Dot(&v2, &v1);
	F64 denom = d00 * d11 - d01 * d01;

	F64 tempV, tempW;
	tempV = (d11 * d20 - d01 * d21)/denom;
	tempW = (d00 * d21 - d01 * d20)/denom;
	*u = 1.0 - tempV - tempW;	
	*v = tempV;
	*w = tempW;
}

/**
	@ingroup math
	@brief Converts float at address to double and writes to given address.
	
	Useful for parsing standard model formats.

	@param[in]     float	Float
	@param[in,out] double	Double
*/
U0 Float2Double(U32 *float, U64 *double)
{
	double->u32[1] = *float;

	// Isolate parts of F32
	U64 MASK_SIGN = 0b1000000000000000000000000000000000000000000000000000000000000000;
	U64 MASK_EXP  = 0b0111111110000000000000000000000000000000000000000000000000000000;
	U64 MASK_MANT = 0b0000000001111111111111111111111100000000000000000000000000000000;

	U64 EXP = *double & MASK_EXP;
	U64 MANT = *double & MASK_MANT;

	// Clear original F64 so that the masked values can be OR'd in
	*double = *double & MASK_SIGN;

	// Exponent of F64 is 11 bits instead of 8, shift mantissa by 3 and OR it back in
	MANT = MANT >> 3;
	*double = *double | MANT;

	// Shift exponent to regular int format
	// F32: [1 bit sign][8 bit exponent][23 bit mantissa]
	EXP = EXP >> 55; // 23 + 32 to get it in regular int format

	if (EXP != 0)
	{
		EXP += 896; // -127, +1023
		EXP = EXP << 52;
	}
	*double = *double | EXP;
}