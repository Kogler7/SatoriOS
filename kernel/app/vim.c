#include "app/vim.h"
#include "io/stdio.h"
#include "lib/string.h"
#include "drivers/kbd.h"
#include "drivers/ansi.h"

void vim_test()
{
    clear_screen();
    curser_move_to(1,2);
    put_char('*');
    curser_reset();
    put_char('*');
    curser_move_down(2);
    put_char('|');
    curser_move_forward(3);
    put_char('*');
    // curser_move_backward(80);
    put_char('-');
    // clear_screen_to_cursor();
    clear_line_to_cursor();
    scroll_down(10);
    set_curser_style(9);
    set_curser_color(33);
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