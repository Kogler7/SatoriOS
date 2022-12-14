#include "vpu/vpu.h"
#include "io/kinfo.h"

vpu_t* cur_vpu;
vpu_t* next_vpu;

bool vpu_switch_flag = false;
bool vpu_exit_flag = false;

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

void vpu_init(vpu_t *vpu, sint cpl, sint asid)
{
    vpu->asid = asid;
    vpu->cpl = cpl;
    vpu->ip= 0;
    vpu->sp = 0;
    vpu->bp = 0;
    vpu->flags = 0;
}

void vpu_lgdt(vpu_t *vpu, vdt_entry_t gdtr)
{
    vpu->gdtr = gdtr;
}
void vpu_lldt(vpu_t *vpu, selector_t ldtr)
{
    vpu->ldtr = ldtr;
}

void vpu_switch_seg(seg_type type)
{
    switch (type)
    {
    case SEG_CS:
        cur_vpu->csr = &cur_vpu->sgr.cs;
        break;
    case SEG_DS:
        cur_vpu->csr = &cur_vpu->sgr.ds;
        break;
    case SEG_SS:
        cur_vpu->csr = &cur_vpu->sgr.ss;
        break;
    case SEG_HS:
        cur_vpu->csr = &cur_vpu->sgr.hs;
        break;
    default:
        vpu_error("Invalid segment type: %d", type);
        break;
    }
}

void vpu_cycle()
{
    logi_addr_t ip = cur_vpu->ip;
    phys_addr_t *phys_ip = get_phys_addr(ip);
    vpu_opcode_t opcode = *(vpu_opcode_t *)phys_ip;
    vpu_info("opcode: %d", opcode);
}

void go_to_vpu_cycle()
{
    if(vpu_exit_flag || !cur_vpu)
    {
        return;
    }
    if (vpu_switch_flag)
    {
        vpu_switch_flag = false;
        cur_vpu = next_vpu;
    }
    vpu_cycle();
}