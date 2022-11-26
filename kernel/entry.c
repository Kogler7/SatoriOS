#pragma GCC diagnostic ignored "-Wimplicit-function-declaration" //正式开发建议删除此行
#include "io/stdio.h"
#include "boot/boot_param.h"
#include <unistd.h>
#include "config/info.h"
#include "boot/boot_param.h"
#include "fs/fs.h"

// extern void mm_init(void);
extern void trap_init(void);

void kernel_entry(int a0, char **args, struct bootparamsinterface *a2)
{
    // env_init(a2);

    printf("There is %d args for kernel:\n", a0);
    for (int i = 0; i < a0; i++)
    {
        printf("cmd arg %d: %s\n", i, args[i]);
    }

    printf("efi system table at %p\n", a2->systemtable);
    printf("efi extend list at %p\n", a2->extlist);

    // mm_init();
    printf("\n\n\n");
    fs_init();
    trap_init();
    stdin_init();

    print_info();
    entry_shell();

    // while (1)
    //     ;
    puts("kernel exited.");
}
