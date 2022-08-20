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

struct CKernel {
    struct CZXE zxe;
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
