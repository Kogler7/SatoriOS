#include "types.h"
#include "vpu/vpu.h"
#include "vpu/addr.h"

#ifndef _VIRTUAL_TRANSLATION_LOOKASIDE_BUFFER_H_
#define _VIRTUAL_TRANSLATION_LOOKASIDE_BUFFER_H_

#define VTLB_SIZE 64 // 2^VADDR_PGN_ODR(6)=64

typedef struct vtlb_entry
{
    byte valid : 1;
    byte ng : 1;
    byte asid : 6;
    u16 tag : VADDR_PDN_ODR;
    addr frame;
} vtlb_entry_t;

void flush_tlb();
void vtlb_insert(logi_addr_t logi_addr, phys_addr_t frame);
phys_addr_t *vtlb_lookup(logi_addr_t logi_addr);

#endif /* !_VIRTUAL_TRANSLATION_LOOKASIDE_BUFFER_H_ */