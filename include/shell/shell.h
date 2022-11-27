#include "boot/boot_param.h"
#ifndef _SATORI_SHELL_H_
#define _SATORI_SHELL_H_

#define SHELL_BUFFER_SIZE   256
#define SHELL_CMD_MAX       64
#define CMD_PARAM_MAX       8
#define NAME_LEN_MAX        16
#define DESC_LEN_MAX        64

typedef struct {
    char sign;
    char name[NAME_LEN_MAX];
    char desc[DESC_LEN_MAX];
} cmd_param;

typedef struct {
    char sign;
    char param[DESC_LEN_MAX];
} param_unit;

typedef struct {
    char cmd[NAME_LEN_MAX];
    char desc[DESC_LEN_MAX];
    cmd_param params[CMD_PARAM_MAX];
    void (*func)();
} shell_cmd;

extern char input_buff[SHELL_BUFFER_SIZE];

extern shell_cmd shell_cmds[SHELL_CMD_MAX];

extern param_unit param_buff[CMD_PARAM_MAX];

extern int shell_exit_flag;

void entry_shell();

#endif /* !_SATORI_SHELL_H_ */