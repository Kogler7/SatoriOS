#include"info.h"
#include"shell.h"

void kernel_entry(void *a0, void *a1, void *a2)
{
    print_info();
    entry_shell();
    while(1);
}
