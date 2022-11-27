#include "boot/boot_param.h"
#ifndef _SATORI_SHELL_H_
#define _SATORI_SHELL_H_

#define SHELL_BUFFER_SIZE 256
#define SHELL_CMD_MAX 64
#define CMD_PARAM_MAX 8

typedef struct {
    char sign;
    char name[16];
    char desc[64];
} cmd_param;

typedef struct {
    char sign;
    char param[64];
} param_unit;

typedef struct {
    char cmd[16];
    char desc[64];
    cmd_param params[4];
    void (*func)();
} shell_cmd;

extern char input_buff[SHELL_BUFFER_SIZE];

extern shell_cmd shell_cmds[SHELL_CMD_MAX];

extern param_unit param_buff[CMD_PARAM_MAX];

extern int shell_exit_flag;

void entry_shell();

#endif /* !_SATORI_SHELL_H_ */