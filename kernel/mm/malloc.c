#include "mm/malloc.h"

void *malloc(int size)
{
    if (size <= 0)
    {
        mm_error("malloc: size <= 0");
        return NULL;
    }
    return buddy_alloc(size);
}

void free(void *addr, int size)
{
    if (addr == NULL || size <= 0)
    {
        mm_error("free: addr == NULL || size <= 0");
        return;
    }
    buddy_free(addr, size);
}

void *realloc(void *addr, int old_size, int new_size)
{
    if (addr == NULL || old_size <= 0 || new_size <= 0)
    {
        mm_error("realloc: addr == NULL || old_size <= 0 || new_size <= 0");
        return NULL;
    }
    return buddy_realloc(addr, old_size, new_size);
}

void *calloc(int size)
{
    if (size <= 0)
    {
        mm_error("calloc: size <= 0");
        return NULL;
    }
    return buddy_calloc(size);
}