#include "types.h"

#ifndef _MEMORY_PAGE_H_
#define _MEMORY_PAGE_H_

typedef struct page
{
    u32 present : 1;  // Page present in memory
    u32 rw : 1;       // Read-only if clear, readwrite if set
    u32 user : 1;     // Supervisor level only if clear
    u32 accessed : 1; // Has the page been accessed since last refresh?
    u32 dirty : 1;    // Has the page been written to since last refresh?
    u32 unused : 7;   // Amalgamation of unused and reserved bits
    u32 frame : 20;   // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
    int nr_pages;
    page_t *pages;
} page_table_t;

typedef struct page_directory
{
    int nr_tables;
    page_table_t *tables;
} page_directory_t;

#endif /* !_MEMORY_PAGE_H_ */