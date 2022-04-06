/*
Press <CTRL-ALT-c> to break.

Rerun Program

Press <CTRL-ALT-d> to enter Debug.
> $LK,"DumpRegs",A="MN:DumpRegs"$;	//Dump Registers
> $LK,"G2",A="MN:G2"$;	//Cont program

Press <CTRL-ALT-d> to enter Debug.
> $LK,"Uf",A="MN:Uf"$("DebugDemo");
> $LK,"U",A="MN:U"$(_RIP);

See $LK,"Debugging",A="HI:Debugging"$
*/

U0 DebugDemo()
{
	I64 i = 0;

	while (TRUE)
		if (!(i++ % 2000000))
			".";
}

DebugDemo;

