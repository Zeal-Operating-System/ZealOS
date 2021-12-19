#define NUM 		100

I64 mp_not_done_flags, grand_total;

U0 MPRoutine(CDoc *doc)
{
	I64 i, sum = 0, 
		lo = NUM * Gs->num / mp_count,		//This is how to divide a job
		hi = NUM * (Gs->num + 1) / mp_count;

	for (i = lo; i < hi; i++)
		sum += i;
	DocPrint(doc, "Core#%d:%d-%d:%d\n", Gs->num, lo, hi - 1, sum);
	lock {grand_total += sum;}
	LBtr(&mp_not_done_flags, Gs->num);
}

U0 Main()
{
	I64 i;

	grand_total = 0;
	mp_not_done_flags = 1 << mp_count - 1;
	for (i = 0; i < mp_count; i++)
		Spawn(&MPRoutine, DocPut, NULL, i);
	while (mp_not_done_flags)
		Yield;
	"Grand total:%d\n", grand_total;
}

Main;
