/* Legacy math library. Is being replaced\, however it will remain 
until Rasterize.CC is ported over to the new math library. */


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

class CMat4
{
	F64 e[4][4];
};

CVec3 *Add3(CVec3 *a, CVec3 *b)
{
	CVec3 *c = MAlloc(sizeof(CVec3));
	c->x = a->x + b->x;
	c->y = a->y + b->y;
	c->z = a->z + b->z;
	return c;
}

CVec2 *Add2(CVec2 *a, CVec2 *b)
{
	CVec2 *c = MAlloc(sizeof(CVec2));
	c->x = a->x + b->x;
	c->y = a->y + b->y;
	return c;
}

CVec3 *Sub3(CVec3 *a, CVec3 *b)
{
	CVec3 *c = MAlloc(sizeof(CVec3));
	c->x = a->x - b->x;
	c->y = a->y - b->y;
	c->z = a->z - b->z;
	return c;
}

CVec2 *Sub2(CVec2 *a, CVec2 *b)
{
	CVec2 *c = MAlloc(sizeof(CVec2));
	c->x = a->x - b->x;
	c->y = a->y - b->y;
	return c;
}

CVec3 *Div3S(CVec3 *a, F64 b)
{
	CVec3 *c = MAlloc(sizeof(CVec3));
	c->x = a->x / b;
	c->y = a->y / b;
	c->z = a->z / b;
	return c;
}

CVec2 *Div2S(CVec2 *a, F64 b)
{
	CVec2 *c = MAlloc(sizeof(CVec2));
	c->x = a->x / b;
	c->y = a->y / b;
	return c;
}

CVec4 *Mul4S(CVec4 *a, F64 b)
{
	CVec4 *c = MAlloc(sizeof(CVec4));
	c->x = a->x * b;
	c->y = a->y * b;
	c->z = a->z * b;
	c->w = a->w * b;
	return c;
}

CVec3 *Mul3S(CVec3 *a, F64 b)
{
	CVec3 *c = MAlloc(sizeof(CVec3));
	c->x = a->x * b;
	c->y = a->y * b;
	c->z = a->z * b;
	return c;
}

CVec2 *Mul2S(CVec2 *a, F64 b)
{
	CVec2 *c = MAlloc(sizeof(CVec2));
	c->x = a->x * b;
	c->y = a->y * b;
	return c;
}

F64 Dot3(CVec3 *a, CVec3 *b)
{
	return (a->x * b->x) + (a->y * b->y) + (a->z * b->z); 
}

F64 Dot2(CVec2 *a, CVec2 *b)
{
	return (a->x * b->x) + (a->y * b->y);
}

CVec3 *Norm3(CVec3 *a)
{
	F64 length = Sqrt(Sqr(a->x) + Sqr(a->y) + Sqr(a->z));
	a->x /= length;
	a->y /= length;
	a->z /= length;
	return a;
}

CVec2 *Norm2(CVec2 *a)
{
	F64 length = Sqrt(Sqr(a->x) + Sqr(a->y));
	a->x /= length;
	a->y /= length;
	return a;
}

// Create direction Vec4 from Vec3
CVec4 *Vec4Dir(CVec3 *a)
{
	CVec4 *b = MAlloc(sizeof(CVec4));
	MemCopy(b, a, 24);
	b->w = 0;
	return b;
}

// Create position Vec4 from Vec3
CVec4 *Vec4Pos(CVec3 *a)
{
	CVec4 *b = MAlloc(sizeof(CVec4));
	MemCopy(b, a, 24);
	b->w = 1;
	return b;
}

// Create Vec3 from Vec4
CVec3 *Vec3Pos(CVec4 *a)
{
	CVec3 *b = MAlloc(sizeof(CVec3));
	MemCopy(b, a, 24);
	return b;
}

CVec4 *MulM44(CMat4 *a, CVec4 *b)
{
	CVec4 *c = MAlloc(sizeof(CVec4));
	c->x = (a->e[0][0] * b->x) + (a->e[0][1] * b->y) + (a->e[0][2] * b->z) + (a->e[0][3] * b->w);
	c->y = (a->e[1][0] * b->x) + (a->e[1][1] * b->y) + (a->e[1][2] * b->z) + (a->e[1][3] * b->w);
	c->z = (a->e[2][0] * b->x) + (a->e[2][1] * b->y) + (a->e[2][2] * b->z) + (a->e[2][3] * b->w);
	c->w = (a->e[3][0] * b->x) + (a->e[3][1] * b->y) + (a->e[3][2] * b->z) + (a->e[3][3] * b->w);
	return c; 
}

CMat4 *MulM4M4(CMat4 *a, CMat4 *b)
{
	CMat4 *c = MAlloc(sizeof(CMat4));
	c->e[0][0] = (a->e[0][0] * b->e[0][0])+(a->e[0][1] * b->e[1][0])+(a->e[0][2] * b->e[2][0])+(a->e[0][3] * b->e[3][0]);
	c->e[0][1] = (a->e[0][0] * b->e[0][1])+(a->e[0][1] * b->e[1][1])+(a->e[0][2] * b->e[2][1])+(a->e[0][3] * b->e[3][1]);
	c->e[0][2] = (a->e[0][0] * b->e[0][2])+(a->e[0][1] * b->e[1][2])+(a->e[0][2] * b->e[2][2])+(a->e[0][3] * b->e[3][2]);
	c->e[0][3] = (a->e[0][0] * b->e[0][3])+(a->e[0][1] * b->e[1][3])+(a->e[0][2] * b->e[2][3])+(a->e[0][3] * b->e[3][3]);

	c->e[1][0] = (a->e[1][0] * b->e[0][0])+(a->e[1][1] * b->e[1][0])+(a->e[1][2] * b->e[2][0])+(a->e[1][3] * b->e[3][0]);
	c->e[1][1] = (a->e[1][0] * b->e[0][1])+(a->e[1][1] * b->e[1][1])+(a->e[1][2] * b->e[2][1])+(a->e[1][3] * b->e[3][1]);
	c->e[1][2] = (a->e[1][0] * b->e[0][2])+(a->e[1][1] * b->e[1][2])+(a->e[1][2] * b->e[2][2])+(a->e[1][3] * b->e[3][2]);
	c->e[1][3] = (a->e[1][0] * b->e[0][3])+(a->e[1][1] * b->e[1][3])+(a->e[1][2] * b->e[2][3])+(a->e[1][3] * b->e[3][3]);

	c->e[2][0] = (a->e[2][0] * b->e[0][0])+(a->e[2][1] * b->e[1][0])+(a->e[2][2] * b->e[2][0])+(a->e[2][3] * b->e[3][0]);
	c->e[2][1] = (a->e[2][0] * b->e[0][1])+(a->e[2][1] * b->e[1][1])+(a->e[2][2] * b->e[2][1])+(a->e[2][3] * b->e[3][1]);
	c->e[2][2] = (a->e[2][0] * b->e[0][2])+(a->e[2][1] * b->e[1][2])+(a->e[2][2] * b->e[2][2])+(a->e[2][3] * b->e[3][2]);
	c->e[2][3] = (a->e[2][0] * b->e[0][3])+(a->e[2][1] * b->e[1][3])+(a->e[2][2] * b->e[2][3])+(a->e[2][3] * b->e[3][3]);

	c->e[3][0] = (a->e[3][0] * b->e[0][0])+(a->e[3][1] * b->e[1][0])+(a->e[3][2] * b->e[2][0])+(a->e[3][3] * b->e[3][0]);
	c->e[3][1] = (a->e[3][0] * b->e[0][1])+(a->e[3][1] * b->e[1][1])+(a->e[3][2] * b->e[2][1])+(a->e[3][3] * b->e[3][1]);
	c->e[3][2] = (a->e[3][0] * b->e[0][2])+(a->e[3][1] * b->e[1][2])+(a->e[3][2] * b->e[2][2])+(a->e[3][3] * b->e[3][2]);
	c->e[3][3] = (a->e[3][0] * b->e[0][3])+(a->e[3][1] * b->e[1][3])+(a->e[3][2] * b->e[2][3])+(a->e[3][3] * b->e[3][3]);
	return c;
}

// Normalized Vec4 to RGBA
U0 Vec4Col(CVec4 *col, CBGR24 *bgrcol)
{
	bgrcol->r = (col->x * 255.0);
	bgrcol->g = (col->y * 255.0);
	bgrcol->b = (col->z * 255.0);
	bgrcol->pad = (col->w * 255.0);
}

// Normalized Vec3 to RGBA
U0 Vec3Col(CVec3 *col, CBGR24 *bgrcol)
{
	bgrcol->r = (col->x * 255.0);
	bgrcol->g = (col->y * 255.0);
	bgrcol->b = (col->z * 255.0);
	bgrcol->pad = 255.0;
}

U0 Barycentric2(CVec2 *p, CVec2 *a, CVec2 *b, CVec2 *c, F64 *u, F64 *v, F64 *w)
{
	CVec2 *v0 = Sub2(b, a);
	CVec2 *v1 = Sub2(c, a);
	CVec2 *v2 = Sub2(p, a);
	
	F64 d00 = Dot2(v0, v0);	
	F64 d01 = Dot2(v0, v1);
	F64 d11 = Dot2(v1, v1);
	F64 d20 = Dot2(v2, v0);
	F64 d21 = Dot2(v2, v1);
	F64 denom = d00 * d11 - d01 * d01;
	*v = (d11 * d20 - d01 * d21)/denom;
	*w = (d00 * d21 - d01 * d20)/denom;
	*u = 1.0 - *v - *w;

	Free(v0);
	Free(v1);
	Free(v2);
}

CVec2 Ayy,Bee,Cee, P;
Ayy.x = 0;
Ayy.y = 0;
Bee.x = 3;
Bee.y = 0;
Cee.x = 0;
Cee.y = 3;

U0 SetTranslateM4(CMat4 *mat, CVec3 *translation)
{
	MemSet(mat, 0, sizeof(CMat4));
	mat->e[0][0] = 1;
	mat->e[1][1] = 1;
	mat->e[2][2] = 1;
	mat->e[3][3] = 1;
	mat->e[0][3] = translation->x;
	mat->e[1][3] = translation->y;
	mat->e[2][3] = translation->z;
}

U0 SetScaleM4(CMat4 *mat, CVec3 *scale) 
{
	MemSet(mat, 0, sizeof(CMat4));
	mat->e[0][0] = scale->x;
	mat->e[1][1] = scale->y;
	mat->e[2][2] = scale->z;
	mat->e[3][3] = 1;
}

U0 SetRotXM4(CMat4 *mat, F64 rot)
{
	MemSet(mat, 0, sizeof(CMat4));
	mat->e[0][0] = 1;
	mat->e[3][3] = 1;
	F64 x = Cos(rot);
	F64 y = Sin(rot);
	mat->e[1][1] = x;
	mat->e[1][2] = -y;
	mat->e[2][1] = y;
	mat->e[2][2] = x;
}

U0 SetRotYM4(CMat4 *mat, F64 rot)
{
	MemSet(mat, 0, sizeof(CMat4));
	mat->e[1][1] = 1;
	mat->e[3][3] = 1;
	F64 x = Cos(rot);
	F64 y = Sin(rot);
	mat->e[0][0] = x;
	mat->e[0][2] = y;
	mat->e[2][0] = -y;
	mat->e[2][2] = x;
}

U0 SetRotZM4(CMat4 *mat, F64 rot)
{
	MemSet(mat, 0, sizeof(CMat4));
	mat->e[2][2] = 1;
	mat->e[3][3] = 1;
	F64 x = Cos(rot);
	F64 y = Sin(rot);
	mat->e[0][0] = x;
	mat->e[0][1] = -y;
	mat->e[1][0] = y;
	mat->e[1][1] = x;
}

U0 TranslateM4(CMat4 *mat, CVec3 *translation)
{
	// Generate CMat4 translation matrix
	CMat4 *translateMat = MAlloc(sizeof(CMat4));
	SetTranslateM4(translateMat, translation);

	
	CMat4 *finalMat = MulM4M4(mat, translateMat);
	MemCopy(mat, finalMat, sizeof(CMat4));
	Free(finalMat);
	Free(translateMat);
}

U0 F32toF64(U32 *float, U64 *double)
{
	MemCopy(&double->u32[1], float, 4);

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

























