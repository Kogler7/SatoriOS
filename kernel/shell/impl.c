#include "shell.h"
#include "info.h"
#include "satio/printf.h"

void show_help()
{
    for (int i = 0; i < SHELL_CMD_MAX; i++)
    {
        if (shell_cmds[i].cmd[0] == 0)
            break;
        printf("\t%s\t%s\n", shell_cmds[i].cmd, shell_cmds[i].desc);
        if (shell_cmds[i].params[0].sign != 0)
        {
            for (int j = 0; j < 4; j++)
            {
                if (shell_cmds[i].params[j].sign == 0)
                    break;
                printf("\t\t%s\t%s\n", shell_cmds[i].params[j].name, shell_cmds[i].params[j].desc);
            }
        }
    }
}

void show_about_info()
{
    printf("Satori OS is a simple OS written by C.\n");
    if (!has_param())
        print_info();
    else
    {
        if (get_param('v') != 0)
            printf("%s\n\r", VERSION);
        if (get_param('a') != 0)
            printf("%s\n\r", AUTHOR);
        if (get_param('c') != 0)
            printf("%s\n\r", COPYRIGHT);
        if (get_param('l') != 0)
            printf("%s\n\r", LABEL);
        if (get_param('o') != 0)
            printf("%s\n\r", ORIGIN);
    }
}