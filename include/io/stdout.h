#include "drivers/serial.h"

#ifndef _SATORI_STD_OUT_H_
#define _SATORI_STD_OUT_H_

static inline void putc(const char c)
{
    serial_send_char(c);
}

static void newline()
{
    putc('\n');
    putc('\r');
}

static inline void puts(const char *str)
{
    while (*str != 0)
    {
        putc(*str);
        str++;
    }
    newline();
}

void print_int(int xx, int base, int sign);
void print_ptr(unsigned long x);

void printf(const char *fmt, ...);

#endif /* !_SATORI_STD_OUT_H_ */