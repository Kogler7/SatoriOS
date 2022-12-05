#include "types.h"
#include "vpu/vpu.h"
#include "vpu/page.h"

#ifndef _VPU_MEMORY_MANAGEMENT_UNIT_H_
#define _VPU_MEMORY_MANAGEMENT_UNIT_H_

typedef struct logical_addr
{
    u32 oft : 12; // offset: 4k
    u32 pgn : 14; // page number: 16k pages
    u32 sgn : 6;  // segment number: 64 segs
} logical_addr_t;

typedef struct linear_addr
{
    u32 offset : 12;
    u32 page : 10;
    u32 directory : 10;
} linear_addr_t;

typedef void *physical_addr_t;

linear_addr_t vmmu_logical_to_linear(vpu_t *vpu, logical_addr_t logical_addr);
physical_addr_t vmmu_linear_to_physical(vpu_t *vpu, linear_addr_t linear_addr);

#endif /* !_VPU_MEMORY_MANAGEMENT_UNIT_H_ */