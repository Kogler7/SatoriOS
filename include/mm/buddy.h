#ifndef _BUDDY_SYSTEM_H__
#define _BUDDY_SYSTEM_H__

#include "mm/mm.h"
#include "mm/kmalloc.h"

#define ALLOCATED 1
#define FREE 0

typedef struct buddy_node
{
    struct buddy_node *left;
    struct buddy_node *right;
    int order;
    int state;
    void* start;
} buddy_node;

void init_buddy();
int split_buddy(buddy_node *node);
void merge_buddy(buddy_node *node);
buddy_node *alloc_buddy(buddy_node *root, int order);
void free_buddy(void* start, int order);
void *buddy_alloc(int size);
void buddy_free(void *addr, int size);
void* buddy_realloc(void* addr, int old_size, int new_size);
void* buddy_calloc(int size);

#endif /* !_BUDDY_SYSTEM_H__ */