#include"info.h"
#include"shell.h"
#include "boot_param.h"
#include "satio/printf.h"


void handle_bootparams(struct BootParamsInterface *a2){
    
}

void kernel_entry(int a0, char **args, struct BootParamsInterface *a2)
{
    print_info();
    // entry_shell();

    int i;

    printf("There is %d args for kernel:\n", a0);
    for (i=0; i < a0; i++) {
        printf("cmd arg %d: %s\n", i, args[i]);
    }


    printf("efi system table at %p\n", a2->SystemTable);
    printf("efi extend list at %p\n", a2->ExtList);

    /* ... read the linux kernel source for how to decode these data */
    // printf("efi memory map at %p\n", a2->memorymap);
    while(1);
}
