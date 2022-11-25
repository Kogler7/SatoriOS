#ifndef _MALLOC_H_
#define _MALLOC_H_

#include "mm/mm.h"
#include "mm/buddy.h"

void *malloc(int size);
void free(void *addr, int size);
void *realloc(void *addr, int old_size, int new_size);
void *calloc(int size);

#endif /* _MALLOC_H_ */