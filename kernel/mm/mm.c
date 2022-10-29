#include "boot.h"

#define NULL ((void *)0)
#define PAGESIZE 4096
#define MAXSPACE 0x80000000L

#define SYSTEM_RAM 1
#define MEM_RESERVED 2
#define ACPI_TABLE 3
#define ACPI_NVS 4

const struct loongsonlist_mem_map mem_map_list = {
    {0, 0, 0, 0},
    .map_count = 15,
    .map = {
        {(u32)1, (u64)0x00200000, (u64)0x0ee00000},
        {(u32)2, (u64)0x0f000000, (u64)0x01000000},
        {(u32)1, (u64)0x00000000, (u64)0x10000000},
        {(u32)1, (u64)0x90000000, (u64)0xf0000000},
        {(u32)1, (u64)0x00000000, (u64)0x10000000},
        {(u32)1, (u64)0x90010000, (u64)0x6e6c0000},
        {(u32)1, (u64)0xfe6e0000, (u64)0x00010000},
        {(u32)1, (u64)0xfe700000, (u64)0x00190000},
        {(u32)1, (u64)0xfef10000, (u64)0x01080000},
        {(u32)1, (u64)0xfffe0000, (u64)0x80020000},
        {(u32)1, (u64)0x100d0000, (u64)0x00001000},
        {(u32)1, (u64)0xfe6f0000, (u64)0x00010000},
        {(u32)1, (u64)0xfe890000, (u64)0x002c0000},
        {(u32)1, (u64)0xfeb60000, (u64)0x003b0000},
        {(u32)1, (u64)0xfff90000, (u64)0x00050000}}};

u64 bitmap[MAXSPACE / 64 / PAGESIZE] = {0}; //8k*64*4K=0x80000000L

// struct page
// {
//     unsigned long flags;
// };

struct zone
{
    int node;
};

void mem_block_add(u64 mem_start, u64 mem_size)
{
    if (mem_size < PAGESIZE)
        return;
    u64 start = mem_start / PAGESIZE;
    u64 end = (mem_start + mem_size) / PAGESIZE;
    if (end > MAXSPACE / PAGESIZE)
        end = MAXSPACE / PAGESIZE;
    for (u64 i = start; i < end; i++)
    {
        bitmap[i / 64] |= (1UL << (i % 64));
    }
}

void mem_block_init(struct loongsonlist_mem_map *mem_map)
{
    u32 mem_type;
    u64 mem_start, mem_end, mem_size;

    for (int i = 0; i <= mem_map->map_count; i++)
    {
        mem_type = mem_map->map[i].mem_type;
        mem_start = mem_map->map[i].mem_start;
        mem_size = mem_map->map[i].mem_size;
        mem_end = mem_start + mem_size;
        if (SYSTEM_RAM == mem_type)
        {
            mem_block_add(mem_start, mem_size);
        }
    }
}

void mem_init()
{
}

void buffer_init()
{
}

void* get_free_page()
{
    for (u64 i = 0; i < MAXSPACE / 64 / PAGESIZE; i++)
    {
        if (bitmap[i] != 0xffffffffffffffff)
        {
            for (u64 j = 0; j < 64; j++)
            {
                if ((bitmap[i] & (1UL << j)) == 0)
                {
                    bitmap[i] |= (1UL << j);
                    return (void *)(i * 64 * PAGESIZE + j * PAGESIZE);
                }
            }
        }
    }
    return NULL;
}

int put_page()
{
    return 0;
}

int free_page(void* addr)
{
    u64 i = (u64)addr / PAGESIZE;
    bitmap[i / 64] &= ~(1UL << (i % 64));
    return 0;
}

//buddy system
// #define MAXORDER 11
// struct page{
//     //mem page struct
//     unsigned long flags;
//     unsigned long _count;

// };
// struct list_head
// {
//     struct list_head *next, *prev;

// };
// struct free_area
// {
    
// };

// struct page *alloc_pages(int order)
// {
//     return NULL;
// }
