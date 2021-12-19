//Pass the task structure you
//wish to spy upon.

U0 SpyStackRep(CTask *task)
{
	CDoc *doc = DocDblBufStart;

	while (!CharScan && TaskValidate(task))
	{
		StackRep(task);
		'\n';
		"$$BK,1$$PRESS A KEY$$BK,0$$\n";
		DocDblBufSwap;
		Refresh;
	}
	if (DocPut == doc)
		DocDblBufSwap;
	DocDblBufEnd;
}

U0 SpyCallerRep(CTask *task)
{
	CDoc *doc = DocDblBufStart;

	while (!CharScan && TaskValidate(task))
	{
		CallerRep(task->rbp,task);
		'\n';
		"$$BK,1$$PRESS A KEY$$BK,0$$\n";
		DocDblBufSwap;
		Refresh;
	}
	if (DocPut == doc)
		DocDblBufSwap;
	DocDblBufEnd;
}

U0 Spy()
{
	I64		i;
	CTask  *task;

	while (TRUE)
	{
		task = Fs->next_task;
		while (task != Fs)
		{
			"$$MA+X,T=\"Task:%08X:%16ts\",LM=\"0x%08X\n\"$$\n", task, task->task_name, task;
			task = task->next_task;
		}
		'\n';
		task = I64Get("Task Addr: ", 0);
		if (TaskValidate(task))
		{
			"\n\n\t$$BT,\"StackRep\",LM=\"1\n\"$$\n\n\n"
			"\n\n\t$$BT,\"CallerRep\",LM=\"2\n\"$$\n\n\n";
			i = I64Get("", 0);
			if (i == 1)
				SpyStackRep(task);
			else if (i == 2)
				SpyCallerRep(task);
			else
				break;
		}
		else
			break;
	}
	'\n';
}

Spy;
