#include "drivers/ansi.h"
#include "types.h"

#ifndef _RICH_TEXT_GRAPHICS_H_
#define _RICH_TEXT_GRAPHICS_H_

#define RTX_MAX_WIDTH 80
#define RTX_MAX_HEIGHT 25

#define RTX_BUFFER_LINES 100

#define hit_test(x, y, buffer)                                        \
    (x >= buffer->offset_x && x < buffer->offset_x + buffer->width && \
     y >= buffer->offset_y && y < buffer->offset_y + buffer->height)

#define hit_align(cur_align, tgt_align) (cur_align & tgt_align)

typedef enum rtx_align
{
    rtx_align_lft = 1 << 0, // left
    rtx_align_mid = 1 << 1, // middle (full width)
    rtx_align_rgt = 1 << 2, // right
    rtx_align_top = 1 << 3, // top
    rtx_align_ctr = 1 << 4, // center (vertical)
    rtx_align_btm = 1 << 5, // bottom
    rtx_align_exp = 1 << 6, // expand (full width and height)
} rtx_align;

typedef struct rtx_char
{
    char ch;
    sint color;
    sint style;
} rtx_char;

typedef struct rtx_line
{
    rtx_char *line;
    sint width;
    bool blank;
    struct rtx_line *next;
    struct rtx_line *prev;
} rtx_line;

typedef struct rtx_buffer
{
    sint prior;
    sint width;
    sint height;
    bool active;
    sint cursor_x;
    sint cursor_y;
    rtx_align align;
    rtx_line *buf_line; // buffer line
    rtx_line *pre_line; // previous line
    rtx_line *cur_line; // current line
    rtx_line *exs_line; // excessive line
} rtx_buffer;

void rtx_init();

rtx_buffer *rtx_create_buffer(rtx_align align);
void rtx_destroy_buffer(rtx_buffer *buffer);

void rtx_clear_buffer(rtx_buffer *buffer);
void rtx_clear_line(rtx_buffer *buffer, int line);
void rtx_clear_char(rtx_buffer *buffer, int x, int y);

void rtx_set_char(rtx_buffer *buffer, int x, int y, char c);
void rtx_set_string(rtx_buffer *buffer, int x, int y, char *str);

void rtx_append_char(rtx_buffer *buffer, char c);
void rtx_append_string(rtx_buffer *buffer, char *str);

void rtx_set_active(rtx_buffer *buffer);
void rtx_set_inactive(rtx_buffer *buffer);

void rtx_render_buffer(rtx_buffer *buffer);
void rtx_render_back(rtx_buffer *buffer);
void rtx_render_line(rtx_buffer *buffer, int line);

void rtx_set_cursor(rtx_buffer *buffer, int x, int y);
void rtx_move_cursor(rtx_buffer *buffer, int x, int y);
void rtx_hide_cursor(rtx_buffer *buffer);
void rtx_show_cursor(rtx_buffer *buffer);

void rtx_set_cursor_style(rtx_buffer *buffer, int style);
void rtx_save_cursor_style(rtx_buffer *buffer);
void rtx_restore_cursor_style(rtx_buffer *buffer);

void rtx_set_cursor_color(rtx_buffer *buffer, int color);
void rtx_save_cursor_color(rtx_buffer *buffer);
void rtx_restore_cursor_color(rtx_buffer *buffer);

void rtx_roll_up(rtx_buffer *buffer, int lines);
void rtx_roll_down(rtx_buffer *buffer, int lines);

// void rtx_set_tab(rtx_buffer *buffer, int x);
// void rtx_show_tabs(rtx_buffer *buffer);
// void rtx_hide_tabs(rtx_buffer *buffer);


#endif /* !_RICH_TEXT_GRAPHICS_H_ */