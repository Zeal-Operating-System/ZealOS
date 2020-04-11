U0 (*fp_test)();

interrupt U0 Test()
{
	"nigger\n";
}

U0 Main()
{
	IntEntrySet(I_USER, &Test);

	INT I_USER

	fp_test = IntEntryGet(I_USER);

	U(fp_test);
}

Main;