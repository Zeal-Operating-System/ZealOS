/* strncmp( const char *, const char *, size_t )
   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stddef.h>

int strncmp(const char *s1, const char *s2, size_t n)
{
    while (n && *s1 && (*s1 == *s2))
    {
        ++s1;
        ++s2;
        --n;
    }

    if (n == 0)
    {
        return 0;
    }
    else
    {
        return (*(unsigned char *)s1 - *(unsigned char *)s2);
    }
}

