#include "vpu/vtlb.h"

#define vtlb_info(fmt, ...) pr_info(VTLB, fmt, ##__VA_ARGS__)
#define vtlb_warn(fmt, ...) pr_warn(VTLB, fmt, ##__VA_ARGS__)
#define vtlb_debug(fmt, ...) pr_debug(VTLB, fmt, ##__VA_ARGS__)
#define vtlb_error(fmt, ...) pr_error(VTLB, fmt, ##__VA_ARGS__)

vtlb_entry_t virtual_tlb[VTLB_SIZE];

#define get_vtlb_entry(logi_addr) (virtual_tlb + ((logi_addr) >> VTLB_OFT_SFT) & VTLB_OFT_MASK)
#define get_vtlb_tag(logi_addr) ((logi_addr) >> VTLB_TAG_SFT & VTLB_TAG_MASK)

void flush_tlb()
{
    for (int i = 0; i < VTLB_SIZE; i++)
    {
        virtual_tlb[i].valid = false;
    }
}

void vtlb_insert(logi_addr_t logi_addr, phys_addr_t base_addr)
{
    vtlb_entry_t *entry = get_vtlb_entry(logi_addr);
    entry->valid = true;
    entry->ng = true;
    entry->asid = cur_vpu->asid;
    entry->tag = get_vtlb_tag(logi_addr);
    entry->base_addr = base_addr;
}

phys_addr_t *vtlb_lookup(logi_addr_t logi_addr)
{
    vtlb_entry_t *entry = get_vtlb_entry(logi_addr);
    if (!entry->valid || (entry->ng && entry->asid != cur_vpu->asid))
    {
        return nullptr;
    }
    if (entry->tag == get_vtlb_tag(logi_addr))
    {
        return entry->base_addr + (logi_addr & 0xfff);
    }
    return nullptr;
}