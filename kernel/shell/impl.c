#include "shell/shell.h"
#include "shell/impl.h"
#include "shell/parser.h"
#include "config/info.h"
#include "boot/boot_param.h"
#include "io/stdio.h"
#include "drivers/ansi.h"

void shell_test(int cmd_id)
{
    puts("Shell Test:");
    printf("\tinput: %s\n\r", input_buff);
    puts("\tparams:");
    for (int i = 0; i < CMD_PARAM_MAX; i++)
    {
        printf("\t[%c] %s\n\r", param_buff[i].sign, param_buff[i].param);
    }
}

void show_help()
{
    for (int i = 0; i < SHELL_CMD_MAX; i++)
    {
        if (shell_cmds[i].cmd[0] == 0)
            break;
        printf("\t%o%s\n\r", shell_cmds[i].cmd, shell_cmds[i].desc);
        if (shell_cmds[i].params[0].sign != 0)
        {
            for (int j = 0; j < CMD_PARAM_MAX; j++)
            {
                if (shell_cmds[i].params[j].sign == 0)
                    break;
                printf("\t\t[-%c] %O %s\n\r", shell_cmds[i].params[j].sign, shell_cmds[i].params[j].name, shell_cmds[i].params[j].desc);
            }
        }
    }
}

void echo()
{
    puts(input_buff);
}

void clear_screen()
{
    clear_screen();
}

void exit_shell()
{
    shell_exit_flag = 1;
}

void show_clock_info(int cmd_id)
{
    puts("Clock Info:");
    puts("Not Implemented Yet");
}

void show_about_info(int cmd_id)
{
    if (!has_param(cmd_id))
    {
        puts("Satori OS is a simple OS written by C.");
        print_info();
    }
    else
    {
        if (get_param('v') != 0)
            puts(VERSION);
        if (get_param('a') != 0)
            puts(AUTHOR);
        if (get_param('c') != 0)
            puts(COPYRIGHT);
        if (get_param('l') != 0)
            puts(LOGO);
        if (get_param('o') != 0)
            puts(ORIGIN);
    }
}
void show_satori_info(int cmd_id)
{
    if (!has_param(cmd_id))
    {
        puts("Satori OS is a simple OS written by C.");
        puts("Not implemented yet.");
    }
    else
    {
        if (get_param('c') != 0)
        {
            puts("CPU Info:");
            // print_cpu_info();
            puts("Not implemented yet.");
        }
        if (get_param('m') != 0)
        {
            puts("Memory Info:");
            // print_mem_info();
            puts("Not implemented yet.");
        }
        if (get_param('b') != 0)
        {
            puts("Boot Info:");
            print_args();
        }
    }
}

void show_datetime()
{
    printf("Date: %s\n\r", "2022-11-26");
    printf("Time: %s\n\r", "14:20:00");
}