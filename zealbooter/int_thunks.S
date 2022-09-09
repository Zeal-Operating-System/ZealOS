.altmacro

.macro THUNK num
interrupt_thunk_\num:
.if \num != 8 && \num != 10 && \num != 11 && \num != 12 && \num != 13 && \num != 14 && \num != 17 && \num != 30
    push $0
.endif

    push %r15
    push %r14
    push %r13
    push %r12
    push %r11
    push %r10
    push %r9
    push %r8
    push %rbp
    push %rdi
    push %rsi
    push %rdx
    push %rcx
    push %rbx
    push %rax
    mov %es, %eax
    push %rax
    mov %ds, %eax
    push %rax

    cld

    mov $\num, %rdi
    mov $(\num * 8), %rax
    lea isr(%rip), %rbx
    add %rax, %rbx
    mov %rsp, %rsi
    call *(%rbx)

.endm

.macro THUNKADDR num
    .quad interrupt_thunk_\num
.endm

.section .data

.global isr_thunks
.align 8
isr_thunks:
.set i,0
.rept 256
    THUNKADDR %i
    .set i,i+1
.endr

.section .text

.set i,0
.rept 256
    THUNK %i
    .set i,i+1
.endr
