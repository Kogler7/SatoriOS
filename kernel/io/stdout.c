#include <stdarg.h>
#include "arch/loongarch.h"
#include "io/stdout.h"
#include "drivers/kbd.h"

static char digits[] = "0123456789abcdef";

void print_int(int xx, int base, int sign)
{
	char buf[16];
	int i;
	unsigned int x;

	if (sign && (sign = xx < 0))
		x = -xx;
	else
		x = xx;

	i = 0;
	do
	{
		buf[i++] = digits[x % base];
	} while ((x /= base) != 0);

	if (sign)
		buf[i++] = '-';

	while (--i >= 0)
		putc(buf[i]);
}

void print_ptr(unsigned long x)
{
	int i;
	putc('0');
	putc('x');
	for (i = 0; i < (sizeof(unsigned long) * 2); i++, x <<= 4)
		putc(digits[x >> (sizeof(unsigned long) * 8 - 4)]);
}

void printf(const char *fmt, ...)
{
	va_list ap;
	int i, c, n;
	char *s;

	if (fmt == 0)
	{
		intr_on();
		return;
	}

	va_start(ap, fmt);
	for (i = 0; (c = fmt[i] & 0xff) != 0; i++)
	{
		if (c != '%')
		{
			putc(c);
			continue;
		}
		c = fmt[++i] & 0xff;
		if (c == 0)
			break;
		switch (c)
		{
		case 'd':
			print_int(va_arg(ap, int), 10, 1);
			break;
		case 'x':
			print_int(va_arg(ap, int), 16, 1);
			break;
		case 'p':
			print_ptr(va_arg(ap, unsigned long));
			break;
		case 's':
			if ((s = va_arg(ap, char *)) == 0)
				s = "(null)";
			for (; *s; s++)
				putc(*s);
			break;
		case 'c':
			putc((char)(va_arg(ap, int)));
			break;
		case 'O':
			n = 16;
			if ((s = va_arg(ap, char *)) == 0)
				s = "(null)  ";
			for (; n; s++, n--)
				putc(*s ? *s : ' ');
			break;
		case 'o':
			n = 8;
			if ((s = va_arg(ap, char *)) == 0)
				s = "(null)  ";
			for (; n; s++, n--)
				putc(*s ? *s : ' ');
			break;
		case '%':
			putc('%');
			break;
		default:
			// Print unknown % sequence to draw attention.
			putc('%');
			putc(c);
			break;
		}
	}
}