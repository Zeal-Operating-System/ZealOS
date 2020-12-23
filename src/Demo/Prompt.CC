U0 PromptDemo()
{
	F64		 d;
	I64		 i;
	U8		*name;
	CDate	 cdt;

	"\n\nNow prompting from the cmd line.\n\n"
	"$$GREEN$$<ENTER>$$FG$$ keeps default.\n\n";

	i = I64Get("Enter int expression(%d):", 123);
	"Int=%d\n", i;

	d = F64Get("Enter float expression(%12g):", 1.2e3);
	"Float=%e\n", d;

	name = StrGet("Name (%s):", "John");
	"Name:%s\n", name;
	Free(name);

	cdt = DateGet("Date (%D):", Now);
	"Date=%D\n", cdt;
}

PromptDemo;
