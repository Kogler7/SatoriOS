#include "types.h"

#ifndef _VPU_MEMORY_MANAGEMENT_UNIT_H_
#define _VPU_MEMORY_MANAGEMENT_UNIT_H_

typedef struct logical_addr
{
    u32 offset : 12;
    u32 page : 10;
    u32 directory : 10;
} logical_addr_t;

typedef struct linear_addr
{
    u32 offset : 12;
    u32 page : 10;
    u32 directory : 10;
} linear_addr_t;

typedef struct physical_addr
{
    u32 offset : 12;
    u32 frame : 20;
} physical_addr_t;

typedef struct segmented_unit
{
    u32 cs;
    u32 ds;
    u32 es;
    u32 fs;
    u32 gs;
    u32 ss;
} segmented_unit_t;

typedef struct paging_unit
{
    u32 cr0;
    u32 cr1;
    u32 cr2;
    u32 cr3;
    u32 cr4;
} paging_unit_t;

#endif /* !_VPU_MEMORY_MANAGEMENT_UNIT_H_ */