#include "types.h"
#include "vpu/vpu.h"
#include "vpu/page.h"

#ifndef _VPU_MEMORY_MANAGEMENT_UNIT_H_
#define _VPU_MEMORY_MANAGEMENT_UNIT_H_

void handle_page_fault(vpu_t *vpu, u32 error_code);

void handle_tlb_miss(vpu_t *vpu, u32 error_code);



phys_addr_t vmmu_access_mem(logi_addr_t logi_addr, virtual_descriptor_t *vdesc);

#endif /* !_VPU_MEMORY_MANAGEMENT_UNIT_H_ */