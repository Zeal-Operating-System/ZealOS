.section .text

.global lower
lower:
    pushq $0x18
    addq $(1f - lower), %rax
    pushq %rax
    lretq

    .code32
    1:

    mov $0x20, %eax
    mov %eax, %ds
    mov %eax, %es
    mov %eax, %fs
    mov %eax, %gs
    mov %eax, %ss

    lgdt (%ecx)

    mov %cr0, %eax
    btr $31, %eax
    mov %eax, %cr0

    mov $0xc0000080, %ecx
    xor %eax, %eax
    xor %edx, %edx
    wrmsr

    mov %ebx, %eax
    mov $2, %ebx

    mov $0x7c00, %esp
    jmp *%eax

