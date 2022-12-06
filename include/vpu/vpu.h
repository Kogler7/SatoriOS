#include "vpu/vdt.h"
#include "types.h"

#ifndef _VIRTUAL_PROCESSOR_UNIT_H_
#define _VIRTUAL_PROCESSOR_UNIT_H_

#define GENERAL_REGISTERS 16
#define SYSCALL_REGISTERS 8

#define VADDR_OFT_ODR 12
#define VADDR_PGN_ODR 6
#define VADDR_PDN_ODR 8
#define VADDR_SGN_ODR 6

typedef struct logi_addr
{
    u32 oft : VADDR_OFT_ODR; // offset: 4k
    u32 pgn : VADDR_PGN_ODR; // page number: 64 pages
    u32 pdn : VADDR_PDN_ODR; // page directory number: 256 page directories
    u32 sgn : VADDR_SGN_ODR; // segment number: 64 segs
} logi_addr_t;

typedef addr phys_addr_t;

typedef struct vpu_flags
{
    u8 cf : 1; // carry flag
    u8 pf : 1; // parity flag
    u8 zf : 1; // zero flag
    u8 sf : 1; // sign flag
    u8 of : 1; // overflow flag
    u8 tf : 1; // trace flag
    u8 rf : 1; // interrupt flag
} vpu_flags_t;

typedef struct segment_register
{
    selector_t selector;
    virtual_descriptor_t descriptor;
} segment_register_t;

typedef struct segment_registers
{
    segment_register_t cs; // Code segment
    segment_register_t ds; // Data segment
    segment_register_t es; // Extra segment
    segment_register_t fs; // Flags segment
    segment_register_t gs; // Global segment
    segment_register_t ss; // Stack segment
} segment_registers_t;

typedef struct page_dir_base
{
    u32 valid : 1;
    u32 ppn : 31;
} page_dir_base_t;

typedef struct vpu
{
    u32 gpr[GENERAL_REGISTERS]; // General purpose registers
    u32 scr[SYSCALL_REGISTERS]; // System call registers
    segment_registers_t sgr;    // Segment registers
    int ip;                     // Instruction pointer
    int sp;                     // Stack pointer
    int bp;                     // Base pointer
    sint asid;                  // Address space identifier
    vpu_flags_t flags;          // Flags
    vdt_entry_t gdtr;           // Global descriptor table register
    selector_t ldtr;            // Local descriptor table register
    page_dir_base_t pdbr;       // Page directory base register
} vpu_t;

descriptor_t vpu_get_descriptor(vpu_t *vpu, selector_t selector);

#define vpu_set_sgr(vpu, reg, selector)                              \
    do                                                               \
    {                                                                \
        vpu->sgr.reg.selector = selector;                            \
        vpu->sgr.reg.descriptor = vpu_get_descriptor(vpu, selector); \
    } while (0)

void vpu_entry();

void vpu_init(vpu_t *vpu);

void vpu_lgdt(vpu_t *vpu, vdt_entry_t gdtr);
void vpu_lldt(vpu_t *vpu, selector_t ldtr);

void construct_segment_descriptor(vpu_t *vpu, selector_t selector, virtual_descriptor_t *vdesc);

extern vpu_t *cur_vpu;
extern vpu_t *next_vpu;

extern bool vpu_switch_flag = false;
extern bool vpu_exit_flag = false;

#endif /* !_VIRTUAL_PROCESSOR_UNIT_H_ */