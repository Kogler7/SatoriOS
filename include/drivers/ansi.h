#include "types.h"
#include "drivers/serial.h"

#ifndef _ANSI_ESCAPE_SEQUENCE_H_
#define _ANSI_ESCAPE_SEQUENCE_H_

#define ANSI_BLACK      0
#define ANSI_RED        1
#define ANSI_GREEN      2
#define ANSI_YELLOW     3
#define ANSI_BLUE       4
#define ANSI_MAGENTA    5
#define ANSI_CYAN       6
#define ANSI_WHITE      7

#define ANSI_CURSOR_STYLE_RESET         0
#define ANSI_CURSOR_STYLE_BOLD          1
#define ANSI_CURSOR_STYLE_FAINT         2
#define ANSI_CURSOR_STYLE_ITALIC        3
#define ANSI_CURSOR_STYLE_UNDERLINE     4
#define ANSI_CURSOR_STYLE_SLOW_BLINK    5
#define ANSI_CURSOR_STYLE_RAPID_BLINK   6
#define ANSI_CURSOR_STYLE_REVERSE       7
#define ANSI_CURSOR_STYLE_CONCEAL       8
#define ANSI_CURSOR_STYLE_CROSSED_OUT   9
#define ANSI_CURSOR_STYLE_PRIMARY_FONT  10

static sint ansi_tmp_color;
static sint ansi_tmp_style;

static inline void put_head()
{
    serial_send_char('\033');
    serial_send_char('[');
}

static char digits[] = "0123456789";

static inline void put_code(sint code)
{
    static char buf[4];
    static sint i;
    i = 0;
    do
    {
        buf[i++] = digits[code % 10];
    } while ((code /= 10) != 0);

    while (--i >= 0)
        serial_send_char(buf[i]);
}

static inline void put_char(char c)
{
    serial_send_char(c);
}

static inline void cursor_move_to(sint x, sint y)
{
    // \033[<L>;<C>H
    put_head(); 
    put_code(y);
    put_char(';');
    put_code(x);
    put_char('H');
}

static inline void cursor_reset(void)
{
    // \033[H
    put_head();
    put_char('H');
}

static inline void cursor_move_up(sint n)
{
    // \033[<N>A
    put_head();
    put_code(n);
    put_char('A');
}

static inline void cursor_move_down(sint n)
{
    // \033[<N>B
    put_head();
    put_code(n);
    put_char('B');
}

static inline void cursor_move_forward(sint n)
{
    // \033[<N>C
    put_head();
    put_code(n);
    put_char('C');
}

static inline void cursor_move_backward(sint n)
{
    // \033[<N>D
    put_head();
    put_code(n);
    put_char('D');
}

static inline void cursor_move_next_line(sint n)
{
    // \033[<N>E
    put_head();
    put_code(n);
    put_char('E');
}

static inline void cursor_move_previous_line(sint n)
{
    // \033[<N>F
    put_head();
    put_code(n);
}

static inline void cursor_move_horizontal(sint n)
{
    // \033[<N>G
    put_head();
    put_code(n);
    put_char('G');
}

static inline void cursor_move_horizontal_absolute(sint n)
{
    // \033[<N>d
    put_head();
    put_code(n);
    put_char('d');
}

static inline void clear_screen_from_cursor()
{
    // \033[J
    put_head();
    put_char('J');
}

static inline void clear_screen_to_cursor()
{
    // \033[1J
    put_head();
    put_char('1');
    put_char('J');
}

static inline void clear_screen()
{
    // \033[2J
    put_head();
    put_char('2');
    put_char('J');
}

static inline void clear_line_from_cursor()
{
    // \033[K
    put_head();
    put_char('K');
}

static inline void clear_line_to_cursor()
{
    // \033[1K
    put_head();
    put_char('1');
    put_char('K');
}

static inline void clear_line()
{
    // \033[2K
    put_head();
    put_char('2');
    put_char('K');
}

static inline void scroll_up(sint n)
{
    // \033[<N>S
    put_head();
    put_code(n);
    put_char('S');
}

static inline void scroll_down(sint n)
{
    // \033[<N>T
    put_head();
    put_code(n);
    put_char('T');
}

static inline void save_cursor_position()
{
    // \033[s
    put_head();
    put_char('s');
}

static inline void restore_cursor_position()
{
    // \033[u
    put_head();
    put_char('u');
}

static inline void hide_cursor()
{
    // \033[?25l
    put_head();
    put_char('?');
    put_code(25);
    put_char('l');
}

static inline void show_cursor()
{
    // \033[?25h
    put_head();
    put_char('?');
    put_code(25);
    put_char('h');
}

static inline void set_cursor_style(sint style)
{
    // \033[<N> q
    put_head();
    put_code(style);
    put_char('m');
}

static inline void set_cursor_color(sint color)
{
    // \033[<N> q
    put_head();
    put_char('3');
    put_code(color);
    put_char('m');
}

static inline void set_cursor_background_color(sint color)
{
    // \033[<N> q
    put_head();
    put_char('4');
    put_code(color);
    put_char('m');
}

static inline void save_cursor_style()
{
    ansi_tmp_style = ansi_cursor_style;
}

static inline void restore_cursor_style()
{
    set_cursor_style(ansi_tmp_style);
}

static inline void save_cursor_color()
{
    ansi_tmp_color = ansi_cursor_color;
}

static inline void restore_cursor_color()
{
    set_cursor_color(ansi_tmp_color);
}

#endif /* !_ANSI_ESCAPE_SEQUENCE_H_ */