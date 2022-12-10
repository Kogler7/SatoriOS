#include "types.h"

#ifndef _VPU_ADDRESS_H_
#define _VPU_ADDRESS_H_

#define VADDR_OFT_ODR 12
#define VADDR_PGN_ODR 6
#define VADDR_PDN_ODR 14

typedef struct logi_addr
{
    u32 oft : VADDR_OFT_ODR; // offset: 4k
    u32 pgn : VADDR_PGN_ODR; // page number: 64 pages
    u32 pdn : VADDR_PDN_ODR; // page directory number: 16k page tables
} logi_addr_t;

typedef addr phys_addr_t;

#endif /* !_VPU_ADDRESS_H_ */