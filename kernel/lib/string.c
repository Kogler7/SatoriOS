#include "lib/string.h"
#include <stdarg.h>

int strcmp(const char *str1, const char *str2)
{
    while (*str1 != 0 && *str2 != 0)
    {
        if (*str1 != *str2)
            return 1;
        str1++;
        str2++;
    }
    if (*str1 != *str2)
        return 1;
    return 0;
}

int strcpy(char *dst, const char *src)
{
    while (*src != 0)
    {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = 0;
    return 0;
}

int strlen(const char *str)
{
    int len = 0;
    while (*str != 0)
    {
        len++;
        str++;
    }
    return len;
}

int strncmp(const char *str1, const char *str2, int n)
{
    while (*str1 != 0 && *str2 != 0 && n > 0)
    {
        if (*str1 != *str2)
            return 1;
        str1++;
        str2++;
        n--;
    }
    // if (*str1 != *str2) return 1;
    return 0;
}

int strncpy(char *dst, const char *src, int n)
{
    while (*src != 0 && n > 0)
    {
        *dst = *src;
        dst++;
        src++;
        n--;
    }
    *dst = 0;
    return 0;
}

int isdigit(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    return 0;
}

int atoi(char *str)
{
    int n = 0;
    int sign = 1;
    if (*str == 0) return 0;
    while (*str == ' ')
    {
        str++;
    }
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    while (*str != 0 && isdigit(*str))
    {
        n = n * 10 + *str - '0';
        str++;
    }
}

void sscanf(char *str, char *format, ...)
{
    va_list ap;
    int i, c, n;
    char *s;
    va_start(ap, format);
    while (*format != 0)
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
            case 'd':
                n = atoi(str);
                *va_arg(ap, int *) = n;
                while (*str != 0 && *str != ' ')
                    str++;
                break;
            case 's':
                s = va_arg(ap, char *);
                while (*str != 0 && *str != ' ')
                {
                    *s = *str;
                    s++;
                    str++;
                }
                *s = 0;
                break;
            }
        }
        else
        {
            while (*str != 0 && *str != ' ')
                str++;
        }
        format++;
        str++;
    }
    va_end(ap);
}

void memset(void *ptr, char c, unsigned long size)
{
    char *p = (char *)ptr;
    while (size--)
    {
        *p = c;
        p++;
    }
}

int memcmp(void *ptr1, void *ptr2, unsigned long size)
{
    char *p1 = (char *)ptr1;
    char *p2 = (char *)ptr2;
    while (size--)
    {
        if (*p1 != *p2)
            return 0;
        p1++;
        p2++;
    }
    return 1;
}

void memcpy(void *ptr1, void *ptr2, unsigned long size)
{
    char *p1 = (char *)ptr1;
    char *p2 = (char *)ptr2;
    while (size--)
    {
        *p1 = *p2;
        p1++;
        p2++;
    }
}