#pragma GCC diagnostic ignored "-Wunused-variable" //正式开发建议删除此行
#include "io/stdio.h"
#include "arch/loongarch.h"
#include "arch/ls7a.h"
#include "drivers/kbd.h"
#include "shell/shell.h"

extern void trap_entry(void);

extern void extioi_init(void);
extern unsigned long extioi_claim(void);
extern void i8042_init(void);

void trap_init(void)
{
    intr_off();

    unsigned int ecfg = (0U << CSR_ECFG_VS_SHIFT) | HWI_VEC | TI_VEC;
    unsigned long tcfg = 0x10000000UL | CSR_TCFG_EN | CSR_TCFG_PER;
    w_csr_ecfg(ecfg);
    w_csr_tcfg(tcfg);
    w_csr_eentry((unsigned long)trap_entry);

    extioi_init();    //拓展io中断初始化
    ls7a_intc_init(); //桥片初始化
    i8042_init();     //键鼠控制芯片初始化

    intr_on();
}
