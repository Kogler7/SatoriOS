#include "fs/fs.h"
#include "utils/string.h"

struct file_folder *root_path = 0x120000000;

long long fs_info_alloc_start = 0x120000000 + sizeof(struct file_folder);
void *fs_info_malloc(int size)
{
    void *p = fs_info_alloc_start;
    fs_info_alloc_start += size;
    if (fs_info_alloc_start > 0x122000000)
        return 0;
    return p;
}

long long fs_alloc_start = 0x122000000;
void *fs_malloc(int size)
{
    void *p = fs_alloc_start;
    fs_alloc_start += size;
    if (fs_alloc_start > 0x130000000)
        return 0;
    return p;
}

void create_folder(struct file_folder *relative_path, char folder_name[])
{
    int list_n = -1;
    for (int i = 0; i < 16; i++)
    {
        if (relative_path->file_folder_list[i] == 0)
        {
            list_n = i;
            break;
        }
    }
    if (list_n == -1)
    {
        printf("Number of folder is up to max!\n");
        return;
    }
    relative_path->file_folder_list[list_n] = (struct file_folder *)fs_info_malloc(sizeof(struct file_folder));
    if (relative_path->file_folder_list[list_n] == 0)
        printf("No room to create folder!\n");
    strcpy(relative_path->file_folder_list[list_n]->file_folder_name, folder_name);
    for (int i = 0; i < 16; i++)
    {
        relative_path->file_folder_list[list_n]->file_folder_list[i] = 0;
        relative_path->file_folder_list[list_n]->file_list[i] = 0;
    }
}

int create_file(struct file_folder *relative_path, char file_name[])
{
    int list_n = -1;
    for (int i = 0; i < 16; i++)
    {
        if (relative_path->file_list[i] == 0)
        {
            list_n = i;
            break;
        }
    }
    if (list_n == -1)
    {
        printf("Number of file is up to max!\n");
        return -1;
    }
    relative_path->file_list[list_n] = (struct file_info *)fs_info_malloc(sizeof(struct file_info));
    if (relative_path->file_list[list_n] == 0)
        printf("No room to create file!\n");
    strcpy(relative_path->file_list[list_n]->file_name, file_name);
    relative_path->file_list[list_n]->file_p = (char *)fs_malloc(4 * 1024 * sizeof(char));
    relative_path->file_list[list_n]->file_size = 4 * 1024 * sizeof(char);
    char split_res[100][100];
    int split_res_n = 0;
    // printf("%p\n%p\n",&split_res[0][0],&split_res[1][1]);
    split(file_name, ".", split_res, &split_res_n);
    // printf("----11111****\n");
    // printf("%x\n\n",relative_path->file_list[list_n]->file_p);
    strcpy(relative_path->file_list[list_n]->file_type, split_res[split_res_n - 1]);
    return list_n;
}

void del_folder(struct file_folder *relative_path, char folder_name[])
{
    int list_n = -1;
    for (int i = 0; i < 16; i++)
    {
        if (relative_path->file_folder_list[i] != 0 && strcmp(folder_name, relative_path->file_folder_list[i]->file_folder_name))
        {
            list_n = i;
            break;
        }
    }
    if (list_n == -1)
    {
        printf("No such folder!\n");
        return;
    }
    relative_path->file_folder_list[list_n] = 0;
}

void del_file(struct file_folder *relative_path, char file_name[])
{
    int list_n = -1;
    for (int i = 0; i < 16; i++)
    {
        if (relative_path->file_list[i]->file_p != 0 && strcmp(file_name, relative_path->file_list[i]->file_name))
        {
            list_n = i;
            break;
        }
    }
    if (list_n == -1)
    {
        printf("No such file!\n");
        return;
    }
    relative_path->file_list[list_n]->file_p = 0;
}

void *path_als(char path[], int type)
{ // 0 folder 1 file 2 folder of file
    int depth;
    char split_path[100][100];
    if (path[0] == '/')
        split(&path[1], "/", split_path, &depth);
    else
        split(path, "/", split_path, &depth);
    struct file_folder *dst_p = root_path;

    if (strcmp(path, "/") == 0 && type == 0)
        return root_path;

    int i = 0;
    while (i < depth - 1)
    {
        int list_n = -1;
        for (int j = 0; j < 16; j++)
        {
            if (dst_p->file_folder_list[j] != 0 && strcmp(split_path[i], dst_p->file_folder_list[j]->file_folder_name))
            {
                list_n = j;
                break;
            }
        }
        if (list_n == -1)
        {
            printf("No such file or folder!\n");
            return 0;
        }
        dst_p = dst_p->file_folder_list[list_n];
        i++;
    }

    if (type == 0)
    {
        int list_n = -1;
        for (int j = 0; j < 16; j++)
        {
            if (dst_p->file_list[j]->file_p != 0 && strcmp(split_path[i], dst_p->file_list[j]->file_name))
            {
                list_n = j;
                break;
            }
        }
        if (list_n == -1)
        {
            printf("No such folder!\n");
            return 0;
        }
        dst_p = dst_p->file_folder_list[list_n];
    }
    else if (type == 1 || type == 2)
    {
        int list_n = -1;
        for (int j = 0; j < 16; j++)
        {
            if (dst_p->file_list[j]->file_p != 0 && strcmp(split_path[i], dst_p->file_list[j]->file_name))
            {
                list_n = j;
                break;
            }
        }
        if (list_n == -1)
        {
            printf("No such file!\n");
            return 0;
        }
        if (type == 1)
            dst_p = dst_p->file_list[list_n];
    }
    return (void *)dst_p;
}

void move_file(char dst[], char src[])
{
    struct file_folder *dst_p = (struct file_folder *)path_als(dst, 0);
    struct file_info *src_p = (struct file_info *)path_als(src, 1);
    struct file_folder *src_folder_p = (struct file_folder *)path_als(src, 2);
    if (dst_p == 0 || src_p == 0 || src_folder_p == 0)
    {
        return;
    }
    int list_n = -1;
    for (int i = 0; i < 16; i++)
    {
        if (dst_p->file_list[i] == 0)
        {
            list_n = i;
            break;
        }
    }
    if (list_n == -1)
    {
        printf("Number of file is up to max!\n");
        return;
    }

    for (int j = 0; j < 16; j++)
    {
        if (src_p != 0 && strcmp(src_folder_p->file_list[j]->file_name, src_p->file_name))
        {
            src_folder_p->file_list[j]->file_p = 0;
            break;
        }
    }
    dst_p->file_list[list_n] = src_p;
}

void move_folder(char dst[], char src[])
{
    struct file_folder *dst_p = (struct file_folder *)path_als(dst, 0);
    struct file_folder *src_p = (struct file_folder *)path_als(src, 0);
    struct file_folder *src_folder_p = (struct file_folder *)path_als(src, 2);
    if (dst_p == 0 || src_p == 0 || src_folder_p == 0)
    {
        return;
    }
    int list_n = -1;
    for (int i = 0; i < 16; i++)
    {
        if (dst_p->file_folder_list[i] == 0)
        {
            list_n = i;
            break;
        }
    }
    if (list_n == -1)
    {
        printf("Number of folder is up to max!\n");
        return;
    }

    for (int j = 0; j < 16; j++)
    {
        if (src_p != 0 && strcmp(src_folder_p->file_list[j]->file_name, src_p->file_folder_name))
        {
            src_folder_p->file_folder_list[j] = 0;
            break;
        }
    }
    dst_p->file_folder_list[list_n] = src_p;
}

void fs_init()
{
    fs_info_alloc_start = 0x120000000;
    fs_alloc_start = 0x122000000;
    struct file_folder *root_file_folder = (struct file_folder *)fs_info_malloc(sizeof(struct file_folder));
}