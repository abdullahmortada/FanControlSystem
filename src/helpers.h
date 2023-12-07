#ifndef __helpers__
#define __helpers__

#include <stddef.h>
#include <stdint.h>

void intToString(int num, char* arr, uint8_t base);

size_t clamp(size_t value, size_t min, size_t max);

#endif
