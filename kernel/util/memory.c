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

int memcmp(void *ptr1, void *ptr2, unsigned long size)
{
    char *p1 = (char*)ptr1;
    char *p2 = (char*)ptr2;
    while (size--)
    {
        if (*p1 != *p2)
            return 0;
        p1++;
        p2++;
    }
    return 1;
}