#include "mm/sys_heap.h"

byte sys_heap[SYS_HEAP_SIZE];

byte sys_heap_bitmap[SYS_HEAP_SIZE / 8];

const int sys_heap_bitmap_size = SYS_HEAP_SIZE / 8;

void *sys_heap_alloc(unsigned int size)
{
    static int last = 0;
    int index;
    if (size < SYS_HEAP_ALLOC_THRESHOLD)
        index = alloc_bits(sys_heap_bitmap, sys_heap_bitmap_size, size, &last);
    else
        index = alloc_aligned_bits(sys_heap_bitmap, sys_heap_bitmap_size, size, &last);
    if (index == -1)
    {
        mm_error("The system heap is out of memory.");
        return NULL;
    }
#ifdef __SATORI_DEBUG_
    if (last > sys_heap_bitmap_size * 0.8)
    {
        mm_warn("The system heap is almost full.");
    }
#endif // __SATORI_DEBUG_
    return sys_heap + index;
}

void sys_heap_free(void *addr, unsigned int size)
{
    int index = (int)((u64)addr - (u64)sys_heap);
    if (size < SYS_HEAP_ALLOC_THRESHOLD)
        free_bits(sys_heap_bitmap, index, size);
    else
        free_aligned_bits(sys_heap_bitmap, index, size);
}

void *sys_heap_realloc(void *addr, unsigned int old_size, unsigned int new_size)
{
    void *new_addr = sys_heap_alloc(new_size);
    if (new_addr == NULL)
        return NULL;
    memcpy(new_addr, addr, old_size);
    sys_heap_free(addr, old_size);
    return new_addr;
}

void *sys_heap_calloc(unsigned int size)
{
    void *addr = sys_heap_alloc(size);
    if (addr == NULL)
        return NULL;
    memset(addr, 0, size);
    return addr;
}

void *sys_heap_memalign(unsigned int size, unsigned int align)
{
    void *addr = sys_heap_alloc(size + align);
    if (addr == NULL)
        return NULL;
    void *aligned_addr = (void *)(((u64)addr + align) & ~(align - 1));
    return aligned_addr;
}