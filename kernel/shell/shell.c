#pragma GCC diagnostic ignored "-Wimplicit-function-declaration" //正式开发建议删除此行
#include "shell/shell.h"
#include "shell/parser.h"
#include "sysio/io.h"
#include "drivers/kbd.h"
#include "utils/string.h"
#include "arch/loongarch.h"
#include "arch/ls7a.h"

char input_buff[SHELL_BUFFER_SIZE];

char shell_path[256] = "/";

int buff_index = 0;
int input_flag = 1;
int shell_exit_flag = 0;

void kbd_getchar(char c, int s)
{
    if (buff_index >= SHELL_BUFFER_SIZE)
    {
        input_buff[SHELL_BUFFER_SIZE - 1] = 0;
        printf("\n\rshell buffer overflowed.\n\r");
        input_flag = 0;
        return;
    }
    if (s == 1)
    {
        putc(c);
        // printf("[%d]",get_cbk_cnt());
        if (c == '\n')
        {
            input_flag = 0;
            return;
        }
        input_buff[buff_index++] = c;
    }
}

void wait_for_input()
{
    int id = register_kbd_cbk(kbd_getchar);
    buff_index = 0;
    input_flag = 1;
    while (input_flag)
    {
        asm volatile("nop");
    }
    input_buff[buff_index] = 0;
    unregister_kbd_cbk(id);
    // print_cbk_table();
}

void entry_shell()
{
    printf("Entering Shell...\n\r");
    shell_exit_flag = 0;
    while (!shell_exit_flag)
    {
        printf("SatoriOS:%s $ ", shell_path);
        wait_for_input();
        parse_command();
    }
    printf("Exiting Shell...\n\r");
}