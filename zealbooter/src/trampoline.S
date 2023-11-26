.section .text

.global trampoline
trampoline:
    // Set new stack
    mov %rdx, %rsp

    // Load GDTR
    lgdt (%rcx)

    // Far jump to 32-bit compatibility mode
    // AKA (set CS to CGDT.cs32)
    pushq $0x30
    addq $(1f - trampoline), %rax
    pushq %rax
    lretq

    .code32
    1:

    // Set all data segments to CGDT.ds
    mov $0x10, %eax
    mov %eax, %ds
    mov %eax, %es
    mov %eax, %fs
    mov %eax, %gs
    mov %eax, %ss

    // Disable paging
    mov %cr0, %eax
    btr $31, %eax
    mov %eax, %cr0

    // Disable LME and friends
    mov $0xc0000080, %ecx
    xor %eax, %eax
    xor %edx, %edx
    wrmsr

    // Set CR0 to (PE | NE) AKA SYS_START_CR0
    mov $0x11, %eax
    mov %eax, %cr0

    // Set flags to 0x02
    pushl $0x02
    popfl

    jmp *%ebx

.global trampoline_end
trampoline_end:
