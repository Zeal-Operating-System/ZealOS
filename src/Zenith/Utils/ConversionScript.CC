U0 Cvt(U8 *ff_mask="*", U8 *fu_flags="+r+l-i+S")
{
	FR(".HC", ".CC", ff_mask);
	
	Find("MemCpy",			ff_mask, fu_flags, "MemCopy");
	Find("MemCmp", 			ff_mask, fu_flags, "MemCompare");
	Find("StrCpy", 			ff_mask, fu_flags, "StrCopy");
	Find("StrCmp", 			ff_mask, fu_flags, "StrCompare");
	Find("StrICmp", 		ff_mask, fu_flags, "StrICompare");
	Find("StrNCmp", 		ff_mask, fu_flags, "StrNCompare");
	Find("StrNICmp", 		ff_mask, fu_flags, "StrNICompare");
	Find("BEqu", 			ff_mask, fu_flags, "BEqual");
	Find("LBEqu", 			ff_mask, fu_flags, "LBEqual");
	Find("ms", 				ff_mask, fu_flags, "mouse");
	Find("Snd", 			ff_mask, fu_flags, "Sound");
	Find("SndTaskEndCB",	ff_mask, fu_flags, "SoundTaskEndCB");
	Find("mp_cnt", 			ff_mask, fu_flags, "mp_count");
	Find("QueIns", 			ff_mask, fu_flags, "QueueInsert");
	Find("QueInit", 		ff_mask, fu_flags, "QueueInit");
	Find("QueRem", 			ff_mask, fu_flags, "QueueRemove");
	Find("QueDel", 			ff_mask, fu_flags, "QueueDel");
	Find("MsSet", 			ff_mask, fu_flags, "MouseSet");
	Find("UnusedStk",		ff_mask, fu_flags, "UnusedStack");
	Find("word_lst", 		ff_mask, fu_flags, "word_list");
	Find("FileExtRem",		ff_mask, fu_flags, "FileExtRemove");
	Find("cnts", 			ff_mask, fu_flags, "counts");
	Find("PostMsg", 		ff_mask, fu_flags, "PostMessage");
	Find("PostMsgWait", 	ff_mask, fu_flags, "PostMessageWait");
	Find("QSort", 			ff_mask, fu_flags, "QuickSort");
	Find("QSortI64", 		ff_mask, fu_flags, "QuickSortI64");
	Find("ScanMsg", 		ff_mask, fu_flags, "ScanMessage");
	Find("cnts", 			ff_mask, fu_flags, "counts");
	Find("Dsk",				ff_mask, fu_flags, "Disk");
	Find("collision_cnt",	ff_mask, fu_flags, "collision_count");
	Find("Drv", 			ff_mask, fu_flags, "Drive");
	Find("DrvRep",			ff_mask, fu_flags, "DriveRep");
	Find("Drv2Let",			ff_mask, fu_flags, "Drive2Letter");
	Find("LstSub",			ff_mask, fu_flags, "ListSub");
	Find("LstMatch",		ff_mask, fu_flags, "ListMatch");
	Find("DefineLstLoad",	ff_mask, fu_flags, "DefineListLoad");
	Find("ExtDft",			ff_mask, fu_flags, "ExtDefault");
	Find("RegDft",			ff_mask, fu_flags, "RegDefault");
	Find("\"HC\"",			ff_mask, fu_flags, "FEXT_DEFAULT_C");
	Find("CDrv",			ff_mask, fu_flags, "CDrive");
	Find("CDbgInfo",		ff_mask, fu_flags, "CDebugInfo");
	Find("dbg_info",		ff_mask, fu_flags, "debug_info");
	Find("StrFirstRem",		ff_mask, fu_flags, "StrFirstRemove");
	Find("StrLastRem",		ff_mask, fu_flags, "StrLastRemove");
	Find("TempleOS/Apps",	ff_mask, fu_flags, "/Apps");
	Find("adam_task",		ff_mask, fu_flags, "zenith_task");
	Find("JobQue",			ff_mask, fu_flags, "JobQueue");
	Find("MSG_",			ff_mask, CatPrint(fu_flags, "-l"), "MESSAGE_");
	Find(".HC",				ff_mask, fu_flags, ".CC");
	CatPrint(fu_flags, "+l");
	Find("Msg",				ff_mask, fu_flags, "Message");
	Find("MusicSettingsRst",ff_mask, fu_flags, "MusicSettingsReset");
	Find("hndlr",			ff_mask, fu_flags, "handler");


	"\n$$BK,1$$$$LTRED$$Might want to go over these$$FG$$$$BK,0$$\n";
	Find("MemSet", ff_mask, fu_flags);
}

//Cvt("Sup1/*");
