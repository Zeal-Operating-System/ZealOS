U0 Test()
{
	MOV			RAX, 30
	CVTSI2SD	XMM0, RAX
	MOVDDUP 	XMM0, RAX
	HADDPD		XMM0, XMM0
	MOVQ		RAX, XMM0
	"%f\n", GetRAX;
}



Test;

U0 Test2()
{
	MOVSD2 XMM0, RCX
}


CHashOpcode *oc = HashFind("ENTER", comp.asm_hash, HTT_OPCODE);
ClassRep(oc->ins);
