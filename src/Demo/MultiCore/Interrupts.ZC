interrupt U0 IntBeepOn()
{
	*(dev.uncached_alias + LAPIC_EOI)(U32 *) = 0; //signal end of interrupt
	Sound(34);
}

interrupt U0 IntBeepOff()
{
	*(dev.uncached_alias + LAPIC_EOI)(U32 *) = 0;
	Sound;
}

U0 IntTest()
{//Modify interrupt descriptor table use by all cores.
	I64 int_on	= IntEntryAlloc,
		int_off = IntEntryAlloc;

	IntEntrySet(int_on,  &IntBeepOn,  IDTET_TRAP);
	IntEntrySet(int_off, &IntBeepOff, IDTET_TRAP);
	//Issue interupt to core1
	MPInt(int_on, 1);
	Sleep(1000);
	MPInt(int_off, 1);
}

IntTest;
