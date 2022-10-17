#include"util.h"

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