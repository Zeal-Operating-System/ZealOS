#help_index "Registry"
#define REGISTRY_FILENAME "~/Registry.CC"

CDoc *sys_registry_doc = NULL;
I64 sys_message_flags[1] = {0};
F64 registry_version;

Bool RegCache()
{
	Bool old_silent;

	if (!sys_registry_doc)
	{
		old_silent = Silent;
		sys_registry_doc = DocRead(REGISTRY_FILENAME);
		Silent(old_silent);
		return FALSE;
	}
	else
		return TRUE;
}

public Bool RegDefault(U8 *path, U8 *val, Bool is_zenith_entry=FALSE)
{//Add code doc tree branch to registry.
	Bool res, unlock_doc;

	RegCache;
	unlock_doc = DocLock(sys_registry_doc);
	if (!DocTreeFind(sys_registry_doc, path))
	{
		DocTreeMake(sys_registry_doc, path);
		DocPrint(sys_registry_doc, "%s", val);
		if (is_zenith_entry)
		{
			if (Fs == zenith_task)
				ExePrint("%s", val);
			else
				Zenith("%s", val);
		}
		if (DriveIsWritable(*sys_registry_doc->filename.name))
			DocWrite(sys_registry_doc);
		res = FALSE;
	}
	else
		res = TRUE;
	if (unlock_doc)
		DocUnlock(sys_registry_doc);

	return res;
}

public I64 RegExe(U8 *path)
{//Execute doc tree branch in registry.
	RegCache;

	return DocTreeExe(sys_registry_doc, path);
}

public Bool RegWrite(U8 *path, U8 *format, ...)
{//Rewrite doc tree branch in registry.
	Bool res;

	RegCache;
	res = DocTreeWriteJoin(sys_registry_doc, path, TRUE, format, argc, argv);

	return res;
}

public I64 RegCount(U8 *path)
{//Tree branch count in registry.
	I64			 res = 0;
	CDocEntry	*tree_branch, *start_indent, *end_indent;
	Bool		 unlock_doc = DocLock(sys_registry_doc);

	if (DocTreeFind(sys_registry_doc, path, &tree_branch, &start_indent, &end_indent))
	{
		end_indent = end_indent->next;
		while (start_indent != end_indent)
		{
			res++;
			start_indent = start_indent->next;
		}
	}
	if (unlock_doc)
		DocUnlock(sys_registry_doc);

	return res;
}

public Bool RegAppend(U8 *path, U8 *format, ...)
{//Append to doc tree branch in registry.
	Bool res;

	RegCache;
	res = DocTreeAppendJoin(sys_registry_doc, path, TRUE, format, argc, argv);

	return res;
}
 
public Bool OneTimePopUp(U8 *_flags, I64 flag_num, U8 *message)
{//See $LK,"::/Apps/X-Caliber/X-Caliber.CC"$.
	Bool		 res = FALSE;
	CDoc		*doc = DocNew;
	CDocEntry	*doc_e;

	if (!Bt(_flags, flag_num))
	{
		if (message)
			DocPrint(doc, "%s", message);
		doc_e = DocPrint(doc, "\n$$CB,\"Do not show this message again.\",LE=1$$");
		DocPrint(doc, "$$CM+CX,0,4$$$$BT,\"OKAY\",LE=1$$\n");
		if (PopUpMenu(doc) == 1 && doc_e->de_flags & DOCEF_CHECKED_COLLAPSED)
		{
			LBts(_flags, flag_num);
			res = TRUE;
		}
		DocDel(doc);
	}

	return res;
}

U0 RegOneTimePopUp(I64 flag_num, U8 *message)
{//You're not supposed to make system pop-up flags, only me.
	if (OneTimePopUp(sys_message_flags, flag_num,message))
		RegWrite("Zenith/SysMessageFlags", "sys_message_flags[0]=0x%X;\n", sys_message_flags[0]);
}

U0 RegInit()
{
	U8   buf[STR_LEN];
	Bool version_present;

	RegDefault("Zenith/SysMessageFlags", "sys_message_flags[0]=0;\n", TRUE);
	StrPrint(buf, "registry_version=%4.3f;\n", sys_os_version);
	version_present = RegDefault("Zenith/SysRegVer", buf, TRUE);
	RegExe("Zenith");
	if (registry_version != sys_os_version)
	{
		RegWrite("Zenith/SysRegVer", buf);
		RegExe("Zenith");
	}
}

#help_index "Boot/Once;Registry/Once"
#help_file "::/Doc/Once"

public U0 ZOnceFlush()
{//Flush ZOnce() buf.
	RegWrite("Once/Zenith", "");
}

public U0 OnceFlush()
{//Flush Once() buf.
	RegWrite("Once/User", "");
}

public U0 ZOnce(U8 *format, ...)
{//Add Zenith code to $LK,"~/Registry.CC"$, executed next boot.
	U8 *buf = StrPrintJoin(NULL, format, argc, argv);

	if (!Bt(&sys_run_level, RLf_ONCE_ZENITH))
		ZOnceFlush;
	RegAppend("Once/Zenith", "%s\n", buf);
	Free(buf);
}

public U0 Once(U8 *format, ...)
{//Add User code to $LK,"~/Registry.CC"$, executed next boot.
	U8 *buf = StrPrintJoin(NULL, format, argc, argv);

	if (!Bt(&sys_run_level, RLf_ONCE_USER))
		OnceFlush;
	RegAppend("Once/User", "%s\n", buf);
	Free(buf);
}

public U0 ZOnceDrive(U8 drv_let=0, U8 *format, ...)
{//Add Zenith code to drv $LK,"~/Registry.CC"$, executed next boot.
	U8 *buf = StrPrintJoin(NULL, format, argc, argv);
	I64 old_drive_let = *sys_registry_doc->filename.name;

	if (drv_let)
		*sys_registry_doc->filename.name = drv_let;
	if (!Bt(&sys_run_level, RLf_ONCE_ZENITH))
		ZOnceFlush;
	RegAppend("Once/Zenith", "%s\n", buf);
	Free(buf);
	*sys_registry_doc->filename.name = old_drive_let;
}

public U0 OnceDrive(U8 drv_let=0, U8 *format, ...)
{//Add User code to drv $LK,"~/Registry.CC"$, executed next boot.
	U8 *buf = StrPrintJoin(NULL, format, argc, argv);
	I64 old_drive_let = *sys_registry_doc->filename.name;

	if (drv_let)
		*sys_registry_doc->filename.name = drv_let;
	if (!Bt(&sys_run_level, RLf_ONCE_USER))
		OnceFlush;
	RegAppend("Once/User", "%s\n", buf);
	Free(buf);
	*sys_registry_doc->filename.name = old_drive_let;
}

public U0 OnceExe()
{//Execute Once code. Call goes in $LK,"~/Once.CC"$.
	try
	{

		RegDefault("Once/Zenith", "");
		if (RegCount("Once/Zenith") > 2)
		{
			Zenith("RegExe(\"Once/Zenith\");");
			ZOnceFlush;
		}
		LBts(&sys_run_level, RLf_ONCE_ZENITH);

		RegDefault("Once/User", "");
		if (RegCount("Once/User") > 2)
		{
			RegExe("Once/User");
			OnceFlush;
		}
		LBts(&sys_run_level, RLf_ONCE_USER);

	}
	catch
	{
		ZOnceFlush;
		LBts(&sys_run_level, RLf_ONCE_ZENITH);
		OnceFlush;
		LBts(&sys_run_level, RLf_ONCE_USER);
	}
}
