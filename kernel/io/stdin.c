#include "io/stdin.h"
#include "io/stdout.h"

std_buffer *stdin_buffer;

int stdin_enabled = 0;
int kbd_cbk_id = -1;

void stdin_init()
{
    stdin_buffer = std_buffer_create(STDIN_BUFFER_SIZE);
}

void stdin_kbd_cbk(char c, int state)
{
    if (state == KEY_STATE_DOWN)
    {
        if (c == '\b')
        {
            if (stdin_buffer->size > 0)
            {
                std_buffer_pop(stdin_buffer);
                putc('\b');
                putc(' ');
                putc('\b');
            }
        }
        else
        {
            std_buffer_put(stdin_buffer, c);
            putc(c);
        }
    }
}

void stdin_clear()
{
    std_buffer_clear(stdin_buffer);
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
    stdin_enable();
    byte c = 0;
    while (c == 0)
    {
        c = std_buffer_get(stdin_buffer);
    }
    stdin_disable();
    return c;
}

int gets(char *str, int size)
{
    stdin_enable();
    int n = std_buffer_wait_line(stdin_buffer, str, size);
    stdin_disable();
    return n;
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
    return 0;
}