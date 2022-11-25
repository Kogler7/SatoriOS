#pragma GCC diagnostic ignored "-Wreturn-type"                   //正式开发建议删除此行
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration" //正式开发建议删除此行
#include "drivers/kbd.h"
#include "arch/ls7a.h"
#include "shell/shell.h"
#include "sysio/io.h"
#include "app/vim.h"

// char kbd_buf[KBD_BUF_SIZE];
// unsigned int kbd_start_ptr = 0;
// unsigned int kbd_end_ptr = 0;
int kbd_status[128] = {0}; // 0 up 1 down
int capslock_state = CAPS_LOWER;

int kbd_callback_table_num = 0;
void (*kbd_callback_table[KBD_CALLBACK_TABLE])(char, int);

int kbd_event_register(void *f_entry)
{
    if (f_entry == 0)
    {
        return -1;
    }
    else
        kbd_callback_table[kbd_callback_table_num] = f_entry;
    kbd_callback_table_num += 1;
    return kbd_callback_table_num - 1;
}

int kbd_event_invoke(char issue_c, int key_state, int kbd_n)
{
    int kbd_event_num = kbd_callback_table_num;
    for (int i = 0; i < kbd_event_num; i++)
    {
        //(kbd_callback_table[i])(kbd_buf[(kbd_end_ptr-1)%KBD_BUF_SIZE]);
        (kbd_callback_table[i])(issue_c, key_state);
    }
}

unsigned char kbd_irq()
{
    char issue_c = 0;
    int kbd_n = 0;
    while (kbd_has_data())
    {
        // printf("%x ", kbd_read_byte());
        kbd_n = keymap[(unsigned int)kbd_read_byte()];
        // printf("%d\n",kbd_n);
        //解析位置
        kbd_status[kbd_n] = KEY_PUSH;
        if (kbd_n == KEY_INSERT)
        { //??
            kbd_n = keymap[(unsigned int)kbd_read_byte()];
            kbd_status[kbd_n] = KEY_RELEASE;
        }
        if (kbd_n == KEY_CAPSLOCK && kbd_status[kbd_n] == KEY_PUSH)
        {
            capslock_state = !capslock_state;
        }
        // else{
        //     kbd_status[kbd_n] = !kbd_status[kbd_n];
        //     continue;
        // }
        //解析内容并保存到键盘缓冲区
        if ((kbd_status[KEY_LEFTSHIFT] == KEY_PUSH || kbd_status[KEY_RIGHTSHIFT] == KEY_PUSH))
        {
            // kbd_buf[(kbd_end_ptr++) % KBD_BUF_SIZE] = kbd_US_up[ kbd_n ];
            issue_c = kbd_US_shift[kbd_n];
        }
        else
        {
            // kbd_buf[(kbd_end_ptr++)% KBD_BUF_SIZE] = kbd_US[ kbd_n ];
            issue_c = kbd_US[kbd_n];
        }
        // kbd_end_ptr %= KBD_BUF_SIZE;
        // printf("%c", kbd_US[ keymap[ (unsigned int)kbd_read_byte() ] ]);
    }

    // kbd_event_invoke(issue_c, kbd_status[kbd_n]);
    //  shell_buf_update(issue_c, kbd_status[kbd_n], kbd_n);
    //  vim_input_handle(issue_c, kbd_status[kbd_n], kbd_n);

    // printf("key done\n");
}

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

// int kbd_has_data(void)
// {
//     unsigned char status = *(volatile unsigned char *)(LS7A_I8042_STATUS);
//     return (status & 0x1);
// }

// unsigned char kbd_read_byte(void)
// {
//     return *(volatile unsigned char *)(LS7A_I8042_DATA);
// }

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
        printf("keyboard error: %x\n", key_no);
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