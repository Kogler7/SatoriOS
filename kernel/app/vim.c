#include "app/vim.h"
#include "lib/text.h"
#include "io/stdio.h"
#include "lib/string.h"
#include "drivers/kbd.h"
#include "drivers/ansi.h"

text_buffer *vim_text_buffer;

void vim_test()
{
    vim_text_buffer = text_buffer_create();
    char c;
    while (c = getc())
    {
        switch (c)
        {
        case '\b':
            text_buffer_backspace(vim_text_buffer);
            break;
        case '\n':
            text_buffer_newline(vim_text_buffer);
            break;
        case KEY_UP:
            text_buffer_cursor_up(vim_text_buffer);
            break;
        case KEY_DOWN:
            text_buffer_cursor_down(vim_text_buffer);
            break;
        case KEY_LEFT:
            text_buffer_cursor_prev(vim_text_buffer);
            break;
        case KEY_RIGHT:
            text_buffer_cursor_next(vim_text_buffer);
            break;
        default:
            text_buffer_insert_char(vim_text_buffer, c);
            break;
        }
        char *text = text_buffer_save(vim_text_buffer);
        clear_screen();
        puts(text);
    }
}

void vim_entry(char *file_path)
{
    // char *p = file_path;
    // char *q = p;
    // char file_name[NAME_LEN_MAX] = {0};
    // char *c = file_name;
    // while (*p != 0)
    // {
    //     if (*p == '/')
    //     {
    //         q = p;
    //     }
    //     p++;
    // }
    // q++;
    // while (*q != 0)
    // {
    //     *c++ = *q++;
    // }
    // printf("file name: %s\n\r", file_name);
    // printf("file path: %s\n\r", file_path);
    vim_test();
}