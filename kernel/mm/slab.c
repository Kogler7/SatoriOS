#include "mm/slab.h"

const kmalloc_info kmalloc_info_arr[] = {
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

    // for (i = 0; i < ARRAY_SIZE(kmalloc_info_arr); i++)
    // {
    //     cachep = kmalloc_caches[i];
    //     slabp = cachep->slabp;
    //     printf("slab info: %s");
    // }
}