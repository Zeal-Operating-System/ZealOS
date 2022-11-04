#define STB_SPRINTF_DECORATE(name) name
#define STB_SPRINTF_IMPLEMENTATION 1
#define STB_SPRINTF_NOFLOAT 1
#include <stb_sprintf.h>
#include <limine.h>

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

#define PRINT_BUFFER_SIZE    8192

int printf(const char *format, ...)
{
    va_list args;
    char buffer[PRINT_BUFFER_SIZE];
    struct limine_terminal *terminal;
    size_t length;

    va_start(args, format);

    length = vsnprintf(buffer, PRINT_BUFFER_SIZE, format, args);
    terminal = terminal_request.response->terminals[0];
    terminal_request.response->write(terminal, buffer, length);

    va_end(args);

    return length;
}

