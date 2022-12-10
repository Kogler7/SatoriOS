#include "vpu/vmmu.h"

#define vmmu_info(fmt, ...) pr_info(VMMU, fmt, ##__VA_ARGS__)
#define vmmu_warn(fmt, ...) pr_warn(VMMU, fmt, ##__VA_ARGS__)
#define vmmu_debug(fmt, ...) pr_debug(VMMU, fmt, ##__VA_ARGS__)
#define vmmu_error(fmt, ...) pr_error(VMMU, fmt, ##__VA_ARGS__)

phys_addr_t get_phys_addr(logi_addr_t logi_addr)
{
    virtual_descriptor_t *vdesc = cur_vpu->csr->descriptor;
    page_directory_t *pdir = (page_directory_t *)(vdesc->entry);
    if ((u32)logi_addr >= vdesc->limit)
    {
        vmmu_error("%x - Unhandled segment fault: Exceed seg limit.", logi_addr);
        return nullptr;
    }
    if (logi_addr.pdn >= pdir->nr_tables)
    {
        vmmu_error("%x - Unhandled page fault: Exceed page directory limit.", logi_addr);
        return nullptr;
    }
    page_table_t *ptable = (page_table_t *)(pdir->tables[logi_addr.pdn]);
    if (logi_addr.pgn >= ptable->nr_pages)
    {
        vmmu_error("%x - Unhandled page fault: Exceed page table limit.", logi_addr);
        return nullptr;
    }
    page_t *page = (page_t *)(ptable->pages[logi_addr.pgn]);
    if (!page->present)
    {
        vmmu_error("%x - Unhandled page fault: Page not present.", logi_addr);
        return nullptr;
    }
    return (page->frame << 12) + logi_addr.oft;
}