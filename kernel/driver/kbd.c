#include "driver/kbd.h"
#include "loongarch.h"
#include "trap/ls7a.h"
#include "satio/printf.h"

#pragma GCC diagnostic ignored "-Warray-bounds"

int shift_state = KEY_STATE_UP;
int ctrl_state = KEY_STATE_UP;
int alt_state = KEY_STATE_UP;
int caps_lock_state = CAPS_UNLOCK;

void (*cbk_table[KBD_CBK_MAX])(char, int) = {0};

int register_kbd_cbk(void (*cbk_func)(char, int))
{
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
    if (cbk_id >= 0 && cbk_id < KBD_CBK_MAX)
    {
        cbk_table[cbk_id] = 0;
    }
    for (; cbk_id < KBD_CBK_MAX - 1; cbk_id++)
    {
        cbk_table[cbk_id] = cbk_table[cbk_id + 1];
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

int kbd_has_data(void)
{
    unsigned char status = *(volatile unsigned char *)(LS7A_I8042_STATUS);
    return (status & 0x1);
}

unsigned char kbd_read_byte(void)
{
    return *(volatile unsigned char *)(LS7A_I8042_DATA);
}

char scan2ascii(int code)
{
    return kbd_US[keymap[(unsigned int)code]];
}

void handle_kbd_irq(void)
{
    unsigned char status = *(volatile unsigned char *)(LS7A_I8042_STATUS);
    unsigned char code = *(volatile unsigned char *)(LS7A_I8042_DATA);
    unsigned char key_no = keymap[(unsigned int)code];

    int key_state = KEY_STATE_DOWN;

    if (status & 0x80) // 0x80待定
    {
        // 键盘错误
        printf("keyboard error: %x\n", key);
        return;
    }

    if (key_no == KEY_INSERT)
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