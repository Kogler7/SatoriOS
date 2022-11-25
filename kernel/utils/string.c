#include"utils/string.h"

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
    //if (*str1 != *str2) return 1;
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

void split(char *str, char *delim, char result[][100], int *result_len)
{
    int len = strlen(str);
    int delim_len = strlen(delim);
    int i = 0;
    int j = 0;
    int k = 0;
    //printf("\n%d %d\n\n",len,delim_len);
    //printf("---%p\n",&(result[0][0]));
    //printf("---%p\n",&(result[1][1]));
    while (k < len)
    {
        //printf("----11111****\n");
        if (strncmp(str + k, delim, delim_len) == 1)
        {
            //printf("\n6666\n\n");
            result[j][i] = str[k];
            //printf("%c ",*(&result[j]+i));
            i++;
            k++;
        }
        else
        {
            //printf("\n7777\n\n");
            result[j][i] = 0;
            //printf("\n\n");
            j++;
            i=0;
            k += delim_len;
        }
        
    }
    //printf("---\n");
    j++;
    *result_len = j;
}