#include"info.h"

void kernel_entry(void *a0, void *a1, void *a2)
{
    print_info();
    while(1);
}
