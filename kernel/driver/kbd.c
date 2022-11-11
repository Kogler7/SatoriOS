#include "driver/kbd.h"
#include "loongarch.h"
#include "trap/ls7a.h"
#include "satio/printf.h"

#pragma GCC diagnostic ignored "-Warray-bounds"

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