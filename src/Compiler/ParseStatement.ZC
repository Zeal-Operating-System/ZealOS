CHashClass *ParseClass(CCompCtrl *cc, I64 keyword, I64 fsp_flags, Bool is_extern)
{
	CHashClass *tmpc, *base_class;

	if (cc->token != TK_IDENT)
		LexExcept(cc, "Expecting identifier at ");
	if (is_extern)
	{
		tmpc = ParseClassNew;
		tmpc->str = cc->cur_str;
		cc->cur_str = NULL;
		HashAdd(tmpc, cc->htc.global_hash_table);
		LBts(&tmpc->flags, Cf_EXTERN);
		HashSrcFileSet(cc, tmpc);
		Lex(cc);
	}
	else
	{
		if (cc->flags & CCF_AOT_COMPILE)
			tmpc = HashFind(cc->cur_str, cc->htc.global_hash_table, HTT_CLASS);
		else
			tmpc = HashSingleTableFind(cc->cur_str, cc->htc.global_hash_table, HTT_CLASS);
		if (tmpc)
		{
			if (!Bt(&tmpc->flags, Cf_EXTERN))
				tmpc = NULL;
			else if (tmpc->use_count < 3)
				UnusedExternWarning(cc, tmpc);
		}
		if (tmpc)
		{
			Free(tmpc->src_link);
			tmpc->src_link = NULL;
			Free(tmpc->idx);
			tmpc->idx = NULL;
		}
		else
		{
			tmpc = ParseClassNew;
			tmpc->str = cc->cur_str;
			cc->cur_str = NULL;
			HashAdd(tmpc, cc->htc.global_hash_table);
		}
		LBtr(&tmpc->flags, Cf_EXTERN);
		if (fsp_flags & FSF_PUBLIC)
			tmpc->type |= HTF_PUBLIC;
		tmpc->use_count = 0;
		if (cc->last_U16 == '\n')
			HashSrcFileSet(cc, tmpc, -1);
		else
			HashSrcFileSet(cc, tmpc,0);
		if (Lex(cc) == ':')
		{
			if (Lex(cc) != TK_IDENT || !(base_class = cc->hash_entry) || !(base_class->type & HTT_CLASS))
				LexExcept(cc, "Invalid class at ");
			if (Lex(cc) == ',')
				LexExcept(cc, "Only one base class allowed at this time at ");
			tmpc->base_class = base_class;
			tmpc->size += base_class->size;
		}
		if (keyword == KW_UNION)
			ParseVarList(cc, tmpc, PRS0_NULL | PRS1_CLASS | PRSF_UNION);
		else
			ParseVarList(cc, tmpc, PRS0_NULL | PRS1_CLASS);
		tmpc->size += tmpc->neg_offset;
	}
	return tmpc;
}

CHashFun *ParseFunJoin(CCompCtrl *cc, CHashClass *tmp_return, U8 *name, I64 fsp_flags)
{
	CMemberList	*tmpm, *header_list;
	CAOTCtrl	*aotc = cc->aotc;
	CHashClass	*header_return;
	CHashFun	*tmpf;
	I64			 header_arg_count;

	if (name)
	{//if not fun_ptr
		if (cc->flags & CCF_AOT_COMPILE)
		{
			if ((tmpf = HashFind(name, cc->htc.global_hash_table, HTT_FUN)) && tmpf->type & HTF_IMPORT)
				tmpf=NULL;
		}
		else
			if ((tmpf = HashSingleTableFind(name, cc->htc.global_hash_table, HTT_FUN)) && !Bt(&tmpf->flags, Cf_EXTERN))
				tmpf = NULL;
		if (tmpf && tmpf->use_count < 3)
			UnusedExternWarning(cc, tmpf);
	}
	else
		tmpf = NULL;
	if (tmpf)
	{
		tmpf->used_reg_mask = REGG_CLOBBERED + REGG_SAVED + REGG_STACK_TMP;
		Free(tmpf->src_link);
		tmpf->src_link = NULL;
		Free(tmpf->idx);
		tmpf->idx = NULL;
		Free(name);
		header_arg_count = tmpf->arg_count;
		header_list = tmpf->member_list_and_root;
		header_return = tmpf->return_class;
		tmpf->member_list_and_root = NULL;
		ClassMemberListDel(tmpf);
	}
	else
	{
		tmpf = ParseFunNew;
		header_return = NULL;
		tmpf->used_reg_mask = REGG_CLOBBERED + REGG_SAVED + REGG_STACK_TMP;
		tmpf->clobbered_reg_mask = REGG_CLOBBERED + REGG_STACK_TMP;
		tmpf->str = name;
		if (cc->flags & CCF_AOT_COMPILE)
			tmpf->exe_addr = aotc->rip;
		else
			tmpf->exe_addr = &UndefinedExtern;
		LBts(&tmpf->flags, Cf_EXTERN);
		tmpf->flags |= fsp_flags & FSG_FUN_FLAGS1;
		if (name) //if not fun_ptr
			HashAdd(tmpf, cc->htc.global_hash_table);
	}
	BEqual(&tmpf->type, HTf_PUBLIC, fsp_flags & FSF_PUBLIC);
	tmpf->return_class = tmp_return;
	tmpf->use_count = 0;
	HashSrcFileSet(cc, tmpf);
	ParseVarList(cc, tmpf, PRS0_NULL | PRS1_FUN_ARG);
	tmpf->arg_count = tmpf->member_count;
	if (0 < tmpf->arg_count << 3 <= I16_MAX && !Bt(&tmpf->flags, Ff_DOT_DOT_DOT))
		LBts(&tmpf->flags, Ff_RET1);
	tmpm = tmpf->member_list_and_root;
	while (tmpm)
	{
		tmpm->offset += 16; //RBP+RETURN
		tmpm = tmpm->next;
	}
	tmpf->size = 0;
	if (header_return)
	{
		if (OptionGet(OPTf_WARN_HEADER_MISMATCH))
		{
			if (tmpf->return_class != header_return)
			{
				PrintWarn("Fun Header return mismatch '%s'\n", tmpf->str);
				cc->warning_count++;
			}
			if (!MemberListCmp(tmpf->member_list_and_root, header_list, header_arg_count))
			{
				PrintWarn("Fun header args mismatch '%s'\n", tmpf->str);
				cc->warning_count++;
			}
		}
		MemberListDel(header_list);
	}

	return tmpf;
}

U0 ParseFun(CCompCtrl *cc, CHashClass *tmp_return, U8 *name, I64 fsp_flags)
{
	CMemberList	*tmpm;
	CCodeMisc	*saved_leave_label;
	I64			 i, j, size, *r;
	Bool		 old_trace;

	cc->fun_lex_file = cc->lex_include_stack;
	cc->min_line=cc->max_line = cc->lex_include_stack->line_num;

	cc->flags &= ~CCF_NO_REG_OPT;
	cc->htc.local_var_list = cc->htc.fun = ParseFunJoin(cc, tmp_return, name, fsp_flags);

	COCPush(cc);
	Btr(&cc->flags, CCf_PASS_TRACE_PRESENT);
	COCInit(cc);
	ICAdd(cc, IC_ENTER, 0, 0);
	saved_leave_label = cc->lb_leave;
	cc->lb_leave = COCMiscNew(cc,CMT_LABEL);
	cc->flags &= ~CCF_HAS_RETURN;
	ParseStatement(cc,,, 0);

	if (cc->max_line < cc->min_line)
		cc->max_line = cc->min_line;

	if (cc->htc.fun->return_class->size && !(cc->flags & CCF_HAS_RETURN))
		LexWarn(cc, "Function should return value ");
	ICAdd(cc, IC_LABEL, cc->lb_leave, 0);
	cc->lb_leave = saved_leave_label;
	ICAdd(cc, IC_LEAVE, 0, cc->htc.fun->return_class);
	cc->htc.fun->size &= ~7;
	if (cc->flags & CCF_AOT_COMPILE)
	{
		cc->htc.fun->exe_addr = cc->aotc->rip;
		cc->htc.fun->type |= HTF_EXPORT | HTF_RESOLVE;
		r = COCCompile(cc, &size, &cc->htc.fun->debug_info, NULL);
		if (r)
		{
			j = (size + 7) >> 3;
			for (i = 0; i < j; i++)
				AOTStoreCodeU64(cc, r[i]);
			Free(r);
		}
	}
	else
	{
		old_trace = Btr(&cc->opts, OPTf_TRACE);
		cc->htc.fun->exe_addr = COCCompile(cc, &size, &cc->htc.fun->debug_info, NULL);
		if (old_trace)
		{
			Bts(&cc->opts, OPTf_TRACE);
			Un(cc->htc.fun->exe_addr, size, 64);
		}
		SysSymImportsResolve(cc->htc.fun->str);
	}
	LBtr(&cc->htc.fun->flags, Cf_EXTERN);
	COCPop(cc);
	tmpm = cc->htc.fun->member_list_and_root;
	while (tmpm)
	{
		if (tmpm->flags & MLF_NO_UNUSED_WARN)
		{
			if (tmpm->use_count > 1 && StrCompare(tmpm->str, "_anon_"))
				PrintWarn("Unneeded no_warn\n $$LK,\"FL:%s,%d\"$$ '%s' in '%s'\n",
							cc->lex_include_stack->full_name, cc->lex_include_stack->line_num, tmpm->str, cc->htc.fun->str);
		}
		else if (!tmpm->use_count && OptionGet(OPTf_WARN_UNUSED_VAR))
			PrintWarn("Unused variable\n $$LK,\"FL:%s,%d\"$$ '%s' in '%s'\n",
						cc->lex_include_stack->full_name, cc->lex_include_stack->line_num, tmpm->str, cc->htc.fun->str);
		tmpm = tmpm->next;
	}
	cc->htc.local_var_list = cc->htc.fun=cc->fun_lex_file = NULL;
}

U0 ParseGlobalVarList(CCompCtrl *cc, I64 saved_mode, CHashClass *saved_tmpc, I64 saved_val, I64 fsp_flags)
{
	I64				 i, j, mode, k, val;
	U8				*st;
	CHashExport		*tmpex;
	CHashGlobalVar	*tmpg;
	CAOTCtrl		*aotc = cc->aotc;
	CAOTHeapGlobal	*tmphg;
	CHashClass		*tmpc;
	CHashFun		*tmpf, *tmpf_fun_ptr;
	CArrayDim		 tmpad;
	Bool			 has_alias, undef_array_size, is_array;

	while (TRUE)
	{
		tmpc = ParseType(cc, &saved_tmpc, &saved_mode, NULL, &st, &tmpf_fun_ptr, &tmpex, &tmpad, fsp_flags);

		if (!st)
			return;
		if (tmpad.next)
			is_array = TRUE;
		else if (tmpad.total_count < 0)
		{
			is_array = TRUE;
			tmpc--;
		}
		else
			is_array = FALSE;

		val = saved_val;
		mode = saved_mode;
		if (tmpex && mode & 255 == PRS0_EXTERN && !(cc->flags & CCF_AOT_COMPILE) && tmpex->type & HTT_EXPORT_SYS_SYM)
		{
			val = tmpex->val;
			mode = PRS0__EXTERN | PRS1_NOT_REALLY__EXTERN;
		}
		if (cc->token == '(')
		{
			switch (mode & 255)
			{
				case PRS0__INTERN:
					tmpf = ParseFunJoin(cc, tmpc, st, fsp_flags);
					tmpf->exe_addr = val;
					Bts(&tmpf->flags, Ff_INTERNAL);
					LBtr(&tmpf->flags, Cf_EXTERN);
					return;

				case PRS0__EXTERN:
					if (!(fsp_flags & FSF__) && !(mode & PRS1_NOT_REALLY__EXTERN))
						LexExcept(cc, "Expecting label with underscore at ");
					tmpf = ParseFunJoin(cc, tmpc, st, fsp_flags);
					tmpf->exe_addr = val;
					SysSymImportsResolve(tmpf->str);
					LBtr(&tmpf->flags, Cf_EXTERN);
					if (saved_mode & 255 == PRS0__EXTERN)
						LBts(&tmpf->flags, Ff__EXTERN);
					if (cc->flags & CCF_AOT_COMPILE)
						tmpf->type |= HTF_RESOLVE;
					return;

				case PRS0_EXTERN:
					ParseFunJoin(cc, tmpc, st, fsp_flags);
					return;

				case PRS0__IMPORT:
					if (!(fsp_flags & FSF__))
						LexExcept(cc, "Expecting label with underscore at ");

				case PRS0_IMPORT:
					if (!(cc->flags & CCF_AOT_COMPILE))
						LexExcept(cc, "import not needed at ");
					else
					{
						tmpf = ParseFunJoin(cc, tmpc, st, fsp_flags);
						tmpf->type |= HTF_IMPORT;
						if (mode & 255 == PRS0__IMPORT)
							tmpf->import_name = StrNew(val);
						else
							tmpf->import_name = StrNew(st);
					}
					return;

				default:
					ParseFun(cc, tmpc, st, fsp_flags);
					return;
			}
		}
		else
		{
			if (tmpad.total_count < 0)
			{
				i = 0;
				undef_array_size = TRUE;
			}
			else
			{
				i = tmpad.total_count;
				undef_array_size = FALSE;
			}
			if (tmpf_fun_ptr)
				j = sizeof(U8 *);
			else
				j = tmpc->size;
			j *= i;
			has_alias = FALSE;
			tmphg = NULL;
			switch (mode & 255)
			{
				case PRS0__EXTERN:
					if (cc->flags & CCF_AOT_COMPILE)
					{
						tmpg = CAlloc(sizeof(CHashGlobalVar));
						tmpg->data_addr_rip = val;
						tmpg->type = HTT_GLOBAL_VAR | HTF_EXPORT;
					}
					else
					{
						tmpg = CAlloc(sizeof(CHashGlobalVar), Fs->code_heap);
						tmpg->data_addr = val;
						tmpg->type = HTT_GLOBAL_VAR;
					}
					tmpg->flags |= GVF_ALIAS;
					break;

				case PRS0__IMPORT:
				case PRS0_IMPORT:
					if (!(cc->flags & CCF_AOT_COMPILE))
						LexExcept(cc, "import not needed at ");
					else
					{
						tmpg = CAlloc(sizeof(CHashGlobalVar));
						tmpg->type = HTT_GLOBAL_VAR | HTF_IMPORT;
						if (mode & 255 == PRS0__IMPORT)
							tmpg->import_name = StrNew(val);
						else
							tmpg->import_name = StrNew(st);
					}
					break;

				case PRS0_EXTERN:
					if (cc->flags & CCF_AOT_COMPILE)
					{
						tmpg = CAlloc(sizeof(CHashGlobalVar));
						tmpg->type = HTT_GLOBAL_VAR;
					}
					else
					{
						tmpg = CAlloc(sizeof(CHashGlobalVar), Fs->code_heap);
						tmpg->type = HTT_GLOBAL_VAR | HTF_UNRESOLVED;
					}
					break;

				default:
					if (cc->flags & CCF_AOT_COMPILE)
					{
						if (Bt(&cc->opts, OPTf_GLOBALS_ON_DATA_HEAP)) {
							if (cc->token == '=')
								LexExcept(cc, "Can't init global variable on data heap in AOT module ");
							tmpg = CAlloc(sizeof(CHashGlobalVar));
							tmphg = tmpg->heap_global = CAlloc(sizeof(CAOTHeapGlobal));
							tmphg->size = j;
							tmphg->str = StrNew(st);
							tmphg->next = aotc->heap_globals;
							aotc->heap_globals = tmphg;
							tmpg->flags = GVF_DATA_HEAP;
							tmpg->type = HTT_GLOBAL_VAR; //TODO: HTF_EXPORT
							if (tmpex && tmpex->type & HTT_GLOBAL_VAR) //TODO!! extern
								LexExcept(cc, "Feature not implemented ");
						}
						else
						{
							tmpg = CAlloc(sizeof(CHashGlobalVar));
							if (cc->token == '=')
								tmpg->data_addr = CAlloc(j);
							if (tmpc->size >= 8) //align
								while (aotc->rip & 7)
									AOTStoreCodeU8(cc, 0);
							else if (tmpc->size == 4)
								while (aotc->rip & 3)
									AOTStoreCodeU8(cc, 0);
							else if (tmpc->size == 2)
								while (aotc->rip & 1)
									AOTStoreCodeU8(cc, 0);
							tmpg->data_addr_rip = aotc->rip;
							tmpg->type = HTT_GLOBAL_VAR | HTF_EXPORT;
							if (tmpex && tmpex->type & HTT_GLOBAL_VAR)
								has_alias = TRUE;
							for (k = 0; k < j; k++)
								AOTStoreCodeU8(cc, 0); //Init AOT global to zero.
						}
					}
					else
					{
						if (Bt(&cc->opts, OPTf_GLOBALS_ON_DATA_HEAP))
						{
							tmpg = CAlloc(sizeof(CHashGlobalVar), Fs->code_heap);
							tmpg->data_addr = MAlloc(j);
							tmpg->flags = GVF_DATA_HEAP;
						}
						else
						{
							tmpg = CAlloc(sizeof(CHashGlobalVar), Fs->code_heap);
							tmpg->data_addr = MAlloc(j, Fs->code_heap);
						}
						tmpg->type = HTT_GLOBAL_VAR;
						if (tmpex && tmpex->type & HTT_GLOBAL_VAR && tmpex->type & HTF_UNRESOLVED &&
								MHeapCtrl(tmpex) == MHeapCtrl(tmpg))
							has_alias = TRUE;
						if (sys_var_init_flag)
							MemSet(tmpg->data_addr, sys_var_init_val, j);
					}
			}
			tmpg->dim.next = tmpad.next;
			if (fsp_flags & FSF_PUBLIC)
				tmpg->type |= HTF_PUBLIC;
			tmpg->var_class = tmpc;
			tmpg->str = st;
			tmpg->size = j;
			tmpg->dim.total_count = i;
			tmpg->use_count = 0;
			if (cc->last_U16 == '\n')
				HashSrcFileSet(cc, tmpg, -1);
			else
				HashSrcFileSet(cc, tmpg, 0);
			if (mode & 255 == PRS0_IMPORT || mode & 255 == PRS0__IMPORT)
				tmpg->flags |= GVF_IMPORT;
			if (mode & 255 == PRS0_EXTERN)
				tmpg->flags |= GVF_EXTERN;
			if (tmpf_fun_ptr)
			{
				tmpg->fun_ptr = tmpf_fun_ptr;
				tmpg->flags |= GVF_FUN;
			}
			if (is_array)
				tmpg->flags |= GVF_ARRAY;
			HashAdd(tmpg, cc->htc.global_hash_table);
			if (!(cc->flags & CCF_AOT_COMPILE) && !(tmpg->flags & GVF_EXTERN))
				SysSymImportsResolve(tmpg->str);
			if (cc->token == '=')
			{
				if (undef_array_size)
				{
					LexPush(cc);
					LexPush(cc);
					Lex(cc);
					ParseGlobalInit(cc, tmpg, 1);
					LexPopNoRestore(cc);
					tmpg->size = tmpg->dim.total_count * tmpc->size;
					if (tmphg)
						tmphg->size = tmpg->size;
					if (cc->flags & CCF_AOT_COMPILE)
						for (k = 0; k < tmpg->size; k++)
							AOTStoreCodeU8(cc, 0);
					else
						if (sys_var_init_flag)
							MemSet(tmpg->data_addr, sys_var_init_val, k);
					LexPopRestore(cc);
				}
				LexPush(cc);
				Lex(cc);
				ParseGlobalInit(cc, tmpg, 2);
				if (cc->flags & CCF_AOT_COMPILE)
					for (k = 0; k < tmpg->size; k++)
						AOTStoreCodeU8At(cc, tmpg->data_addr_rip + k, tmpg->data_addr[k]);
				LexPopNoRestore(cc);
			}
			if (has_alias)
			{
				if (tmpex(CHashGlobalVar *)->use_count < 2)
				{
					PrintWarn("Unused extern '%s'\n", tmpex(CHashGlobalVar *)->str);
					cc->warning_count++;
				}
				tmpex(CHashGlobalVar *)->flags |= GVF_ALIAS;
				tmpex(CHashGlobalVar *)->data_addr = tmpg->data_addr;
				tmpex(CHashGlobalVar *)->data_addr_rip = tmpg->data_addr_rip;
			}
			if (cc->token == ',')
				Lex(cc);
			else
			{
				if (cc->token != ';')
					LexExcept(cc, "Missing ';' at");
				Lex(cc);
				return;
			}
		}
	}
}

U0 ParseIf(CCompCtrl *cc, I64 try_count, CCodeMisc *lb_break)
{
	CCodeMisc	*lb, *lb1;
	I64			 k;

	if (cc->token != '(')
		LexExcept(cc, "Expecting '(' at ");
	Lex(cc);
	if (!ParseExpression(cc, NULL, FALSE))
		throw('Compiler');
	if (cc->token != ')')
		LexExcept(cc, "Missing ')' at ");
	Lex(cc);
	lb = COCMiscNew(cc, CMT_LABEL);
	ICAdd(cc, IC_BR_ZERO, lb, 0);
	ParseStatement(cc, try_count, lb_break);
	k = ParseKeyWord(cc);
	if (k == KW_ELSE)
	{
		Lex(cc);
		lb1 = COCMiscNew(cc, CMT_LABEL);
		ICAdd(cc, IC_JMP, lb1, 0);
		ICAdd(cc, IC_LABEL, lb, 0);
		ParseStatement(cc, try_count, lb_break);
		ICAdd(cc, IC_LABEL, lb1, 0);
	}
	else
		ICAdd(cc, IC_LABEL, lb, 0);
}

U0 ParseWhile(CCompCtrl *cc, I64 try_count)
{
	CCodeMisc *lb, *lb_done;

	if (cc->token != '(')
		LexExcept(cc, "Expecting '(' at ");
	Lex(cc);
	lb = COCMiscNew(cc, CMT_LABEL);
	ICAdd(cc, IC_LABEL, lb, 0);
	if (!ParseExpression(cc, NULL,FALSE))
		throw('Compiler');
	if (cc->token != ')')
		LexExcept(cc, "Missing ')' at ");
	Lex(cc);
	lb_done = COCMiscNew(cc, CMT_LABEL);
	ICAdd(cc, IC_BR_ZERO, lb_done, 0);
	ParseStatement(cc, try_count, lb_done);
	ICAdd(cc, IC_JMP, lb, 0);
	ICAdd(cc, IC_LABEL, lb_done, 0);
}

U0 ParseDoWhile(CCompCtrl *cc, I64 try_count)
{
	CCodeMisc *lb, *lb_done;

	lb = COCMiscNew(cc, CMT_LABEL);
	lb_done = COCMiscNew(cc, CMT_LABEL);
	ICAdd(cc, IC_LABEL, lb, 0);
	ParseStatement(cc, try_count, lb_done);
	if (ParseKeyWord(cc) != KW_WHILE)
		LexExcept(cc, "Missing 'while' at");
	if (Lex(cc) != '(')
		LexExcept(cc, "Expecting '(' at ");
	Lex(cc);
	if (!ParseExpression(cc, NULL, FALSE))
		throw('Compiler');
	if (cc->token != ')')
		LexExcept(cc, "Missing ')' at ");
	ICAdd(cc, IC_BR_NOT_ZERO, lb, 0);
	ICAdd(cc, IC_LABEL, lb_done, 0);
	if (Lex(cc) != ';')
		LexExcept(cc, "Missing ';' at");
	Lex(cc);
}

U0 ParseFor(CCompCtrl *cc, I64 try_count)
{
	CCodeCtrl *tmpcbh;
	CCodeMisc *lb, *lb_done;

	if (cc->token != '(')
		LexExcept(cc, "Expecting '(' at ");
	Lex(cc);
	ParseStatement(cc, try_count);

	lb = COCMiscNew(cc, CMT_LABEL);
	ICAdd(cc, IC_LABEL, lb, 0);
	if (!ParseExpression(cc, NULL, FALSE))
		throw('Compiler');
	lb_done = COCMiscNew(cc, CMT_LABEL);
	ICAdd(cc, IC_BR_ZERO, lb_done, 0);
	if (cc->token != ';')
		LexExcept(cc, "Missing ';' at");
	Lex(cc);

	COCPush(cc);
	COCInit(cc);
	if (cc->token != ')')
		ParseStatement(cc, try_count, NULL, 0);
	COCPush(cc);
	tmpcbh = COCPopNoFree(cc);
	COCPop(cc);
	if (cc->token != ')')
		LexExcept(cc, "Missing ')' at ");
	Lex(cc);

	ParseStatement(cc, try_count, lb_done);
	COCAppend(cc, tmpcbh);
	ICAdd(cc, IC_JMP, lb, 0);
	ICAdd(cc, IC_LABEL, lb_done, 0);
}

class CSubSwitch
{
	CSubSwitch *next, *last;
	CCodeMisc  *lb_start, *lb_break;
};

class CSwitchCase
{
	CSwitchCase	*next;
	CCodeMisc	*label;
	I64			 val;
	CSubSwitch	*ss;
};

U0 ParseSwitch(CCompCtrl *cc, I64 try_count)
{
	CSwitchCase			*header = NULL, *tmps, *tmps1;	//Leaks on except
	CSubSwitch			 head, *tmpss; 					//Leaks on except
	CCodeMisc			*lb_default, *lb_fwd_case, *mc_jt, *lb_entry, **jmp_table;
	CIntermediateCode	*tmpi_sub, *tmpi_cmp, *tmpi_jmp, *tmpi_start;
	Bool				 default_found = FALSE, nobound;
	I64					 i, k_start = I64_MIN, k_end, lo = I64_MAX, hi = I64_MIN, range;

	if (cc->token == '(')
		nobound = FALSE;
	else if (cc->token == '[')
		nobound = TRUE;
	else
		LexExcept(cc, "Expecting '(' or '[' at ");
	Lex(cc);
	QueueInit(&head);

	head.last->lb_break = COCMiscNew(cc, CMT_LABEL);
	head.last->lb_break->use_count++;
	lb_default = COCMiscNew(cc, CMT_LABEL);
	lb_default->use_count++;
	mc_jt = COCMiscNew(cc, CMT_JMP_TABLE);
	mc_jt->begin = COCMiscNew(cc, CMT_LABEL);
	mc_jt->begin->use_count++;
	if (!ParseExpression(cc, NULL, FALSE))
		throw('Compiler');
	tmpi_sub = ICAdd(cc, IC_IMM_I64, 0, cmp.internal_types[RT_I64]);
	ICAdd(cc, IC_SUB, 0, cmp.internal_types[RT_I64]);
	tmpi_cmp = ICAdd(cc, IC_IMM_I64, 0, cmp.internal_types[RT_I64]);
	if (nobound)
	{
		ICAdd(cc, IC_NOBOUND_SWITCH, mc_jt, 0);
		if (cc->token != ']')
			LexExcept(cc, "Missing ']' at ");
	}
	else
	{
		ICAdd(cc, IC_SWITCH, mc_jt, 0);
		if (cc->token != ')')
			LexExcept(cc, "Missing ')' at ");
	}
	if (Lex(cc) != '{')
		LexExcept(cc, "Expecting '{' at ");
	Lex(cc);
	ICAdd(cc, IC_LABEL, mc_jt->begin, 0);
	while (TRUE)
	{
		while (cc->token && cc->token != '}')
		{
sw_cont:
			switch (ParseKeyWord(cc))
			{
				case KW_END:
					goto sw_sub_end;

				case KW_START:
					if (Lex(cc) == ':')
						Lex(cc);
					else
						LexExcept(cc, "Expecting ':' at ");
					tmpss = MAlloc(sizeof(CSubSwitch));
					QueueInsert(tmpss, head.last);
					head.last->lb_break = COCMiscNew(cc, CMT_LABEL);
					head.last->lb_break->use_count++;
					lb_fwd_case = COCMiscNew(cc, CMT_LABEL);
					tmpi_jmp = ICAdd(cc, IC_JMP, lb_fwd_case, 0);

					tmpss->lb_start = COCMiscNew(cc, CMT_LABEL);
					tmpi_start = ICAdd(cc, IC_LABEL, tmpss->lb_start, 0);
					while (cc->token && cc->token != '}')
					{
						switch (ParseKeyWord(cc))
						{
							case KW_END:
								OptFree(tmpi_jmp);
								goto sw_sub_end;

							case KW_START:
							case KW_CASE:
							case KW_DEFAULT:
								if (cc->coc.coc_head.last == tmpi_start)
								{
									OptFree(tmpi_jmp);
									tmpss->lb_start = NULL;
								}
								else
								{
									ICAdd(cc, IC_RET, 0, 0);
									ICAdd(cc, IC_LABEL, lb_fwd_case, 0);
									ICAdd(cc, IC_SUB_CALL, tmpss->lb_start, 0);//In case fall-thru
								}
								goto sw_cont;

							default:
								ParseStatement(cc, try_count);
						}
					}
					break;

				case KW_CASE:
					if (head.next != &head)
					{
						lb_fwd_case = COCMiscNew(cc, CMT_LABEL);
						tmpi_jmp = ICAdd(cc, IC_JMP, lb_fwd_case, 0);//In case fall-thru
					}
					Lex(cc);
					lb_entry = COCMiscNew(cc, CMT_LABEL);
					ICAdd(cc, IC_LABEL, lb_entry, 0);
					lb_entry->use_count++;
					if (head.next != &head)
					{
						tmpss = head.next;
						while (tmpss != &head)
						{
							if (tmpss->lb_start)
								ICAdd(cc, IC_SUB_CALL, tmpss->lb_start, 0);
							tmpss = tmpss->next;
						}
						ICAdd(cc, IC_LABEL, lb_fwd_case, 0);
					}
					if (cc->token == ':')
					{
						if (k_start == I64_MIN)
							k_start = 0;
						else
							k_start++;
					}
					else
						k_start = LexExpressionI64(cc);
					if (k_start < lo)
						lo = k_start;
					if (k_start > hi)
						hi = k_start;
					if (cc->token == ':')
					{
						Lex(cc);
						tmps = MAlloc(sizeof(CSwitchCase));
						tmps->label = lb_entry;
						tmps->val = k_start;
						tmps->next = header;
						header = tmps;
					}
					else if (cc->token == TK_ELLIPSIS)
					{
						Lex(cc);
						k_end = LexExpressionI64(cc);
						if (cc->token == ':')
						{
							Lex(cc);
							if (k_end < lo)
								lo = k_end;
							if (k_end > hi)
								hi = k_end;
							if (k_start > k_end)
								SwapI64(&k_start, &k_end);
							for (i = k_start; i <= k_end; i++)
							{
								tmps = MAlloc(sizeof(CSwitchCase));
								tmps->label = lb_entry;
								tmps->val = i;
								tmps->next = header;
								header = tmps;
							}
							k_start = k_end;
						}
						else
							LexExcept(cc, "Expecting ':' at ");
					}
					else
						LexExcept(cc, "Expecting ':' at ");
					break;

				case KW_DEFAULT:
					if (head.next != &head)
					{
						lb_fwd_case = COCMiscNew(cc, CMT_LABEL);
						tmpi_jmp = ICAdd(cc, IC_JMP, lb_fwd_case, 0);//In case fall-thru
					}
					Lex(cc);
					ICAdd(cc, IC_LABEL, lb_default, 0);
					if (cc->token == ':')
						Lex(cc);
					else
						LexExcept(cc, "Expecting ':' at ");
					if (head.next != &head)
					{
						tmpss = head.next;
						while (tmpss != &head)
						{
							if (tmpss->lb_start)
								ICAdd(cc, IC_SUB_CALL, tmpss->lb_start, 0);
							tmpss = tmpss->next;
						}
						ICAdd(cc, IC_LABEL, lb_fwd_case, 0);
					}
					default_found = TRUE;
					break;

				default:
					ParseStatement(cc, try_count, head.last->lb_break);
			}
		}
sw_sub_end:
		tmpss = head.last;
		ICAdd(cc, IC_LABEL, tmpss->lb_break, 0);
		if (tmpss == &head)
		{
			if (cc->token != '}')
				LexExcept(cc, "Missing '}' at ");
			Lex(cc);
			break;
		}
		else
		{
			QueueRemove(tmpss);
			Free(tmpss);
			if (ParseKeyWord(cc) != KW_END)
				LexExcept(cc, "Missing 'end' at ");
			if (Lex(cc) == ':')
				Lex(cc);
			else
				LexExcept(cc, "Expecting ':' at ");
		}
	}
	if (!default_found)
		ICAdd(cc, IC_LABEL, lb_default, 0);

	if (0 < lo <= 16)
		lo = 0;
	range = hi - lo + 1;
	if (lo > hi || !(0 < range <= 0xFFFF))
		LexExcept(cc, "switch range error at ");
	jmp_table = MAlloc((sizeof(CCodeMisc *) * range + 0x1FF) & ~0x1FF);
	MemSetI64(jmp_table, lb_default, range);
	tmpi_sub->ic_data = lo;
	tmpi_cmp->ic_data = range;
	tmps = header;
	while (tmps)
	{
		tmps1 = tmps->next;
		if (jmp_table[tmps->val - lo] != lb_default)
			LexExcept(cc, "Duplicate case at ");
		else
			jmp_table[tmps->val - lo] = tmps->label;
		Free(tmps);
		tmps = tmps1;
	}
	mc_jt->default = lb_default;
	mc_jt->jmp_table = jmp_table;
	mc_jt->range = range;
}

U0 ParseNoWarn(CCompCtrl *cc)
{
	CMemberList *tmpm;

	while (cc->token == TK_IDENT)
	{
		if (!(tmpm = cc->local_var_entry))
			LexExcept(cc, "Expecting local variable at ");
		tmpm->flags |= MLF_NO_UNUSED_WARN;
		if (Lex(cc) == ',')
			Lex(cc);
		else if (cc->token != ';')
			LexExcept(cc, "Expecting ',' at ");
	}
}

U0 ParseStreamBlk(CCompCtrl *cc)
{
	CLexHashTableContext	*htc = MAlloc(sizeof(CLexHashTableContext));
	CStreamBlk				*tmpe = MAlloc(sizeof(CStreamBlk));

	tmpe->body = StrNew("");
	QueueInsert(tmpe, cc->last_stream_blk);
	COCPush(cc);
	QueueInit(&cc->coc.coc_next_misc);

	MemCopy(htc, &cc->htc, sizeof(CLexHashTableContext));
	htc->old_flags = cc->flags;
	cc->htc.next = htc;
	cc->htc.fun = cc->htc.local_var_list  =NULL;
	cc->htc.define_hash_table = cc->htc.hash_table_list =
		cc->htc.global_hash_table = cc->htc.local_hash_table = Fs->hash_table;
	cc->flags = cc->flags & ~(CCF_ASM_EXPRESSIONS | CCF_AOT_COMPILE) | CCF_EXE_BLK;
	if (cc->token == '{')
		Lex(cc);
	else
		LexExcept(cc, "Missing '}' at ");
	while (cc->token && cc->token != '}')
		ExeCmdLine(cc);

	MemCopy(&cc->htc, htc, sizeof(CLexHashTableContext));
	cc->flags = cc->flags & ~CCF_EXE_BLK | htc->old_flags & (CCF_ASM_EXPRESSIONS | CCF_EXE_BLK | CCF_AOT_COMPILE);
	Free(htc);
	COCPop(cc);
	QueueRemove(tmpe);
	if (*tmpe->body)
		LexIncludeStr(cc, "StreamBlk", tmpe->body, FALSE);
	else
		Free(tmpe->body);
	Free(tmpe);
	Lex(cc); //Skip '}'
}

U0 ParseTryBlk(CCompCtrl *cc, I64 try_count)
{
	CCodeMisc 	*lb_catch, *lb_done, *lb_untry;
	CHashClass	*tmpc = cmp.internal_types[RT_PTR];
	CHashFun	*tmp_try   = HashFind("SysTry", cc->htc.hash_table_list, HTT_FUN),
				*tmp_untry = HashFind("SysUntry", cc->htc.hash_table_list, HTT_FUN);

	if (!tmp_try || !tmp_untry)
		LexExcept(cc, "Missing header for SysTry() and SysUntry() at ");

	cc->flags |= CCF_NO_REG_OPT; //TODO:Currently no register variables in functions with try/catch

	lb_catch = COCMiscNew(cc, CMT_LABEL);
	lb_done  = COCMiscNew(cc, CMT_LABEL);
	lb_untry = COCMiscNew(cc, CMT_LABEL);

	ICAdd(cc, IC_CALL_START, 0, 0);
	ICAdd(cc, IC_GET_LABEL, lb_untry, tmpc, ICF_PUSH_RES);
	ICAdd(cc, IC_GET_LABEL, lb_catch, tmpc, ICF_PUSH_RES);
	if (Bt(&tmp_try->flags, Cf_EXTERN))
	{
		cc->abs_counts.externs++;
		if (cc->flags & CCF_AOT_COMPILE)
			ICAdd(cc, IC_CALL_IMPORT, tmp_try, tmpc);
		else
			ICAdd(cc, IC_CALL_INDIRECT2, &tmp_try->exe_addr, tmpc);
	}
	else
		ICAdd(cc, IC_CALL, tmp_try->exe_addr, tmpc);
	if ((Bt(&tmp_try->flags, Ff_RET1) || Bt(&tmp_try->flags, Ff_ARGPOP)) && !Bt(&tmp_try->flags, Ff_NOARGPOP))
		ICAdd(cc, IC_ADD_RSP1, 16, tmpc);
	else
		ICAdd(cc, IC_ADD_RSP, 16, tmpc);
	ICAdd(cc, IC_CALL_END, 0, tmpc);
	ICAdd(cc, IC_END_EXP, 0, 0, ICF_RES_NOT_USED);

	ParseStatement(cc, try_count + 1);

	ICAdd(cc, IC_LABEL, lb_untry, 0);
	ICAdd(cc, IC_CALL_START, 0, 0);
	if (Bt(&tmp_untry->flags, Cf_EXTERN))
	{
		cc->abs_counts.externs++;
		if (cc->flags & CCF_AOT_COMPILE)
			ICAdd(cc, IC_CALL_IMPORT, tmp_untry, tmpc);
		else
			ICAdd(cc, IC_CALL_INDIRECT2, &tmp_untry->exe_addr, tmpc);
	}
	else
		ICAdd(cc, IC_CALL, tmp_untry->exe_addr, tmpc);
	ICAdd(cc, IC_CALL_END, 0, tmpc);
	ICAdd(cc, IC_END_EXP, 0, 0, ICF_RES_NOT_USED);

	ICAdd(cc, IC_JMP, lb_done, 0);

	if (ParseKeyWord(cc) != KW_CATCH)
		LexExcept(cc, "Missing 'catch' at");

	Lex(cc);
	ICAdd(cc, IC_LABEL, lb_catch, 0);
	ParseStatement(cc, try_count + 1);
	ICAdd(cc, IC_RET, 0, tmpc);
	ICAdd(cc, IC_LABEL, lb_done, 0);
}

Bool ParseStatement(CCompCtrl *cc, I64 try_count=0, CCodeMisc *lb_break=NULL, I64 comp_flags=CMPF_PRS_SEMICOLON)
{
	I64			 i, fsp_flags = 0;
	CHashExport	*tmpex;
	CCodeMisc	*g_lb;
	U8			*import_name;
	CHashFun	*tmp_untry;
	CAOT		*tmpaot;

	if (comp_flags & CMPF_ONE_ASM_INS)
	{
		if (cc->flags & CCF_AOT_COMPILE || cc->aot_depth)
			ParseAsmBlk(cc, CMPF_ONE_ASM_INS);
		else if (tmpaot = CompJoin(cc, CMPF_ASM_BLK | CMPF_ONE_ASM_INS))
			CompFixUpJITAsm(cc, tmpaot);
		fsp_flags = FSF_ASM;
	}
	else
		while (TRUE)
		{
			while (cc->token == ',')
				Lex(cc);
			if (cc->token == '{')
			{
				Lex(cc);
				while (cc->token != '}' && cc->token != TK_EOF)
					ParseStatement(cc, try_count, lb_break);
				if (cc->lex_include_stack == cc->fun_lex_file)
					cc->max_line = cc->lex_include_stack->line_num;
				if (Lex(cc) != ',')
					goto sm_done;
			}
			else if (cc->token == ';')
			{
				if (comp_flags & CMPF_PRS_SEMICOLON)
					Lex(cc);
				if (cc->token != ',')
					goto sm_done;
			}
			else
			{
				if (cc->token == TK_IDENT)
				{
					if (tmpex = cc->hash_entry)
					{
						if (tmpex->type & HTT_KEYWORD)
						{
							i = tmpex(CHashGeneric *)->user_data0;
							switch [i]
							{
								case KW_KWS_NUM - 1: //nobound switch
								default: //A keyword that is not valid here is just a symbol.
									goto sm_not_keyword_afterall;
								start:
									case KW_ASM:
										if (cc->htc.fun)
										{
											if (tmpaot = CompJoin(cc, CMPF_ASM_BLK))
												ICAdd(cc, IC_ASM, tmpaot, 0);
											Lex(cc); //Skip '}' of asm{}
										}
										else
										{
											if (cc->flags & CCF_AOT_COMPILE || cc->aot_depth)
											{
												Lex(cc);
												ParseAsmBlk(cc, 0);
												if (cc->flags & CCF_AOT_COMPILE && cc->aot_depth == 1)
													Lex(cc); //Skip '}' of asm{}
											}
											else
											{
												if (tmpaot = CompJoin(cc, CMPF_ASM_BLK))
													CompFixUpJITAsm(cc, tmpaot);
												Lex(cc); //Skip '}' of asm{}
											}
											fsp_flags = FSF_ASM;
										}
										break;
									start:
										Lex(cc);
										case KW_LOCK:
											cc->lock_count++;
											ParseStatement(cc, try_count);
											cc->lock_count--;
											break;

										case KW_TRY:
											ParseTryBlk(cc, try_count);
											break;

										case KW_IF:
											ParseIf(cc, try_count, lb_break);
											break;

										case KW_FOR:
											ParseFor(cc, try_count);
											break;

										case KW_WHILE:
											ParseWhile(cc, try_count);
											break;

										case KW_DO:
											ParseDoWhile(cc, try_count);
											break;

										case KW_SWITCH:
											ParseSwitch(cc, try_count);
											break;
									end:
								end:
									if (cc->token != ',')
										goto sm_done;
									break;
								start:
									if (cc->htc.fun)
										LexExcept(cc, "Not allowed in function");
									Lex(cc);
									case KW__EXTERN:
										if (Bt(&cc->opts, OPTf_EXTERNS_TO_IMPORTS))
											goto sm_underscore_import;
										if (cc->token != TK_IDENT || !(tmpex = cc->hash_entry) ||
												!(tmpex->type & HTT_EXPORT_SYS_SYM))
											LexExcept(cc, "Expecting system symbol at ");
										if (*cc->cur_str == '_')
											fsp_flags |= FSF__;
										i = tmpex->val;
										Lex(cc);
										if (cc->token != TK_IDENT || !(tmpex = cc->hash_entry) ||
												!(tmpex->type & (HTT_CLASS | HTT_INTERNAL_TYPE)))
											LexExcept(cc, "Expecting type at ");
										Lex(cc);
										ParseGlobalVarList(cc, PRS0__EXTERN | PRS1_NULL, tmpex, i, fsp_flags);
										break;

									case KW__IMPORT:
sm_underscore_import:
										if (cc->token != TK_IDENT)
											LexExcept(cc, "Expecting system symbol at ");
										if (*cc->cur_str == '_')
											fsp_flags |= FSF__;
										import_name = cc->cur_str;
										cc->cur_str = 0;
										if (Lex(cc) != TK_IDENT || !(tmpex = cc->hash_entry) ||
												!(tmpex->type & (HTT_CLASS | HTT_INTERNAL_TYPE)))
											LexExcept(cc, "Expecting type at ");
										Lex(cc);
										ParseGlobalVarList(cc, PRS0__IMPORT | PRS1_NULL, tmpex, import_name, fsp_flags);
										Free(import_name);
										break;

									case KW_EXTERN:
										if (cc->token != TK_IDENT)
											LexExcept(cc, "Expecting type at ");
										tmpex = cc->hash_entry;
										i = ParseKeyWord(cc);
										if (i == KW_CLASS || i == KW_UNION)
										{
											Lex(cc);
											ParseClass(cc, i, fsp_flags, TRUE);
											fsp_flags &= FSF_ASM;
											goto sm_semicolon;
										}
										if (!tmpex || !(tmpex->type & (HTT_CLASS | HTT_INTERNAL_TYPE)))
											LexExcept(cc, "Expecting type at ");
										if (Bt(&cc->opts, OPTf_EXTERNS_TO_IMPORTS))
											goto sm_import;
										Lex(cc);
										ParseGlobalVarList(cc, PRS0_EXTERN | PRS1_NULL, tmpex, 0, fsp_flags);
										break;

									case KW_IMPORT:
										if (cc->token != TK_IDENT || !(tmpex = cc->hash_entry) ||
												!(tmpex->type & (HTT_CLASS | HTT_INTERNAL_TYPE)))
											LexExcept(cc, "Expecting type at ");
sm_import:
										Lex(cc);
										ParseGlobalVarList(cc, PRS0_IMPORT | PRS1_NULL, tmpex, 0, fsp_flags);
										break;

									case KW__INTERN:
										i = LexExpressionI64(cc);
										if (cc->token != TK_IDENT || !(tmpex = cc->hash_entry) ||
												!(tmpex->type & (HTT_CLASS | HTT_INTERNAL_TYPE)))
											LexExcept(cc, "Expecting type at ");
										Lex(cc);
										ParseGlobalVarList(cc, PRS0__INTERN | PRS1_NULL, tmpex, i, fsp_flags);
										break;
								end:
									fsp_flags &= FSF_ASM;
									break;
								start:
									case KW_STATIC:
										fsp_flags = FSF_STATIC | fsp_flags & FSF_ASM;
										break;

									case KW_INTERRUPT:
										fsp_flags = FSF_INTERRUPT | FSF_NOARGPOP | fsp_flags & (FSG_FUN_FLAGS2 | FSF_ASM);
										break;

									case KW_HASERRCODE:
										fsp_flags = FSF_HASERRCODE | fsp_flags & (FSG_FUN_FLAGS2 | FSF_ASM);
										break;

									case KW_ARGPOP:
										fsp_flags = FSF_ARGPOP | fsp_flags & (FSG_FUN_FLAGS2 | FSF_ASM);
										break;

									case KW_NOARGPOP:
										fsp_flags = FSF_NOARGPOP | fsp_flags & (FSG_FUN_FLAGS2 | FSF_ASM);
										break;

									case KW_PUBLIC:
										fsp_flags = FSF_PUBLIC | fsp_flags & (FSG_FUN_FLAGS2 | FSF_ASM);
										break;
								end:
									Lex(cc);
									break;

								case KW_RETURN:
									if (!cc->htc.fun)
										LexExcept(cc, "Not in function.  Can't return a value ");
									if (try_count)
									{
										tmp_untry = HashFind("SysUntry", cc->htc.hash_table_list, HTT_FUN);
										for (i = 0; i < try_count; i++)
										{
											if (Bt(&tmp_untry->flags, Cf_EXTERN))
											{
												cc->abs_counts.externs++;
												if (cc->flags & CCF_AOT_COMPILE)
													ICAdd(cc, IC_CALL_IMPORT, tmp_untry, cmp.internal_types[RT_PTR]);
												else
													ICAdd(cc, IC_CALL_INDIRECT2, &tmp_untry->exe_addr,
														  cmp.internal_types[RT_PTR]);
											}
											else
												ICAdd(cc, IC_CALL, tmp_untry->exe_addr, cmp.internal_types[RT_PTR]);
										}
									}
									if (Lex(cc) != ';')
									{
										if (!cc->htc.fun->return_class->size)
											LexWarn(cc, "Function should NOT return value ");
										if (!ParseExpression(cc, NULL, FALSE))
											throw('Compiler');
										ICAdd(cc, IC_RETURN_VAL, 0, cc->htc.fun->return_class);
										cc->flags |= CCF_HAS_RETURN;
									}
									else if (cc->htc.fun->return_class->size)
										LexWarn(cc, "Function should return value ");
									ICAdd(cc, IC_JMP, cc->lb_leave, 0);
									goto sm_semicolon;

								case KW_GOTO:
									if (Lex(cc) != TK_IDENT)
										LexExcept(cc, "Expecting identifier at ");
									if (!(g_lb = COCGoToLabelFind(cc, cc->cur_str)))
									{
										g_lb = COCMiscNew(cc, CMT_GOTO_LABEL);
										g_lb->str = cc->cur_str;
										cc->cur_str = NULL;
									}
									g_lb->use_count++;
									ICAdd(cc, IC_JMP, g_lb, 0);
									Lex(cc);
									goto sm_semicolon;

								case KW_BREAK:
									Lex(cc);
									if (!lb_break)
										LexExcept(cc, "'break' not allowed\n");
									ICAdd(cc, IC_JMP, lb_break, 0);
									goto sm_semicolon;

								case KW_NO_WARN:
									Lex(cc);
									ParseNoWarn(cc);
									goto sm_semicolon;

								case KW_UNION:
								case KW_CLASS:
									Lex(cc);
									tmpex = ParseClass(cc, i, fsp_flags, FALSE);
									if (!cc->htc.fun && cc->token != ';') {
										ParseGlobalVarList(cc, PRS0_NULL | PRS1_NULL, tmpex, 0, fsp_flags);
										fsp_flags &= FSF_ASM;
										break;
									}
									else
									{
										fsp_flags &= FSF_ASM;
										goto sm_semicolon;
									}
							}
						}
						else
						{//Ident, found in hash table, not keyword
sm_not_keyword_afterall:
							if (tmpex->type & (HTT_CLASS | HTT_INTERNAL_TYPE))
							{
								if (cc->htc.fun)
								{
									if (fsp_flags & FSF_STATIC)
										ParseVarList(cc, cc->htc.fun, PRS0_NULL | PRS1_STATIC_LOCAL_VAR);
									else
										ParseVarList(cc, cc->htc.fun, PRS0_NULL | PRS1_LOCAL_VAR);
									if (cc->token == '}')
										goto sm_done;
								}
								else
								{
									Lex(cc);
									ParseGlobalVarList(cc, PRS0_NULL | PRS1_NULL, tmpex, 0, fsp_flags);
								}
							}
							else
							{
								if (tmpex->type & (HTT_OPCODE | HTT_ASM_KEYWORD))
								{
									if (cc->htc.fun)
									{
										if (tmpaot = CompJoin(cc, CMPF_ASM_BLK | CMPF_ONE_ASM_INS))
											ICAdd(cc, IC_ASM, tmpaot, 0);
									}
									else
										LexExcept(cc, "Use Asm Block at ");
									if (cc->token != ',')
										goto sm_done;
								}
								else
									goto sm_parse_exp;
							}
							fsp_flags &= FSF_ASM;
						}
					}
					else
					{//Ident, not in hash table
						if (cc->local_var_entry)
							goto sm_parse_exp;
						if (!(g_lb = COCGoToLabelFind(cc, cc->cur_str)))
						{
							g_lb = COCMiscNew(cc, CMT_GOTO_LABEL);
							g_lb->str = cc->cur_str;
							cc->cur_str = NULL;
						}
						else if (g_lb->flags & CMF_DEFINED)
							LexExcept(cc, "Duplicate goto label at ");
						g_lb->flags |= CMF_DEFINED;
						ICAdd(cc, IC_LABEL, g_lb, 0);
						if (Lex(cc) == ':') //skip cur_str
							Lex(cc); //skip colon
						else
							LexExcept(cc, "Undefined identifier at ");
						if (!cc->htc.fun)
							LexExcept(cc, "No global labels at ");
						if (cc->token != ',')
							goto sm_done;
					}
				}
				else if (cc->token == TK_STR || cc->token == TK_CHAR_CONST)
				{
					ParseFunCall(cc, NULL, FALSE, NULL);
					goto sm_semicolon;
				}
				else if (cc->token != TK_EOF)
				{//Non-cur_str symbol, num or something
sm_parse_exp:
					if (!ParseExpression(cc, NULL, TRUE))
						throw('Compiler');
sm_semicolon:
					if (comp_flags & CMPF_PRS_SEMICOLON)
					{
						if (cc->token == ';')
							Lex(cc);
						else if (cc->token != ',')
							LexExcept(cc, "Missing ';' at");
					}
					if (cc->token != ',')
						goto sm_done;
				}
				else
					goto sm_done; //TK_EOF
			}
		}
sm_done:

	return fsp_flags & FSF_ASM;
}
