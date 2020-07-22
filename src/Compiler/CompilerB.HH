#help_index "Compiler"
extern U0 CInit(Bool first);
public extern I64	ExeFile(U8 *name, I64 ccf_flags=0);
public extern I64	ExeFile2(U8 *name, I64 ccf_flags=0);
public extern I64	ExePrint(U8 *format, ...);
public extern I64	ExePrint2(U8 *format, ...);
public extern I64	ExePutS(U8 *buf, U8 *filename=NULL, I64 ccf_flags=0, CLexHashTableContext *htc=NULL);
public extern I64	ExePutS2(U8 *buf, U8 *filename=NULL, I64 ccf_flags=0);
public _extern _LAST_FUN I64 LastFun(I64 argc, I64 *argv);
public extern I64	RunFile(U8 *name, I64 ccf_flags=0, ...);
public extern I64	RunFile2(U8 *name, I64 ccf_flags=0, ...);
public extern CCompGlobals cmp;

#help_index "Compiler/Directive"
#help_file "::/Doc/Directives"
public extern Bool	Echo(Bool val);
public extern Bool	OptionGet(I64 num);
public extern I64	PassTrace(I64 i=0b1001111101);
       extern U0 StreamDir();
public extern I64	StreamExePrint(U8 *format, ...);
public extern U0	StreamPrint(U8 *format, ...);
public extern Bool	Trace(Bool val=ON);

#help_index "Compiler/Lex"
#help_file "::/Doc/Lex"
extern U0 ClassMemberListDel(CHashClass *c);
public extern U0		 CompCtrlDel(CCompCtrl *cc);
public extern CCompCtrl *CompCtrlNew(U8 *buf=NULL, I64 flags=0, U8 *filename=NULL);
public extern I64		 CompCtrlSize(CCompCtrl *cc);
public extern I64		 IsLexExpression2Bin(CCompCtrl *cc, U8 **machine_code); //FALSE=no error
public extern I64		 Lex(CCompCtrl *cc);
public extern U0		 LexAttachDoc(CCompCtrl *cc, CLexFile *tmpf=NULL, CDoc *doc=NULL,
							U8 *abs_filename=NULL, CDocEntry *doc_e=NULL, I64 col=0);
public extern CD2I32	*LexD2I32(CCompCtrl *cc, CD2I32 *p);
public extern CD3I32	*LexD3I32(CCompCtrl *cc, CD3I32 *p);
public extern U0		 LexExcept(CCompCtrl *cc, U8 *str=NULL);
public extern I64		 LexExpression(CCompCtrl *cc);
public extern U8		*LexExpression2Bin(CCompCtrl *cc, I64 *_type=NULL);
public extern F64		 LexExpressionF64(CCompCtrl *cc);
public extern I64		 LexExpressionI64(CCompCtrl *cc);
public extern U8		*LexExtStr(CCompCtrl *cc, I64 *_size=NULL, Bool lex_next=TRUE);
public extern U8		*LexFirstRemove(CCompCtrl *cc, U8 *marker, I64 _len=NULL);
public extern I64		 LexCharGet(CCompCtrl *cc);
public extern U0		 LexPopNoRestore(CCompCtrl *cc);
public extern U0		 LexPopRestore(CCompCtrl *cc);
public extern U0		 LexPush(CCompCtrl *cc);
public extern U0		 LexPutLine(CCompCtrl *cc, U8 *start);
public extern U0		 LexPutPos(CCompCtrl *cc);
public extern U0		 LexPutToken(CCompCtrl *cc);
public extern U0		 LexSkipEol(CCompCtrl *cc);
public extern U8		*LexStatement2Bin(CCompCtrl *cc, I64 *_type, I64 comp_flags=CMPF_PRS_SEMICOLON);
public extern U0		 LexWarn(CCompCtrl *cc, U8 *str=NULL);
	   extern CMemberList		*MemberClassBaseFind(CHashClass *needle_class, CHashClass *haystack_class);
public extern CMemberList		*MemberFind(U8 *needle_str, CHashClass *haystack_class);
extern U0 MemberListDel(CMemberList *tmpm);
public extern I64				 MemberMetaData(U8 *st, CMemberList *ml);
public extern CMemberListMeta	*MemberMetaFind(U8 *st, CMemberList *ml);
public extern CHashClass		*OptClassFwd(CHashClass *tmpc);
public extern I64				 ParseKeyWord(CCompCtrl *cc);

#help_index "Compiler;Cmd Line (Typically)"
       extern I64	Comp(U8 *filename, U8 *map_name=NULL, U8 *out_name=NULL, U8 mapfile_drive_let=0);

#help_index "Debugging/Unassemble"
public extern U8	*U(U8 *rip, I64 count=20, I64 seg_size=64);
public extern U0	 Ui(U8 *buf, U8 **_rip, I64 seg_size=64, I64 *_jmp_dst=NULL, Bool just_ins=FALSE);
public extern I64	 Un(U8 *rip, I64 count=0x80, I64 seg_size=64);
extern CUAsmGlobals uasm;

#help_index "Hash/System"
public extern I64 HashEntrySize(CHashSrcSym *tmph);
public extern I64 HashEntrySize2(CHashSrcSym *tmph);
public extern I64 HashTableSize2(CHashTable *table);
