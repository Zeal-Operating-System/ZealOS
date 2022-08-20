#ifndef __LIB_H__
#define __LIB_H__

#include <stddef.h>

#define DIV_ROUNDUP(A, B) ({ \
    typeof(A) _a_ = A;       \
    typeof(B) _b_ = B;       \
    (_a_ + (_b_ - 1)) / _b_; \
})

#define ALIGN_UP(A, B) ({        \
    typeof(A) _a__ = A;           \
    typeof(B) _b__ = B;           \
    DIV_ROUNDUP(_a__, _b__) * _b__; \
})

#define ALIGN_DOWN(A, B) ({ \
    typeof(A) _a_ = A;      \
    typeof(B) _b_ = B;      \
    (_a_ / _b_) * _b_;      \
})

typedef char symbol[];

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
size_t strlen(const char *str);

#endif
