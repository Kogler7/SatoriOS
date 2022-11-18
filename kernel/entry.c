#include "info.h"
#include "shell.h"
#include "boot.h"
#include "satio/printf.h"
#include "boot/env_init.h"
#include "mm/mm.h"
#define NULL ((void *)0)

void handle_bootparams(struct BootParamsInterface *a2){
    env_init(a2);
    int cnt=loongson_mem_map->map_count;
    printf("%d\n\r",cnt);
    for (int i=0;i<cnt;i++){
        struct loongson_mem_map *map=&loongson_mem_map->map[i];
        printf("------");
    }
}

extern void trap_init(void);

void kernel_entry(int a0, char **args, struct BootParamsInterface *a2)
{
    print_info();
    trap_init();
    mem_init();
    // entry_shell();

    int i;

    printf("There is %d args for kernel:\n\r", a0);
    for (i=0; i < a0; i++) {
        printf("cmd arg %d: %s\n\r", i, args[i]);
    }


    printf("efi system table at %p\n\r", a2->SystemTable);
    printf("efi extend list at %p\n\r", a2->ExtList);

    // handle_bootparams(a2);

    // struct _extention_list_hdr *hdr=a2->ExtList;

    // printf("flags:%d\n\r",a2->Flags);

    // while(hdr!=NULL){
    //     printf("hdr: %s\n\r",hdr->Signature);

    //     hdr=hdr->next;
    //     printf("finish\n\r");
    // }

    while(1);
}
