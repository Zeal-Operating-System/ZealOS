//See $LK,"Define",A="HI:Define"$.

//These might be in the System task.
DefineLoad("ST_YES_NO", "(Yes or No)");
DefineLoad("ST_EXIT", "Exit");
DefineListLoad("ST_NO_YES_LIST", "No\0Yes\0");

//New strings might be loaded for each user
//to override.

"Spanish";
if (YorN) {
	DefineLoad("ST_YES_NO", "(Si or No)");
	DefineLoad("ST_EXIT", "Salida");
	DefineListLoad("ST_NO_YES_LIST", "No\0Si\0");
}

Bool Quit()
{
	Bool res;
	U8  *st;
	I64  i;

	while (TRUE)
	{
		"%S %S?", "ST_EXIT", "ST_YES_NO";
		st = StrGet;
		i = DefineMatch(st, "ST_NO_YES_LIST", LMF_IGNORE_CASE);
		if (i >= 0)
		{
			res = i;
			break;
		}
		Free(st);
	}

	return res;
}

Quit;
