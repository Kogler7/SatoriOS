#ifndef __SATORI_UTILS_
#define __SATORI_UTILS_

void memset(void *ptr, char c, unsigned long size);
int memcmp(void *ptr1, void *ptr2, unsigned long size);
void memcpy(void *ptr1, void *ptr2, unsigned long size);
int strcmp(const char *str1, const char *str2);
int strcpy(char *dst, const char *src);
int strlen(const char *str);
int strncmp(const char *str1, const char *str2, int n);
int strncpy(char *dst, const char *src, int n);
void split(char *str, char *delim, char *result[], int *result_len);

#endif /* !__SATORI_UTILS_ */