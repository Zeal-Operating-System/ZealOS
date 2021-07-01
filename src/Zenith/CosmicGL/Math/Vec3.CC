
asm
{
_VEC3::
	PUSH		RBP
	MOV			RBP, RSP

	MOV			RAX, SF_ARG4[RBP]	// = *dest

//	CVTSD2SS	XMM0, SF_ARG1[RBP]
	DU8			0xF2, 0x0F, 0x5A, 0x45, 0x10;
//	MOVSS		[RAX], XMM0
	DU8			0xF3, 0x0F, 0x11, 0x00;

//	CVTSD2SS	XMM0, SF_ARG1[RBP]
	DU8			0xF2, 0x0F, 0x5A, 0x45, 0x18;
//	MOVSS		4[RAX], XMM0
	DU8			0xF3, 0x0F, 0x11, 0x40, 0x04;

//	CVTSD2SS	XMM0, SF_ARG1[RBP]
	DU8			0xF2, 0x0F, 0x5A, 0x45, 0x20;
//	MOVSS		8[RAX], XMM0
	DU8			0xF3, 0x0F, 0x11, 0x40, 0x08;

	POP			RBP
	RET1		32
}
/**
	@ingroup gfxmath
	@brief Initialize members of a vector with double-precision floats.

	@param[in]     x	X component.
	@param[in]     y	Y component.
	@param[in]     z	Z component.
	@param[in,out] dest	Destination
*/
_extern _VEC3 U0 Vec3(F64 x, F64 y, F64 z, CVec3 *dest);

asm
{
_VEC3_PRINT::
	PUSH		RBP
	MOV			RBP, RSP

	MOV			RAX, SF_ARG1[RBP]	// = *v
	SUB			RSP, 24

//	CVTSS2SD	XMM0, 8[RAX]						// (F64) v->z
	DU8			0xF3, 0x0F, 0x5A, 0x40, 0x08;
//	MOVSD		16[RSP], XMM0						// Push v->z
	DU8			0xF2, 0x0F, 0x11, 0x44, 0x24, 0x10;

//	CVTSS2SD	XMM0, 4[RAX]						// (F64) v->y
	DU8			0xF3, 0x0F, 0x5A, 0x40, 0x04;
//	MOVSD		8[RSP], XMM0						// Push v->y
	DU8			0xF2, 0x0F, 0x11, 0x44, 0x24, 0x08;

//	CVTSS2SD	XMM0, [RAX]							// (F64) v->x
	DU8			0xF3, 0x0f, 0x5A, 0x00;
//	MOVSD		[RSP], XMM0							// Push v->x
	DU8			0xF2, 0x0F, 0x11, 0x04, 0x24;

	PUSH		3									// # of varargs
	PUSH		"X: %n | Y: %n | Z: %n\n"
	CALL		&Print
	ADD			RSP, 40

	POP			RBP
	RET1		8
}
/**
	@ingroup gfxmath
	@brief Print members of a vector.

	@param[in] v	Vector
*/
_extern _VEC3_PRINT U0 Vec3Print(CVec3 *v);

/**
	@ingroup gfxmath
	@brief Copy all members of a vector to destination.

	@param[in]     src	Source
	@param[in,out] dest	Destination 
*/
_extern _VEC4_COPY U0 Vec3Copy(CVec3 *src, CVec3 *dest);

asm
{
_VEC3_IS_EQUAL::
	PUSH		RBP
	MOV			RBP, RSP

	MOV			RAX, SF_ARG1[RBP]	// = *a
//	MOVAPS		XMM0, [RAX]
	DU8			0x0F, 0x28, 0x00;
	MOV			RAX, SF_ARG2[RBP]	// = *b
//	MOVAPS		XMM1, [RAX]
	DU8			0x0F, 0x28, 0x08;
//	CMPPS		XMM0, XMM1, 0		// CMPEQPS
	DU8			0x0F, 0xC2, 0xC1, 0x00;

//	PMOVMSKB	RAX, XMM0
	DU8			0x66, 0x0F, 0xD7, 0xC0;
	AND			RAX, 0xFFF
	CMP			RAX, 0xFFF
	JNZ			_is_not_equal
	MOV			RAX, 1
	JMP			_return
_is_not_equal:
	MOV			RAX, 0

_return:
	POP		RBP
	RET1	16
}
/**
	@ingroup gfxmath
	@brief Checks if two vectors are equal.

	@param[in] a	Vector 1
	@param[in] b	Vector 2
*/
_extern _VEC3_IS_EQUAL Bool Vec3IsEqual(CVec3 *a, CVec3 *b);

/**
	@ingroup gfxmath
	@brief Sum of two vectors.

	@param[in]     a	Vector 1
	@param[in]     b	Vector 2
	@param[in,out] dest	Destination
*/
_extern _VEC4_ADD U0 Vec3Add(CVec3 *a, CVec3 *b, CVec3 *dest);

/**
	@ingroup gfxmath
	@brief Add a scalar to a vector.

	@param[in]     v	Vector
	@param[in]     s	Scalar
	@param[in,out] dest	Destination
*/
_extern _VEC4_ADDS U0 Vec3AddS(CVec3 *v, I32 *s, CVec3 *dest);

/**
	@ingroup gfxmath
	@brief Difference of two vectors.

	@param[in]     a	Vector 1
	@param[in]     b	Vector 2
	@param[in,out] dest	Destination
*/
_extern _VEC4_SUB U0 Vec3Sub(CVec3 *a, CVec3 *b, CVec3 *dest);

/**
	@ingroup gfxmath
	@brief Subtract a scalar from a vector.

	@param[in]     v	Vector
	@param[in]     s	Scalar
	@param[in,out] dest	Destination
*/
_extern _VEC4_SUBS U0 Vec3SubS(CVec3 *v, I32 *s, CVec3 *dest);

/**
	@ingroup gfxmath
	@brief Product  of two vectors (element multiplication).

	@param[in]     a	Vector 1
	@param[in]     b	Vector 2
	@param[in,out] dest	Destination
*/
_extern _VEC4_MUL U0 Vec3Mul(CVec3 *a, CVec3 *b, CVec3 *dest);

/**
	@ingroup gfxmath
	@brief Scale a vector by a scalar.

	@param[in]     v	Vector
	@param[in]     s	Scalar
	@param[in,out] dest	Destination
*/
_extern _VEC4_MULS U0 Vec3MulS(CVec3 *v, I32 *s, CVec3 *dest);

/**
	@ingroup gfxmath
	@brief Quotient of two vectors.

	@param[in]     a	Vector 1
	@param[in]     b	Vector 2
	@param[in,out] dest	Destination
*/
_extern _VEC4_DIV U0 Vec3Div(CVec3 *a, CVec3 *b, CVec3 *dest);

/**
	@ingroup gfxmath
	@brief Divide a vector by a scalar.

	@param[in]     v	Vector
	@param[in]     s	Scalar
	@param[in,out] dest	Destination
*/
_extern _VEC4_DIVS U0 Vec3DivS(CVec3 *v, I32 *s, CVec3 *dest);












