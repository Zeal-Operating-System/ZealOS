I64 Cond(Bool cond, I64 true, I64 false) {
  if (cond)
    return true;
  return false;
}

U0 PatchCallRel32(U32 from, U32 to) {
  *(from(U8 *)) = 0xE8;
  *((from + 1)(I32 *)) = to - from - 5;
}

U0 PatchJmpRel32(U32 from, U32 to) {
  *(from(U8 *)) = 0xE9;
  *((from + 1)(I32 *)) = to - from - 5;
}

U0 EnableSSE() {
  asm
  {
  MOV_EAX_CR0
  AND AX, 0xFFFB // clear coprocessor emulation CR0.EM
  OR AX, 0x2 // set coprocessor monitoring  CR0.MP
  MOV_CR0_EAX
  MOV_EAX_CR4
  OR AX, 3 << 9 // set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
  MOV_CR4_EAX
  }
}

EnableSSE;
