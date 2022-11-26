#include "shell/shell.h"
#include "shell/impl.h"
#include "config/info.h"
#include "sysio/io.h"

void shell_test()
{
    printf("Shell Test:\n\r");
    printf("\tinput: %s\n\r", input_buff);
    printf("\tparams:\n\r");
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

void show_about_info(int cmd_id)
{
    if (!has_param(cmd_id))
    {
        printf("Satori OS is a simple OS written by C.\n\r");
        print_info();
    }
    else
    {
        if (get_param('v') != 0)
            printf("%s\n\r", VERSION);
        if (get_param('a') != 0)
            printf("%s\n\r", AUTHOR);
        if (get_param('c') != 0)
            printf("%s\n\r", COPYRIGHT);
        if (get_param('l') != 0)
            printf("%s\n\r", LOGO);
        if (get_param('o') != 0)
            printf("%s\n\r", ORIGIN);
    }
}

void exit_shell()
{
    shell_exit_flag = 1;
}