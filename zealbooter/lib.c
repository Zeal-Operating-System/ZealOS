#include <stdint.h>
#include <lib.h>

uint64_t div_roundup_u64(uint64_t a, uint64_t b)
{
	return (a + (b - 1)) / b;
}

uint64_t align_up_u64(uint64_t a, uint64_t b)
{
	return div_roundup_u64(a, b) * b;
}

