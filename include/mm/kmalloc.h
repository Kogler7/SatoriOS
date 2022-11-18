#ifndef __KERN_MM_ALLOC_H__
#define __KERN_MM_ALLOC_H__

#include "mm/sys_heap.h"

void *kmalloc(int size);
void kfree(void *addr, int size);
void *krealloc(void *addr, int old_size, int new_size);
void *kcalloc(int size);
void *kmemalign(int size, int align);

#endif /* !__KERN_MM_ALLOC_H__ */