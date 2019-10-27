#ifndef COMMON_H
#define COMMON_h

#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x, y) ((x) <= (y) ? (x) : (y))
#define MAX(x, y) ((x) >= (y) ? (x) : (y))
#define CLAMP_MAX(x, max) MIN(x, max)
#define CLAMP_MIN(x, min) MAX(x, min)

void* xmalloc(size_t p_size);
void* xrealloc(void* p_ptr, size_t p_bytes);

char* read_file(const char* p_path);

#endif // COMMON_H
