class Person
{
	U8 first		[32];
	U8 last 		[32];
	U8 address1 	[64];
	U8 address2 	[64];
	U8 city 		[32];
	U8 state_zip	[32];
};

U0 OffsetDemo1()
{
	Person *p = MAlloc(sizeof(Person));

	StrCopy(p->first, 	  "Terry");
	StrCopy(p->last,	  "Davis");
	StrCopy(p->address1,  "8144 Sickle Lane");
	StrCopy(p->address2,  "");
	StrCopy(p->city,	  "Las Vegas");
	StrCopy(p->state_zip, "NV 89128");
}

U(&OffsetDemo1, 34);
PressAKey;

/*

x86 has signed 8-bit	displacements
		and signed 32-bit displacements.

This example uses 8-bit negative displacements.

*/

class Person
{ $$ = -128;
U8 first		[32];
U8 last 		[32];
U8 address1 	[64];
U8 address2 	[64];
U8 city 		[32];
U8 state_zip	[32];
};

U0 OffsetDemo2()
{
	Person *p = MAlloc(sizeof(Person))(I64) + 128;

	StrCopy(p->first, 	  "Terry");
	StrCopy(p->last,	  "Davis");
	StrCopy(p->address1,  "8144 Sickle Lane");
	StrCopy(p->address2,  "");
	StrCopy(p->city,	  "Las Vegas");
	StrCopy(p->state_zip, "NV 89128");
}

U(&OffsetDemo2, 34);
PressAKey;
