#include "mm/kmalloc.h"

void *kmalloc(int size)
{
    if (size <= 0)
        return NULL;
    return sys_heap_alloc(size);
}

void kfree(void *addr, int size)
{
    if (addr == NULL || size <= 0)
        return;
    sys_heap_free(addr, size);
}

void *krealloc(void *addr, int old_size, int new_size)
{
    if (addr == NULL || old_size <= 0 || new_size <= 0)
        return NULL;
    return sys_heap_realloc(addr, old_size, new_size);
}

void *kcalloc(int size)
{
    if (size <= 0)
        return NULL;
    return sys_heap_calloc(size);
}

void *kmemalign(int size, int align)
{
    if (size <= 0 || align <= 0)
        return NULL;
    return sys_heap_memalign(size, align);
}