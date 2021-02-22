CTask *net_log_task = NULL;

U0 NetLogTask(I64)
{

	while (TRUE)
	{
		Refresh;
	}
}

U0 NetLogInit()
{
	net_log_task = Spawn(&ServerCmdLine, NULL, "Network Log");
	TaskWait(net_log_task);

	net_log_task->border_src	= BDS_CONST;
	net_log_task->border_attr	= DKGRAY << 4 + LTGRAY;
	net_log_task->text_attr		= WHITE  << 4 + LTGRAY;

	if (Fs == zenith_task)
		WinFocus(zenith_task->next_task);
	else
		WinFocus;

	WinTileHorz;
}

U0 NetLog(U8 *format, ...)
{ // Output text to NetLogTask as Log.
	U8 *buf = StrPrintJoin(NULL, format, argc, argv);

	DocBottom(net_log_task->put_doc);
	DocPrint(net_log_task->put_doc, "%s\n", buf);

	Free(buf);
}

U0 NetWarn(U8 *format, ...)
{ // Output text to NetLogTask as Warning.
	U8 *buf = StrPrintJoin(NULL, format, argc, argv);

	DocBottom(net_log_task->put_doc);
	DocPrint(net_log_task->put_doc, "$$BG,BROWN$$$$WHITE$$%s$$BG$$$$FG$$\n", buf);

	Free(buf);
}

U0 NetErr(U8 *format, ...)
{ // Output text to NetLogTask as Error.
	U8 *buf = StrPrintJoin(NULL, format, argc, argv);

	DocBottom(net_log_task->put_doc);
	DocPrint(net_log_task->put_doc, "$$BG,RED$$$$WHITE$$%s$$BG$$$$FG$$\n", buf);

	Free(buf);
}

NetLogInit;