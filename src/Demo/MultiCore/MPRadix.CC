/*
On an 8-core machine, this takes the top 3-bits
of random numbers and distributes them to the 8 cores
for sorting.	Then, it merge sorts them.
*/

#define NUM 		1000000

I64 my_mp_count = 1 << Bsr(mp_count);//Power of 2

I32 *arg1, *arg2;
I32 *b[my_mp_count], bn[my_mp_count];
I64  mp_not_done_flags;

I64 Compare(I32 *e1, I32 *e2)
{
	return *e1 - *e2;
}

U0 QuickSortU32(I32 *base, I64 num)
{//By customizing, we dramatically improve it!
//Cut and paste from $LK,"QuickSortI64",A="MN:QuickSortI64"$().
	I64  i;
	I32 *less, *greater, pivot;

	if (num > 1)
	{
		do
		{
			less = base;
			greater = base + num;
			pivot = base[num / 2];
			while (less < greater)
			{
				if (*less <= pivot)
					less++;
				else
				{
					greater--;
					SwapU32(less, greater);
				}
			}
			i = less - base;
			if (i == num)
			{//All less or equ to pivot

				//Point greater to first less
				do greater--;
				while (--i && *greater == pivot);

				if (i)
				{
					less = base  +num / 2; //Pivot was not moved, point to it
					if (less < greater)
						SwapU32(less, greater);
					num = i;
				}
				else //All equ
					break;
			}
			else if (i < num / 2)
			{
				QuickSortU32(base, i);
				num -= i;
				base = greater;
			}
			else
			{
				QuickSortU32(greater, num - i);
				num = i;
			}
		}
		while (num > 1);
	}
}

U0 MPSort(I64 dummy=0)
{
	no_warn dummy;
	QuickSortU32(b[Gs->num], bn[Gs->num]);
	LBtr(&mp_not_done_flags, Gs->num);
}

U0 MPRadixSortDemo(I64 dummy=0)
{
	no_warn dummy;
	I64 i, j, k1, k2;
	F64 t0;

	arg1 = MAlloc(NUM * sizeof(I32));
	for (i = 0; i < NUM; i++)
		arg1[i] = RandI32;

	arg2 = MAlloc(NUM * sizeof(I32));

	"$$GREEN$$QuickSort$$FG$$\n";
	t0 = tS;
	MemCopy(arg2, arg1, sizeof(I32) * NUM);
	QuickSort(arg2, NUM, sizeof(I32), &Compare);
	"Time:%9.6f\n", tS - t0;
	Dump(arg2 + NUM / 4);

	"$$GREEN$$QuickSortU32$$FG$$\n";
	t0 = tS;
	MemCopy(arg2, arg1, sizeof(I32)*NUM);
	QuickSortU32(arg2, NUM);
	"Time:%9.6f\n", tS - t0;
	Dump(arg2 + NUM / 4);

	for (i = 0; i < my_mp_count; i++)
	{
		//$WW,0$We must do full size, just in case.
		//There will be uneven split between cores
		//depending on the distribution of rand numbers.
		b[i] = MAlloc(NUM * sizeof(I32));
		bn[i] = 0;
	}

	if (my_mp_count < 2)
		throw('MultCore');

	"$$GREEN$$MP Radix QuickSortU32$$FG$$\n";
	t0 = tS;
	k1 = 32 - Bsr(my_mp_count);
	k2 = my_mp_count / 2;
	for (i = 0; i < NUM; i++)
	{
		j = arg1[i] >> k1 + k2; //This is a preliminary radix sort.
		b[j][bn[j]++] = arg1[i];
	}
	mp_not_done_flags = 1 << my_mp_count - 1;
	for (i = 0; i < my_mp_count; i++)
		Spawn(&MPSort, NULL, NULL, i);
	while (mp_not_done_flags)
		Yield;
	j = 0;
	for (i = 0; i < my_mp_count; i++)
	{
		MemCopy(&arg2[j], b[i], bn[i] * sizeof(I32));
		j += bn[i];
	}
	"Time:%9.6f\n", tS - t0;
	Dump(arg2 + NUM / 4);

	Free(arg1);
	Free(arg2);
	for (i = 0; i < my_mp_count; i++)
		Free(b[i]);
}

MPRadixSortDemo;

/*$HL,0$ Results on 8 Cores 3.397GHz Core i7:
$FG,2$QuickSort$FG$
Time: 0.759998
$FG,2$QuickSortU32$FG$
Time: 0.093684
$FG,2$MP Radix QuickSortU32$FG$
Time: 0.045450
$HL,1$*/
