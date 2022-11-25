#pragma GCC diagnostic ignored "-Wunused-variable" //正式开发建议删除此行
#include "sysio/io.h"
#include "arch/loongarch.h"
#include "arch/ls7a.h"
#include "drivers/kbd.h"
#include "shell/shell.h"

// extern void trap_entry(void);

extern void ls7a_intc_init(void);
extern void ls7a_intc_complete(unsigned long irq);

extern void extioi_init(void);
extern void extioi_complete(unsigned long irq);
extern unsigned long extioi_claim(void);
extern void extioi_complete(unsigned long irq);
extern void i8042_init(void);
extern unsigned char kbd_read_byte(void);
extern int kbd_has_data(void);

int time_n = 0;

void timer_interrupt(void)
{
    // printf("timer interrupt\n");
    time_n += 1;
    w_csr_ticlr(r_csr_ticlr() | CSR_TICLR_CLR);
}

void uart0_interrupt(void)
{
    printf("uart0 interrupt\n\r");
}

void keyboard_interrupt(void)
{
    // kbd_irq();
    handle_kbd_irq();
}

void mouse_interrupt(void)
{
    printf("mouse interrupt\n\r");
}

void trap_entry()
{
    // intr_off(); // 会导致cbk取消注册失败，尚不清楚原因
    asm volatile(
        "        addi.d $sp, $sp, -256\n"
        "        st.d $ra, $sp, 0\n"
        "        st.d $tp, $sp, 8\n"
        "        st.d $sp, $sp, 16\n"
        "        st.d $a0, $sp, 24\n"
        "        st.d $a1, $sp, 32\n"
        "        st.d $a2, $sp, 40\n"
        "        st.d $a3, $sp, 48\n"
        "        st.d $a4, $sp, 56\n"
        "        st.d $a5, $sp, 64\n"
        "        st.d $a6, $sp, 72\n"
        "        st.d $a7, $sp, 80\n"
        "        st.d $t0, $sp, 88\n"
        "        st.d $t1, $sp, 96\n"
        "        st.d $t2, $sp, 104\n"
        "        st.d $t3, $sp, 112\n"
        "        st.d $t4, $sp, 120\n"
        "        st.d $t5, $sp, 128\n"
        "        st.d $t6, $sp, 136\n"
        "        st.d $t7, $sp, 144\n"
        "        st.d $t8, $sp, 152\n"
        "        st.d $r21, $sp,160\n"
        "        st.d $fp, $sp, 168\n"
        "        st.d $s0, $sp, 176\n"
        "        st.d $s1, $sp, 184\n"
        "        st.d $s2, $sp, 192\n"
        "        st.d $s3, $sp, 200\n"
        "        st.d $s4, $sp, 208\n"
        "        st.d $s5, $sp, 216\n"
        "        st.d $s6, $sp, 224\n"
        "        st.d $s7, $sp, 232\n"
        "        st.d $s8, $sp, 240\n"
        "        bl trap_handler\n"
        "        ld.d $ra, $sp, 0\n"
        "        ld.d $tp, $sp, 8\n"
        "        ld.d $sp, $sp, 16\n"
        "        ld.d $a0, $sp, 24\n"
        "        ld.d $a1, $sp, 32\n"
        "        ld.d $a2, $sp, 40\n"
        "        ld.d $a3, $sp, 48\n"
        "        ld.d $a4, $sp, 56\n"
        "        ld.d $a5, $sp, 64\n"
        "        ld.d $a6, $sp, 72\n"
        "        ld.d $a7, $sp, 80\n"
        "        ld.d $t0, $sp, 88\n"
        "        ld.d $t1, $sp, 96\n"
        "        ld.d $t2, $sp, 104\n"
        "        ld.d $t3, $sp, 112\n"
        "        ld.d $t4, $sp, 120\n"
        "        ld.d $t5, $sp, 128\n"
        "        ld.d $t6, $sp, 136\n"
        "        ld.d $t7, $sp, 144\n"
        "        ld.d $t8, $sp, 152\n"
        "        ld.d $r21, $sp,160\n"
        "        ld.d $fp, $sp, 168\n"
        "        ld.d $s0, $sp, 176\n"
        "        ld.d $s1, $sp, 184\n"
        "        ld.d $s2, $sp, 192\n"
        "        ld.d $s3, $sp, 200\n"
        "        ld.d $s4, $sp, 208\n"
        "        ld.d $s5, $sp, 216\n"
        "        ld.d $s6, $sp, 224\n"
        "        ld.d $s7, $sp, 232\n"
        "        ld.d $s8, $sp, 240\n"
        "        addi.d $sp, $sp, 256\n"
        "        ertn\n"
        :
        :
        :);
    // intr_on();
}

void trap_handler(void)
{
    intr_off();
    unsigned long era = r_csr_era();
    unsigned long prmd = r_csr_prmd();
    unsigned int estat = r_csr_estat();
    unsigned int ecfg = r_csr_ecfg();

    if ((prmd & PRMD_PPLV) != 0)
        printf("kerneltrap: not from privilege0");
    if (intr_get() != 0)
        printf("kerneltrap: interrupts enabled");

    // printf("\n");
    // printf("estat %x, ecfg %x\n", estat, ecfg);
    // printf("era=%p eentry=%p\n", r_csr_era(), r_csr_eentry());

    if (estat & ecfg & TI_VEC)
    {
        timer_interrupt();
    }
    else if (estat & ecfg & HWI_VEC)
    {
        unsigned long irq = extioi_claim();

        if (irq & (1UL << UART0_IRQ))
        {
            uart0_interrupt();
        }

        if (irq & (1UL << KEYBOARD_IRQ))
        {
            keyboard_interrupt();
        }

        if (irq & (1UL << MOUSE_IRQ))
        {
            mouse_interrupt();
        }

        // ack
        ls7a_intc_complete(irq);
        extioi_complete(irq);
    }
    else
    {
        printf("unexpected interrupt\n");
        while (1)
            ;
    }

    // restore era
    w_csr_era(era);
    w_csr_prmd(prmd);
    intr_on();
}

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
