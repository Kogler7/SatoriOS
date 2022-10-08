#include"satio/serial.h"

unsigned long uart_base = 0x1fe001e0; // UART0

#define UART0_THR  (uart_base + 0) // Transmit Holding Register
#define UART0_LSR  (uart_base + 5) // Line Status Register
#define LSR_TX_IDLE  (1 << 5) // Transmitter is idle

char read_byte(unsigned long addr)
{
    return *(volatile char*)addr;
}

void write_byte(unsigned long addr, char c)
{
    *(char*)addr = c;
}

void getc(char *c)
{
    while((read_byte(UART0_LSR) & LSR_TX_IDLE) == 0);
    *c = read_byte(UART0_THR);
}

void input_c(char *c)
{
    getc(c);
    putc(*c);   //echo
    write_byte(UART0_LSR, 0x0f);
    
}

void putc(char c)
{
    // wait for Transmit Holding Empty to be set in LSR.
    while((read_byte(UART0_LSR) & LSR_TX_IDLE) == 0);
    write_byte(UART0_THR, c);
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
        input_c(&c);
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