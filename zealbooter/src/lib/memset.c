/* memset( void *, int, size_t )
   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stddef.h>

void *memset(void *s, int c, size_t n)
{
    unsigned char *p = (unsigned char *)s;

    while (n--)
    {
        *p++ = (unsigned char)c;
    }

    return s;
}


