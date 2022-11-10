#define SHELL_BUFFER_SIZE 1024
#define SHELL_CMD_MAX 64

void entry_shell();
void show_help();

extern char input_buff[SHELL_BUFFER_SIZE];

extern shell_cmd shell_cmds[SHELL_CMD_MAX];

typedef struct {
    char sign;
    char name[16];
    char desc[64];
    void (*func)();
} cmd_param;

typedef struct {
    char cmd[16];
    char desc[64];
    cmd_param params[4];
    void (*func)();
} shell_cmd;