/* strlen( const char * )
   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stddef.h>

size_t strlen(const char *s)
{
    size_t rc = 0;

    while (s[rc])
    {
        ++rc;
    }

    return rc;
}

