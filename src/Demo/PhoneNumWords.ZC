U8 char_map[26]="22233344455566677778889999";

/*
Format of word list entry:
	U8 ACD_WORD_CHAR
	U8 word[] with terminating zero
	I16 block; //definition offset in ::/System/AutoComplete/ACDefs.DATA
*/
U0 PhoneNumWords(U8 *num)
{
	I64  ch;
	U8	*_num = StrNew(num), *dst = _num, 
		*dict = acd.word_list, *st, *src;

	while (*num)
	{
		if ('0' <= *num <= '9')
			*dst++ = *num;
		num++;
	}
	*dst = 0;

	while (*dict++)
	{
		if (StrLen(dict) > 2)
		{
			dst = st = StrNew(dict);
			while (ch = ToUpper(*dst))
			{
				if ('A' <= ch <= 'Z')
					*dst = char_map[ch - 'A'];
				else
					*dst = CH_SPACE;
				dst++;
			}
			*dst = 0;

			src = _num;
			while (*src)
			{
				if (!StrNCompare(st, src, StrLen(st)))
				{
					ch = *src;
					*src = 0;
					"%s", _num;
					*src = ch;
					"$$GREEN$$%s$$FG$$", dict;
					"%s\n", src + StrLen(st);
				}
				src++;
			}
			Free(st);
		}
		dict += StrLen(dict) + 3;
	}
	Free(_num);
	'\n';
}

U0 PNWDemo()
{
	U8 *st;

	while ((st = StrGet("Phone Num:")) && *st)
	{
		PhoneNumWords(st);
		Free(st);
	}
	Free(st);
}

PNWDemo;
