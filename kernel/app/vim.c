#include "app/vim.h"
#include "lib/text.h"
#include "io/kbdin.h"
#include "lib/string.h"
#include "drivers/ansi.h"
#include "mm/kmalloc.h"

text_buffer *vim_text_buffer;

const char vim_prompt[] =
    "void text_buffer_write_char(text_buffer *buffer, char c)\n"
    "{\n"
    "    if (is_reserved(buffer->cur_char))\n"
    "    {\n"
    "        text_buffer_insert_char(buffer, c);\n"
    "    }\n"
    "    buffer->cur_char->ch = c;\n"
    "    text_buffer_cursor_next(buffer);\n"
    "}";

void vim_render(text_buffer *buffer)
{
    cursor_reset();
    static char line_buffer[80];
    text_cursor cursor = buffer->cursor;
    text_line *line = buffer->fst_line;
    char *ptr = nullptr;
    puts("SatoriOS Vim");
    cursor_move_to(60, 1);
    puts("| Press ESC to exit");
    puts_nr('-', 80);
    putc('\n');
    while (line != nullptr)
    {
        text_buffer_save_line(buffer, line_buffer, 80);
        ptr = line_buffer;
        while (*ptr)
        {
            putc(*ptr);
            ptr++;
        }
        newline();
        clear_line_from_cursor();
        line = line->next;
    }
    clear_screen_from_cursor();
    cursor_move_to(1, 23);
    puts_nr('-', 80);
    cursor_move_to(1, 24);
    puts_st("Test.txt");
    cursor_move_to(60, 24);
    printf("Line: %d/%d, Col: %d/%d", buffer->cursor.y, buffer->nr_lines, buffer->cursor.x, buffer->cur_line->nr_chars);
    cursor_move_to(cursor.x, cursor.y);
}

void vim_test()
{
    vim_text_buffer = text_buffer_create();
    text_buffer_load_text(vim_text_buffer, vim_prompt);
    kbd_event e;
    vim_render(vim_text_buffer);
    while (true)
    {
        e = kbd_wait_key_down();
        if (e.key_no == KEY_ESC)
        {
            clear_screen();
            cursor_reset();
            break;
        }
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
        vim_render(vim_text_buffer);
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