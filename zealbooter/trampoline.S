.section .text

.global trampoline
trampoline:
    lgdt (%rcx)

    pushq $0x30
    addq $(1f - trampoline), %rax
    pushq %rax
    lretq

    .code32
    1:

    mov $0x10, %eax
    mov %eax, %ds
    mov %eax, %es
    mov %eax, %fs
    mov %eax, %gs
    mov %eax, %ss

    mov %cr0, %eax
    btr $31, %eax
    mov %eax, %cr0

    mov $0xc0000080, %ecx
    xor %eax, %eax
    xor %edx, %edx
    wrmsr

    mov %ebx, %eax
    mov $2, %ebx

    jmp *%eax

.global trampoline_end
trampoline_end:
