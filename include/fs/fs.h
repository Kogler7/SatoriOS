#pragma once
#define DISK_INFO_BASE 0x120000000
#define FILE_INFO_BASE 0x122000000
#define FILE_BASE      0x124000000
//#define MAX_FILE_NUM 131072 //128*1024


struct file_info{
    char file_name[128];
    char file_type[16];
    char *file_p;
    unsigned int file_size;
};

struct file_folder{
    char file_folder_name[128];
    struct file_info *file_list[16];
    struct file_folder *file_folder_list[16];
};

void* fs_info_malloc(int size);
void* fs_malloc(int size);

void create_folder(struct file_folder *relative_path, char folder_name[]);
int create_file(struct file_folder *relative_path, char file_name[]);
void del_folder(struct file_folder *relative_path, char folder_name[]);
void del_file(struct file_folder *relative_path, char file_name[]);
void *path_als(char path[],int type);
void move_file(char dst[],char src[]);
void move_folder(char dst[],char src[]);
void fs_init();