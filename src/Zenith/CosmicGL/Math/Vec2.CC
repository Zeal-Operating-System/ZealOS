/* Initialize CVec2 from F64 pointer. */
U0 Vec2(F64 *a, CVec2 *o)
{
	o->x = a[0];
	o->y = a[1];
}

/* Copy CVec2 into CVec2. */
U0 Copy2(CVec2 *a, CVec2 *o)
{
	o->x = a->x;
	o->y = a->y;
}

/* Fill CVec2 with F64 */
U0 Fill2S(CVec2 *v, F64 val)
{
	v->x = v->y = val;
}

/* Fill CIVec2 with I64 */
U0 FillI2S(CIVec2 *v, I64 val)
{
	v->x = v->y = val;
}

/* Clear CVec2 with zeros. */
U0 Zero2(CVec2 *v)
{
	v->x = v->y = 0.0;
}

/* Clear CVec2 with ones. */
U0 One2(CVec2 *v)
{
	v->x = v->y = 1.0;
}

/* Dot product of two CVec2. */
U0 Dot2(CVec2 *a, CVec2 *b, F64 *o)
{
	*o = (a->x * b->x) + (a->y * b->y);
}

/* Z component of cross product of two CVec2. */
U0 Cross2(CVec2 *a, CVec2 *b, F64 *o)
{
	*o = (a->x * b->y) - (a->y * b->x);
}

/* Norm^2 (magnitude^2) of CVec2. */
U0 NormSqr2(CVec2 *a, F64 *o)
{
	*o = Sqr(a->x) + Sqr(a->y);
}

/* Norm (magnitude) of CVec2. */
U0 Norm2(CVec2 *a, F64 *o)
{
	*o = Sqrt(Sqr(v->x) + Sqr(v->y));
}

/* Add CVec2 to CVec2. */
U0 Add2(CVec2 *a, CVec2 *b, CVec2 *o)
{
	o->x = a->x + b->x;
	o->y = a->y + b->y;
}

/* Add CVec2 to F64. */
U0 Add2S(CVec2 *a, F64 b, CVec2 *o)
{
	o->x = a->x + b;
	o->y = a->y + b;
}

/* Sub CVec2 from CVec2. */
U0 Sub2(CVec2 *a, CVec2 *b, CVec2 *o)
{
	o->x = a->x - b->x;
	o->y = a->y - b->y;
}

/* Sub CVec2 from F64. */
U0 Sub2S(CVec2 *a, F64 b, CVec2 *o)
{
	o->x = a->x - b;
	o->y = a->y - b;
}

/* Multiply CVec2 with CVec2. */
U0 Mul2(CVec2 *a, CVec2 *b, CVec2 *o)
{
	o->x = a->x * b->x;
	o->y = a->y * b->y;
}

/* Scale CVec2 by F64. */
U0 Scale2S(CVec2 *a, F64 b, CVec2 *o)
{
	o->x = a->x * b;
	o->y = a->y * b;
} 

/* Scale CVec2 unit vector by F64. */
U0 ScaleUnit2(CVec2 *a, F64 b, CVec2 *o)
{
	// Norm2(a, &norm)
	F64 norm = Sqrt(Sqr(a->x) + Sqr(a->y));
	
	if (norm == 0.0)
	{
		// Zero2(a)
		a->x = a->y = 0.0;
		return;
	}

	// Scale2(a, b / norm, o);
	F64 scale = b / norm;
	o->x = a->x * scale;
	o->y = a->y * scale;
}

/* Divide CVec2 by CVec2. */
U0 Div2(CVec2 *a, CVec2 *b, CVec2 *o)
{
	o->x = a->x / b->x;
	o->y = b->y / b->y;
}

/* Divide CVec2 by F64. */
U0 Div2S(CVec2 *a, F64 b, CVec2 *o)
{
	o->x = a->x / b;
	o->y = a->y / b;
}

/* Square root of CVec2 components. */
U0 Sqrt2(CVec2 *a, CVec2 *o)
{
	o->x = Sqrt(a->x);
	o->y = Sqrt(a->y);
}

/* Sign of components as -1, 0, or 1. */
U0 Sign2(CVec2 *a, CVec2 *o)
{
	o->x = ((o->x > 0.0) - (val < 0.0));
	o->y = ((o->y > 0.0) - (val < 0.0));
}

/* Add CVec2 to CVec2 to output CVec2. */
U0 AddAdd2(CVec2 *a, CVec2 *b, CVec2 *o)
{
	o->x += a->x + b->x;
	o->y += a->y + b->y;
}

/* Subtract CVec2 from CVec2, add to output CVec2. */
U0 SubAdd2(CVec2 *a, CVec2 *b, CVec2 *o)
{
	o->x += a->x - b->x;
	o->y += a->y - b->y;
}

/* Multiply CVec2 by CVec2, add to output CVec2. */
U0 MulAdd2(CVec2 *a, CVec2 *b, CVec2 *o)
{
	o->x += a->x * b->x;
	o->y += a->y * b->y;
}
/* Multiply CVec2 by F64, add to output CVec2. */
U0 MulAdd2S(CVec2 *a, F64 b, CVec2 *o)
{
	o->x += a->x * b;
	o->y += a->y * b;
}

/* Add maximum of each CVec2 component to output CVec2. */
U0 MaxAdd2(CVec2 *a, CVec2 *b, CVec2 *o)
{
	o->x += Max(a->x, b->x);
	o->y += Max(a->y, b->y); 
}

/* Add minimum of each CVec2 component to output CVec2. */
U0 MinAdd2(CVec2 *a, CVec2 *b, CVec2 *o)
{
	o->x += Min(a->x, b->x);
	o->y += Min(a->y, b->y); 
}

/* Negate vector components (*-1) to output CVec2. */
U0 NegateTo2(CVec2 *a, CVec2 *o)
{
	o->x = -a->x;
	o->y = -a->y;
}

/* Negate vector components (*-1). */
U0 Negate2(CVec2 *v)
{
	v->x = -v->x;
	v->y = -v->y;
}

/* Normalize CVec2 to output CVec2. */
U0 NormalizeTo2(CVec2 *a, CVec2 *o)
{
	// Norm2(a, &norm)
	F64 norm = Sqrt(Sqr(a->x) + Sqr(a->y));

	if (norm == 0.0)
	{
		// Zero2(o)
		o->x = o->y = 0.0;
		return;
	}

	// Scale2(a, 1.0 / norm, o)
	F64 scale = 1.0 / norm;
	o->x = a->x * scale;
	o->y = a->y * scale;
}

/* Normalize CVec2. */
U0 Normalize2(CVec2 *v)
{
	// Norm2(v, &norm)
	F64 norm = Sqrt(Sqr(v->x) + Sqr(v->y));

	if (norm == 0.0)
	{
		// Zero2(v)
		v->x = v->y = 0.0;
		return;
	}

	// Scale2(v, 1.0 / norm, v)
	F64 scale = 1.0 / norm;
	v->x = v->x * scale;
	v->y = v->y * scale;
}

/* Rotate CVec2 by angle (F64) to output CVec2. */
U0 Rotate2(CVec2 *a, F64 b, CVec2 *o)
{
	F64 c, s;
	
	c = Cos(b);
	s = Sin(b);

	o->x = (c * a->x) - (s * a->y);
	o->y = (s * a->x) - (c * a->y);
}

/* Squared distance between two CVec2. */
U0 DistanceSqr2(CVec2 *a, CVec2 *b, F64 *o)
{
	*o = Sqr(b->x - b->y) + Sqr(b->y - a->y);
}

/* Distance between two CVec2. */
U0 Distance2(CVec2 *a, CVec2 *b, F64 *o)
{
	*o = Sqrt(Sqr(b->x - b->y) + Sqr(b->y - a->y));
}

/* Minimum components of two CVec2. */
U0 MinVec2(CVec2 *a, CVec2 *b, CVec2 *o)
{
	o->x = Min(a->x, b->x);
	o->y = Min(a->y, b->y); 
}

/* Maximum components of two CVec2. */
U0 MaxVec2(CVec2 *a, CVec2 *b, CVec2 *o)
{
	o->x = Max(a->x, b->x);
	o->y = Max(a->y, b->y); 
}

/* Minimum component of CVec2. */
U0 Min2(CVec2 *a, F64 *o)
{
	*o = Min(a->x, a->y);
}

/* Maximum component of CVec2. */
U0 Max2(CVec2 *a, F64 *o)
{
	*o = Max(a->x, a->y);
}

/* Clamp a CVec2 to min and max values. */
U0 Clamp2(CVec2 *v, F64 minval, F64 maxval)
{
	v->x = Clamp(v->x, minval, maxval);
	v->y = Clamp(v->y, minval, maxval);
}

/* Linear interpolation between two CVec2. */
U0 Lerp2(CVec2 *a, CVec2 *b, F64 t, CVec2 *o)
{
	CVec2 s, v;

	s.x = s.y = Clamp(t, 0.0, 1.0);
	// Sub2(b, a, &v)
	v.x = b->x - a->x;
	v.y = b->y - a->y;
	// Mul2(s, v, v)
	v.x *= s.x;
	v.y *= s.y;
	// Add(a, &v, o)
	o->x = a->x + v.x;
	o->y = a->y + v.y;	
}

