#include"satio/serial.h"

unsigned long uart_base = 0x1fe001e0;

#define UART0_THR  (uart_base + 0)
#define UART0_LSR  (uart_base + 5)
#define LSR_TX_IDLE  (1 << 5)

char io_readb(unsigned long addr)
{
    return *(volatile char*)addr;
}

void io_writeb(unsigned long addr, char c)
{
    *(char*)addr = c;
}

void getc(char *c)
{
    while((io_readb(UART0_LSR) & LSR_TX_IDLE) == 0);
    *c = io_readb(UART0_THR);
}

void putc(char c)
{
    // wait for Transmit Holding Empty to be set in LSR.
    while((io_readb(UART0_LSR) & LSR_TX_IDLE) == 0);
    io_writeb(UART0_THR, c);
}

void puts(const char *str)
{
    while (*str != 0) {
        putc(*str);
        str++;
    }
}

void gets(char *str)
{
    char c;
    while (1)
    {
        getc(&c);
        if (c == '\r')
            break;
        *str = c;
        str++;
    }
    *str = 0;
}

void newline()
{
    putc('\n');
}