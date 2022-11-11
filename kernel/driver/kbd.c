#include "driver/kbd.h"
#include "loongarch.h"
#include "trap/ls7a.h"
#include "satio/printf.h"

#pragma GCC diagnostic ignored "-Warray-bounds"

int kbd_status[128] = {0};
int kbd_status_shift = 0;
int caps_lock_state = CAPS_UNLOCK;

void (*cbk_table[KBD_CBK_MAX])(char, int) = {0};

int register_kbd_cbk(void (*cbk_func)(char, int))
{
    for (int i = 0; i < KBD_CBK_MAX; i++)
    {
        if (cbk_table[i] == 0)
        {
            cbk_table[i] = cbk_func;
            return 0;
        }
    }
    return -1;
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
    unsigned char data = *(volatile unsigned char *)(LS7A_I8042_DATA);
    if (status & 0x80)
    {
        // printf("keyboard error: %x\n", data);
        return;
    }
    if (data == 0xe0)
    {
        kbd_status_shift = 1;
        return;
    }
    if (kbd_status_shift)
    {
        kbd_status_shift = 0;
        data += 128;
    }
    if (data == 0x3a)
    {
        caps_lock_state = !caps_lock_state;
        return;
    }
    if (data == 0x2a || data == 0x36)
    {
        kbd_status_shift = 1;
        return;
    }
    if (data == 0xaa || data == 0xb6)
    {
        kbd_status_shift = 0;
        return;
    }
    if (kbd_status[data] == 0)
    {
        kbd_status[data] = 1;
        char key = scan2ascii(data);
        if (caps_lock_state == CAPS_LOCK)
        {
            if (key >= 'a' && key <= 'z')
            {
                key = key - 'a' + 'A';
            }
        }
        invoke_kbd_cbk(key, 1);
    }
    else
    {
        kbd_status[data] = 0;
        char key = scan2ascii(data);
        if (caps_lock_state == CAPS_LOCK)
        {
            if (key >= 'a' && key <= 'z')
            {
                key = key - 'a' + 'A';
            }
        }
        invoke_kbd_cbk(key, 0);
    }
}

void handle_kbd_irq()
{
    while (kbd_has_data())
    {
        char key = scan2ascii(kbd_read_byte());
        for(int i=0;i<KBD_CBK_MAX;i++)
        {
            if(cbk_table[i]!=0)
            {
                if(kbd_status_shift)
                {
                    cbk_table[i](key, KBD_SHIFT);
                }
                else
                {
                    cbk_table[i](key, KBD_NORMAL);
                }
                cbk_table[i](key, 1);
            }
        }
    }
}