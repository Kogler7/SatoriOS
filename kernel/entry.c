#pragma GCC diagnostic ignored "-Wimplicit-function-declaration" // 正式开发建议删除此行
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
    printf(
        "_text  is %08x--%08x , \
            _data is %08x--%08x , \
            __bss_start  is %08x--%08x , \
            __init_begin is %08x--%08x , \
            _sinittext  is %08x--%08x   , \
            __initdata_begin  is %08x--%08x  , \
            __start_rodata  is %08x--%08x \n ",
        _stext, _etext,
        _sdata, _edata,
        __bss_start, __bss_stop,
        __init_begin, __init_end,
        _sinittext, _einittext,
        __initdata_begin, __initdata_end,
        __start_rodata, __end_rodata);
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
