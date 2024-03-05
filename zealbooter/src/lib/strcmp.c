/* strcmp( const char *, const char * )
   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stddef.h>

int strcmp(const char *s1, const char *s2)
{
    while ((*s1) && (*s1 == *s2))
    {
        ++s1;
        ++s2;
    }

    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}


