#include "app/vim.h"
#include "lib/text.h"
#include "io/kbdin.h"
#include "lib/string.h"
#include "drivers/ansi.h"
#include "mm/kmalloc.h"

text_buffer *vim_text_buffer;

const char* vim_prompt = 
"void text_buffer_write_char(text_buffer *buffer, char c)\n
{\n
    if (is_reserved(buffer->cur_char))\n
    {\n
        text_buffer_insert_char(buffer, c);\n
    }\n
    buffer->cur_char->ch = c;\n
    text_buffer_cursor_next(buffer);\n
}";

void vim_test()
{
    vim_text_buffer = text_buffer_create();
    text_buffer_load(vim_text_buffer, vim_prompt);
    kbd_event e;
    clear_screen();
    cursor_reset();
    while (true)
    {
        e = kbd_wait_key_down();
        if (e.key_no == KEY_ESC)
            break;
        switch (e.key_no)
        {
        case KEY_UP_ADJUST:
            text_buffer_cursor_up(vim_text_buffer);
            break;
        case KEY_DOWN_ADJUST:
            text_buffer_cursor_down(vim_text_buffer);
            break;
        case KEY_LEFT_ADJUST:
            text_buffer_cursor_prev(vim_text_buffer);
            break;
        case KEY_RIGHT_ADJUST:
            text_buffer_cursor_next(vim_text_buffer);
            break;
        case KEY_DELETE_ADJUST:
            text_buffer_delete_char(vim_text_buffer);
            break;
        case KEY_BACKSPACE:
            text_buffer_backspace(vim_text_buffer);
            break;
        case KEY_ENTER:
            text_buffer_newline(vim_text_buffer);
            break;
        default:
            if (e.key == '\t')
                text_buffer_insert_string(vim_text_buffer, "    ");
            else
                text_buffer_insert_char(vim_text_buffer, e.key);
            break;
        }
        clear_screen();
        cursor_reset();
        // text_buffer_print_info(vim_text_buffer);
        text_buffer_print_text(vim_text_buffer);
        text_cursor cursor = vim_text_buffer->cursor;
        cursor_move_to(cursor.x, cursor.y);
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