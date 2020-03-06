Bool ParseAsmImm(CCompCtrl *cc, CAsmArg *arg)
{
	if (arg->imm_or_off_present)
		LexExcept(cc,"Already one immediate at ");

	arg->imm_or_off_present = TRUE;
	arg->num.local_asm_undef_hash = NULL;
	arg->num.global_asm_undef_hash = NULL;
	cc->asm_undef_hash = NULL;
	cc->abs_counts = 0;
	cc->flags &= ~(CCF_UNRESOLVED + CCF_LOCAL);

	if (!IsLexExpression2Bin(cc, &arg->num.machine_code))
		LexSkipEol(cc);
	else
	{
		if (cc->abs_counts.externs)
			LexExcept(cc,"Extern Not Allowed at ");
		if (cc->flags & CCF_UNRESOLVED)
		{
			if (cc->flags & CCF_LOCAL)
				arg->num.local_asm_undef_hash = cc->asm_undef_hash;
			else
				arg->num.global_asm_undef_hash = cc->asm_undef_hash;

			cc->asm_undef_hash = NULL;
		} 
		else
		{
			arg->num.i = Call(arg->num.machine_code);
			arg->num.global_asm_undef_hash = cc->asm_undef_hash;
			cc->asm_undef_hash = NULL;
			Free(arg->num.machine_code);
			arg->num.machine_code = NULL;
		}
	}
	return TRUE;
}

U0 ParseAsmArg(CCompCtrl *cc,CAsmArg *arg,Bool rel)
{
	CHashGeneric *tmph,*tmph1;
	CHashReg *tmpr;

	MemSet(arg, 0, sizeof(CAsmArg));

	arg->seg  = REG_NONE;
	arg->reg1 = REG_NONE;
	arg->reg2 = REG_NONE;
	arg->scale = 1;

	while (TRUE)
	{
		if (cc->token == TK_IDENT)
		{
			if (tmph = cc->hash_entry)
			{
				if (tmph->type & HTG_TYPE_MASK == HTT_REG)
				{
					tmpr = tmph;
					arg->reg1_type = tmpr->reg_type;
					switch (tmpr->reg_type)
					{
						start:
							case REGT_R8:
								arg->size = 1;
								break;
							case REGT_R16:
								arg->size = 2;
								break;
							case REGT_R32:
								arg->size = 4;
								break;
							case REGT_R64:
							case REGT_FSTACK:
								arg->size = 8;
								break;
							case REGT_XMM:
								arg->size = 16;
						end:
							arg->reg1 = tmpr->reg_num;
							Lex(cc);
							return;
						case REGT_SEG:
							arg->seg = tmpr->reg_num;
							if (Lex(cc) != ':')
							{
								arg->just_seg = TRUE;
								return;
							}
							else
								Lex(cc); //skip ":"
							break;
					}
				}
				else
				{
					if ((tmph->type & HTG_TYPE_MASK == HTT_CLASS || tmph->type & HTG_TYPE_MASK == HTT_INTERNAL_TYPE) &&
								(tmph1 = HashFind(cc->cur_str, comp.asm_hash, HTT_ASM_KEYWORD)))
						tmph = tmph1;
					if (tmph->type & HTG_TYPE_MASK == HTT_ASM_KEYWORD)
					{
						switch (tmph->user_data0) {
							case AKW_I8:
							case AKW_U8:
								arg->size = 1;
								break;
							case AKW_I16:
							case AKW_U16:
								arg->size = 2;
								break;
							case AKW_I32:
							case AKW_U32:
								arg->size = 4;
								break;
							case AKW_I64:
							case AKW_U64:
								arg->size = 8;
								break;
							default:
								LexExcept(cc, "syntax error at ");
						}
						Lex(cc); //skip keyword
					} else
						goto pa_asm_direct_imm;
				}
			}
			else
			{
pa_asm_direct_imm:
				ParseAsmImm(cc, arg);
				arg->num.abs_counts = cc->abs_counts;
				if (arg->size <= 1 && !rel && arg->num.abs_counts & 1)
				{
					if (cc->aotc->seg_size == 16)
						arg->size = 2;
					else
						arg->size = 4;
				}
				if (cc->token != '[')
					return;
			}
		}
		else if (cc->token == '[')
		{
			arg->indirect = TRUE;
			Lex(cc); // skip [
			while (cc->token && cc->token != ']')
			{
				if (cc->token == TK_IDENT)
				{
					if (tmph = cc->hash_entry)
					{
						if (tmph->type & HTG_TYPE_MASK == HTT_REG && REGT_R16 <= tmph(CHashReg *)->reg_type <= REGT_XMM)
						{
							tmpr = tmph;
							arg->reg2_type = tmpr->reg_type;

							if (arg->reg1 == REG_NONE)
							{
								if (tmpr->reg_num & 7 == REG_RSP)
								{
									arg->reg1 = 4;
									arg->reg2 = tmpr->reg_num;
								}
								else
									arg->reg1 = tmpr->reg_num;
							}
							else
								arg->reg2 = tmpr->reg_num;

							Lex(cc);
						}
						else
							goto pa_asm_indirect_imm;
					}
					else
						goto pa_asm_indirect_imm;
				}
				else if (cc->token == '*')
				{
					Lex(cc);

					if (cc->token != TK_I64)
						LexExcept(cc, "Expecting scale factor at ");

					arg->scale = cc->cur_i64;
					Lex(cc); //skip scale

					if (arg->reg2 != REG_NONE)
					{
						SwapI64(&arg->reg1, &arg->reg2);
						SwapI64(&arg->reg1_type, &arg->reg2_type);
					}
				}
				else if (cc->token == '+')
				{
					Lex(cc); //skip '+'
				}
				else
				{
pa_asm_indirect_imm:
					ParseAsmImm(cc, arg);
					arg->num.abs_counts = cc->abs_counts;
				}
			}
			if (cc->token != ']')
				LexExcept(cc, "Missing ']' at ");
			Lex(cc); //skip ']'
			return;
		}
		else
			goto pa_asm_direct_imm;
	}
}

I64 AsmMakeArgMask(CCompCtrl *cc, CAsmArg *arg)
{
	CAOTCtrl *aotc = cc->aotc;
	I64 res;

	if (arg->just_seg)
	{
		switch (arg->seg)
		{//null case starts at zero
			case: res = ARGT_ES | ARGT_SREG; break;
			case: res = ARGT_CS | ARGT_SREG; break;
			case: res = ARGT_SS | ARGT_SREG; break;
			case: res = ARGT_DS | ARGT_SREG; break;
			case: res = ARGT_FS | ARGT_SREG; break;
			case: res = ARGT_GS | ARGT_SREG; break;
		}
		goto mm_done;
	}

	if (arg->reg1_type == REGT_FSTACK)
	{
		if (arg->reg1)
			res = ARGT_STI;
		else
			res = ARGT_ST0 | ARGT_STI;
		goto mm_done;
	}

	res = comp.size_arg_mask[arg->size];

	if (aotc->seg_size == 64)
		res &= ~ARGG_MOFFS;

	if (arg->reg1 != REG_NONE && arg->imm_or_off_present && !arg->num.i && !arg->num.global_asm_undef_hash && !arg->num.local_asm_undef_hash)
		arg->imm_or_off_present = FALSE;	//Zero displacement

	if (arg->reg2 != REG_NONE || arg->scale != 1)
	{//if reg or scale
		res &= ARGG_M|ARGG_RM;
		goto mm_done;
	}

	if (arg->indirect)
	{
		if (arg->imm_or_off_present)
			res &= ARGG_RM | ARGG_M | ARGG_MN | ARGG_MOFFS;
		else
			res &= ARGG_RM | ARGG_M | ARGG_MN;
	}
	else
	{
		if (arg->imm_or_off_present)
			res &= ARGG_MN | ARGG_IMM | ARGG_UIMM | ARGG_REL;
		else
			res &= ARGG_R | ARGG_RM | ARGG_M | ARGG_MN | ARGG_AXCLDX;
	}

	if (arg->seg != REG_NONE)
		res &= ARGG_RM | ARGG_M | ARGG_MN | ARGG_MOFFS;

	if (arg->reg1 == REG_NONE)
	{
		if (arg->indirect)
			res &= ARGG_RM | ARGG_M | ARGG_MN | ARGG_MOFFS;
		else if (arg->num.i < 0)
		{
			if (arg->num.i >= I8_MIN)
				res &= ARGG_REL | ARGG_IMM;
			else if (arg->num.i >= I16_MIN)
				res &= ARGG_REL | ARGT_IMM64 | ARGT_IMM32 | ARGT_IMM16;
			else if (arg->num.i >= I32_MIN)
				res &= ARGG_REL | ARGT_IMM64 | ARGT_IMM32;
			else
				res &= ARGG_REL | ARGT_IMM64;
		}
		else
		{
			if (arg->num.i <= I8_MAX)
				res &= ARGG_REL | ARGG_IMM | ARGG_UIMM;
			else if (arg->num.i <= U8_MAX)
				res &= ARGG_REL | ARGG_IMM & ~ARGT_IMM8 | ARGG_UIMM;
			else if (arg->num.i <= I16_MAX)
				res &= ARGG_REL | ARGG_IMM & ~ARGT_IMM8 | ARGG_UIMM & ~ARGT_UIMM8;
			else if (arg->num.i <= U16_MAX)
				res &= ARGG_REL | ARGT_IMM64 | ARGT_IMM32 | ARGG_UIMM & ~ARGT_UIMM8;
			else if (arg->num.i <= I32_MAX)
				res &= ARGG_REL | ARGT_IMM64 | ARGT_IMM32 | ARGT_UIMM64 | ARGT_UIMM32;
			else if (arg->num.i <= U32_MAX)
				res &= ARGG_REL | ARGT_IMM64 | ARGT_UIMM64 | ARGT_UIMM32;
			else
				res &= ARGG_REL | ARGT_IMM64 | ARGT_UIMM64;
		}
	}
	else
	{
		res &= ARGG_R | ARGG_RM | ARGG_M | ARGG_AXCLDX;
		if (!arg->indirect) //M8-M128
			res &= ~ARGG_M;
	}

	switch (arg->reg1)
	{
		case REG_RAX: res &= ~(ARGT_CL | ARGT_DX);		break;
		case REG_RCX: res &= ~(ARGG_AXCLDX & ~ARGT_CL); break;
		case REG_RDX: res &= ~(ARGG_AXCLDX & ~ARGT_DX); break;
		default:      res &= ~ARGG_AXCLDX;
	}
mm_done:
	return res;
}

Bool AsmStoreNum(CCompCtrl *cc,  CAsmNum2 *num2, I64 count, Bool u8_avail)
{
	CAOTCtrl *aotc = cc->aotc;
	I64 i;
	CAOTAbsAddr *tmpa;

	if (!num2->imm_flag)
		num2->num.i -= num2->rel;

	for (i = 0; i < count; i++)
	{
		if (num2->u8_count == 1)
		{
			if (num2->num.local_asm_undef_hash || num2->num.global_asm_undef_hash)
				AsmUnresolvedAdd(cc, num2->num.machine_code, IET_REL_I8 + num2->imm_flag, aotc->rip, num2->rel, num2->num.local_asm_undef_hash, 
							num2->num.global_asm_undef_hash, cc->lex_include_stack->line_num, u8_avail);
			else if (!num2->imm_flag && !(I8_MIN <= num2->num.i <= I8_MAX))
				LexExcept(cc, "Branch out of range at ");

			if (num2->imm_flag)
			{
				if (num2->num.abs_counts.abs_address & 1)
				{
					tmpa = CAlloc(sizeof(CAOTAbsAddr));
					tmpa->next = aotc->abss;
					aotc->abss = tmpa;
					tmpa->rip = aotc->rip;
					tmpa->type = AAT_ADD_U8;
				}
			}
			else
			{
				if (num2->num.abs_counts.c_address & 1)
				{
					tmpa = CAlloc(sizeof(CAOTAbsAddr));
					tmpa->next = aotc->abss;
					aotc->abss = tmpa;
					tmpa->rip = aotc->rip;
					tmpa->type = AAT_SUB_U8;
				}
			}
			AOTStoreCodeU8(cc, num2->num.i);
		}
		else
		{
			if (num2->u8_count == 2)
			{
				if (num2->num.local_asm_undef_hash || num2->num.global_asm_undef_hash)
					AsmUnresolvedAdd(cc, num2->num.machine_code, IET_REL_I16 + num2->imm_flag, aotc->rip, num2->rel, num2->num.local_asm_undef_hash, 
								num2->num.global_asm_undef_hash, cc->lex_include_stack->line_num, u8_avail);
				else if (!num2->imm_flag && !(I16_MIN <= num2->num.i <= I16_MAX))
					LexExcept(cc, "Branch out of range at ");

				if (num2->imm_flag)
				{
					if (num2->num.abs_counts.abs_address & 1)
					{
						tmpa = CAlloc(sizeof(CAOTAbsAddr));
						tmpa->next = aotc->abss;
						aotc->abss = tmpa;
						tmpa->rip  = aotc->rip;
						tmpa->type = AAT_ADD_U16;
					}
				}
				else
				{
					if (num2->num.abs_counts.c_address & 1)
					{
						tmpa = CAlloc(sizeof(CAOTAbsAddr));
						tmpa->next = aotc->abss;
						aotc->abss = tmpa;
						tmpa->rip  = aotc->rip;
						tmpa->type = AAT_SUB_U16;
					}
				}
				AOTStoreCodeU8(cc, num2->num.i.u8[0]);
				AOTStoreCodeU8(cc, num2->num.i.u8[1]);

			}
			else if (num2->u8_count==4)
			{
				if (num2->num.local_asm_undef_hash||num2->num.global_asm_undef_hash)
					AsmUnresolvedAdd(cc, num2->num.machine_code, IET_REL_I32+num2->imm_flag, aotc->rip, num2->rel, num2->num.local_asm_undef_hash, 
								num2->num.global_asm_undef_hash, cc->lex_include_stack->line_num, u8_avail);
				else if (!num2->imm_flag && !(I32_MIN <= num2->num.i <= I32_MAX))
					LexExcept(cc, "Branch out of range at ");

				if (num2->imm_flag)
				{
					if (num2->num.abs_counts.abs_address & 1)
					{
						tmpa = CAlloc(sizeof(CAOTAbsAddr));
						tmpa->next = aotc->abss;
						aotc->abss = tmpa;
						tmpa->rip  = aotc->rip;
						tmpa->type = AAT_ADD_U32;
					}
				}
				else
				{
					if (num2->num.abs_counts.c_address & 1)
					{
						tmpa = CAlloc(sizeof(CAOTAbsAddr));
						tmpa->next = aotc->abss;
						aotc->abss = tmpa;
						tmpa->rip  = aotc->rip;
						tmpa->type = AAT_SUB_U32;
					}
				}
				AOTStoreCodeU32(cc, num2->num.i);
			}
			else if (num2->u8_count == 8)
			{
				if (num2->num.local_asm_undef_hash || num2->num.global_asm_undef_hash)
					AsmUnresolvedAdd(cc, num2->num.machine_code, IET_REL_I64 + num2->imm_flag, aotc->rip, num2->rel, num2->num.local_asm_undef_hash, 
								num2->num.global_asm_undef_hash, cc->lex_include_stack->line_num, u8_avail);

				if (num2->imm_flag)
				{
					if (num2->num.abs_counts.abs_address & 1)
					{
						tmpa = CAlloc(sizeof(CAOTAbsAddr));
						tmpa->next = aotc->abss;
						aotc->abss = tmpa;
						tmpa->rip  = aotc->rip;
						tmpa->type = AAT_ADD_U64;
					}
				}
				else
				{
					if (num2->num.abs_counts.c_address & 1)
					{
						tmpa = CAlloc(sizeof(CAOTAbsAddr));
						tmpa->next = aotc->abss;
						aotc->abss = tmpa;
						tmpa->rip  = aotc->rip;
						tmpa->type = AAT_SUB_U64;
					}
				}
				AOTStoreCodeU64(cc, num2->num.i);
			}
			if (u8_avail && !num2->num.local_asm_undef_hash && !num2->num.global_asm_undef_hash && !num2->imm_flag && -124 <= num2->num.i <= 123)
			{
				LexWarn(cc, "could use I8 displacement at ");
				return FALSE;
			}
		}
	}
	return TRUE;
}

U8 asm_seg_prefixes[6]={0x26, 0x2E, 0x36, 0x3E, 0x64, 0x65};

Bool ParseAsmInst(CCompCtrl *cc, CHashOpcode *tmpo, I64 argcount)
{
	CAOTCtrl *aotc = cc->aotc;
	I64 i, j, arg1, arg2, ocm, seg, arg1mask, arg2mask;
	CAsmArg *tmpa1, *tmpa2;
	Bool ModrM_complete, u8_avail = FALSE, found_second_possible = FALSE;
	CInst *tmpins;
	CAsmInst cur, best;

	best.u8_count = 255;

	arg1mask = arg2mask = 1;

	if (argcount > 0)
		arg1mask=AsmMakeArgMask(cc, &aotc->arg1);
	if (argcount > 1)
		arg2mask=AsmMakeArgMask(cc, &aotc->arg2);

	for (i = 0; i < tmpo->inst_entry_count; i++)
	{
		tmpins = &tmpo->ins[i];

		if (tmpins->arg1 == ARGt_REL8 || tmpins->arg2 == ARGt_REL8)
			u8_avail = TRUE;

		if (Bt(&arg1mask, tmpins->arg1) && Bt(&arg2mask, tmpins->arg2) && (!(tmpins->flags & IEF_NOT_IN_64_BIT) || aotc->seg_size != 64))
		{
			MemSet(&cur, 0, sizeof(CAsmInst));
			cur.tmpins = tmpins;
			ModrM_complete = FALSE;
			cur.is_default = ToBool(tmpins->flags & IEF_DEFAULT);

			if (aotc->seg_size == 64)
			{
				if (tmpins->flags & IEF_48_REX)
					cur.REX = 0x48;
				else
					cur.REX = 0x40;
			}

			cur.disp.imm_flag = TRUE;
			cur.imm.imm_flag = TRUE;
			ocm = tmpins->opcode_modifier;
			arg1 = 1 << tmpins->arg1;
			arg2 = 1 << tmpins->arg2;
			tmpa1 = &aotc->arg1;
			tmpa2 = &aotc->arg2;
			cur.last_opcode_U8 = tmpins->opcode[tmpins->opcode_count - 1];

			if (tmpins->slash_val < 8)
			{
				cur.ModrM |= tmpins->slash_val << 3;
				cur.has_ModrM = TRUE;
			}

			if (aotc->seg_size == 16 && tmpins->flags & IEF_OP_SIZE32 || aotc->seg_size!=16 && tmpins->flags & IEF_OP_SIZE16)
				cur.has_operand_prefix = TRUE;

			switch (ocm)
			{
				case OCM_CB:
					cur.imm.imm_flag = FALSE;
				case OCM_IB:
					cur.imm.u8_count = 1;
					break;
				case OCM_CW:
					cur.imm.imm_flag = FALSE;
				case OCM_IW:
					cur.imm.u8_count = 2;
					break;
				case OCM_CD:
					cur.imm.imm_flag = FALSE;
				case OCM_ID:
					cur.imm.u8_count = 4;
			}

			if (argcount == 1)
			{
				if (best.u8_count != 255 && !found_second_possible && !best.is_default)
				{
					found_second_possible = TRUE;

					if (!aotc->arg1.size)
						PrintWarn("no size specified at %s : Line %04d\n", cc->lex_include_stack->full_name, cc->lex_include_stack->line_num - 1);
				}

				if (tmpins->flags & IEF_PLUS_OPCODE)
				{
					if (tmpins->slash_val == SV_R_REG)
					{
						cur.last_opcode_U8 |= tmpa1->reg1 & 7;

						if (tmpa1->reg1 & 15 > 7)
							cur.REX |= 1;

						if (tmpa1->reg1 >= 20) //RBPu8, RSPu8, RSIu8, RDIu8?
							cur.has_REX = TRUE;
					}
					else
					{//SV_I_REG
						if (tmpa1->reg1_type == REGT_FSTACK)
							cur.last_opcode_U8 += tmpa1->reg1;
					}
				}

				if (arg1 == ARGT_R64 || arg1 == ARGT_RM64 || arg1 == ARGT_M64)
					cur.REX |= 8;

				if (arg1 & (ARGG_RM | ARGG_M))
				{
					if (aotc->seg_size == 16)
						cur.has_addr_prefix = TRUE;

					cur.has_ModrM = TRUE;
					if (tmpa1->imm_or_off_present && tmpa1->indirect && tmpa1->reg1 == REG_NONE)
					{
						cur.ModrM = cur.ModrM + 5;
						MemCopy(&cur.disp.num, &tmpa1->num, sizeof(CAsmNum));
						cur.disp.u8_count = 4;

						if (aotc->seg_size == 64)
							cur.disp.imm_flag = FALSE;
					}
					else
					{
						if (tmpa1->reg2 == REG_NONE && tmpa1->scale == 1)
						{
							cur.ModrM |= tmpa1->reg1 & 7;
							if (tmpa1->reg1 & 0xF > 7)
								cur.REX |= 1;
							if (tmpa1->reg1 >= 20) //RBPu8, RSPu8, RSIu8, RDIu8?
								cur.has_REX = TRUE;
						}
						else
						{
							cur.ModrM |= 4;
							cur.has_SIB = TRUE;

							switch (tmpa1->scale)
							{
								case 1: cur.SIB = 0x00;	break;
								case 2: cur.SIB = 0x40; break;
								case 4: cur.SIB = 0x80; break;
								case 8: cur.SIB = 0xC0; break;
							}

							if (tmpa1->reg2 == REG_NONE)
							{
								ModrM_complete = TRUE;
								cur.SIB |= (tmpa1->reg1 & 7) << 3 + REG_RBP;

								if (tmpa1->reg1 & 15 > 7)
									cur.REX |= 2;

								if (tmpa1->reg1 >= 20) //RBPu8, RSPu8, RSIu8, RDIu8?
									cur.has_REX = TRUE;

								MemCopy(&cur.disp.num, &tmpa1->num, sizeof(CAsmNum));
								cur.disp.u8_count = 4;
							}
							else
							{
								cur.SIB |= (tmpa1->reg1 & 7) << 3 + tmpa1->reg2 & 7;

								if (tmpa1->reg1 & 0xF > 7)
									cur.REX |= 2;

								if (tmpa1->reg1 >= 20) //RBPu8, RSPu8, RSIu8, RDIu8?
									cur.has_REX = TRUE;

								if (tmpa1->reg2 & 0xF > 7)
									cur.REX |= 1;

								if (tmpa1->reg2 >= 20) //RBPu8, RSPu8, RSIu8, RDIu8?
									cur.has_REX = TRUE;

								if (tmpa1->reg2 & 7 == REG_RBP && !tmpa1->imm_or_off_present && tmpa1->indirect)
								{
									cur.ModrM |= 0x40;
									cur.disp.u8_count = 1;
									ModrM_complete = TRUE;
								}
							}
						}

						if (!ModrM_complete)
						{
							if (tmpa1->imm_or_off_present)
							{
								MemCopy(&cur.disp.num, &tmpa1->num, sizeof(CAsmNum));

								if (!cur.disp.num.machine_code && I8_MIN <= cur.disp.num.i <= I8_MAX)
								{
									cur.ModrM |= 0x40;
									cur.disp.u8_count = 1;
								}
								else if (aotc->seg_size == 16)
								{
									cur.ModrM |= 0x80;
									cur.disp.u8_count = 2;
								}
								else
								{
									cur.ModrM |= 0x80;
									cur.disp.u8_count = 4;
								}
							}
							else if (!tmpa1->indirect)
							{
								cur.has_addr_prefix = FALSE;
								cur.ModrM |= 0xC0;
							}
							else
							{
								if (tmpa1->reg1 & 7 == REG_RBP)
								{
									cur.ModrM |= 0x40;
									cur.disp.u8_count = 1;
								}
							}
						}
					}
				}
				else if (arg1 & (ARGG_REL | ARGG_IMM | ARGG_UIMM))
				{
					if (arg1 == ARGT_IMM64 || arg2 == ARGT_UIMM64)
						cur.REX |= 8;
					MemCopy(&cur.imm.num, &tmpa1->num, sizeof(CAsmNum));
				}
			}
			else if (argcount == 2)
			{
				if (best.u8_count != 255 && !found_second_possible && !best.is_default)
				{
					found_second_possible = TRUE;
					if (!aotc->arg1.size && !aotc->arg2.size)
						PrintWarn("no size specified at %s, %04d\n", cc->lex_include_stack->full_name, cc->lex_include_stack->line_num - 1);
				}

				if (tmpins->flags & IEF_PLUS_OPCODE)
				{
					if (tmpins->slash_val == SV_R_REG)
					{
						if (arg1 & (ARGG_AXCLDX & ~(ARGT_CL | ARGT_DX)))
						{
							cur.last_opcode_U8 |= tmpa2->reg1 & 7;

							if (tmpa2->reg1 & 0xF > 7)
								cur.REX |= 1;

							if (tmpa2->reg1 >= 20) //RBPu8, RSPu8, RSIu8, RDIu8?
								cur.has_REX = TRUE;
						}
						else
						{
							cur.last_opcode_U8 |= tmpa1->reg1 & 7;

							if (tmpa1->reg1 & 15 > 7)
								cur.REX |= 1;

							if (tmpa1->reg1 >= 20) //RBPu8, RSPu8, RSIu8, RDIu8?
								cur.has_REX = TRUE;
						}
					}
					else
					{//SV_I_REG
						if (tmpa1->reg1_type == REGT_FSTACK)
							cur.last_opcode_U8 |= tmpa1->reg1;

						if (tmpa2->reg1_type == REGT_FSTACK)
							cur.last_opcode_U8 |= tmpa2->reg1;
					}
				}

				if	(arg1 == ARGT_RM64 || arg2 == ARGT_RM64 ||
					 arg1 == ARGT_M64  || arg2 == ARGT_M64  ||
					 arg1 == ARGT_R64  || arg2 == ARGT_R64)
					cur.REX |= 8;

				if (arg1 & (ARGG_RM | ARGG_M) || arg2 & (ARGG_M | ARGG_RM))
				{
					if (aotc->seg_size == 16)
						cur.has_addr_prefix = TRUE;
					cur.has_ModrM = TRUE;

					if (arg2 & (ARGG_RM | ARGG_M)) {
						tmpa1 = &aotc->arg2;
						tmpa2 = &aotc->arg1;
					}

					if (tmpins->slash_val == SV_R_REG)
					{
						if (tmpa2->just_seg)
							cur.ModrM |= tmpa2->seg << 3;
						else
						{
							if (tmpa2->reg1 == REG_NONE)
							{
								cur.ModrM |= (tmpa1->reg1 & 7) << 3;

								if (tmpa1->reg1 & 0xF > 7)
									cur.REX |= 4;

								if (tmpa1->reg1 >= 20) //RBPu8, RSPu8, RSIu8, RDIu8?
									cur.has_REX = TRUE;
							}
							else
							{
								cur.ModrM |= (tmpa2->reg1 & 7) << 3;

								if (tmpa2->reg1 & 0xF > 7)
									cur.REX |= 4;
								if (tmpa2->reg1 >= 20) //RBPu8, RSPu8, RSIu8, RDIu8?
									cur.has_REX = TRUE;
							}
						}
					}

					if (tmpa1->reg2 == REG_NONE && tmpa1->scale == 1)
					{
						if (tmpa1->reg1 != REG_NONE)
						{
							cur.ModrM |= tmpa1->reg1 & 7;

							if (tmpa1->reg1 & 15 > 7)
								cur.REX |= 1;

							if (tmpa1->reg1 >= 20) //RBPu8, RSPu8, RSIu8, RDIu8?
								cur.has_REX=TRUE;
						}
					}
					else
					{
						cur.ModrM |= 4;
						cur.has_SIB = TRUE;

						switch (tmpa1->scale)
						{
							case 1: cur.SIB = 0;    break;
							case 2: cur.SIB = 0x40; break;
							case 4:	cur.SIB = 0x80; break;
							case 8: cur.SIB = 0xC0; break;
						}

						if (tmpa1->reg2 == REG_NONE)
						{
							ModrM_complete = TRUE;
							cur.SIB |= (tmpa1->reg1 & 7) << 3 + 5;
							if (tmpa1->reg1 & 0xF > 7)
								cur.REX |= 2;
							if (tmpa1->reg1 >= 20) //RBPu8, RSPu8, RSIu8, RDIu8?
								cur.has_REX = TRUE;
							MemCopy(&cur.disp.num, &tmpa1->num, sizeof(CAsmNum));
							cur.disp.u8_count = 4;
						}
						else
						{
							cur.SIB |= (tmpa1->reg1 & 7) << 3 + tmpa1->reg2 & 7;

							if (tmpa1->reg1 & 0xF > 7)
								cur.REX |= 2;

							if (tmpa1->reg1 >= 20) //RBPu8, RSPu8, RSIu8, RDIu8?
								cur.has_REX = TRUE;

							if (tmpa1->reg2 & 15 > 7)
								cur.REX |= 1;

							if (tmpa1->reg2 >= 20) //RBPu8, RSPu8, RSIu8, RDIu8?
								cur.has_REX=TRUE;

							if (tmpa1->reg2 & 7 == REG_RBP && !tmpa1->imm_or_off_present && tmpa1->indirect)
							{
								cur.ModrM |= 0x40;
								cur.disp.u8_count = 1;
								ModrM_complete = TRUE;
							}
						}
					}

					if (!ModrM_complete)
					{
						if (tmpa1->imm_or_off_present && tmpa1->indirect && tmpa1->reg1 == REG_NONE)
						{
							cur.ModrM = cur.ModrM & 0xF8 + 5;
							MemCopy(&cur.disp.num, &tmpa1->num, sizeof(CAsmNum));
							cur.disp.u8_count = 4;
							if (aotc->seg_size == 64)
								cur.disp.imm_flag = FALSE;
						}
						else
						{
							if (tmpa1->imm_or_off_present)
							{
								MemCopy(&cur.disp.num, &tmpa1->num, sizeof(CAsmNum));

								if (!cur.disp.num.machine_code && I8_MIN <= cur.disp.num.i <= I8_MAX)
								{
									cur.ModrM |= 0x40;
									cur.disp.u8_count = 1;
								}
								else if (aotc->seg_size == 16)
								{
									cur.ModrM |= 0x80;
									cur.disp.u8_count = 2;
								}
								else
								{
									cur.ModrM |= 0x80;
									cur.disp.u8_count = 4;
								}
							}
							else if (!tmpa1->indirect)
							{
								cur.has_addr_prefix = FALSE;
								cur.ModrM |= 0xC0;
							}
							else
							{
								if (tmpa1->reg1 & 7 == REG_RBP)
								{
									cur.ModrM |= 0x40;
									cur.disp.u8_count = 1;
								}
							}
						}
					}
				}
				else if (arg1 & ARGG_MOFFS)
				{
					MemCopy(&cur.disp.num, &tmpa1->num, sizeof(CAsmNum));
					if (aotc->seg_size == 16)
						cur.disp.u8_count = 2;
					else
						cur.disp.u8_count = 4;
					cur.has_addr_prefix = FALSE;
				}
				else if (arg2 & ARGG_MOFFS)
				{
					MemCopy(&cur.disp.num, &tmpa2->num, sizeof(CAsmNum));
					if (aotc->seg_size == 16)
						cur.disp.u8_count = 2;
					else
						cur.disp.u8_count = 4;
					cur.has_addr_prefix = FALSE;
				}
				else if (arg1 & (ARGG_IMM | ARGG_UIMM))
				{
					MemCopy(&cur.imm.num, &tmpa1->num, sizeof(CAsmNum));
					if		(arg1 & ARGG_SIZE_1) cur.imm.u8_count = 1;
					else if (arg1 & ARGG_SIZE_2) cur.imm.u8_count = 2;
					else if (arg1 & ARGG_SIZE_4) cur.imm.u8_count = 4;
					else
					{
						cur.imm.u8_count = 8;
						cur.REX |= 8;
					}
				}

				if (arg2 & (ARGG_IMM | ARGG_UIMM))
				{
					MemCopy(&cur.imm.num, &tmpa2->num, sizeof(CAsmNum));

					if		(arg2 & ARGG_SIZE_1) cur.imm.u8_count = 1;
					else if (arg2 & ARGG_SIZE_2) cur.imm.u8_count = 2;
					else if (arg2 & ARGG_SIZE_4)
					{
						cur.imm.u8_count = 4;

						if (tmpins->flags & IEF_REX_ONLY_R8_R15 && arg2 == ARGT_UIMM32)
							cur.REX &= ~8;
					}
					else
					{
						cur.imm.u8_count = 8;
						cur.REX |= 8;
					}
				}
			}
			cur.u8_count = tmpins->opcode_count + cur.disp.u8_count + cur.imm.u8_count;

			if (cur.has_ModrM)	cur.u8_count++;
			if (cur.has_SIB)	cur.u8_count++;

			if (aotc->seg_size == 64 && cur.REX & 0x40 == 0x40 && (cur.REX != 0x40 || cur.has_REX) && (cur.REX & 7 || !(tmpins->flags & IEF_REX_ONLY_R8_R15 ||
										 tmpins->flags & IEF_REX_XOR_LIKE && tmpa1->reg1 == tmpa2->reg1 && cur.ModrM & 0xC0 == 0xC0)))
				cur.u8_count++;

			if (cur.u8_count < best.u8_count && !(tmpins->flags & IEF_DONT_SWITCH_MODES && (cur.has_addr_prefix || cur.has_operand_prefix)))
				MemCopy(&best, &cur, sizeof(CAsmInst));
		}
	}

	if (best.u8_count < 255)
	{
		tmpins = best.tmpins;
		seg = REG_NONE;

		if (argcount > 1 && aotc->arg2.seg != REG_NONE && !aotc->arg2.just_seg)
			seg = aotc->arg2.seg;
		else if (argcount > 0 && aotc->arg1.seg != REG_NONE && !aotc->arg1.just_seg)
			seg = aotc->arg1.seg;

		if (seg != REG_NONE)
			AOTStoreCodeU8(cc, asm_seg_prefixes[seg]);

		if (best.has_operand_prefix)
			AOTStoreCodeU8(cc, OC_OP_SIZE_PREFIX); //Operand size override

		if (best.has_addr_prefix	|| aotc->seg_size==16 && cur.has_SIB)
			AOTStoreCodeU8(cc, OC_ADDR_SIZE_PREFIX); //Operand size override

		if (aotc->seg_size == 64 && best.REX & 0x40 == 0x40 && (best.REX != 0x40 || best.has_REX) &&
					(best.REX & 7 || !(tmpins->flags & IEF_REX_ONLY_R8_R15 || tmpins->flags & IEF_REX_XOR_LIKE && tmpa1->reg1 == tmpa2->reg1 && best.ModrM & 0xC0 == 0xC0)))
			AOTStoreCodeU8(cc, best.REX);

		for (j = 0; j < tmpins->opcode_count - 1; j++)
			AOTStoreCodeU8(cc, tmpins->opcode[j]);

		AOTStoreCodeU8(cc, best.last_opcode_U8);

		if (best.has_ModrM)
			AOTStoreCodeU8(cc, best.ModrM);

		if (best.has_SIB)
			AOTStoreCodeU8(cc, best.SIB);

		if (best.disp.u8_count)
		{
			best.disp.rel = aotc->rip + best.disp.u8_count + best.imm.u8_count;

			if (!AsmStoreNum(cc, &best.disp, 1, u8_avail))
				return FALSE;
		}

		if (best.imm.u8_count)
		{
			best.imm.rel = aotc->rip+best.imm.u8_count;

			if (!AsmStoreNum(cc, &best.imm, 1, u8_avail))
				return FALSE;
		}

		if (tmpins->flags & IEF_ENDING_ZERO) //ENTER inst
			AOTStoreCodeU8(cc, 0);

		return TRUE;
	}

	LexExcept(cc, "Invalid instruction at ");
}

U0 ParseAsmDefine(CCompCtrl *cc, I64 u8_count)
{
	Bool is_dup;
	I64 i, dup_val;
	U8 *ptr;
	CAsmNum2 num2;
	num2.u8_count = u8_count;

	while (cc->token && cc->token != ';')
	{
		num2.num.local_asm_undef_hash = NULL;
		num2.num.global_asm_undef_hash = NULL;

		if (cc->token == TK_STR)
		{
			ptr = cc->cur_str;
			i = cc->cur_str_len - 1;

			while (i--)
				AOTStoreCodeU8(cc, *ptr++);

			Lex(cc);	//Skip Str
		}
		else
		{
			is_dup = FALSE;
			cc->abs_counts = 0;
			cc->asm_undef_hash = NULL;
			cc->flags &= ~(CCF_UNRESOLVED + CCF_LOCAL);

			if (!IsLexExpression2Bin(cc, &num2.num.machine_code))
				LexSkipEol(cc);
			else
			{
				if (cc->abs_counts.externs)
					LexExcept(cc, "Extern not allowed at ");

				if (cc->flags & CCF_UNRESOLVED)
				{
					if (cc->flags & CCF_LOCAL)
					{
						num2.num.local_asm_undef_hash = cc->asm_undef_hash;
						cc->asm_undef_hash = NULL;
					}
					else
					{
						num2.num.global_asm_undef_hash = cc->asm_undef_hash;
						cc->asm_undef_hash = NULL;
					}
				}
				else
				{
					i = Call(num2.num.machine_code);
					Free(num2.num.machine_code);
				}
			}

			if (cc->token == TK_IDENT && cc->hash_entry)
			{
				if (cc->hash_entry->type & HTT_ASM_KEYWORD && cc->hash_entry->user_data0 == AKW_DUP)
				{
					is_dup = TRUE;

					if (Lex(cc) != '(')
						LexExcept(cc, "Expecting '(' at ");

					Lex(cc); //skip (
					dup_val = AsmLexExpression(cc);

					if (cc->token != ')')
						LexExcept(cc, "Expecting ')' at ");

					Lex(cc); //SKIP )
				}
			}
			num2.rel = 0;
			num2.imm_flag = TRUE;
			num2.num.abs_counts = cc->abs_counts;
			if (is_dup)
			{
				if (num2.num.local_asm_undef_hash || num2.num.global_asm_undef_hash)
					LexExcept(cc, "Undefined DUP count at ");
				num2.num.i = dup_val;
				AsmStoreNum(cc, &num2, i, FALSE);
			}
			else
			{
				num2.num.i = i;
				AsmStoreNum(cc, &num2, 1, FALSE);
			}
		}
		if (cc->token==',')
			Lex(cc);
	}
	if (cc->token!=';')
		LexExcept(cc, "Missing ';' at ");

	Lex(cc);
}

U0 ParseBinFile(CCompCtrl *cc)
{
	I64 i, size;
	U8 *buf, *st;

	if (cc->token != TK_STR)
		LexExcept(cc, "Expecting string at ");

	st = ExtDefault(cc->cur_str, "BIN");
	buf = FileRead(st, &size);
	Free(st);

	for (i = 0; i < size; i++)
		AOTStoreCodeU8(cc, buf[i]);

	if (Lex(cc) != ';')
		LexExcept(cc, "Missing ';' at ");

	Lex(cc);
}

U0 ParseAsmBlk(CCompCtrl *cc, I64 comp_flags)
{
	CAOTCtrl *aotc = cc->aotc;
	I64 i, j, k, argcount,  old_flags = cc->flags & CCF_ASM_EXPRESSIONS;
	CHashOpcode *tmpo;
	CHashExport *tmpex;
	U8 *next_last_label;
	CCodeMisc *g_lb;

	aotc->seg_size = 64;
	cc->flags |= CCF_ASM_EXPRESSIONS;

	if (!(comp_flags & CMPF_ONE_ASM_INS))
	{
		if (cc->token != '{')
			LexExcept(cc, "Expecting '{' at ");

		Lex(cc);
	}

	while (cc->token && cc->token!='}')
	{
		AsmLineList(cc);

		if (cc->token == TK_IDENT && cc->hash_entry)
		{
			if (cc->hash_entry->type & HTT_ASM_KEYWORD)
			{
				i = cc->hash_entry->user_data0;
				Lex(cc); //skip keyword

				switch (i)
				{
					case AKW_IMPORT:
						while (cc->token && cc->token != ';')
						{
							if (cc->token != TK_IDENT)
								LexExcept(cc, "Expecting identifier at ");
							else
							{
								tmpex = NULL;
								tmpex = CAlloc(sizeof(CHashExport));
								tmpex->str = cc->cur_str;
								cc->cur_str = NULL;
								tmpex->type = HTT_EXPORT_SYS_SYM|HTF_UNRESOLVED;
								HashAdd(tmpex, cc->htc.global_hash_table);
								tmpex->type |= HTF_IMPORT;
								if (Lex(cc) == ',')
									Lex(cc); //skip ','
							}
						}

						if (cc->token != ';')
							LexExcept(cc, "Missing ';' at");
						Lex(cc); //skip ';';
						break;
					case AKW_ORG:
						if (cc->htc.local_var_list)
							LexExcept(cc, "ORG not allowed in function asm blk ");

						if (aotc->org != INVALID_PTR)
							LexExcept(cc, "Only one ORG allowed ");

						if (aotc->rip)
							LexExcept(cc, "ORG must be at beginning ");

						aotc->org = AsmLexExpression(cc);
						break;
					case AKW_ALIGN:
						if (cc->htc.local_var_list)
							LexExcept(cc, "ALIGN not allowed in function asm blk ");

						i = AsmLexExpression(cc);
						j = Bsf(i);
						if (!i || j != Bsr(i))
							LexExcept(cc, "ALIGN must be power of two at ");

						if (!(cc->flags & CCF_AOT_COMPILE) && i > 8)
							LexExcept(cc, "In JIT mode, max ALIGN is 8 ");

						if (j > aotc->max_align_bits)
							aotc->max_align_bits = j;

						i = CeilU64(aotc->rip, i);

						if (cc->token!=',')
							LexExcept(cc, "Expecting ',' at ");

						Lex(cc);
						k = AsmLexExpression(cc);

						for (j = aotc->rip; j < i; j++)
							AOTStoreCodeU8(cc, k);
						break;
					case AKW_DU8:
						ParseAsmDefine(cc, 1);
						break;
					case AKW_DU16:
						ParseAsmDefine(cc, 2);
						break;
					case AKW_DU32:
						ParseAsmDefine(cc, 4);
						break;
					case AKW_DU64:
						ParseAsmDefine(cc, 8);
						break;
					case AKW_BINFILE:
						ParseBinFile(cc);
						break;
					case AKW_LIST:
						aotc->list = TRUE;
						break;
					case AKW_NOLIST:
						aotc->list = FALSE;
						break;
					case AKW_USE16:
						aotc->seg_size = 16;
						break;
					case AKW_USE32:
						aotc->seg_size = 32;
						break;
					case AKW_USE64:
						aotc->seg_size = 64;
						break;
					default:
						LexExcept(cc, "Syntax error at ");
				}
			}
			else if (cc->hash_entry->type & HTT_OPCODE)
			{
				tmpo = cc->hash_entry;
				Lex(cc); //skip opcode
				argcount = 0;

				if (tmpo->ins[0].arg1)
				{
					argcount++;

					if (1 << tmpo->ins[0].arg1 & ARGG_REL)
						ParseAsmArg(cc, &aotc->arg1, TRUE);
					else
						ParseAsmArg(cc, &aotc->arg1, FALSE);

					if (tmpo->ins[0].arg2)
					{
						argcount++;

						if (cc->token != ',')
							LexExcept(cc, "Expecting ',' at ");
						else
						{
							Lex(cc); //skip ','

							if (1 << tmpo->ins[0].arg2 & ARGG_REL)
								ParseAsmArg(cc, &aotc->arg2, TRUE);
							else
								ParseAsmArg(cc, &aotc->arg2, FALSE);
						}
					}
				}
				ParseAsmInst(cc, tmpo, argcount);
			}
			else if (cc->hash_entry->type & HTT_EXPORT_SYS_SYM)
			{
				if (Btr(&cc->hash_entry->type, HTf_UNRESOLVED))
				{
					if (cc->hash_entry->type & HTF_LOCAL)
					{
						cc->hash_entry(CHashExport *)->val = aotc->rip;

						if (Lex(cc) != ':')
							LexExcept(cc, "Expecting ':' at ");

						Lex(cc);
					}
					else
					{
						if (cc->hash_entry->type & HTF_IMPORT)
							LexExcept(cc, "Attempt to define import at ");

						cc->hash_entry(CHashExport *)->val = aotc->rip;
						next_last_label = cc->hash_entry->str;
						Lex(cc); //Skip cur_str

						if (cc->token != ':' && cc->token != TK_DBL_COLON)
							LexExcept(cc, "Expecting ':' at ");

						if (cc->token == TK_DBL_COLON)
						{
							cc->hash_entry->type |= HTF_EXPORT;
							HashSrcFileSet(cc, cc->hash_entry);

							AOTLocalsResolve(cc);
							aotc->last_label = next_last_label;
						}
						Lex(cc);
					}
				}
				else if (cc->hash_entry(CHashExport *)->val == aotc->rip)
				{
					Lex(cc); //Skip cur_str
					if (cc->token != ':' && cc->token != TK_DBL_COLON)
						LexExcept(cc, "Expecting ':' at ");
					Lex(cc);
				}
				else
					LexExcept(cc, "Redefinition at ");
			}
			else
				LexExcept(cc, "Syntax error at ");
		}
		else if (cc->token == TK_IDENT)
		{
			tmpex = CAlloc(sizeof(CHashExport));
			tmpex->str = cc->cur_str;
			cc->cur_str = NULL;
			tmpex->type = HTT_EXPORT_SYS_SYM;
			tmpex->val = aotc->rip;
			Lex(cc);	//Skip cur_str
			if (cc->token!=':' && cc->token != TK_DBL_COLON)
				LexExcept(cc, "Expecting ':' at ");
			else
			{
				if (*tmpex->str == '@' && tmpex->str[1] == '@')
				{
					if (cc->token == TK_DBL_COLON)
						LexExcept(cc, "No local global exports at ");
					HashAdd(tmpex, cc->htc.local_hash_table);
				}
				else
					HashAdd(tmpex, cc->htc.global_hash_table);

				if (cc->htc.local_var_list)
				{//AsmBlk in fun? Also add goto-like label.
					if (!(g_lb = COCGoToLabelFind(cc, tmpex->str)))
					{
						g_lb = COCMiscNew(cc, CMT_ASM_LABEL);
						g_lb->str = StrNew(tmpex->str);
					}
					else if (g_lb->flags & CMF_DEFINED)
						LexExcept(cc, "Duplicate goto label at ");

					g_lb->type = CMT_ASM_LABEL;
					g_lb->flags |= CMF_DEFINED;
					g_lb->rip = aotc->rip;
					g_lb->use_count++; //Disable warning on unused labels.
					ICAdd(cc, IC_LABEL, g_lb, 0);
				}
				if (cc->token==TK_DBL_COLON)
				{
					tmpex->type |= HTF_EXPORT;
					HashSrcFileSet(cc, tmpex);

					AOTLocalsResolve(cc);
					aotc->last_label=tmpex->str;
				}

				Lex(cc);
			}
		}
		else if (cc->token == ';')
			Lex(cc);
		else
			LexExcept(cc, "Syntax error at ");

		if (comp_flags & CMPF_ONE_ASM_INS && (cc->token!=TK_IDENT || !(tmpo = cc->hash_entry) || !(tmpo->type & (HTT_OPCODE | HTT_ASM_KEYWORD))))
			break;
	}
	AOTLocalsResolve(cc);
	aotc->list = FALSE;
	cc->flags &= cc->flags & ~CCF_ASM_EXPRESSIONS | old_flags;
}
