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
    save_args(a0, args, a2);

    // mm_init();
    fs_init();
    trap_init();
    stdin_init();

    print_info();
    entry_shell();

    // while (1)
    //     ;
    puts("kernel exited.");
}
