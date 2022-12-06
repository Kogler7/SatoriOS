#include "types.h"
#include "vpu/vpu.h"

#ifndef _VIRTUAL_TRANSLATION_LOOKASIDE_BUFFER_H_
#define _VIRTUAL_TRANSLATION_LOOKASIDE_BUFFER_H_

#define VTLB_SIZE 64         // 2^6
#define VTLB_OFT_MASK 63     // VTLB_SIZE - 1
#define VTLB_OFT_SFT 12      // 2^12
#define VTLB_TAG_ODR 14      //(VADDR_SGN_ODR + VADDR_PDN_ODR)
#define VTLB_TAG_SFT 18      //(VADDR_OFT_ODR + VADDR_PGN_ODR)
#define VTLB_TAG_MASK 0x3FFF // 2^14 - 1

typedef struct vtlb_entry
{
    byte valid : 1;
    byte ng : 1;
    byte asid : 6;
    u16 tag : VTLB_TAG_ODR;
    addr base_addr;
} vtlb_entry_t;

void flush_tlb();
void vtlb_insert(logi_addr_t logi_addr, phys_addr_t base_addr);
phys_addr_t *vtlb_lookup(logi_addr_t logi_addr);

#endif /* !_VIRTUAL_TRANSLATION_LOOKASIDE_BUFFER_H_ */