#include "shell/shell.h"
#include "io/stdio.h"
#include "utils/string.h"

param_unit param_buff[CMD_PARAM_MAX];

void parse_params(int cmd_id)
{
    if (shell_cmds[cmd_id].params[0].sign == 0)
        return;
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
            // 实现不够完善
            while (*p != ' ' && *p != 0 && j < CMD_PARAM_MAX)
            {
                param_buff[++j].sign = *(p++);
            }
            while (*p == ' ')
                p++;
            int k = 0;
            while (*p != ' ' && *p != 0 && *p != '-')
            {
                // 将解析结果存入param_buff
                param_buff[j].param[k] = *p;
                p++;
                k++;
            }
            if (++j >= CMD_PARAM_MAX)
                break;
        }
    }
}

void parse_command()
{
    // 清空param_buff
    memset(param_buff, 0, sizeof(param_buff));

    char cmd_buff[16] = {0};

    char *p, *q = input_buff;
    char *c = cmd_buff;

    // 解析input_buff
    while (*p == ' ')
        p++;
    while (*p != ' ' && *p != 0 && c - cmd_buff < 16)
    {
        *c++ = *p++;
    }
    while (*p == ' ')
        p++;
    // 参数部分前移
    while (*p != 0)
    {
        *q++ = *p++;
    }
    *q = 0;

    for (int i = 0; i < SHELL_CMD_MAX; i++)
    {
        if (strcmp(cmd_buff, shell_cmds[i].cmd) == 0)
        {
            if (shell_cmds[i].func != 0)
            {
                // 解析参数
                parse_params(i);
                // 调用对应的函数
                shell_cmds[i].func(i);
            }
            else
            {
                printf("Command %s is not implemented yet.\n\r", shell_cmds[i].cmd);
            }
            return;
        }
    }
    printf("Command %s not found.\n\r", cmd_buff);
}

int has_param(int cmd_id = 0)
{
    cmd_param *cmd_params = shell_cmds[cmd_id].params;
    if (cmd_params[0].sign == 0 || param_buff[0].sign == 0)
        return 0;
    for (int i = 0; i < CMD_PARAM_MAX; i++)
    {
        if (param_buff[i].sign == 0)
            return 0;
        for (int j = 0; j < CMD_PARAM_MAX; j++)
        {
            if (cmd_params[j].sign == 0)
                break;
            if (cmd_params[j].sign == param_buff[i].sign)
                return 1;
        }
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