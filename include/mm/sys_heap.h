#include "mm/mm.h"
#include "mm/bitmap.h"
#ifndef _SYS_HEAP_H_
#define _SYS_HEAP_H_

#define SYS_HEAP_ALLOC_THRESHOLD 16

void* sys_heap_alloc(unsigned int size);
void sys_heap_free(void* addr, unsigned int size);
void* sys_heap_realloc(void* addr, unsigned int old_size, unsigned int new_size);
void* sys_heap_calloc(unsigned int size);
void* sys_heap_memalign(unsigned int size, unsigned int align);

#endif /* !_SYS_HEAP_H_ */