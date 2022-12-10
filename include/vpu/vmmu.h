#include "types.h"
#include "vpu/vpu.h"
#include "vpu/addr.h"
#include "vpu/page.h"

#ifndef _VPU_MEMORY_MANAGEMENT_UNIT_H_
#define _VPU_MEMORY_MANAGEMENT_UNIT_H_

void handle_page_fault(u32 error_code);

void handle_tlb_miss(logi_addr_t logi_addr, phys_addr_t phys_addr);

phys_addr_t get_phys_addr(logi_addr_t logi_addr);

phys_addr_t access_memory(logi_addr_t logi_addr);

#endif /* !_VPU_MEMORY_MANAGEMENT_UNIT_H_ */