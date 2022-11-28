#include "drivers/serial.h"

#ifndef _ANSI_ESCAPE_SEQUENCE_H_
#define _ANSI_ESCAPE_SEQUENCE_H_

#define ANSI_BLACK_FRONT    0
#define ANSI_RED_FRONT      1
#define ANSI_GREEN_FRONT    2
#define ANSI_YELLOW_FRONT   3
#define ANSI_BLUE_FRONT     4
#define ANSI_MAGENTA_FRONT  5
#define ANSI_CYAN_FRONT     6
#define ANSI_WHITE_FRONT    7

#define ANSI_BLACK_BACK     0
#define ANSI_RED_BACK       1
#define ANSI_GREEN_BACK     2
#define ANSI_YELLOW_BACK    3
#define ANSI_BLUE_BACK      4
#define ANSI_MAGENTA_BACK   5
#define ANSI_CYAN_BACK      6
#define ANSI_WHITE_BACK     7

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

static inline void put_head()
{
    serial_send_char('\033');
    serial_send_char('[');
}

static char digits[] = "0123456789";

static inline void put_code(unsigned int code)
{
    static char buf[4];
    static int i;
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

static inline void cursor_move_to(int x, int y)
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

static inline void cursor_move_up(int n)
{
    // \033[<N>A
    put_head();
    put_code(n);
    put_char('A');
}

static inline void cursor_move_down(int n)
{
    // \033[<N>B
    put_head();
    put_code(n);
    put_char('B');
}

static inline void cursor_move_forward(int n)
{
    // \033[<N>C
    put_head();
    put_code(n);
    put_char('C');
}

static inline void cursor_move_backward(int n)
{
    // \033[<N>D
    put_head();
    put_code(n);
    put_char('D');
}

static inline void cursor_move_next_line(int n)
{
    // \033[<N>E
    put_head();
    put_code(n);
    put_char('E');
}

static inline void cursor_move_previous_line(int n)
{
    // \033[<N>F
    put_head();
    put_code(n);
}

static inline void cursor_move_horizontal(int n)
{
    // \033[<N>G
    put_head();
    put_code(n);
    put_char('G');
}

static inline void cursor_move_horizontal_absolute(int n)
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

static inline void scroll_up(int n)
{
    // \033[<N>S
    put_head();
    put_code(n);
    put_char('S');
}

static inline void scroll_down(int n)
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

static inline void set_cursor_style(int style)
{
    // \033[<N> q
    put_head();
    put_code(style);
    put_char('m');
}

static inline void set_cursor_color(int color)
{
    // \033[<N> q
    put_head();
    put_char('3');
    put_code(color);
    put_char('m');
}

static inline void set_cursor_background_color(int color)
{
    // \033[<N> q
    put_head();
    put_char('4');
    put_code(color);
    put_char('m');
}

#endif /* !_ANSI_ESCAPE_SEQUENCE_H_ */