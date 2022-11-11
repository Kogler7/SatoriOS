#include "loongarch.h"

extern void extioi_init();
extern void ls7a_intc_init();
extern void ls7a_i8042_init();

extern void trap_entry();

void trap_init(void)
{
    intr_off();
    unsigned int ecfg = (0U << CSR_ECFG_VS_SHIFT) | HWI_VEC | TI_VEC;
    unsigned long tcfg = 0x10000000UL | CSR_TCFG_EN | CSR_TCFG_PER;
    w_csr_ecfg(ecfg);
    w_csr_tcfg(tcfg);
    w_csr_eentry((unsigned long)trap_entry);

    extioi_init();
    ls7a_intc_init();
    ls7a_i8042_init();

    intr_on();
}