#include "types.h"

#ifndef _MEMORY_PAGE_H_
#define _MEMORY_PAGE_H_

typedef struct page
{
    u32 present : 1;
    u32 rw : 1;
    u32 user : 1;
    u32 accessed : 1;
    u32 dirty : 1;
    u32 unused : 7;
    u32 frame : 20;
} page_t;

typedef struct page_table_entry
{
    int vir_page_no;
    int phy_page_no;
} page_table_entry_t;

typedef struct page_table
{
    page_table_entry_t entries[1024];
} page_table_t;

typedef struct page_middle_directory
{
    page_table_t *tables[1024];
    u32 tables_physical[1024];
    u32 physical_address;
} page_middle_directory_t;

typedef struct page_upper_directory
{
    page_middle_directory_t *tables[1024];
    u32 tables_physical[1024];
    u32 physical_address;
} page_upper_directory_t;

typedef struct page_global_directory
{
    page_upper_directory_t *tables[1024];
    u32 tables_physical[1024];
    u32 physical_address;
} page_global_directory_t;

typedef struct vaddr
{
    u32 vpo : 12;
    u32 vpn : 10;
    u32 directory : 10;
} vaddr_t;

typedef struct paddr
{
    u32 offset : 12;
    u32 frame : 20;
} paddr_t;

typedef struct translation_lookaside_buffer
{
    u32 valid : 1;
    u32 ppn : 31;
} translation_lookaside_buffer_t;

#endif /* !_MEMORY_PAGE_H_ */