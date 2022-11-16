#include "boot.h"
#include "mm/mm.h"

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

void mem_block_add(u64 mem_start, u64 mem_size)
{
    if (mem_size < PAGE_SIZE)
        return;
    u64 start = mem_start / PAGE_SIZE;
    u64 end = (mem_start + mem_size) / PAGE_SIZE;
    if (end > MAXSPACE / PAGE_SIZE)
        end = MAXSPACE / PAGE_SIZE;
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
