#help_index "AutoComplete"
#help_file "::/Doc/AutoComplete"
public extern CAutoCompleteGlobals ac;

#help_index "AutoComplete/Dictionary"
public extern CAutoCompleteDictGlobals acd;

#help_index "Bit"
public extern U8 *rev_bits_table;

#help_index "Boot"
#help_file "::/Doc/Boot"
public extern U0 Reboot(Bool format_ramdisks=FALSE);

#help_index "Call"
public argpop extern I64 CallStackGrow(I64 stack_size_threshold, I64 stack_size, /*argpop*/I64 (*fp_addr)(...), ...);
//fp_addr can have any fixed number of arguments.

#help_index "Call/FarCall32"
public _extern _FAR_CALL32	Bool FarCall32(U0 (*fp_addr)());//Not reentrant
public _extern C32_EAX		U32  c32_eax;
public _extern C32_EBX		U32  c32_ebx;
public _extern C32_ECX		U32  c32_ecx;
public _extern C32_EDI		U32  c32_edi;
public _extern C32_EDX		U32  c32_edx;
public _extern C32_EFLAGS	U32  c32_eflags;
public _extern C32_ESI		U32  c32_esi;

#help_index "Char/BitMaps"
public extern U32	char_bmp_alpha[16],					char_bmp_alpha_numeric[16],	char_bmp_alpha_numeric_no_at[16],
					char_bmp_word[16],
					char_bmp_dec_numeric[16],			char_bmp_hex_numeric[16],
					char_bmp_white_space[16],			char_bmp_non_eol_white_space[16], 
					char_bmp_zero_cr_nl_cursor[16],
					char_bmp_zero_tab_cr_nl_cursor[16],	char_bmp_zero_tab_cr_nl_cursor_dollar[16], 
					char_bmp_macro[16],
					char_bmp_printable[16],				char_bmp_displayable[16],	char_bmp_safe_dollar[16], 
					char_bmp_filename[16],
					char_bmp_non_eol[16];

#help_index "Char/Conversion"
public extern U8	*Char2KeyName( I64 ch, Bool include_ctrl=TRUE);
public extern I64	 Char2ScanCode(I64 ch, I64 sc_flags=0);
public extern U8	 ScanCode2Char(   I64 sc);
public extern U8	*ScanCode2KeyName(I64 sc);
public extern F64	 Str2F64(U8 *src, U8 **_end_ptr=NULL);
public extern I64	 Str2I64(U8 *st, I64 radix=10, U8 **_end_ptr=NULL);
public extern U8	*StrScan(U8 *src, U8 *format, ...);

#help_index "Char/Conversion;Time/Date/CDate;Date/CDate"
public extern CDate Str2Date(U8 *src);

#help_index "Char/Flags"
public extern U0  FlagsScan(U8 *_dst_flags, U8 *list, U8 *src);
public extern U8 *FlagsStrPrint(U8 *dst, U8 *list, I64 flags, Bool print_all=FALSE, I64 print_all_length=0);

#help_index "Char/Lists"
public extern I64 ListMatch(U8 *needle, U8 *haystack_list, I64 flags=0);
public extern U8 *ListSub(I64 sub, U8 *list);

#help_index "Char/Operations"
public extern					U8		*MStrPrint(U8 *format, ...);
public extern					U8		*MStrUtil(U8 *src, I64 flags, F64 indent_scale_factor=0);
public extern					U8		*ScaleIndent(U8 *src, F64 indent_scale_factor);
public extern					I64		 Spaces2Tabs(U8 *dst, U8 *src);
public _extern _STRCOMPARE		I64		 StrCompare(U8 *st1, U8 *st2);
public _extern _STRCOPY			U0		 StrCopy(U8 *dst, U8 *src);
public extern					U8		*StrFind(U8 *needle, U8 *haystack_str, I64 flags=0);
public extern					U8		*StrFirstOcc(   U8 *src, U8 *marker);
public extern					U8		*StrFirstRemove(U8 *src, U8 *marker, U8 *dst=NULL);
public _extern _STRICOMPARE		I64		 StrICompare(U8 *st1, U8 *st2);
public _extern _STRIMATCH		U8		*StrIMatch(U8 *needle, U8 *haystack_str);
public extern					U8		*StrLastOcc(U8 *src, U8 *marker);
public extern					U8		*StrReplace(U8 *str, U8 *old, U8 *new, I64 sff_flags=NONE, Bool free_str=FALSE);
public extern					U8		*StrLastRemove(U8 *src, U8 *marker, U8 *dst=NULL);
public _extern _STRMATCH		U8		*StrMatch(U8 *needle, U8 *haystack_str);
public _extern _STRNCOMPARE		I64		 StrNCompare( U8 *st1, U8 *st2, I64 n);
public _extern _STRNICOMPARE	I64		 StrNICompare(U8 *st1, U8 *st2, I64 n);
public extern					I64		 StrOcc(U8 *src, U8 ch);
public extern					U8		*StrPrint(    U8 *dst, U8 *format, ...);
public extern					U8		*StrPrintJoin(U8 *dst, U8 *format, I64 argc, I64 *argv);
public extern					U8		*StrUtil(U8 *_src, I64 flags);
public extern					U8		*Tabs2Spaces(U8 *src);
public extern					Bool	 WildMatch(U8 *test_str, U8 *wild_str);

#help_index "Char/Operations;Memory"
public extern U8 *CatPrint(U8 *dst, U8 *format, ...);

#help_index "Char/Operations;Memory/Zenith Heap"
public extern U8 *ZStrNew(U8 *buf);

#help_index "Char/Operations;Memory/Heap"
public extern U8 *StrNew(U8 *buf, CTask *mem_task=NULL);

#help_index "Char/Output;StdOut"
public extern	U0		 GetOutOfDollar();
public extern	Bool	 IsSilent();
public extern	U0		 Print(    U8 *format, ...);
public extern	U0		 PrintErr( U8 *format, ...);
public extern	U0		 PrintWarn(U8 *format, ...);
public extern	U0		 PutChars(U64 ch);
extern			U0		 PutHex(I64 num, I64 width);
public extern	U0		 PutKey(I64 ch=0, I64 sc=0);
extern			U0		 PutS(U8 *st); //Use $LK,"Print",A="MN:Print"$()
public extern	Bool	 Silent(Bool val=ON);
extern			U8		*StrPrintHex(U8 *dst, I64 num;I64 width);

#help_index "Char;Debugging/Raw Output;TextBase Layer/Char"
public extern CTextGlobals text;

#help_index "Compiler/Lex"
public extern U0 HashSrcFileSet(CCompCtrl *cc, CHashSrcSym *h, I64 line_num_offset=0);

#help_index "Compiler;Cmd Line (Typically)"
extern U8 *Load(U8 *filename, I64 ld_flags=0, CBinFile *bfh_addr=INVALID_PTR); //INVALID_PTR=don't care what load addr

#help_index "Data Types/Circular Queue"
public extern I64 		 QueueCount(CQueue *head);
public extern CQueue	*QueueCopy( CQueue *head, CTask *mem_task=NULL);
public extern U0		 QueueDel(  CQueue *head, Bool querem=FALSE);
public extern I64 		 QueueSize( CQueue *head);

#help_index "Data Types/Fifo"
public extern I64 		 FifoI64Count(CFifoI64 *f);
public extern U0		 FifoI64Del(  CFifoI64 *f);
public extern U0		 FifoI64Flush(CFifoI64 *f);
public extern Bool		 FifoI64Ins(  CFifoI64 *f, I64 q);
public extern CFifoI64	*FifoI64New(I64 size, CTask *mem_task=NULL);
public extern Bool		 FifoI64Peek(  CFifoI64 *f, I64 *_q);
public extern Bool		 FifoI64Remove(CFifoI64 *f, I64 *_q);
public extern I64 		 FifoU8Count( CFifoU8 *f);
public extern U0		 FifoU8Del(   CFifoU8 *f);
public extern U0		 FifoU8Flush( CFifoU8 *f);
public extern Bool		 FifoU8Insert(CFifoU8 *f, U8 b);
public extern CFifoU8 	*FifoU8New(I64 size, CTask *mem_task=NULL);
public extern Bool		 FifoU8Peek(  CFifoU8 *f, U8 *_b);
public extern Bool		 FifoU8Remove(CFifoU8 *f, U8 *_b);

#help_index "Data Types/Linked List"
public extern I64	 LinkedListCount(U8 **_list);
public extern U8	*LinkedListCopy( U8 **_list, CTask *mem_task=NULL);
public extern U0	 LinkedListDel(  U8 **_list);
public extern I64	 LinkedListSize( U8 **_list);

#help_index "Data Types/Queue Vector"
public extern U0			 QueueVectU8Del(CQueueVectU8 *v);
public extern I64			 QueueVectU8Get(CQueueVectU8 *v, I64 idx);
public extern CQueueVectU8	*QueueVectU8New(I64 min_idx=0);
public extern U0			 QueueVectU8Put(CQueueVectU8 *v, I64 idx, U8 ch);

#help_index "Debugging"
public extern U8			*Caller(I64 num=1);
public extern Bool			 CheckCodePtr(U8 *ptr);
public extern Bool			 CheckOnStack(U8 *ptr, CTask *task=NULL);
public extern Bool			 CheckPtr(    U8 *ptr);
public extern Bool			 IsSingleUser();
public extern Bool			 IsSysDebug();
public extern Bool			 SingleUser(Bool val);
public extern Bool			 SysDebug(  Bool val);
public extern U8			*TaskCaller( CTask *task=NULL, I64 num=0, Bool saved_context=FALSE);
public extern I64			 UnusedStack(CTask *task=NULL);
public extern CDebugGlobals	 debug;

#help_index "Debugging/Debugger"
public extern	Bool	 B(U8 *addr, CTask *task=NULL, Bool live=TRUE) //Toggle bpt.
public extern	I64		 B2(CTask *task=NULL, Bool live=TRUE);
extern			CBpt	*BptFind(U8 *needle_addr, CTask *haystack_task=NULL, Bool rem=FALSE);
public extern	Bool	 BptR(U8 *addr, CTask *task=NULL, Bool live=TRUE, Bool rem=TRUE);
public extern	Bool	 BptS(U8 *addr, CTask *task=NULL, Bool live=TRUE);
public extern	Bool	 DebugMode(Bool val);
public extern	Bool	 E(U8 *addr, I64 count=512, I64 edf_dof_flags=0);
public extern	Bool	 EdLite(U8 *filename, I64 num=1, I64 edf_dof_flags=0);
extern			Bool	 EdLiteFileLine(U8 *fl_file_line, I64 edf_dof_flags=0);
public extern	Bool	 Fix(I64 edf_dof_flags=0);
public extern	U0		 FixSet(U8 *filename, I64 line);
public extern	U0		 G( U8 *mouse=INVALID_PTR, CTask *task=NULL);
public extern	U0		 G2(U8 *mouse=INVALID_PTR, CTask *task=NULL);
public extern	Bool	 IsDebugMode();
public extern	U0		 S( U8 *mouse=INVALID_PTR, CTask *task=NULL);

#help_index "Debugging/Debugger;DolDoc/Cmd Line (Typically);Cmd Line (Typically);Help System"
public extern Bool Man(U8 *st, I64 edf_dof_flags=0);

#help_index "Debugging/Dump"
public extern	U0	 CallerRep(U8 **rbp=NULL, CTask *task=NULL);
public extern	U0	 D( U8  *addr, I64 count=0x80, Bool show_offset=TRUE);
public extern	U0	 Da(U8 **addr, I64 count=0x10);
public extern	U0	 Dm(U8  *addr, I64 count=0x80);
public extern	U0	 Dr(         CTask *task=NULL);
public extern	U0	 StackRep(   CTask *task=NULL);
extern			I64	*TaskRegAddr(CTask *task, I64 reg_num);

#help_index "Debugging/FunSeg"
#help_file "::/Doc/DebugFunSeg"
public extern Bool	 PutSrcLink( U8 *addr, I64 count=1, U8 *buf=NULL);
public extern U8	*SrcEdLink(  U8 *addr, I64 count=1, CTask *mem_task=NULL);
public extern U8	*SrcFileName(U8 *addr, I64 count=1, CTask *mem_task=NULL);
public extern I64	 SrcLineNum( U8 *addr, I64 count=1);

#help_index "Debugging/FunSeg;Hash/System"
public extern CHash *FunSegFind(U8 *addr, I64 *_offset);

#help_index "Debugging/Raw Output"
public extern	Bool	IsRaw();
public extern	Bool	Raw(Bool val);
public extern	U0		RawD( I64 mS=100, U8 *addr, I64 count=0x80);
public extern	U0		RawDm(I64 mS=100, U8 *addr, I64 count=0x80);
extern			U0		RawDr(CTask *task=NULL);
public extern	U0		RawPrint(I64 mS=100, U8 *format, ...);
public extern	U0		RawPutChar(I64 ch);
public extern	U0		LFBFlush();

#help_index "Debugging;Debugging/Debugger"
public extern U0 Debug(U8 *message=NULL, I64 message_num=0);
public extern U0 Panic(U8 *message=NULL, I64 message_num=0, Bool panic=TRUE);

#help_index "Define;Char/Define"
#help_file "::/Doc/Define"
public extern U8				*Define(     U8 *dname);
public extern CHashDefineStr	*DefineLoad( U8 *dname, U8 *st);
public extern U0				 DefinePrint(U8 *dname, U8 *src, ...);

#help_index "Define;Char/Define;Char/Lists"
public extern I64				 DefineCount(   U8 *dname);
public extern CHashDefineStr	*DefineListLoad(U8 *dname, U8 *list);
public extern I64				 DefineMatch(U8 *needle, U8 *haystack_list_dname, I64 flags=0);
public extern U8				*DefineSub(I64 sub, U8 *dname);

#help_index "Devices;Memory/Page Tables"
public extern U8			*Mem32DevAlloc(I64 size, I64 alignment);
public extern U0			 Mem32DevFree(U8 *base);
public extern U8			*Mem64DevAlloc(I64 *_pages1Gig);
public extern U0			 Mem64DevFree(U8 *base, I64 pages1Gig);
public extern CDevGlobals	 dev;

#help_index "DolDoc/Clip"
public extern CDoc *sys_clip_doc;

#help_index "DolDoc/Task;StdOut/Task"
#help_file "::/Doc/StdOutTask"
extern CDoc *(*fp_doc_put)(CTask *task=NULL);

#help_index "Exceptions"
public extern	U0		Break();
public extern	Bool	BreakLock(  CTask *task=NULL);
public extern	Bool	BreakUnlock(CTask *task=NULL);
public extern	U0		PutExcept(Bool catch_it=TRUE);
extern			U0		SysTry(U8 *start_label, U8 *skip_label);
extern			U0		SysUntry();
public extern	U0		throw(I64 ch=0, Bool no_log=FALSE);

#help_index "File/CD DVD"
public extern U0 DVDImageRead( U8 dvd_drive_let, U8 *out_name);
public extern U0 DVDImageWrite(U8 dvd_drive_let, U8 *in_name=NULL, I64 media_type=MT_DVD);

#help_index "File/CFile"
public extern Bool	 FBlkRead( CFile *f, U8 *buf, I64 blk=FFB_NEXT_BLK, I64 count=1);
public extern Bool	 FBlkWrite(CFile *f, U8 *buf, I64 blk=FFB_NEXT_BLK, I64 count=1);
public extern U0	 FClose(   CFile *f);
public extern CFile	*FOpen(U8 *filename, U8 *flags, I64 count=0);
public extern I64	 FSize(    CFile *f);

#help_index "File/Cmd Line (Typically);Cmd Line (Typically)"
public extern Bool	Cd(U8 *dirname=NULL, Bool make_dirs=FALSE);
public extern I64	Del(U8 *files_find_mask, Bool make_mask=FALSE, Bool del_dir=FALSE, Bool print_message=TRUE);
public extern I64	Dir(U8 *files_find_mask="*", Bool full=FALSE);
public extern Bool	DirMake(U8 *filename, I64 entry_count=0);
public extern Bool	Drive(     U8 drv_let);
public extern U0	DiskChange(U8 drv_let=0);
public extern U0	HomeSet(U8 *dirname);

#help_index "File/FileNames"
extern			CDirEntry	*Cd2DirEntry(CDirEntry *tmpde, U8 *abs_name);
public extern	U8			*DirCur(CTask *task=NULL, CTask *mem_task=NULL);
public extern	U8			*DirFile(   U8 *dirname, U8 *name=NULL, U8 *_extension=NULL);
public extern	U8			*DirNameAbs(U8 *dirname);
public extern	CBlkDev		*DriveIsWritable(U8 drv_let=0, Bool except=FALSE);
public extern	U8			*ExtChange( U8 *filename, U8 *extension);
public extern	U8			*ExtDefault(U8 *filename, U8 *extension);
public extern	U8			*FileExtDot(   U8 *src);
public extern	U8			*FileExtRemove(U8 *src, U8 *dst=NULL);
public extern	U8			*FileNameAbs(  U8 *filename, I64 fuf_flags=0);
public extern	Bool		 FileNameCheck(U8 *filename);
public extern	Bool		 FilesFindMatch(U8 *_test_name, U8 *files_find_mask, I64 fuf_flags=0);
public extern	Bool		 IsDir(U8 *dir_name);
public extern	Bool		 IsDotC(U8 *filename);
public extern	U0			 PutDirLink(U8 *dirname, U8 *full_name=NULL);
public extern	U0			 PutFileLink(U8 *filename, U8 *full_name=NULL, I64 line=0, Bool plain_text=FALSE);
public extern	U0			 ToFileLine(U8 *_fl_file_line, U8 **_filename, I64 *_linenum);

#help_index "File/FileNames;Misc"
public extern U8 *FileNameTmpTxt();

#help_index "File/Internal"
public extern	U0			 DirContextDel(CDirContext *dirc, Bool restore=TRUE);
public extern	CDirContext	*DirContextNew(U8 *mask, Bool make_mask=FALSE, Bool make_dirs=FALSE, Bool no_mask=FALSE);
public extern	Bool		 DirNew(CDrive *drive, U8 *cur_dir, CDirEntry *tmpde, Bool free_old_chain=TRUE);
extern			I64			 FileAttr(U8 *name, I64 old_attr=0);

#help_index "File/Low Level"
#help_file "::/Doc/FileLowLevel"
public extern	CBlkDev	*BlkDevCheck(CBlkDev *bd, Bool except=TRUE);
public extern	U0		 BlkDevDel(  CBlkDev *bd);
public extern	Bool	 BlkDevLock( CBlkDev *bd);
public extern	CBlkDev	*BlkDevNextFreeSlot(U8 first_drive_let, I64 type);
public extern	Bool	 BlkDevUnlock(CBlkDev *bd, Bool reset=FALSE);
public extern	U0		 BlkDevsRelease();
public extern	Bool	 BlkRead(     CDrive *drive, U8 *buf, I64 blk, I64 count);
public extern	Bool	 BlkWrite(    CDrive *drive, U8 *buf, I64 blk, I64 count);
public extern	U0		 BlkWriteZero(CDrive *drive, I64 blk, I64 count);
public extern	I64		 Clus2Blk(    CDrive *drive, I64 c);
public extern	I64		 ClusAlloc(   CDrive *drive, I64 c=0, I64 count=1, Bool contiguous=FALSE);
public extern	I64		 ClusBlkRead( CDrive *drive, U8 *buf, I64 c, I64 blks);
public extern	I64		 ClusBlkWrite(CDrive *drive, U8 *buf, I64 c, I64 blks);
public extern	I64		 ClusNumNext( CDrive *drive, I64 c, I64 count=1);
public extern	I64		 ClusRead(    CDrive *drive, U8 *buf, I64 c, I64 count);
public extern	I64		 ClusWrite(   CDrive *drive, U8 *buf, I64 c, I64 count);
extern			Bool	 CopySingle(U8 *f1, U8 *f2); //Just one file
public extern	U8		 Drive2Letter(CDrive *drive=NULL);
public extern	CDrive	*DriveCheck(  CDrive *drive, Bool except=TRUE);
public extern	U0		 DriveDel(    CDrive *drive);
public extern	Bool	 DriveLock(   CDrive *drive);
public extern	CDrive	*DriveMakeFreeSlot(U8 drv_let);
public extern	U8		*DriveModelNum(U8 drv_let=0);
public extern	U8		 DriveNextFreeLet(U8 first_drive_let='C');
public extern	U8		*DriveSerialNum(  U8 drv_let=0);
public extern	U8		 DriveTextAttrGet(U8 drv_let=0);
public extern	Bool	 DriveUnlock(CDrive *drive, Bool reset=FALSE);
public extern	U0		 DrivesRelease();
extern			U0		 FAT32FreeClus(CDrive *drive, I64 c);
public extern	CBlkDev	*Letter2BlkDev(    U8 drv_let=0, Bool except=TRUE);
public extern	I64		 Letter2BlkDevType(U8 drv_let);
public extern	CDrive	*Letter2Drive(     U8 drv_let=0, Bool except=TRUE);
public extern	U8		 Letter2Letter(    U8 drv_let=0);
extern			I64		 Name2DirClus(      CDrive *drive, U8 *dirname);
extern			I64		 Name2ParentDirClus(CDrive *drive, U8 *dirname);
extern			U0		 RedSeaFreeClus(    CDrive *drive, I64 c, I64 count);

#help_index "File/Program Routines"
public extern U0	 DirEntryDel( CDirEntry *tmpde);
public extern U0	 DirEntryDel2(CDirEntry *tmpde);
public extern U0	 DirTreeDel(  CDirEntry *tmpde);
public extern U0	 DirTreeDel2( CDirEntry *tmpde);
public extern Bool	 FileFind( U8 *filename, CDirEntry *_de=NULL, I64 fuf_flags=0);
public extern U8	*FileRead( U8 *filename, I64 *_size=NULL, I64 *_attr=NULL);
public extern I64	 FileWrite(U8 *filename, U8 *fbuf, I64 size, CDate cdt=0, I64 attr=0);

#help_index "File/Program Routines;File/FileNames"
public extern CDirEntry *FilesFind(U8 *files_find_mask, I64 fuf_flags=0);

#help_index "File/System"
public extern	CATARep			*ATAIDDrives(CATARep *head, CATARep **_ata_drive, CATARep **_atapi_drive);
extern			CBlkDev			*ATAMount(U8 first_drive_let, I64 type, I64 base0, I64 base1, I64 unit);
extern			Bool			 ATAPIStartStop(CBlkDev *bd, F64 timeout, Bool start);
extern			I64				 ATAProbe(I64 base0, I64 base1, I64 unit);
extern			U0				 ATAReadBlks( CBlkDev *bd, U8 *buf, I64 blk, I64 count);
extern			U0				 ATAWriteBlks(CBlkDev *bd, U8 *buf, I64 blk, I64 count);
extern			I64				 BlkDevAdd(   CBlkDev *bd, I64 prt_num=I64_MIN, Bool whole_drive, Bool make_free);
extern			U0				 DiskCacheInit(I64 size_in_U8s);
public extern	U0				 DiskCacheInvalidate(CDrive *drive);
public extern	I64				 MountIDEAuto();
public extern	CBlkDevGlobals	 blkdev;

#help_index "Graphics/Color"
extern			U0				(*fp_set_std_palette)();
public extern	U8				 *Color2Str(U8 *buf, CColorROPU32 c);
public extern	CColorROPU16	  Str2ColorU16(U8 *st);
public extern	CColorROPU32	  Str2ColorU32(U8 *st);

#help_index "Hash"
#help_file "::/Doc/Hash"
public _extern _HASH_ADD				U0			  HashAdd(     CHash *tmph,              CHashTable *table);
public _extern _HASH_ADD_AFTER			U0			  HashAddAfter(CHash *tmph, CHash *pred, CHashTable *table);
//Add hash entry after entry.
public _extern _HASH_BUCKET_FIND		CHash		**HashBucketFind(     U8 *needle_str, CHashTable *haystack_table);
public _extern _HASH_FIND				CHash		 *HashFind(           U8 *needle_str, CHashTable *haystack_table,
																		  I64 mask, I64 instance=1);
public _extern _HASH_SINGLE_TABLE_FIND	CHash		 *HashSingleTableFind(U8 *needle_str, CHashTable *haystack_table,
																		  I64 mask, I64 instance=1);
public _extern _HASH_STR				I64			  HashStr(U8 *st);
public extern							CHashTable	 *HashTableNew(I64 size, CTask *mem_task=NULL);

#help_index "Hash/Frame"
#help_file "::/Doc/Frame"
public extern I64			 FramePtr(U8 *name, CTask *task=NULL);
public extern CHashGeneric	*FramePtrAdd(U8 *name, I64 val=0, CTask *task=NULL);
public extern I64			 FramePtrDel(U8 *name, CTask *task=NULL);
public extern I64			 FramePtrSet(U8 *name, I64 val, CTask *task=NULL);

#help_index "Hash/System"
public extern					U0				HashDel(CHashSrcSym *tmph);
public extern					CHashGeneric	*HashGenericAdd(U8 *name, I64 type,
																I64 val=0, I64 u8=0, I64 u16=0, CTask *task=NULL);
public extern					CHashGeneric	*HashPublic(U8 *st, I64 mask, Bool val=TRUE);
public _extern _HASH_REM_DEL	Bool			HashRemDel(CHash *tmph, CHashTable *table, I64 instance=1);
//instance must match tmph's
public extern					U0				HashTableDel(  CHashTable *table);
public extern					I64				HashTablePurge(CHashTable *table);
public extern					I64				HashTypeNum(CHash *tmph);
public extern					I64				HashVal(    CHash *tmph);
extern							U0				SysSymImportsResolve(U8 *sptr, I64 ld_flags=0);

#help_index "Hash/System;Char/Lists"
public extern I64 HashListAdd(U8 *list, I64 type, CHashTable *table);

#help_index "Hash/System;Define;Char/Define;Char/Lists"
public extern I64 HashDefineListAdd(U8 *dname, I64 type, CHashTable *table);

#help_index "Help System;Debugging/Debugger"
public extern U0 Help();

#help_index "Info;File/Cmd Line (Typically);Cmd Line (Typically);Install"
public extern U0 DriveRep();

#help_index "Install"
#help_file "::/Doc/Install"
extern			CATARep	*ATARepFind(CATARep *haystack_head, I64 needle_num);
public extern	Bool	 DriveEnable(U8 drv_let, Bool val);

#help_index "Install;File/Cmd Line (Typically);Cmd Line (Typically);"
public extern U0 Format(U8 drv_let, Bool quick=TRUE, Bool confirm=TRUE, I64 type=FSt_FAT32);

#help_index "Install;Memory/BlkPool"
public extern I64 Scale2Mem(I64 min, I64 max, I64 limit=2*1024*1024*1024);

#help_index "Job/Exe;Task/Job/Exe"
public extern	U0		 ZenithErr( U8 *format, ...);
public extern	U0		 ZenithWarn(U8 *format, ...);
public extern	U0		 ZenithLog( U8 *format, ...);
public extern	I64		 ExeCmdLine(CCompCtrl *cc);
public extern	U0		 JobDel(CJob *tmpc);
public extern	I64		 JobsHandler(I64 run_flags, CTask *task=NULL);
extern			U0		 ServerCmdLine();
public extern	U0		 ServerTaskCont();
public extern	CJob	*TaskExe(CTask *server, CTask *master, U8 *data, I64 flags);
public extern	U0		 TaskResetAwaitingMessage(CTask *task=NULL);
public extern	U0		 UserTaskCont();

#help_index "Job/Exe;Task/Job/Exe;Compiler"
public extern I64 Zenith(U8 *format, ...);
public extern I64 PopUp(U8 *buf, CTask *parent=NULL, CTask **_pu_task=NULL);
public extern I64 PopUpPrint(U8 *format, ...);

#help_index "Job/Exe;Task/Job/Exe;MultiCore"
public extern I64  JobResGet( CJob *request=NULL);
public extern Bool JobResScan(CJob *request=NULL, I64 *_res=NULL);

#help_index "Job/Text & Messages;Task/Job/Text & Messages"
public extern CJob *TaskText(CTask *server, CTask *master, U8 *data, I64 flags);

#help_index "Job/Text & Messages;Task/Job/Text & Messages;InFile;StdIn/InFile"
public extern U0 In(U8 *format, ...);
public extern U0 InFile(U8 *filename);
public extern U0 InStr(U8 *format, ...);
public extern U0 XTalk(       CTask *task, U8 *format, ...);
public extern U0 XTalkStr(    CTask *task, U8 *format, ...);
public extern U0 XTalkStrWait(CTask *task, U8 *format, ...);
public extern U0 XTalkWait(   CTask *task, U8 *format, ...);

#help_index "Job/Text & Messages;Task/Job/Text & Messages;Messages"
public extern U0	 Message(I64 message_code, I64 arg1, I64 arg2, I64 flags=0);
public extern U0	 MessagePost(    CTask *task, I64 message_code, I64 arg1, I64 arg2, I64 flags=0);
public extern U0	 MessagePostWait(CTask *task, I64 message_code, I64 arg1, I64 arg2, I64 flags=0);
public extern CJob	*TaskMessage(CTask *server, CTask *master, I64 message_code, I64 arg1, I64 arg2, I64 flags);

#help_index "Job;Task/Job"
#help_file "::/Doc/Job"

#help_index "Keyboard Devices/System;Char/System"
#help_file "::/Doc/KeyDev"
public extern	U0				 CtrlAltCBSet(U8 ch, U0 (*fp_handler)(I64 sc), 
											  U8 *no_shift_desc=NULL, U8 *shift_desc=NULL, Bool in_irq=FALSE);
public extern	U0				 KeyDescSet(U8 *format, ...);
public extern	CKeyDevEntry	*KeyDevAdd(Bool (*fp_put_key)(I64 ch, I64 sc), Bool (*fp_puts)(U8 *st),
										   I64 priority, Bool key_descs=FALSE);
public extern	U0				 KeyDevRemove(CKeyDevEntry *tmpk);
extern			CKeyDevGlobals	 keydev;
extern			CJob			 sys_macro_head;
extern			CTask			*sys_macro_task;

#help_index "Keyboard Devices;Char/Input;StdIn"
extern			U8 *(*fp_getstr2)(I64 flags=0); //StrGet $LK,"Flags",A="MN:SGF_SHIFT_ESC_EXIT"$
public extern	Bool				 AreYouSure();
public extern	I64					 CharGet(I64 *_scan_code=NULL, Bool echo=TRUE,  Bool raw_cursor=FALSE);
public extern	I64					 KeyGet( I64 *_scan_code=NULL, Bool echo=FALSE, Bool raw_cursor=FALSE);
public extern	I64					 StrNGet(U8 *buf, I64 size, Bool allow_ext=TRUE);
public extern	U8					*StrGet(U8 *message=NULL, U8 *default=NULL, I64 flags=0);
extern			U0					 KbdInit();
public extern	I64					 KbdMouseEventTime();
extern			U0					 KbdMouseHandler(Bool poll_kbd, Bool poll_mouse);
extern			U0					 KbdMouseInit();
extern			I64					 KbdMessagesQueue();
public extern	U0					 KbdTypeMatic(U8 delay);
extern			Bool				 MouseHardDriverInstall();
public extern	Bool				 MouseHardEnable(Bool val=TRUE);
public extern	I64					 PressAKey();
public extern	I64					 CharScan();
public extern	Bool				 KeyScan(I64 *_ch=NULL, I64 *_scan_code=NULL, Bool echo=FALSE);
public extern	Bool				 YorN();
public extern	CKbdStateGlobals	 kbd;

#help_index "Math"
public extern I64 CeilI64(I64 num, I64 to);
public extern U64 CeilU64(U64 num, U64 to);
public extern F64 Clamp(F64 d, F64 lo, F64 hi);
public extern I64 FloorI64(I64 num, I64 to);
public extern U64 FloorU64(U64 num, U64 to);
public extern F64 Max(F64 n1, F64 n2);
public extern F64 Min(F64 n1, F64 n2);
public extern F64 Pow10I64(I64 i);
public extern F64 Rand(); //With timestamp
public extern U8  RandU8();
public extern I16 RandI16();
public extern I32 RandI32();
public extern I64 RandI64();
public extern U16 RandU16();
public extern U32 RandU32();
public extern U64 RandU64();
public extern I64 RoundI64(I64 num, I64 to);
public extern I64 Seed(I64 seed=0, CTask *task=NULL);

#help_index "Memory/Info"
public extern I64 MemBIOSTotal();

#help_index "Memory/Zenith Heap"
public extern U8 *ZCAlloc(I64 size);
public extern U8 *ZMAlloc(I64 size);
public extern U8 *ZMAllocIdent(U8 *src);
public extern U8 *ZReAlloc(    U8 *src, U64 size);

#help_index "Memory/BlkPool"
public extern U0  BlkPoolAdd( CBlkPool *bp, CMemBlk *m, I64 pags);
public extern U0  BlkPoolInit(CBlkPool *bp, I64 pags);
public extern U8 *MemPagAlloc(I64 pags,  CBlkPool *bp=NULL);
public extern U0  MemPagFree(CMemBlk *m, CBlkPool *bp=NULL);

#help_index "Memory/Heap"
public extern				U8			*CAlloc(       I64 size,                CTask *mem_task=NULL);
public extern				U8			*CAllocAligned(I64 size, I64 alignment, CTask *mem_task=NULL, I64 misalignment=0);
public _extern _FREE		U0			 Free(U8 *addr);
public _extern _MALLOC		U8			*MAlloc(       I64 size,                CTask *mem_task=NULL);
public extern				U8			*MAllocAligned(I64 size, I64 alignment, CTask *mem_task=NULL, I64 misalignment=0);
public extern				U8			*MAllocIdent(U8 *src,                   CTask *mem_task=NULL);
public extern				U8			*ReAlloc(    U8 *src, U64 size,         CTask *mem_task=NULL);
public _extern _MHEAP_CTRL	CHeapCtrl	*MHeapCtrl(  U8 *src);
public _extern _MSIZE		I64			 MSize(      U8 *src); 	//size of heap object
public _extern _MSIZE2		I64			 MSize2(     U8 *src); //Internal size

#help_index "Memory/HeapCtrl"
public extern U0		 HeapCtrlDel( CHeapCtrl *hc);
public extern CHeapCtrl	*HeapCtrlInit(CHeapCtrl *hc=NULL, CTask *task=NULL, CBlkPool *bp);

#help_index "Memory/Segmentation"
public extern U8 *Seg2Linear(U32 *ptr);

#help_index "Memory/Page Tables"
public extern I64 *MemPageTable(U8 *a);

#help_index "Messages"
#help_file "::/Doc/Messages"
public extern	I64	FlushMessages(CTask *task=NULL);
public extern	I64	MessageGet( I64 *_arg1=NULL, I64 *_arg2=NULL, I64 mask=~1, CTask *task=NULL);
extern			U0	InputFilterTask();
public extern	I64	MessageScan(I64 *_arg1=NULL, I64 *_arg2=NULL, I64 mask=~1, CTask *task=NULL);

#help_index "Misc"
public extern U0	QuickSort(   U8  *base, I64 num, I64 width, I64 (*fp_compare)(U8 *e1, U8 *e2));
public extern U0	QuickSortI64(I64 *base, I64 num,            I64 (*fp_compare)(I64 e1, I64 e2));
public extern F64	sys_os_version;

#help_index "Misc/Progress Bars"
public extern U0 ProgressBarsReset(U8 *path=NULL);

#help_index "Mouse"
#help_file "::/Doc/Mouse"
public extern	U0						GridInit();
public extern	U0						MouseSet(I64 x=I64_MAX, I64 y=I64_MAX, I64 z=I64_MAX, I64 l=I64_MAX, I64 r=I64_MAX);
public extern	CMouseStateGlobals		mouse;
public extern	CGridGlobals			mouse_grid;
public extern	CMouseHardStateGlobals	mouse_hard;
extern			CMouseHardStateGlobals	mouse_hard_last;
extern			CMouseStateGlobals		mouse_last;

#help_index "Mouse/Ptr"
extern U0 MouseInit();
extern U0 MouseUpdate(I64 x, I64 y, I64 z, Bool l, Bool r);

#help_index "MultiCore"
extern			U0		 Core0StartMP();
extern			U0		 CoreAPSethTask();
public extern	U0		 MPInt(U8 num, I64 cpu_num=1);
public extern	U0		 MPIntAll(U8 num);
public extern	U0		 MPNMInt();
extern			CTask	*SpawnQueue(U0 (*fp_addr)(U8 *data), U8 *data=NULL, U8 *task_name=NULL, I64 target_cpu, 
									CTask *parent=NULL, //NULL means zenith
									I64 stack_size=0, I64 flags=1<<JOBf_ADD_TO_QUE);

#help_index "MultiCore;Boot"
public extern U0 MPHalt();

#help_index "MultiCore;Job/Exe;Task/Job/Exe"
public extern CJob *JobQueue(I64 (*fp_addr)(U8 *data), U8 *data=NULL, I64 target_cpu=1, I64 flags=1<<JOBf_FREE_ON_COMPLETE, 
							 I64 job_code=JOBT_CALL, U8 *aux_str=NULL, I64 aux1=0, I64 aux2=0);

#help_index "PCI"
public extern							I64	PCIClassFind(I64 class_code, I64 n);
public extern							U16	PCIReadU16( I64 bus, I64 dev, I64 fun, I64 rg);
public extern							U32	PCIReadU32( I64 bus, I64 dev, I64 fun, I64 rg);
public extern							U8	PCIReadU8(  I64 bus, I64 dev, I64 fun, I64 rg);
public extern							U0	PCIWriteU16(I64 bus, I64 dev, I64 fun, I64 rg, I64 val);
public extern							U0	PCIWriteU32(I64 bus, I64 dev, I64 fun, I64 rg, I64 val);
public extern							U0	PCIWriteU8( I64 bus, I64 dev, I64 fun, I64 rg, I64 val);
public _extern SYS_PCIBIOS_SERVICE_DIR	U32	sys_PCIBIOS_service_dir;//Far call routine in the BIOS
public _extern SYS_PCI_SERVICES			U32	sys_pci_services;//Far call routine in the BIOS

#help_index "PCI;Info;File/System;Devices"
public extern I64 ATARep(Bool prompt=TRUE, Bool just_ide=FALSE, CATARep **_head=NULL);

#help_index "Processor"
public extern U8 *IntEntryGet(I64 irq);
public extern U8 *IntEntrySet(I64 irq, U0 (*fp_new_handler)(), I64 type=IDTET_IRQ);

#help_index "ScreenCast;Cmd Line (Typically)"
public extern Bool					ScreenCast(Bool val=ON, Bool just_audio=FALSE, U8 *print_format="B:/Tmp/%X.GR")
public extern CScreenCastGlobals	screencast;

#help_index "Sound"
#help_file "::/Doc/Sound"
public extern U0	Beep(I8 ona=62, Bool busy=FALSE);
public extern I8	Freq2Ona(F64 freq);
public extern Bool	IsMute();
public extern Bool	Mute(Bool val);
public extern F64	Ona2Freq(I64 ona);
public extern U0	Sound(I8 ona=0);
public extern U0	SoundReset();

#help_index "StdIn"
#help_file "::/Doc/Streams"

#help_index "StdOut"
#help_file "::/Doc/Streams"

#help_index "Task"
public extern					I64		BirthWait(CTask **_task, I64 task_num=-1);
public extern					U0		DeathWait(CTask **_task, Bool send_exit=FALSE);
public extern					U0		Exit();
public extern					Bool	IsSuspended(CTask *task=NULL);
public extern					Bool	Kill(       CTask *task, Bool wait=TRUE, Bool just_break=FALSE);
public extern					Bool	Suspend(    CTask *task=NULL, Bool state=TRUE);
_extern _TASK_CONTEXT_RESTORE	U0		TaskContextRestore();
_extern _TASK_END_NOW			U0		TaskEndNow();
extern							U0		TaskKillDying();
public extern					U0		TaskQueueIns(   CTask *task, CTask *pred=NULL);
public extern					U0		TaskQueueRemove(CTask *task);
public extern					Bool	TaskValidate(   CTask *task);
public extern					U0		TaskWait(       CTask *task=NULL, Bool cmd_line_prompt=FALSE);
public extern					CTask	*User(U8 *format=NULL, ...);
public extern					U0		UserCmdLine();
public _extern _YIELD			U0		Yield();
public extern					CTask	*zenith_task;
public extern					I64		sys_num_spawned_tasks;
extern							CTask	*sys_winmgr_task, *sys_task_being_screen_updated;

#help_index "Task/Delay;Time/CPU Cycles"
public extern	U0	Busy(I64 æS); //Loosely timed
public extern	U0	PortNop(); //On the order of 1uS
extern			I64	TimeCal();

#help_index "Task/Delay;Time/Jiffies"
public extern U0 Sleep(I64 mS);
public extern U0 SleepUntil(I64 wake_jiffy);

#help_index "Task/Misc"
extern			U0 (*fp_update_ctrls)(CTask *task);
public extern	U0   TSSBusy(I64 tr, Bool val=OFF);
public extern	U0   TaskDerivedValsUpdate(CTask *task=NULL, Bool update_z_buf=TRUE);
public extern	U0   WinDerivedValsUpdate( CTask *task);

#help_index "Task;Job/Exe;Task/Job/Exe;MultiCore"
public extern CTask *Spawn(U0 (*fp_addr)(U8 *data), U8 *data=NULL, 
						   U8 *task_name=NULL, I64 target_cpu=-1, 	//-1 means current CPU
						   CTask *parent=NULL, //NULL means zenith
						   I64 stack_size=0, I64 flags=1<<JOBf_ADD_TO_QUE);

#help_index "Time/CPU Cycles;Time/Jiffies"
public extern CCountsGlobals counts;

#help_index "Time/Date/CDate;Date/CDate"
#help_file "::/Doc/TimeDate"
public extern	U0		 Date2Struct(CDateStruct *_ds, CDate cdt);
extern			U8		*MPrintDate(CDate cdt);
extern			U8		*MPrintTime(CDate cdt);
public extern	CDate	 Now();
public extern	CDate	 Struct2Date(CDateStruct *_ds);
public extern	CDate	 local_time_offset;

#help_index "Time/Date/CMOS;Date/CMOS"
public extern U8	CMOSRegRead( I64 register);
public extern U0	CMOSRegWrite(I64 register, I64 val);
public extern Bool	CMOSIsBcd();
public extern U0	TimeSet(CDateStruct *ds);

#help_index "Time/Date;Date"
#help_file "::/Doc/Date"
public extern I64 DayOfWeek(     I64 i);
public extern I64 FirstDayOfMon( I64 i);
public extern I64 FirstDayOfYear(I64 i);
public extern I64 LastDayOfMon(  I64 i);
public extern I64 LastDayOfYear( I64 i);
public extern I64 YearStartDate(I64 year);
public extern U16 month_start_days[12];
public extern U16 month_start_days_leap[12];

#help_index "Time/Jiffies"
#help_file "::/Doc/TimeJiffy"
public extern I64 SysTimerRead();//18.33333*65536Hz (SYS_TIMER_FREQ)

#help_index "Time/Seconds"
public extern Bool	Blink(F64 Hz=2.5);
public extern F64	tS(); //From SysTimerFreq.

#help_index "Windows"
public extern Bool WinInside(I64 x, I64 y, CTask *task=NULL, I64 border=0);

#help_index ""