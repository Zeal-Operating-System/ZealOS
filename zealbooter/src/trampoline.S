// Offsets into struct trampoline_args
.set ARGS_STACK, 0
.set ARGS_KERNEL, 4
.set ARGS_KERNEL_SIZE, 8
.set ARGS_KERNEL_BASE, 12
.set ARGS_GDT_PTR, 16
.set ARGS_ENTRY_POINT, 20
.set ARGS_PATCH_TABLE_BASE, 24
.set ARGS_BOOT_BASE, 28
.set ARGS_BOOT_STACK, 32

.section .text

.global trampoline
trampoline:
    // Set new stack
    movl ARGS_STACK(%rbx), %esp

    // Clear PCIDE, CR0.PG cannot be cleared with it set
    mov %cr4, %rcx
    btr $17, %rcx
    mov %rcx, %cr4

    // Far jump to 32-bit compatibility mode
    // AKA (set CS to Limine's 32-bit code descriptor)
    pushq $0x18
    addq $(1f - trampoline), %rax
    pushq %rax
    lretq

    .code32
    1:

    // Set all data segments to Limine's 32-bit data descriptor
    mov $0x20, %eax
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

    // Clear CR4
    mov %eax, %cr4

    // Copy the kernel to BOOT_RAM_BASE, nothing of Limine's is in use anymore
    mov ARGS_KERNEL(%ebx), %esi
    mov ARGS_KERNEL_BASE(%ebx), %edi
    mov ARGS_KERNEL_SIZE(%ebx), %ecx
    cld
    rep movsb

    // Load GDTR
    mov ARGS_GDT_PTR(%ebx), %eax
    lgdt (%eax)

    // Far jump to set CS to CGDT.cs32
    call 2f
    2:
    popl %eax
    addl $(3f - 2b), %eax
    pushl $0x30
    pushl %eax
    lretl

    3:

    // Set all data segments to CGDT.ds
    mov $0x60, %eax
    mov %eax, %ds
    mov %eax, %es
    mov %eax, %fs
    mov %eax, %gs
    mov %eax, %ss

    // Set what CORE0_32BIT_INIT sets for the kernel
    mov ARGS_BOOT_STACK(%ebx), %esp
    mov ARGS_PATCH_TABLE_BASE(%ebx), %esi
    mov ARGS_BOOT_BASE(%ebx), %edi
    mov ARGS_ENTRY_POINT(%ebx), %ebx

    // Set CR0 to (PE | NE) AKA SYS_START_CR0
    mov $0x21, %eax
    mov %eax, %cr0

    // Set flags to 0x02
    pushl $0x02
    popfl

    jmp *%ebx

.global trampoline_end
trampoline_end:
