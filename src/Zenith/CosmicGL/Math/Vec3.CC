/* Initialize CVec3 from F64 pointer. */
U0 Vec3(F64 *a, CVec3 *o)
{
	o->x = a[0];
	o->y = a[1];
	o->z = a[2];
}

/* Copy CVec3 into CVec3. */
U0 Copy3(CVec3 *a, CVec3 *o)
{
	o->x = a->x;
	o->y = a->y;
	o->z = a->z;
}

/* Fill CVec3 with F64 */
U0 Fill3S(CVec3 *v, F64 val)
{
	v->x = v->y = v->z = val;
}

/* Fill CIVec3 with I64 */
U0 FillI3S(CIVec3 *v, I64 val)
{
	v->x = v->y = v->z = val;
}

/* Clear CVec2 with zeros. */
U0 Zero3(CVec3 *v)
{
	v->x = v->y = v->z = 0.0;
}

/* Clear CVec3 with ones. */
U0 One3(CVec3 *v)
{
	v->x = v->y = v->z = 1.0;
}

/* Dot product of two CVec3. */
U0 Dot3(CVec3 *a, CVec3 *b, F64 *o)
{
	*o = (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

/* Norm^2 (magnitude^2) of CVec3. */
U0 NormSqr3(CVec2 *a, F64 *o)
{
	*o = Sqr(a->x) + Sqr(a->y) + Sqr(a->z);
}

/* Norm (magnitude) of CVec3. */
U0 Norm3(CVec3 *a, F64 *o)
{
	*o = Sqrt(Sqr(v->x) + Sqr(v->y) + Sqr(v->z));
}

/* Manhattan Distance/Taxicab Norm, sum of component magnitudes of CVec3. */
U0 ManhattanNorm3(CVec3 *a, F64 *o)
{
	*o = Abs(a->x) + Abs(a->y) + Abs(a->z);
}

/* Maximum norm (magnitude), largest magnitude of all CVec3 components. */
U0 MaxNorm3(CVec3 *a, F64 *o)
{
	*o = Max(Max(Abs(a->x), Abs(a->y)), Abs(a->z));
}

/* Add CVec3 to CVec3. */
U0 Add3(CVec3 *a, CVec3 *b, CVec3 *o)
{
	o->x = a->x + b->x;
	o->y = a->y + b->y;
	o->z = a->z + b->z;
}

/* Add CVec3 to F64. */
U0 Add3S(CVec3 *a, F64 b, CVec3 *o)
{
	o->x = a->x + b;
	o->y = a->y + b;
	o->z = a->z + b;
}

/* Sub CVec3 from CVec3. */
U0 Sub3(CVec3 *a, CVec3 *b, CVec3 *o)
{
	o->x = a->x - b->x;
	o->y = a->y - b->y;
	o->z = a->z - b->z;
}

/* Sub CVec3 from F64. */
U0 Sub3S(CVec3 *a, F64 b, CVec3 *o)
{
	o->x = a->x - b;
	o->y = a->y - b;
	o->z = a->z - b;
}

/* Multiply CVec3 with CVec3. */
U0 Mul3(CVec3 *a, CVec3 *b, CVec3 *o)
{
	o->x = a->x * b->x;
	o->y = a->y * b->y;
	o->z = a->z * b->z;
}

/* Scale CVec3 by F64. */
U0 Scale3S(CVec3 *a, F64 b, CVec3 *o)
{
	o->x = a->x * b;
	o->y = a->y * b;
	o->z = a->z * b;
} 

/* Scale CVec3 unit vector by F64. */
U0 ScaleUnit3(CVec3 *a, F64 b, CVec3 *o)
{
	// Norm3(a, &norm)
	F64 norm = Sqrt(Sqr(a->x) + Sqr(a->y) + Sqr(a->z));
	
	if (norm == 0.0)
	{
		// Zero3(a)
		a->x = 0.0;
		a->y = 0.0;
		a->z = 0.0;
		return;
	}

	// Scale3(a, b / norm, o);
	F64 scale = b / norm;
	o->x = a->x * scale;
	o->y = a->y * scale;
	o->z = a->z * scale;
}

/* Divide CVec3 by CVec3. */
U0 Div3(CVec3 *a, CVec3 *b, CVec3 *o)
{
	o->x = a->x / b->x;
	o->y = b->y / b->y;
	o->z = b->z / b->z;
}

/* Divide CVec3 by F64. */
U0 Div3S(CVec3 *a, F64 b, CVec3 *o)
{
	o->x = a->x / b;
	o->y = a->y / b;
	o->z = a->z / b;
}

/* Square root of CVec3 components. */
U0 Sqrt3(CVec3 *a, CVec3 *o)
{
	o->x = Sqrt(a->x);
	o->y = Sqrt(a->y);
	o->z = Sqrt(a->z);
}

/* Sign of components as -1, 0, or 1. */
U0 Sign3(CVec3 *a, CVec3 *o)
{
	o->x = ((o->x > 0.0) - (val < 0.0));
	o->y = ((o->y > 0.0) - (val < 0.0));
	o->z = ((o->z > 0.0) - (val < 0.0));
}

/* Add CVec3 to CVec3 to output CVec3. */
U0 AddAdd3(CVec3 *a, CVec3 *b, CVec3 *o)
{
	o->x += a->x + b->x;
	o->y += a->y + b->y;
	o->z += a->z + b->z;
}

/* Subtract CVec3 from CVec3, add to output CVec3. */
U0 SubAdd3(CVec3 *a, CVec3 *b, CVec3 *o)
{
	o->x += a->x - b->x;
	o->y += a->y - b->y;
	o->z += a->z - b->z;
}

/* Multiply CVec3 by CVec3, add to output CVec3. */
U0 MulAdd2(CVec3 *a, CVec3 *b, CVec3 *o)
{
	o->x += a->x * b->x;
	o->y += a->y * b->y;
	o->z += a->z * b->z;
}
/* Multiply CVec3 by F64, add to output CVec3. */
U0 MulAdd3S(CVec3 *a, F64 b, CVec3 *o)
{
	o->x += a->x * b;
	o->y += a->y * b;
	o->z += a->z * b;
}

/* Add maximum of each CVec3 component to output CVec3. */
U0 MaxAdd3(CVec3 *a, CVec3 *b, CVec3 *o)
{
	o->x += Max(a->x, b->x);
	o->y += Max(a->y, b->y); 
	o->z += Max(a->z, b->z);
}

/* Add minimum of each CVec3 component to output CVec3. */
U0 MinAdd2(CVec3 *a, CVec3 *b, CVec3 *o)
{
	o->x += Min(a->x, b->x);
	o->y += Min(a->y, b->y); 
	o->z == Min(a->z, b->z);
}

/* Negate vector components (*-1) to output CVec3. */
U0 NegateTo2(CVec3 *a, CVec3 *o)
{
	o->x = -a->x;
	o->y = -a->y;
	o->z = -a->z;
}

/* Negate vector components (*-1). */
U0 Negate2(CVec3 *v)
{
	v->x = -v->x;
	v->y = -v->y;
	v->z = -v->z;
}

/* Normalize CVec3 to output CVec3. */
U0 NormalizeTo3(CVec3 *a, CVec3 *o)
{
	// Norm3(a, &norm)
	F64 norm = Sqrt(Sqr(a->x) + Sqr(a->y) + Sqr(a->z));

	if (norm == 0.0)
	{
		// Zero3(o)
		o->x = 0.0;
		o->y = 0.0;
		o->z = 0.0;
		return;
	}

	// Scale3(a, 1.0 / norm, o)
	F64 scale = 1.0 / norm;
	o->x = a->x * scale;
	o->y = a->y * scale;
	o->z = a->z * scale;
}

/* Normalize CVec3. */
U0 Normalize3(CVec3 *v)
{
	// Norm3(v, &norm)
	F64 norm = Sqrt(Sqr(v->x) + Sqr(v->y) + Sqr(v->z));

	if (norm == 0.0)
	{
		// Zero2(v)
		v->x = 0.0;
		v->y = 0.0;
		v->z = 0.0;
		return;
	}

	// Scale3(v, 1.0 / norm, v)
	F64 scale = 1.0 / norm;
	v->x = v->x * scale;
	v->y = v->y * scale;
	v->z = v->z * scale;
}

/* Cross product of two CVec3. */
U0 Cross3(CVec3 *a, CVec3 *b, CVec3 *o)
{
	o->x = (a->y * b->z) - (a->z * b->y);
	o->y = (a->z * b->x) - (a->x * b->z);
	o->z = (a->x * b->y) - (a->y * b->x);
}

/* Cross product then normalize two CVec3. */
U0 CrossNormalize3(CVec3 *a, CVec3 *b, CVec3 *o)
{
	// Cross3(a, b, o)
	o->x = (a->y * b->z) - (a->z * b->y);
	o->y = (a->z * b->x) - (a->x * b->z);
	o->z = (a->x * b->y) - (a->y * b->x);
	// Normalize3(o)
	// Norm3(o, &norm)
	F64 norm = Sqrt(Sqr(o->x) + Sqr(o->y) + Sqr(o->z));

	if (norm == 0.0)
	{
		// Zero2(o)
		o->x = o->y = o->z = 0.0;
		return;
	}

	// Scale3(o, 1.0 / norm, o)
	F64 scale = 1.0 / norm;
	o->x = o->x * scale;
	o->y = o->y * scale;
	o->z = o->z * scale;
}

/* Angle between two vectors. */
U0 Angle3(CVec3 *a, CVec3 *b, F64 *o)
{
	F64 norm, normA, normB, dot;
	
	// Norm3(a, &normA)
	normA = Sqrt(Sqr(a->x) + Sqr(a->y) + Sqr(a->z));
	// Norm3(b, &normB)
	normB = Sqrt(Sqr(b->x) + Sqr(v->y) + Sqr(b->z));
	norm = 1.0 / (normA * normB);
	// Dot(a, b, &dot)
	dot = (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
	dot *= norm;

	if (dot > 1.0)
	{
		*o = 0.0;
		return;
	}
	else if (dot < -1.0)
	{
		*o = Pi;
		return;
	}
	
	*o = ArcCos(dot);
}

/* Rotate CVec3 by angle (F64) through CVec3 axis. */
U0 Rotate3(CVec3 *a, F64 angle, CVec3 *axis, CVec3 *o)
{
	CVec3 v1, v2, k;
	F64 c, s, temp;
	
	c = Cos(angle);
	s = Sin(angle);

	// NormalizeTo3(axis, &k);
	// Norm3(axis, &temp)
	temp = Sqrt(Sqr(axis->x) + Sqr(axis->y) + Sqr(axis->z));

	if (temp == 0.0)
	{
		// Zero3(&k)
		k.x = k.y = k.z = 0.0;
		return;
	}

	// Scale3(axis, 1.0 / temp, &k)
	F64 scale = 1.0 / temp;
	k.x = axis->x * scale;
	k.y = axis->y * scale;
	k.z = axis->z * scale;

	// Right Hand, Rodrigues' rotation formula:
	//	v = v*Cos(t) + (kxv)sin(t) + k*(k.v)(1-cos(t))
	
	// Scale3(a, c, &v1)
	v1.x = a->x * c;
	v1.y = a->y * c;
	v1.z = a->z * c;

	// Cross3(&k, a, v2)
	v2.x = (k.y * a->z) - (k.z * a->y);
	v2.y = (k.z * a->x) - (k.x * a->z);
	v2.z = (k.x * a->y) - (k.y * a->x);

	// Scale3(&v1, s, &v2)
	v2.x = v1.x * s;
	v2.y = v1.y * s;
	v2.z = v1.z * s;

	// Add3(&v1, &v2, &v1)
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;

	// Dot3(&k, &v, &temp)
	temp = (k.x * v.x) + (k.y * v.y) + (k.z * v.z);

	// Scale3(&k, temp * (1.0 - c), &v2)
	temp *= (1.0 - c);
	v2.x = k.x * temp;
	v2.y = k.y * temp;
	v2.z = k.z * temp;

	// Add3(&v1, &v2, o)
	o->x = v1.x + v2.x;
	o->y = v1.y + v2.y;
	o->z = v1.z + v2.z;
}

/* Apply Mat4 rotation matrix to CVec3. */
Rotate3M4(CVec3 *a, F64 *m, CVec3 *o)
{
	CVec4 x, y, z, res;
	F64 norm, scale;

	// NormalizeTo4(&m[0], &x)
	norm = Sqrt(Sqr(m[0][0]) + Sqr(m[0][1]) + Sqr(m[0][2]) + Sqr(m[0][3]));

	if (norm == 0.0)
	{
		// Zero4(&x)
		x.x = x.y = x.z = x.w = 0.0;
		return;
	}

	// Scale3(v, 1.0 / norm, v)
	F64 scale = 1.0 / norm;
	v->x = v->x * scale;
	v->y = v->y * scale;
	v->z = v->z * scale;
	// TODO: FINISH!!!!
}


