#include "satio/printf.h"
#include "satio/serial.h"
#include "loongarch.h"
#include "trap/ls7a.h"
#include "driver/kbd.h"

extern void trap_entry(void);

extern void handle_kbd_irq(void);

void timer_interrupt(void)
{
	printf("timer interrupt\n\r");
	/* ack */
	w_csr_ticlr(r_csr_ticlr() | CSR_TICLR_CLR);
}

void uart0_interrupt(void)
{
	// char c;
	// c = r_csr_uartrx();
	// printf("uart interrupt: %c\n\r", c);
}

void keyboard_interrupt(void)
{
	void handle_kbd_irq();
}

void mouse_interrupt(void)
{
	printf("mouse interrupt\n");
}

void trap_handler(void)
{
	intr_off(); // 关中断
	unsigned long era = r_csr_era();
	unsigned long prmd = r_csr_prmd();
	unsigned int estat = r_csr_estat();
	unsigned int ecfg = r_csr_ecfg();

	// printf("estat %x, ecfg %x\n\r", estat, ecfg);
	// printf("era=%p eentry=%p\n\r", r_csr_era(), r_csr_eentry());

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
		// hardware interrupt
		unsigned long irq = extioi_claim();

		// printf("irq=%x\n", irq);

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

		// acknowledge
		ls7a_intc_complete(irq);
		extioi_complete(irq);
	}
	else
	{
		printf("unexpected interrupt\n\r");
	}

	w_csr_era(era);
	w_csr_prmd(prmd);
	intr_on(); // 开中断
}