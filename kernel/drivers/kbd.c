#pragma GCC diagnostic ignored "-Wreturn-type"                   // 正式开发建议删除此行
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration" // 正式开发建议删除此行
#include "drivers/kbd.h"
#include "arch/ls7a.h"
#include "shell/shell.h"
#include "io/stdio.h"
#include "app/vim.h"

int shift_state = KEY_STATE_UP;
int ctrl_state = KEY_STATE_UP;
int alt_state = KEY_STATE_UP;
int caps_lock_state = CAPS_UNLOCK;

void (*cbk_table[KBD_CBK_MAX])(char, int) = {0};

int register_kbd_cbk(void (*cbk_func)(char, int))
{
    // printf("reg");
    for (int i = 0; i < KBD_CBK_MAX; i++)
    {
        if (cbk_table[i] == 0)
        {
            cbk_table[i] = cbk_func;
            return i;
        }
    }
    return -1;
}

void unregister_kbd_cbk(int cbk_id)
{
    // printf("unreg");
    if (cbk_id >= 0 && cbk_id < KBD_CBK_MAX)
    {
        cbk_table[cbk_id] = 0;
    }
}

int get_cbk_cnt()
{
    int n = 0;
    for (int i = 0; i < KBD_CBK_MAX; i++)
    {
        if (cbk_table[i] != 0)
        {
            n++;
        }
    }
    return n;
}

void print_cbk_table()
{
    for (int i = 0; i < KBD_CBK_MAX; i++)
    {
        if (cbk_table[i])
            putc('1');
        else
            putc('0');
    }
}

void invoke_kbd_cbk(char key, int state)
{
    for (int i = 0; i < KBD_CBK_MAX; i++)
    {
        if (cbk_table[i] != 0)
        {
            cbk_table[i](key, state);
        }
    }
}

char scan2ascii(int code)
{
    return kbd_US[keymap[(unsigned int)code]];
}

void handle_kbd_irq(void)
{
    while (kbd_has_data()) // while 用于稳定键盘中断，具体原理不详
    {
        unsigned char code = kbd_read_byte();
        unsigned char key_no = keymap[(unsigned int)code];

        int key_state = KEY_STATE_DOWN;

        if (code == 0xF0 && kbd_has_data())
        {
            key_no = keymap[(unsigned int)kbd_read_byte()];
            key_state = KEY_STATE_UP;
        }

        if (key_no == KEY_LEFTSHIFT || key_no == KEY_RIGHTSHIFT)
        {
            shift_state = key_state;
        }
        else if (key_no == KEY_LEFTCTRL || key_no == KEY_RIGHTCTRL)
        {
            ctrl_state = key_state;
        }
        else if (key_no == KEY_LEFTALT || key_no == KEY_RIGHTALT)
        {
            alt_state = key_state;
        }
        else if (key_no == KEY_CAPSLOCK && key_state == KEY_STATE_DOWN)
        {
            caps_lock_state = !caps_lock_state;
        }
        else
        {
            char key;
            if (shift_state == KEY_STATE_DOWN)
            {
                key = kbd_US_shift[key_no];
            }
            else
            {
                key = kbd_US[key_no];
            }

            if (caps_lock_state == CAPS_LOCK)
            {
                if (key >= 'a' && key <= 'z')
                {
                    key = key - 'a' + 'A';
                }
            }
            invoke_kbd_cbk(key, key_state);
        }
    }
}