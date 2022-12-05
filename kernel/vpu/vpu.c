#include "vpu/vpu.h"
#include "io/kinfo.h"

#define vpu_info(fmt, ...) pr_info(VPU, fmt, ##__VA_ARGS__)
#define vpu_warn(fmt, ...) pr_warn(VPU, fmt, ##__VA_ARGS__)
#define vpu_debug(fmt, ...) pr_debug(VPU, fmt, ##__VA_ARGS__)
#define vpu_error(fmt, ...) pr_error(VPU, fmt, ##__VA_ARGS__)

descriptor_t vpu_get_descriptor(vpu_t *vpu, selector_t selector)
{
    descriptor_t *desc = nullptr;
    if (selector.ti == 0)
    {
        if (selector.index >= vpu->gdtr.limit)
        {
            vpu_error("Invalid descriptor index: %d", selector.index);
        }
        desc = vpu->gdtr.base + selector.index * sizeof(descriptor_t);
    }
    else
    {
        vdt_entry_t *ldt = vpu->gdtr.base + vpu->ldtr.index * sizeof(descriptor_t);
        if (selector.index >= ldt->limit)
        {
            vpu_error("Invalid descriptor index: %d", selector.index);
        }
        desc = ldt->base + selector.index * sizeof(descriptor_t);
    }
    return *desc;
}

void vpu_init(vpu_t *vpu)
{
    // vpu->vpu_id = 0;
    // vpu->vpu_name = "vpu0";
    // vpu->vpu_type = VPU_TYPE_0;
    // vpu->vpu_status = VPU_STATUS_IDLE;
    // vpu->vpu_ops = &vpu_ops;
}

void vpu_lgdt(vpu_t *vpu, vdt_entry_t gdtr)
{
    vpu->gdtr = gdtr;
}
void vpu_lldt(vpu_t *vpu, selector_t ldtr)
{
    vpu->ldtr = ldtr;
}