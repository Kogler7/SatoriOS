#include "drivers/ansi.h"

sint ansi_cur_color = ANSI_WHITE;
sint ansi_cur_style = ANSI_CURSOR_STYLE_RESET;

sint ansi_color_stack[ANSI_STACK_SIZE];
sint ansi_style_stack[ANSI_STACK_SIZE];

int color_stack_ptr = 0;
int style_stack_ptr = 0;

void save_cursor_style()
{
    if (style_stack_ptr >= ANSI_STACK_SIZE)
        return;
    ansi_style_stack[style_stack_ptr++] = ansi_cur_style;
}

void restore_cursor_style()
{
    if (style_stack_ptr <= 0)
        return;
    ansi_cur_style = ansi_style_stack[--style_stack_ptr];
    set_cursor_style(ansi_cur_style);
}

void save_cursor_color()
{
    if (color_stack_ptr >= ANSI_STACK_SIZE)
        return;
    ansi_color_stack[color_stack_ptr++] = ansi_cur_color;
}

void restore_cursor_color()
{
    if (color_stack_ptr <= 0)
        return;
    ansi_cur_color = ansi_color_stack[--color_stack_ptr];
    set_cursor_color(ansi_cur_color);
}