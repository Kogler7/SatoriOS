#include "types.h"
#include "mm/mm.h"

// 利用数组实现双向链表

typedef struct page
{
    void *addr;
    int next;
    int prev;
} page;

typedef struct free_list
{
    page pages[LIST_LEN];
    int head;
    int tail;
    int order;
} free_list;

typedef struct free_zone
{
    void *start_addr;
    void *end_addr;
    free_list free_areas[MAX_ORDER];
} free_zone;

// free_zone zone;

void init_free_list(free_list *list, int order)
{
    list->head = 0;
    list->tail = 0;
    list->order = order;
    for (int i = 0; i < LIST_LEN; i++)
    {
        list->pages[i].next = i + 1;
        list->pages[i].prev = i - 1;
    }
    list->pages[0].prev = -1;
    list->pages[LIST_LEN - 1].next = -1;
}

void insert_page(free_list *list, page *p)
{
    if (list->head == -1)
    {
        list->head = (int)(p - list->pages);
        list->tail = (int)(p - list->pages);
        p->next = -1;
        p->prev = -1;
    }
    else
    {
        p->next = list->head;
        p->prev = -1;
        list->pages[list->head].prev = (int)(p - list->pages);
        list->head = (int)(p - list->pages);
    }
}

void init_free_zone(free_zone *zone, void *start_addr, void *end_addr)
{
    zone->start_addr = start_addr;
    zone->end_addr = end_addr;
    for (int i = 0; i < MAX_ORDER; i++)
    {
        init_free_list(&zone->free_areas[i], i);
    }
}