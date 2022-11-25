#ifndef _KERN_MM_ALLOC_H_
#define _KERN_MM_ALLOC_H_

#include "mm/sys_heap.h"

void *kmalloc(int size);
void kfree(void *addr, int size);
void *krealloc(void *addr, int old_size, int new_size);
void *kcalloc(int size);
void *kmemalign(int size, int align);

#endif /* !_KERN_MM_ALLOC_H_ */