#include"../include/satio.h"
#include"../include/info.h"

void print_info()
{
    puts(LOGO);
    newline();
    puts(LABEL);
    newline();
    puts(COPYRIGHT);
    puts(THANKS);
    newline();
}

void kernel_entry(void *a0, void *a1, void *a2)
{
    print_info();
    while(1);
}
