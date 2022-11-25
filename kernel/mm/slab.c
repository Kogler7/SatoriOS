#include "mm/slab.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]) + __must_be_array(arr))

#define INIT_KMALLOC_INFO(size, _short)           \
    {                                             \
        .name = "kmalloc-" #_short, .size = size \
    }

typedef struct list_head
{
    struct list_head *next, *prev;
} list_head;

typedef struct kmalloc_info
{
    const char *name;
    size_t size;
} kmalloc_info;
3                                   
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
}

typedef struct slab
{
    list_head *obj_list;

} slab;

const struct kmalloc_info kmalloc_info[] = {
    INIT_KMALLOC_INFO(32, 32),
    INIT_KMALLOC_INFO(64, 64),
    INIT_KMALLOC_INFO(128, 128),
    INIT_KMALLOC_INFO(256, 256),
    INIT_KMALLOC_INFO(512, 512),
    INIT_KMALLOC_INFO(1024, 1k),
    INIT_KMALLOC_INFO(2048, 2k)};

void show_slab_info(void)
{
    int i;
    struct kmem_cache *cachep;
    struct slab *slabp;

    for (i = 0; i < ARRAY_SIZE(kmalloc_info); i++)
    {
        cachep = kmalloc_caches[i];
        slabp = cachep->slabp;
        printf("slab info: %s");
    }
}