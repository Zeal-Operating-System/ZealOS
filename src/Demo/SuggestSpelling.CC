/*This does a really crappy job of
suggesting spellings.  Write a better
one for fun.
*/

U8 *SuggestMatchForm(U8 *src)
{
	I64 ch, ch1 = 0;
	U8 *res = MStrUtil(src, SUF_TO_UPPER), *dst;

	dst = src = res;
	while (ch = *src++)
	{
		if (!StrOcc("AEIOU", ch))
		{
			if (ch == 'C')
				ch = 'K';
			if (ch == 'Z')
				ch = 'S';
			if (ch != ch1) //double chars to single
				*dst++ = ch;
		}
		ch1 = ch;
	}
	*dst = 0;

	return res;
}

/*Format of word list entry:
	U8 ACD_WORD_CHAR
	U8 word[] with terminating zero
	I16 block; //definition offset in ::/System/AutoComplete/ACDefs.DATA
*/

Bool SuggestSpelling(U8 *word)
{
	U8	*dict = acd.word_list,
		*pf = SuggestMatchForm(word),
		*wf;
	I64  len = StrLen(pf),
		 num_cols = Fs->win_width / 16,
		 col = 0;

	if (len)
		while (*dict)
		{
			wf = SuggestMatchForm(dict + 1);
			if (!StrNCompare(pf, wf, len))
			{
				"%16s", dict + 1;
				if (++col >= num_cols)
				{
					col=0;
					'\n';
				}
			}
			Free(wf);
			dict += StrLen(dict + 1) + 4;
		}
	Free(pf);
	'\n';

	return ToBool(len);
}

U0 SuggestSpellingDemo()
{
	U8 *w;

	while (TRUE)
	{
		w = StrGet("Word:");
		if (*w) {
			SuggestSpelling(w);
			Free(w);
		}
		else
			break;
	}
}

//If you "System Include" this file, it will
//install this command as a hot-key.

U0 CtrlAltL(I64)
{
//$LK,"ac.cur_word",A="MN:CAutoCompleteGlobals"$ is only set if AutoComplete
	//is running.
	if (!TaskValidate(ac.task))
	{
		AutoComplete(ON);
		Sleep(500);
	}
	PopUp("if (SuggestSpelling(ac.cur_word)) View;");
}

if (Fs != sys_task)
	SuggestSpellingDemo;
else
{
	CtrlAltCBSet('L', &CtrlAltL, "Cmd /Suggest Spelling");
//Appears in the System Task Window
	"<CTRL-ALT-l> installed\n";
}

//Note: It would be more appropriate
//to define a key in $LK,"MyPutKey",A="MN:MyPutKey"$().
