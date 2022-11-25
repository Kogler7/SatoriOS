#include "mm/mm.h"
#ifndef _MM_SLAB_H_
#define _MM_SLAB_H_

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]) + __must_be_array(arr))

#define INIT_KMALLOC_INFO(_size, _short)          \
    {                                            \
        .name = "kmalloc-" #_short, .size = _size \
    }

typedef struct list_head
{
    struct list_head *next, *prev;
} list_head;

typedef struct kmalloc_info
{
    const char *name;
    int size;
} kmalloc_info;

typedef struct kmem_cache
{
    int obj_size;
    int nr_objs;

    int nr_slabs;
    int nr_pages;
    list_head slabs_partial;
    list_head slabs_full;
    list_head slabs_free;
    kmalloc_info *info;
} kmem_cache;

typedef struct slab
{
    list_head *obj_list;

} slab;

#endif /* !_MM_SLAB_H_ */