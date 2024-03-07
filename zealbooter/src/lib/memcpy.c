/* memcpy( void *, const void *, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stddef.h>

void *memcpy(void *s1, const void *s2, size_t n)
{
    char *dest = (char *)s1;
    const char *src = (const char *)s2;

    while (n--)
    {
        *dest++ = *src++;
    }

    return s1;
}

