#define INTERNAL_TYPES_NUM	17

class CInternalType
{
	U8 type, size, name[8];
} internal_types_table[INTERNAL_TYPES_NUM] = {
	{RT_I0,  0, "I0i"},
	{RT_I0,  0, "I0"},
	{RT_U0,  0, "U0i"},
	{RT_U0,  0, "U0"},
	{RT_I8,  1, "I8i"},
	{RT_I8,  1, "I8"},
	{RT_I8,  1, "Bool"},
	{RT_U8,  1, "U8i"},
	{RT_U8,  1, "U8"},
	{RT_I16, 2, "I16i"},
	{RT_U16, 2, "U16i"},
	{RT_I32, 4, "I32i"},
	{RT_U32, 4, "U32i"},
	{RT_I64, 8, "I64i"},
	{RT_U64, 8, "U64i"},
	{RT_F64, 8, "F64i"},
	{RT_F64, 8, "F64"},
};

CIntermediateStruct intermediate_code_table[IC_ICS_NUM] = {
	{IS_0_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "END"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "NOP1"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "END_EXP"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "NOP2"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "LABEL"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "CALL_START"},
	{IS_0_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "CALL_END"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "CALL_END2"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "RETURN_VAL"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "RETURN_VAL2"},
	{IS_0_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "IMM_I64"},
	{IS_0_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "IMM_F64"},
	{IS_0_ARG, 1, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "STR_CONST"},
	{IS_0_ARG, 1, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "ABS_ADDR"},
	{IS_0_ARG, 1, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "ADDR_IMPORT"},
	{IS_0_ARG, 1, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "HEAP_GLOBAL"},
	{IS_0_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "SIZEOF"},
	{IS_0_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "TYPE"},
	{IS_0_ARG, 1, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "GET_LABEL"},
	{IS_0_ARG, 1, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "RBP"},
	{IS_0_ARG, 1, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "REG"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "FS"},
	{IS_0_ARG, 1, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "MOV_FS"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "GS"},
	{IS_0_ARG, 1, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "MOV_GS"},
	{IS_0_ARG, 1, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "LEA"},
	{IS_0_ARG, 1, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "MOV"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "TO_I64"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "TO_F64"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "TO_BOOL"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "TOUPPER"},
	{IS_1_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "POSTFIX_TYPECAST"},
	{IS_1_ARG, 1, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "ADDR"},
	{IS_1_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "COM"},
	{IS_1_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "NOT"},
	{IS_1_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "UNARY_MINUS"},
	{IS_1_ARG, 1, IST_DEREF,	FALSE,	TRUE,	0, 0, 0, "DEREF"},
	{IS_1_ARG, 1, IST_DEREF,	FALSE,	TRUE,	0, 0, 0, "DEREF_PP"},
	{IS_1_ARG, 1, IST_DEREF,	FALSE,	TRUE,	0, 0, 0, "DEREF_MM"},
	{IS_1_ARG, 1, IST_DEREF,	TRUE,	TRUE,	0, 0, 0, "_PP"},
	{IS_1_ARG, 1, IST_DEREF,	TRUE,	TRUE,	0, 0, 0, "_MM"},
	{IS_1_ARG, 1, IST_DEREF,	TRUE,	TRUE,	0, 0, 0, "PP_"},
	{IS_1_ARG, 1, IST_DEREF,	TRUE,	TRUE,	0, 0, 0, "MM_"},
	{IS_2_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "SHL"},
	{IS_2_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "SHR"},
	{IS_1_ARG, 1, IST_ASSIGN,	FALSE,	FALSE,	0, 0, 0, "SHL_CONST"},
	{IS_1_ARG, 1, IST_ASSIGN,	FALSE,	FALSE,	0, 0, 0, "SHR_CONST"},
	{IS_2_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "POWER"},
	{IS_2_ARG, 1, IST_NULL,		TRUE,	FALSE,	0, 0, 0, "MUL"},
	{IS_2_ARG, 1, IST_NULL,		TRUE,	FALSE,	0, 0, 0, "DIV"},
	{IS_2_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "MOD"},
	{IS_2_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "AND"},
	{IS_2_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "OR"},
	{IS_2_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "XOR"},
	{IS_2_ARG, 1, IST_NULL,		TRUE,	FALSE,	0, 0, 0, "ADD"},
	{IS_2_ARG, 1, IST_NULL,		TRUE,	FALSE,	0, 0, 0, "SUB"},
	{IS_1_ARG, 1, IST_ASSIGN,	FALSE,	FALSE,	0, 0, 0, "ADD_CONST"},
	{IS_1_ARG, 1, IST_ASSIGN,	FALSE,	FALSE,	0, 0, 0, "SUB_CONST"},
	{IS_2_ARG, 1, IST_CMP,		FALSE,	FALSE,	0, 0, 0, "EQU_EQU"},
	{IS_2_ARG, 1, IST_CMP,		FALSE,	FALSE,	0, 0, 0, "NOT_EQU"},
	{IS_2_ARG, 1, IST_CMP,		FALSE,	FALSE,	0, 0, 0, "LESS"},
	{IS_2_ARG, 1, IST_CMP,		FALSE,	FALSE,	0, 0, 0, "GREATER_EQU"},
	{IS_2_ARG, 1, IST_CMP,		FALSE,	FALSE,	0, 0, 0, "GREATER"},
	{IS_2_ARG, 1, IST_CMP,		FALSE,	FALSE,	0, 0, 0, "LESS_EQU"},
	{IS_0_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "PUSH_CMP"},
	{IS_2_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "AND_AND"},
	{IS_2_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "OR_OR"},
	{IS_2_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "XOR_XOR"},
	{IS_2_ARG, 1, IST_ASSIGN,	FALSE,	TRUE,	0, 0, 0, "ASSIGN"},
	{IS_2_ARG, 1, IST_ASSIGN,	FALSE,	TRUE,	0, 0, 0, "ASSIGN_PP"},
	{IS_2_ARG, 1, IST_ASSIGN,	FALSE,	TRUE,	0, 0, 0, "ASSIGN_MM"},
	{IS_2_ARG, 1, IST_ASSIGN,	FALSE,	TRUE,	0, 0, 0, "SHL_EQU"},
	{IS_2_ARG, 1, IST_ASSIGN,	FALSE,	TRUE,	0, 0, 0, "SHR_EQU"},
	{IS_2_ARG, 1, IST_ASSIGN,	FALSE,	TRUE,	0, 0, 0, "MUL_EQU"},
	{IS_2_ARG, 1, IST_ASSIGN,	FALSE,	TRUE,	0, 0, 0, "DIV_EQU"},
	{IS_2_ARG, 1, IST_ASSIGN,	FALSE,	TRUE,	0, 0, 0, "MOD_EQU"},
	{IS_2_ARG, 1, IST_ASSIGN,	FALSE,	TRUE,	0, 0, 0, "AND_EQU"},
	{IS_2_ARG, 1, IST_ASSIGN,	FALSE,	TRUE,	0, 0, 0, "OR_EQU"},
	{IS_2_ARG, 1, IST_ASSIGN,	FALSE,	TRUE,	0, 0, 0, "XOR_EQU"},
	{IS_2_ARG, 1, IST_ASSIGN,	FALSE,	TRUE,	0, 0, 0, "ADD_EQU"},
	{IS_2_ARG, 1, IST_ASSIGN,	FALSE,	TRUE,	0, 0, 0, "SUB_EQU"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "JMP"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "SUB_CALL"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "SWITCH"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "NOBOUND_SWITCH"},
	{IS_V_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "ADD_RSP"},
	{IS_V_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "ADD_RSP1"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "ENTER"},
	{IS_0_ARG, 0, IST_ASSIGN,	FALSE,	FALSE,	0, 0, 0, "PUSH_REGS"},
	{IS_0_ARG, 0, IST_ASSIGN,	FALSE,	FALSE,	0, 0, 0, "POP_REGS"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "LEAVE"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "RET"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "CALL"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "CALL_INDIRECT"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "CALL_INDIRECT2"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "CALL_IMPORT"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "CALL_EXTERN"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "ASM"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "PUSH"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "POP"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "CLFLUSH"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "INVLPG"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "IN_U8"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "IN_U16"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "IN_U32"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "OUT_U8"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "OUT_U16"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "OUT_U32"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "GET_RFLAGS"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "CARRY"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "SET_RFLAGS"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "GET_RAX"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "SET_RAX"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "GET_RBP"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "SET_RBP"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "GET_RSP"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "SET_RSP"},
	{IS_0_ARG, 1, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "RIP"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "RDTSC"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "BT"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "BTS"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "BTR"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "BTC"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "LBTS"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "LBTR"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "LBTC"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "BSF"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "BSR"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "QUE_INIT"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "QUE_INS"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "QUE_INS_REV"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "QUE_REM"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "STRLEN"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_ZERO"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_NOT_ZERO"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_CARRY"},
	{IS_0_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_NOT_CARRY"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_EQU_EQU"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_NOT_EQU"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_LESS"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_GREATER_EQU"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_GREATER"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_LESS_EQU"},
	{IS_2_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_2EQU_EQU"},
	{IS_2_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_2NOT_EQU"},
	{IS_2_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_2LESS"},
	{IS_2_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_2GREATER_EQU"},
	{IS_2_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_2GREATER"},
	{IS_2_ARG, 1, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_2LESS_EQU"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_AND_ZERO"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_AND_NOT_ZERO"},
	{IS_1_ARG, 0, IST_DEREF,	FALSE,	TRUE,	0, 0, 0, "BR_MM_ZERO"},
	{IS_1_ARG, 0, IST_DEREF,	FALSE,	TRUE,	0, 0, 0, "BR_MM_NOT_ZERO"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_AND_AND_ZERO"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_AND_AND_NOT_ZERO"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_OR_OR_ZERO"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "BR_OR_OR_NOT_ZERO"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "BR_BT"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "BR_BTS"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "BR_BTR"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "BR_BTC"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "BR_NOT_BT"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "BR_NOT_BTS"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "BR_NOT_BTR"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "BR_NOT_BTC"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "SWAP_U8"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "SWAP_U16"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "SWAP_U32"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "SWAP_U64"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "ABS_I64"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "SIGN_I64"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "I64_MIN"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "U64_MIN"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "I64_MAX"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "U64_MAX"},
	{IS_2_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "MOD_U64"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "SQRI64"},
	{IS_1_ARG, 0, IST_NULL,		FALSE,	FALSE,	0, 0, 0, "SQRU64"},
	{IS_1_ARG, 1, IST_NULL,		TRUE,	FALSE,	0, 0, 0, "SQR"},
	{IS_1_ARG, 1, IST_NULL,		TRUE,	FALSE,	0, 0, 0, "ABS"},
	{IS_1_ARG, 1, IST_NULL,		TRUE,	FALSE,	0, 0, 0, "SQRT"},
	{IS_1_ARG, 1, IST_NULL,		TRUE,	FALSE,	0, 0, 0, "SIN"},
	{IS_1_ARG, 1, IST_NULL,		TRUE,	FALSE,	0, 0, 0, "COS"},
	{IS_1_ARG, 1, IST_NULL,		TRUE,	FALSE,	0, 0, 0, "TAN"},
	{IS_1_ARG, 1, IST_NULL,		TRUE,	FALSE,	0, 0, 0, "ATAN"},
	{IS_1_ARG, 1, IST_NULL,		FALSE,	TRUE,	0, 0, 0, "POPCNT"},
};

U0 CompLoadDefines()
{
	DefineListLoad("ST_RAW_TYPES",
					" \0"
					" \0"
					"I0\0"
					"U0\0"
					"I8\0"
					"U8\0"
					"I16\0"
					"U16\0"
					"I32\0"
					"U32\0"
					"I64\0"
					"U64\0"
					"F32\0"
					"UF32\0"
					"F64\0"
					"UF64\0");

	DefineListLoad("ST_NATURAL_TYPES",
					"I8\0"
					"U8\0"
					"I16\0"
					"U16\0"
					"I32\0"
					"U32\0"
					"I64\0"
					"U64\0"
					"F64\0"
					"String\0");

	DefineListLoad("ST_INT_SIZE_TYPES",
					"I8\0"
					"U8\0"
					"I16\0"
					"U16\0"
					"I32\0"
					"U32\0"
					"I64\0"
					"U64\0");

	DefineListLoad("ST_TY_TYPES",
					"NULL\0"
					"STACK\0"
					"IMM\0"
					"REG\0"
					"DISP\0"
					"SIB\0"
					"RIP\0");

	DefineListLoad("ST_U8_REGS",
					"AL\0"
					"CL\0"
					"DL\0"
					"BL\0"
					"AH\0"
					"CH\0"
					"DH\0"
					"BH\0"
					"R8u8\0"
					"R9u8\0"
					"R10u8\0"
					"R11u8\0"
					"R12u8\0"
					"R13u8\0"
					"R14u8\0"
					"R15u8\0");

	DefineListLoad("ST_U8_REX_REGS",
					"AL\0"
					"CL\0"
					"DL\0"
					"BL\0"
					"RSPu8\0"
					"RBPu8\0"
					"RSIu8\0"
					"RDIu8\0"
					"R8u8\0"
					"R9u8\0"
					"R10u8\0"
					"R11u8\0"
					"R12u8\0"
					"R13u8\0"
					"R14u8\0"
					"R15u8\0");

	DefineListLoad("ST_U16_REGS",
					"AX\0"
					"CX\0"
					"DX\0"
					"BX\0"
					"SP\0"
					"BP\0"
					"SI\0"
					"DI\0"
					"R8u16\0"
					"R9u16\0"
					"R10u16\0"
					"R11u16\0"
					"R12u16\0"
					"R13u16\0"
					"R14u16\0"
					"R15u16\0");

	DefineListLoad("ST_U32_REGS",
					"EAX\0"
					"ECX\0"
					"EDX\0"
					"EBX\0"
					"ESP\0"
					"EBP\0"
					"ESI\0"
					"EDI\0"
					"R8u32\0"
					"R9u32\0"
					"R10u32\0"
					"R11u32\0"
					"R12u32\0"
					"R13u32\0"
					"R14u32\0"
					"R15u32\0");

	DefineListLoad("ST_U64_REGS",
					"RAX\0"
					"RCX\0"
					"RDX\0"
					"RBX\0"
					"RSP\0"
					"RBP\0"
					"RSI\0"
					"RDI\0"
					"R8\0"
					"R9\0"
					"R10\0"
					"R11\0"
					"R12\0"
					"R13\0"
					"R14\0"
					"R15\0");

	DefineListLoad("ST_MM_REGS",
					"MM0\0"
					"MM1\0"
					"MM2\0"
					"MM3\0"
					"MM4\0"
					"MM5\0"
					"MM6\0"
					"MM7\0");

	DefineListLoad("ST_XMM_REGS",
					"XMM0\0"
					"XMM1\0"
					"XMM2\0"
					"XMM3\0"
					"XMM4\0"
					"XMM5\0"
					"XMM6\0"
					"XMM7\0"
					"XMM8\0"
					"XMM9\0"
					"XMM10\0"
					"XMM11\0"
					"XMM12\0"
					"XMM13\0"
					"XMM14\0"
					"XMM15\0");

	DefineListLoad("ST_ARG_TYPES",
					"NONE\0"
					"REL8\0"
					"REL16\0"
					"REL32\0"
					"IMM8\0"
					"IMM16\0"
					"IMM32\0"
					"IMM64\0"
					"UIMM8\0"
					"UIMM16\0"
					"UIMM32\0"
					"UIMM64\0"
					"R8\0"
					"R16\0"
					"R32\0"
					"R64\0"
					"RM8\0"
					"RM16\0"
					"RM32\0"
					"RM64\0"
					"M8\0"
					"M16\0"
					"M32\0"
					"M64\0"
					"M1632\0"
					"M16N32\0"
					"M16N16\0"
					"M32N32\0"
					"MOFFS8\0"
					"MOFFS16\0"
					"MOFFS32\0"
					"MOFFS64\0"
					"AL\0"
					"AX\0"
					"EAX\0"
					"RAX\0"
					"CL\0"
					"DX\0"
					" \0"
					"SREG\0"
					"SS\0"
					"DS\0"
					"ES\0"
					"FS\0"
					"GS\0"
					"CS\0"
					"ST0\0"
					"STI\0"
					"MM\0"
					"MM32\0"
					"MM64\0"
					"XMM\0"
					"XMM32\0"
					"XMM64\0"
					"XMM128\0"
					"XMM0\0");

	DefineListLoad("ST_SEG_REGS",
					"ES\0"
					"CS\0"
					"SS\0"
					"DS\0"
					"FS\0"
					"GS\0");

	DefineListLoad("ST_FSTACK_REGS",
					"ST0\0"
					"ST1\0"
					"ST2\0"
					"ST3\0"
					"ST4\0"
					"ST5\0"
					"ST6\0"
					"ST7\0");
}

U0 CompFillTables()
{
	I64  i;
	U32 *d;

	cmp.to_reg_vars_map = CAlloc(REG_REGS_NUM * sizeof(U8));
	cmp.num_reg_vars = 0;
	cmp.reg_vars_mask = REGG_LOCAL_VARS;
	for (i = 0; i < REG_REGS_NUM; i++)
		if (Bt(&cmp.reg_vars_mask, i))
			cmp.to_reg_vars_map[cmp.num_reg_vars++] = i;

	cmp.non_ptr_vars_map = CAlloc(REG_REGS_NUM * sizeof(U8));
	cmp.num_non_ptr_vars = 0;
	cmp.non_ptr_vars_mask = REGG_LOCAL_NON_PTR_VARS;
	for (i = 0; i < REG_REGS_NUM; i++)
		if (Bt(&cmp.non_ptr_vars_mask, i))
			cmp.non_ptr_vars_map[cmp.num_non_ptr_vars++] = i;

	cmp.dual_U16_tokens1 = d = CAlloc(sizeof(U32) * TK_TKS_NUM);
	d['!'] = TK_NOT_EQU		<< 16 + '=';
	d['&'] = TK_AND_AND		<< 16 + '&';
	d['*'] = TK_MUL_EQU		<< 16 + '=';
	d['+'] = TK_PLUS_PLUS	<< 16 + '+';
	d['-'] = TK_DEREFERENCE	<< 16 + '>';
	d['/'] = '*';
	d[':'] = TK_DBL_COLON	<< 16 + ':';
	d['<'] = TK_LESS_EQU	<< 16 + '=';
	d['='] = TK_EQU_EQU		<< 16 + '=';
	d['>'] = TK_GREATER_EQU	<< 16 + '=';
	d['^'] = TK_XOR_EQU		<< 16 + '=';
	d['|'] = TK_OR_OR		<< 16 + '|';
	d['%'] = TK_MOD_EQU		<< 16 + '=';

	cmp.dual_U16_tokens2 = d = CAlloc(sizeof(U32) * TK_TKS_NUM);
	d['&'] = TK_AND_EQU		<< 16 + '=';
	d['+'] = TK_ADD_EQU		<< 16 + '=';
	d['-'] = TK_MINUS_MINUS	<< 16 + '-';
	d['/'] = '/';
	d['<'] = TK_SHL			<< 16 + '<';
	d['>'] = TK_SHR			<< 16 + '>';
	d['^'] = TK_XOR_XOR		<< 16 + '^';
	d['|'] = TK_OR_EQU		<< 16 + '=';

	cmp.dual_U16_tokens3 = d = CAlloc(sizeof(U32) * TK_TKS_NUM);
	d['-'] = TK_SUB_EQU << 16 + '=';
	d['/'] = TK_DIV_EQU << 16 + '=';

	cmp.binary_ops = d = CAlloc(sizeof(U32) * TK_TKS_NUM);
	d['`']    = (PREC_EXP + ASSOCF_RIGHT) << 16 + IC_POWER;
	d[TK_SHL] = (PREC_EXP + ASSOCF_LEFT)  << 16 + IC_SHL;
	d[TK_SHR] = (PREC_EXP + ASSOCF_LEFT)  << 16 + IC_SHR;

	d['*'] = PREC_MUL << 16 + IC_MUL;
	d['/'] = (PREC_MUL + ASSOCF_LEFT) << 16 + IC_DIV;
	d['%'] = (PREC_MUL + ASSOCF_LEFT) << 16 + IC_MOD;

	d['&'] = PREC_AND << 16 + IC_AND;

	d['^'] = PREC_XOR << 16 + IC_XOR;

	d['|'] = PREC_OR  << 16 + IC_OR;

	d['+'] = PREC_ADD << 16 + IC_ADD;
	d['-'] = (PREC_ADD + ASSOCF_LEFT) << 16 + IC_SUB;

	d['<']			  = PREC_CMP << 16 + IC_LESS;
	d['>']			  = PREC_CMP << 16 + IC_GREATER;
	d[TK_LESS_EQU]	  = PREC_CMP << 16 + IC_LESS_EQU;
	d[TK_GREATER_EQU] = PREC_CMP << 16 + IC_GREATER_EQU;

	d[TK_EQU_EQU] = PREC_CMP2 << 16 + IC_EQU_EQU;
	d[TK_NOT_EQU] = PREC_CMP2 << 16 + IC_NOT_EQU;

	d[TK_AND_AND] = PREC_AND_AND << 16 + IC_AND_AND;

	d[TK_XOR_XOR] = PREC_XOR_XOR << 16 + IC_XOR_XOR;

	d[TK_OR_OR]   = PREC_OR_OR   << 16 + IC_OR_OR;

	d['=']		  = (PREC_ASSIGN + ASSOCF_RIGHT) << 16 + IC_ASSIGN;
	d[TK_SHL_EQU] = (PREC_ASSIGN + ASSOCF_RIGHT) << 16 + IC_SHL_EQU;
	d[TK_SHR_EQU] = (PREC_ASSIGN + ASSOCF_RIGHT) << 16 + IC_SHR_EQU;
	d[TK_MUL_EQU] = (PREC_ASSIGN + ASSOCF_RIGHT) << 16 + IC_MUL_EQU;
	d[TK_DIV_EQU] = (PREC_ASSIGN + ASSOCF_RIGHT) << 16 + IC_DIV_EQU;
	d[TK_MOD_EQU] = (PREC_ASSIGN + ASSOCF_RIGHT) << 16 + IC_MOD_EQU;
	d[TK_AND_EQU] = (PREC_ASSIGN + ASSOCF_RIGHT) << 16 + IC_AND_EQU;
	d[TK_OR_EQU]  = (PREC_ASSIGN + ASSOCF_RIGHT) << 16 + IC_OR_EQU;
	d[TK_XOR_EQU] = (PREC_ASSIGN + ASSOCF_RIGHT) << 16 + IC_XOR_EQU;
	d[TK_ADD_EQU] = (PREC_ASSIGN + ASSOCF_RIGHT) << 16 + IC_ADD_EQU;
	d[TK_SUB_EQU] = (PREC_ASSIGN + ASSOCF_RIGHT) << 16 + IC_SUB_EQU;
}
