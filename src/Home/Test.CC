
















U0 Test()
{
	SetRAX(9999);
	MOV		RCX,40
	MOVQ	XMM15, RCX
	MOVQ	RAX, XMM15
	"%d\n", GetRAX;
}

Uf("Test");

Test;