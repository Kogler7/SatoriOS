#include "mm/mm.h"

typedef struct list_head
{
    struct list_head *next, *prev;
} list_head;

typedef struct slab
{
    struct slab *next;
    void *base;
    void *limit;
    void *free;
    void *size;
    void *tag;
    void *flags;
} slab;