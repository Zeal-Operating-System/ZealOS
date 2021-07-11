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
	DocClear(net_log_task->border_doc, TRUE);

/*
	if (Fs == sys_task)
		WinFocus(sys_task->next_task);
	else
		WinFocus;*/

	WinHorz(TEXT_COLS / 3, 2 * TEXT_COLS / 3, net_log_task);
	WinVert(2 * TEXT_ROWS / 3, 5 * TEXT_ROWS / 6, net_log_task);
	WinFocus(net_log_task);

	DocPrint(net_log_task->put_doc, "$$WW+H,1$$");
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

U0 NetDebug(U8 *format, ...)
{ // Output text to NetLogTask as Debug.
	U8 *buf = StrPrintJoin(NULL, format, argc, argv);

	DocBottom(net_log_task->put_doc);
	DocPrint(net_log_task->put_doc, "$$BG,YELLOW$$$$DKGRAY$$%s$$BG$$$$FG$$\n", buf);

	Free(buf);
}

NetLogInit;