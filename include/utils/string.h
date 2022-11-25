#ifndef _SATORI_UTILS_STR_
#define _SATORI_UTILS_STR_

int strcmp(const char *str1, const char *str2);
int strcpy(char *dst, const char *src);
int strlen(const char *str);
int strncmp(const char *str1, const char *str2, int n);
int strncpy(char *dst, const char *src, int n);
void split(char *str, char *delim, char result[][100], int *result_len);

#endif /* !_SATORI_UTILS_STR_ */