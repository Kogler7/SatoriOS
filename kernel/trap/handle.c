#include "io/stdio.h"
#include "arch/loongarch.h"
#include "arch/ls7a.h"
#include "drivers/kbd.h"
#include "shell/shell.h"

extern void ls7a_intc_complete(unsigned long irq);

extern void extioi_complete(unsigned long irq);
extern unsigned long extioi_claim(void);
extern void extioi_complete(unsigned long irq);

int time_n = 0;

void timer_interrupt(void)
{
    time_n += 1;
    w_csr_ticlr(r_csr_ticlr() | CSR_TICLR_CLR);
}

void uart0_interrupt(void)
{
    printf("uart0 interrupt\n\r");
}

void keyboard_interrupt(void)
{
    handle_kbd_irq();
}

void mouse_interrupt(void)
{
    printf("mouse interrupt\n\r");
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