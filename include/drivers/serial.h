#ifndef _DEV_SERIAL_H_
#define _DEV_SERIAL_H_

unsigned long uart_base = 0x1fe001e0;

#define UART0_THR  (uart_base + 0)
#define UART0_LSR  (uart_base + 5)
#define LSR_TX_IDLE  (1 << 5)

static inline char serial_read_lsr()
{
    return *(volatile char*)UART0_LSR;
}

static inline void serial_send_char(const char c)
{
    // wait for Transmit Holding Empty to be set in LSR.
    while ((serial_read_lsr() & LSR_TX_IDLE) == 0)
	{
		asm volatile("nop");
	}
    *(char*)UART0_THR = c;
}

#endif /* !_DEV_SERIAL_H_ */