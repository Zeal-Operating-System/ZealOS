
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
	WinTileHorz;
	WinFocus;
}

U0 NetLog(U8 *format, ...)
{ // Output text to NetLogTask as Log.
	U8 *buf = StrPrintJoin(NULL, format, argc, argv);

	DocBottom(net_log_task->put_doc);
	DocPrint(net_log_task->put_doc, "$$LTGRAY$$%s$$FG$$\n", buf);

}

U0 NetWarn(U8 *format, ...)
{ // Output text to NetLogTask as Warning.
	U8 *buf = StrPrintJoin(NULL, format, argc, argv);

	DocBottom(net_log_task->put_doc);
	DocPrint(net_log_task->put_doc, "$$BG,BROWN$$$$WHITE$$%s$$BG$$$$FG$$\n", buf);

}

U0 NetErr(U8 *format, ...)
{ // Output text to NetLogTask as Error.
	U8 *buf = StrPrintJoin(NULL, format, argc, argv);

	DocBottom(net_log_task->put_doc);
	DocPrint(net_log_task->put_doc, "$$BG,RED$$$$WHITE$$%s$$BG$$$$FG$$\n", buf);

}

NetLogInit;