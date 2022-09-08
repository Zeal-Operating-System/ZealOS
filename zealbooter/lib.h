#ifndef __LIB_H__
#define __LIB_H__

#include <stdint.h>
#include <memcpy.h>
#include <memset.h>
#include <memmove.h>
#include <memcmp.h>
#include <strcpy.h>
#include <strncpy.h>
#include <strcmp.h>
#include <strncmp.h>
#include <strlen.h>
#include <print.h>

uint64_t div_roundup_u64(uint64_t a, uint64_t b);
uint64_t align_up_u64(uint64_t a, uint64_t b);

typedef char symbol[];

#endif // __LIB_H__
