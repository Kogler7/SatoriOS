#ifndef _VIRTUAL_FILESYSTEM_SWITCH_H_
#define _VIRTUAL_FILESYSTEM_SWITCH_H_

typedef struct file
{
    char *name;

} file;

void fs_init();

file *fopen(char *path, char *mode);
int fclose(file *fp);
int fcreate(char *path);
int fdelete(char *path);
int fmove(char *src, char *dst);

int fread(void *ptr, int size, int count, file *fp);
int fwrite(void *ptr, int size, int count, file *fp);
void fappend(file *fp, char *str);
void fappendln(file *fp, char *str);
void fprintf(file *fp, char *fmt, ...);

#endif /* !_VIRTUAL_FILESYSTEM_SWITCH_H_ */