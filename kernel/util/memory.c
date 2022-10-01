#include"util.h"

void memset(void *ptr, char c, unsigned long size)
{
    char *p = (char*)ptr;
    while (size--)
    {
        *p = c;
        p++;
    }
}