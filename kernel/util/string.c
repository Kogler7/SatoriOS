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
    if (*str1 != *str2)
        return 1;
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

void split(char *str, char *delim, char *result[], int *result_len)
{
    int len = strlen(str);
    int delim_len = strlen(delim);
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < len)
    {
        if (strncmp(str + i, delim, delim_len) == 0)
        {
            result[j] = str + k;
            j++;
            i += delim_len;
            k = i;
        }
        else
        {
            i++;
        }
    }
    result[j] = str + k;
    j++;
    *result_len = j;
}