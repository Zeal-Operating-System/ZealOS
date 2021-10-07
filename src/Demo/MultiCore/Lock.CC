/*lock{} is a compiler statement
which places asm LOCK instruction
prefixes on code.  Only use it on
read-modify-write statements.
It will generate invalid insts
if you misuse it and it will crash.
$LK,"U",A="MN:U"$() to see what code was generated.
*/

#define COUNT 	0x1000000

I64 global;

U0 MPUnlockedInc(I64)
{
	I64 i;

	for (i = 0; i < COUNT; i++)
		global++;
}

U0 UnlockedInc()
{
	CJob *tmpm0, *tmpm1;

	global= 0;
	tmpm0 = JobQueue(&MPUnlockedInc, NULL, 0, 0);
	tmpm1 = JobQueue(&MPUnlockedInc, NULL, 1, 0);
	JobResGet(tmpm0);
	JobResGet(tmpm1);
	"Correct Count:%X Actual Count:%X\n", COUNT * 2, global;
}

U0 MPLockedInc(I64)
{
	I64 i;

	for (i = 0; i < COUNT; i++)
		lock /*Can be used without {} */ global++;
}

U0 LockedInc()
{
	CJob *tmpm0, *tmpm1;

	global = 0;
	tmpm0 = JobQueue(&MPLockedInc, NULL, 0, 0);
	tmpm1 = JobQueue(&MPLockedInc, NULL, 1, 0);
	JobResGet(tmpm0);
	JobResGet(tmpm1);
	"Correct Count:%X Actual Count:%X\n", COUNT * 2, global;
}

UnlockedInc;
LockedInc;
