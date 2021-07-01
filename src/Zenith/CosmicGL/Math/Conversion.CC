asm
{
_DOUBLE_TO_SINGLE::
	PUSH		RBP
	MOV			RBP, RSP

//	

	POP			RBP
	RET1		8
}
/**
	@ingroup gfxmath
	@brief Convert double-precision scalar to single-precision.

	@param[in] d	Double-precision scalar.
	@return			Single-precision scalar.
*/
_extern _DOUBLE_TO_SINGLE I32 DoubleToSingle(F64 d);