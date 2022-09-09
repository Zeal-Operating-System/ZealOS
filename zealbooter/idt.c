#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <idt.h>
#include <print.h>

struct cpu_ctx {
    uint64_t ds;
    uint64_t es;
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t err;
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
};

struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t flags;
    uint16_t offset_mid;
    uint32_t offset_hi;
    uint32_t reserved;
};

struct idtr {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

static struct idt_entry idt[256];

void *isr[256];

static void register_handler(uint8_t vector, void *handler, uint8_t flags) {
    uint64_t handler_int = (uint64_t)handler;

    idt[vector] = (struct idt_entry){
        .offset_low = (uint16_t)handler_int,
        .selector = 0x28,
        .ist = 0,
        .flags = flags,
        .offset_mid = (uint16_t)(handler_int >> 16),
        .offset_hi = (uint32_t)(handler_int >> 32),
        .reserved = 0
    };
}

extern void *isr_thunks[];

static const char *exceptions[] = {
    "Division exception",
    "Debug",
    "NMI",
    "Breakpoint",
    "Overflow",
    "Bound range exceeded",
    "Invalid opcode",
    "Device not available",
    "Double fault",
    "???",
    "Invalid TSS",
    "Segment not present",
    "Stack-segment fault",
    "General protection fault",
    "Page fault",
    "???",
    "x87 exception",
    "Alignment check",
    "Machine check",
    "SIMD exception",
    "Virtualisation"
};

static inline uint64_t read_cr0(void) {
    uint64_t ret;
    asm volatile ("mov %%cr0, %0" : "=r"(ret) :: "memory");
    return ret;
}

static inline uint64_t read_cr2(void) {
    uint64_t ret;
    asm volatile ("mov %%cr2, %0" : "=r"(ret) :: "memory");
    return ret;
}

static inline uint64_t read_cr3(void) {
    uint64_t ret;
    asm volatile ("mov %%cr3, %0" : "=r"(ret) :: "memory");
    return ret;
}

static inline uint64_t read_cr4(void) {
    uint64_t ret;
    asm volatile ("mov %%cr4, %0" : "=r"(ret) :: "memory");
    return ret;
}

static void exception_handler(uint8_t vector, struct cpu_ctx *ctx) {
    printf("Exception %s triggered\n\n", exceptions[vector]);

    printf("  RAX=%016lx  RBX=%016lx\n"
           "  RCX=%016lx  RDX=%016lx\n"
           "  RSI=%016lx  RDI=%016lx\n"
           "  RBP=%016lx  RSP=%016lx\n"
           "  R08=%016lx  R09=%016lx\n"
           "  R10=%016lx  R11=%016lx\n"
           "  R12=%016lx  R13=%016lx\n"
           "  R14=%016lx  R15=%016lx\n"
           "  RIP=%016lx  RFLAGS=%08lx\n"
           "  CS=%04lx DS=%04lx ES=%04lx SS=%04lx\n"
           "  CR0=%016lx  CR2=%016lx\n"
           "  CR3=%016lx  CR4=%016lx\n"
           "  ERR=%016lx",
           ctx->rax, ctx->rbx, ctx->rcx, ctx->rdx,
           ctx->rsi, ctx->rdi, ctx->rbp, ctx->rsp,
           ctx->r8, ctx->r9, ctx->r10, ctx->r11,
           ctx->r12, ctx->r13, ctx->r14, ctx->r15,
           ctx->rip, ctx->rflags,
           ctx->cs, ctx->ds, ctx->es, ctx->ss,
           read_cr0(), read_cr2(),
           read_cr3(), read_cr4(),
           ctx->err);

    for (;;) {
        asm ("hlt");
    }
    __builtin_unreachable();
}

void idt_init(void) {
    for (size_t i = 0; i < 256; i++) {
        register_handler(i, isr_thunks[i], 0x8e);
    }

    for (size_t i = 0; i < sizeof(exceptions) / sizeof(exceptions[0]); i++) {
        isr[i] = exception_handler;
    }

    struct idtr idtr = {
        .limit = sizeof(idt) - 1,
        .base = (uint64_t)idt
    };

    asm volatile ("lidt %0" :: "m"(idtr) : "memory");
}
