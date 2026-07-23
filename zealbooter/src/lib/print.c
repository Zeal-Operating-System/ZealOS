#define STB_SPRINTF_DECORATE(name) name
#define STB_SPRINTF_IMPLEMENTATION 1
#define STB_SPRINTF_NOFLOAT 1
#include <stb_sprintf.h>
#include <limine.h>

//static volatile struct limine_terminal_request terminal_request = {
//    .id = LIMINE_TERMINAL_REQUEST,
//    .revision = 0
//};

#define PRINT_BUFFER_SIZE    8192

// Emit a byte to QEMU's debug console (I/O port 0xE9). View with -debugcon stdio.
// Limine dropped the terminal-write feature, so this is the only ZealBooter output.
static inline void debugcon_putc(char c)
{
    __asm__ volatile ("outb %0, %1" : : "a"((unsigned char)c), "Nd"((unsigned short)0xE9));
}

int printf(const char *format, ...)
{
    va_list args;
    char buffer[PRINT_BUFFER_SIZE];
    size_t length, i;

    va_start(args, format);

    length = vsnprintf(buffer, PRINT_BUFFER_SIZE, format, args);
    for (i = 0; i < length; i++)
        debugcon_putc(buffer[i]);

    va_end(args);

    return length;
}

