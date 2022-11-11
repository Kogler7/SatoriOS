#define SHELL_BUFFER_SIZE 1024
#define SHELL_CMD_MAX 64
#define CMD_PARAM_MAX 4

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

void entry_shell();
void show_help();

int has_param();
char* get_param(char sign);