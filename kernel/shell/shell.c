#include "shell/shell.h"
#include "shell/parser.h"
#include "io/stdio.h"

char input_buff[SHELL_BUFFER_SIZE];

char shell_path[256] = "/";

int shell_exit_flag = 0;

void entry_shell()
{
    puts("Entering Shell...");
    shell_exit_flag = 0;
    while (!shell_exit_flag)
    {
        printf("SatoriOS:%s $ ", shell_path);
        gets(input_buff);
        parse_command();
    }
    puts("Exiting Shell...");
}