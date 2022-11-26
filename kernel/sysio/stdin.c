#include "io/stdin.h"

std_buffer stdin_buffer;

int stdin_enabled = 0;
int kbd_cbk_id = -1;

void stdin_init()
{
    stdin_buffer = std_buffer_create(STDIN_BUFFER_SIZE);
    stdin_enable();
}

void stdin_kbd_cbk(char c, int state);
{
    if (state == KEY_STATE_DOWN)
    {
        std_buffer_put(&stdin_buffer, c);
    }
}

void stdin_clear()
{
    std_buffer_clear(&stdin_buffer);
}

void stdin_enable()
{
    if (stdin_enabled)
        return;
    kbd_cbk_id = register_kbd_cbk(stdin_kbd_cbk);
    if (kbd_cbk_id != -1)
        stdin_enabled = 1;
}

void stdin_disable()    
{
    if (!stdin_enabled)
        return;
    unregister_kbd_cbk(kbd_cbk_id);
    kbd_cbk_id = -1;
    stdin_enabled = 0;
}

char getc()
{
    return std_buffer_get(&stdin_buffer);
}

void gets(char *str)
{
    if (!stdin_enabled)
        return;
    std_buffer_wait_line(&stdin_buffer, str, STDIN_BUFFER_SIZE);
}

int scanf(const char *format, ...)
{
    // if (!stdin_enabled)
    //     return 0;
    // va_list args;
    // va_start(args, format);
    // int ret = vsscanf(stdin_buffer.data, format, args);
    // va_end(args);
    // return ret;
}