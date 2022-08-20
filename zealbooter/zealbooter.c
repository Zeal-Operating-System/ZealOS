#include <stdint.h>
#include <stddef.h>
#include <limine.h>

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent.

static volatile struct limine_module_request module_request = {
    .id = LIMINE_MODULE_REQUEST,
    .revision = 0
};

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

static void done(void) {
    for (;;) {
        __asm__("hlt");
    }
}

struct CZXE {
    uint16_t jmp;
    uint8_t module_align_bits;
    uint8_t reserved;
    uint32_t signature;
    int64_t org;
    int64_t patch_table_offset;
    int64_t file_size;
};

struct CDate {
    uint32_t time;
    int32_t date;
};

struct CMemE820 {
    uint8_t *base;
    int64_t len;
    uint8_t type;
    uint8_t pad[3];
};

struct CSysLimitBase {
    uint16_t limit;
    uint8_t *base;
};

struct CKernel {
    struct CZXE zxe;
    uint32_t jmp;
    uint32_t boot_src;
    uint32_t boot_blk;
    uint32_t boot_patch_table_base;
    uint32_t sys_run_level;
    struct CDate compile_time;
//U0 start;
    uint32_t boot_base;
    uint16_t mem_E801[2];
    struct CMemE820 mem_E820[48];
    uint64_t mem_physical_space;
    struct CSysLimitBase sys_gdt_ptr;
    uint16_t sys_pci_buses;
// ;$ = ($ + 15) & -16;
//    struct CGDT sys_gdt;
//    uint32_t sys_font_ptr;
//    struct CVBEInfo sys_vbe_info;
//    struct CVBEModeShort sys_vbe_modes[32];
//    struct CVBEMode sys_vbe_mode;
//    uint16_t sys_vbe_mode_num;

};

// The following will be our kernel's entry point.
void _start(void) {
    // Ensure we got a terminal
    if (terminal_request.response == NULL
     || terminal_request.response->terminal_count < 1) {
        done();
    }

    // We should now be able to call the Limine terminal to print out
    // a simple "Hello World" to screen.
    struct limine_terminal *terminal = terminal_request.response->terminals[0];
    terminal_request.response->write(terminal, "Hello World", 11);

    struct limine_file *kernel_module = module_request.response->modules[0];
    struct CKernel *kernel = kernel_module->address;

    char str[128];
    str[0] = ' ';
    str[1] = kernel->zxe.signature;
    str[2] = kernel->zxe.signature >> 8;
    str[3] = kernel->zxe.signature >> 16;
    str[4] = kernel->zxe.signature >> 24;
    str[5] = 0;

    terminal_request.response->write(terminal, str, 5);

    // We're done, just hang...
    done();
}
