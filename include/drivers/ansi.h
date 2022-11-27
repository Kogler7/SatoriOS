#ifndef _ANSI_ESCAPE_SEQUENCE_H_
#define _ANSI_ESCAPE_SEQUENCE_H_

#define ANSI_BLACK_FRONT    30
#define ANSI_RED_FRONT      31
#define ANSI_GREEN_FRONT    32
#define ANSI_YELLOW_FRONT   33
#define ANSI_BLUE_FRONT     34
#define ANSI_MAGENTA_FRONT  35
#define ANSI_CYAN_FRONT     36
#define ANSI_WHITE_FRONT    37

#define ANSI_BLACK_BACK     40
#define ANSI_RED_BACK       41
#define ANSI_GREEN_BACK     42
#define ANSI_YELLOW_BACK    43
#define ANSI_BLUE_BACK      44
#define ANSI_MAGENTA_BACK   45
#define ANSI_CYAN_BACK      46
#define ANSI_WHITE_BACK     47

#define ANSI_CURSOR_STYLE_BLINKING_BLOCK        5
#define ANSI_CURSOR_STYLE_BLINKING_UNDERSCORE   6
#define ANSI_CURSOR_STYLE_STEADY_BLOCK          7
#define ANSI_CURSOR_STYLE_STEADY_UNDERSCORE     8
#define ANSI_CURSOR_STYLE_BLINKING_BAR          9
#define ANSI_CURSOR_STYLE_STEADY_BAR            10

static inline void curser_move_to(int x, int y)
{
    printf("\033[%d;%dH", y, x);
}

static inline void curser_reset(void)
{
    printf("\033[H");
}

static inline void curser_move_up(int n)
{
    printf("\033[%dA", n);
}

static inline void curser_move_down(int n)
{
    printf("\033[%dB", n);
}

static inline void curser_move_forward(int n)
{
    printf("\033[%dC", n);
}

static inline void curser_move_backward(int n)
{
    printf("\033[%dD", n);
}

static inline void curser_move_next_line(int n)
{
    printf("\033[%dE", n);
}

static inline void curser_move_previous_line(int n)
{
    printf("\033[%dF", n);
}

static inline void curser_move_horizontal(int n)
{
    printf("\033[%dG", n);
}

static inline void curser_move_horizontal_absolute(int n)
{
    printf("\033[%d`", n);
}

static inline void clear_screen_from_cursor()
{
    printf("\033[J");
}

static inline void clear_screen_to_cursor()
{
    printf("\033[1J");
}

static inline void clear_screen()
{
    printf("\033[2J");
}

static inline void clear_line_from_cursor()
{
    printf("\033[K");
}

static inline void clear_line_to_cursor()
{
    printf("\033[1K");
}

static inline void clear_line()
{
    printf("\033[2K");
}

static inline void scroll_up(int n)
{
    printf("\033[%dS", n);
}

static inline void scroll_down(int n)
{
    printf("\033[%dT", n);
}

static inline void save_curser_position()
{
    printf("\033[s");
}

static inline void restore_curser_position()
{
    printf("\033[u");
}

static inline void hide_curser()
{
    printf("\033[?25l");
}

static inline void show_curser()
{
    printf("\033[?25h");
}

static inline void set_curser_style(int style)
{
    printf("\033[%d q", style);
}

static inline void set_curser_color(int color)
{
    printf("\033[%d q", color);
}

static inline void set_curser_background_color(int color)
{
    printf("\033[%d q", color);
}

// static inline void set_curser_position(int x, int y)
// {
//     printf("\033[%d;%d q", x, y);
// }

#endif /* !_ANSI_ESCAPE_SEQUENCE_H_ */