import U8			*Doc2PlainText(CDoc *doc, CDocEntry *doc_e);
import U0			 DocBinsValidate(CDoc *doc);
import U0			 DocDel(CDoc *doc);
import U0			 DocLoad(CDoc *doc, U8 *src2, I64 size);
import CDoc			*DocNew(U8 *filename=NULL, CTask *task=NULL);
import CDocEntry	*DocPrint(CDoc *doc=NULL, U8 *format, ...);
import CDocEntry	*DocPutLine(CDoc *doc, CDocEntry *doc_e);
import I64			 DocSize(CDoc *doc);
import Bool			 DocWrite(CDoc *doc, Bool prompt=FALSE);
extern U8  *CmdLinePrompt();
extern I64  HashEntrySize2(CHashSrcSym *tmph);
extern Bool	IsLexExpression2Bin(CCompCtrl *cc, U8 **_machine_code);
extern I64	Lex(CCompCtrl *cc);
extern I64	LexExpression(CCompCtrl *cc);
extern I64	LexCharGet(CCompCtrl *cc);
extern CCodeMisc			*OptLabelFwd(CCodeMisc *lb);
extern CIntermediateCode	*OptPass012(CCompCtrl *cc);
extern U0					 OptPass3(CCompCtrl *cc, COptReg *reg_offsets);
extern U0					 OptPass4(CCompCtrl *cc, COptReg *reg_offsets, I64 *_type);
extern U0					 OptPass5(CCompCtrl *cc);
extern U0					 OptPass6(CCompCtrl *cc);
extern I64					 OptPass789A(CCompCtrl *cc, COptReg *reg_offsets, U8 *buf, CDebugInfo **_debug);
extern CHashClass	*ParseClass(CCompCtrl *cc, I64 keyword, I64 fsp_flags, Bool is_extern);
extern CHashFun		*ParseFunJoin(CCompCtrl *cc, CHashClass *tmp_return, U8 *name, I64 fsp_flags);
extern I64			 ParseKeyWord(CCompCtrl *cc);
extern Bool			 ParseStatement(CCompCtrl *cc, I64 try_count=0, CCodeMisc *lb_break=NULL, I64 comp_flags=CMPF_PRS_SEMICOLON);
extern U0			 ParseStreamBlk(CCompCtrl *cc);
extern CHashClass	*ParseType(CCompCtrl *cc, CHashClass **_tmpc1,
							   I64 *_mode, CMemberList *tmpm, U8 **_ident, CHashFun **_fun_ptr,
							   CHashExport **_tmpex, CArrayDim *tmpad, I64 fsp_flags);
extern I64			 ParseUnaryModifier(CCompCtrl *cc, CParseStack *ps,
									   CMemberList **_local_var, CArrayDim **_tmpad, I64 *unary_post_prec);
extern I64			 ParseUnaryTerm(CCompCtrl *cc, CParseStack *ps, CMemberList **_local_var, CArrayDim **_tmpad,
								   I64 *max_prec, I64 *unary_pre_prec, I64 *paren_prec);
extern U0			 ParseVarInit2(CCompCtrl *cc, U8 **_dst, CHashClass *tmpc,
								  CArrayDim *tmpad, U8 *data_addr_rip, U8 **_base, Bool data_heap, I64 pass);
_extern CMP_TEMPLATES 				U32 comp_templates[1];
_extern CMP_TEMPLATES_DONT_POP		U32 comp_templates_dont_pop[1];
_extern CMP_TEMPLATES_DONT_PUSH2	U32 comp_templates_dont_push2[1];
_extern CMP_TEMPLATES_DONT_PUSH 	U32 comp_templates_dont_push[1];
_extern CMP_TEMPLATES_DONT_PUSH_POP U32 comp_templates_dont_push_pop[1];
