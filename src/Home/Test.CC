
















U0 Test()
{
	SetRAX(9999);
	MOV		ECX,	40
	MOVD	XMM15,	ECX
	MOVD	EAX,	XMM15
	"%d\n", GetRAX;
}

Uf("Test");

Test;