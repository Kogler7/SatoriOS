#ifndef __MALLOC_H__
#define __MALLOC_H__

#include "mm/mm.h"
#include "mm/buddy.h"

void *malloc(int size);
void free(void *addr, int size);
void *realloc(void *addr, int old_size, int new_size);
void *calloc(int size);

#endif /* __MALLOC_H__ */