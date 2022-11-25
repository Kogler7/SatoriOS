#include "shell.h"
#include "utils.h"

param_unit param_buff[CMD_PARAM_MAX];

void parse_command()
{
    // 清空param_buff
    memset(param_buff, 0, sizeof(param_buff));

    char cmd_buff[16] = {0};

    char *p = input_buff;
    char *c = cmd_buff;

    // 解析input_buff
    while (*p == ' ')
        p++;
    while (*p != ' ' && *p != 0)
    {
        *c = *p;
        p++;
    }
    while (*p == ' ')
        p++;
    for (int i = 0; i < SHELL_CMD_MAX; i++)
    {
        if (strcmp(cmd_buff, shell_cmds[i].cmd) == 0)
        {
            if (shell_cmds[i].func != 0)
            {
                // 解析参数
                if (shell_cmds[i].params[0].sign != 0)
                {
                    int j = 0;
                    while (*p != 0)
                    {
                        while (*p == ' ')
                            p++;
                        if (*p == '-')
                        {
                            p++;
                            param_buff[j].sign = *p;
                            p++;
                            while (*p == ' ')
                                p++;
                            int k = 0;
                            while (*p != ' ' && *p != 0)
                            {
                                // 将解析结果存入param_buff
                                param_buff[j].param[k] = *p;
                                p++;
                                k++;
                            }
                            j++;
                        }
                    }
                }
                // 调用对应的函数
                shell_cmds[i].func();
            }
            else
                printf("Command %s is not implemented yet.\r", shell_cmds[i].cmd);
            return;
        }
        printf("Command %s not found.\r", cmd_buff);
    }
}

int has_param()
{
    for (int i = 0; i < CMD_PARAM_MAX; i++)
    {
        if (param_buff[i].sign != 0)
            return 1;
    }
    return 0;
}

char *get_param(char sign)
{
    for (int i = 0; i < CMD_PARAM_MAX; i++)
    {
        if (param_buff[i].sign == sign)
            return param_buff[i].param;
    }
    return 0;
}