#include "drivers/ansi.h"

sint ansi_cur_color;
sint ansi_cur_style;

sint ansi_color_stack[ANSI_STACK_SIZE];
sint ansi_style_stack[ANSI_STACK_SIZE];

void save_cursor_style()
{
    static sint i = 0;
    if(i >= ANSI_STACK_SIZE)
    {
        return;
    }
    ansi_style_stack[i++] = ansi_cur_style;
}

void restore_cursor_style()
{
    static sint i = 0;
    if (i <= 0)
    {
        return;
    }
    ansi_cur_style = ansi_style_stack[i--];
    set_cursor_style(ansi_cur_style);
}

void save_cursor_color()
{
    static sint i = 0;
    if(i >= ANSI_STACK_SIZE)
    {
        return;
    }
    ansi_color_stack[i++] = ansi_cur_color;
}

void restore_cursor_color()
{
    static sint i = 0;
    if (i <= 0)
    {
        return;
    }
    ansi_cur_color = ansi_color_stack[i--];
    set_cursor_color(ansi_cur_color);
}