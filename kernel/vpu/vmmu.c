#include "vpu/vmmu.h"

#define vmmu_info(fmt, ...) pr_info(VMMU, fmt, ##__VA_ARGS__)
#define vmmu_warn(fmt, ...) pr_warn(VMMU, fmt, ##__VA_ARGS__)
#define vmmu_debug(fmt, ...) pr_debug(VMMU, fmt, ##__VA_ARGS__)
#define vmmu_error(fmt, ...) pr_error(VMMU, fmt, ##__VA_ARGS__)

linear_addr_t vmmu_logical_to_linear(logi_addr_t logi_addr, virtual_descriptor_t *vdesc)
{
    linear_addr_t linear_addr = 0;
    if (vdesc->p == 0)
    {
        vmmu_error("Page fault: %x", logi_addr);
        return 0;
    }
    linear_addr = (vdesc->base << 12) + (logi_addr & 0xfff);
    return linear_addr;
}
phys_addr_t vmmu_linear_to_physical(linear_addr_t linear_addr, virtual_descriptor_t *vdesc);

phys_addr_t vmmu_access_mem(logi_addr_t logi_addr, virtual_descriptor_t *vdesc)
{
    
}