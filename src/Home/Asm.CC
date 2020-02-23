asm {

HELLO:	DU8	"Hello, World!\n",0;

_TEST::
	PUSH	HELLO
	CALL	&PutS
	RET
};

_extern _TEST U0 HelloWorld();


HelloWorld;
