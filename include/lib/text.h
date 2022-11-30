#ifndef _SYSTEM_LIB_TEXT_H_
#define _SYSTEM_LIB_TEXT_H_

typedef struct text_cursor
{
    int x;
    int y;
} text_cursor;

typedef struct text_char
{
    char ch;
    struct text_char *next;
    struct text_char *prev;
} text_char;

typedef struct text_line
{
    int nr_chars;
    text_char *fst_char;
    text_char *lst_char;
    struct text_line *next;
    struct text_line *prev;
} text_line;

typedef struct text_buffer
{
    int nr_lines;
    text_line *fst_line;
    text_line *lst_line;
    text_line *cur_line;
    text_char *cur_char;
    text_cursor cursor;
} text_buffer;

text_buffer *text_buffer_create();

int text_buffer_count_lines(text_buffer *buffer);
int text_buffer_count_chars(text_buffer *buffer);

void text_buffer_load(text_buffer *buffer, char *str);
void text_buffer_save(text_buffer *buffer, char *str, int size);

void text_buffer_destroy(text_buffer *buffer);

void text_buffer_write_char(text_buffer *buffer, char c);

void text_buffer_insert_line(text_buffer *buffer);
void text_buffer_insert_char(text_buffer *buffer, char c);

void text_buffer_split_line(text_buffer *buffer);
void text_buffer_merge_line(text_buffer *buffer);

static inline void text_buffer_newline(text_buffer *buffer)
{
    text_buffer_split_line(buffer);
}

void text_buffer_delete_char(text_buffer *buffer);
void text_buffer_delete_line(text_buffer *buffer);

void text_buffer_backspace(text_buffer *buffer);

void text_buffer_cursor_up(text_buffer *buffer);
void text_buffer_cursor_down(text_buffer *buffer);
void text_buffer_cursor_prev(text_buffer *buffer);
void text_buffer_cursor_next(text_buffer *buffer);

void text_buffer_cursor_move_to(text_buffer *buffer, int x, int y);
void text_buffer_cursor_to_line(text_buffer *buffer, int line);
void text_buffer_cursor_to_col(text_buffer *buffer, int col);

void text_buffer_cursor_home(text_buffer *buffer);
void text_buffer_cursor_end(text_buffer *buffer);

void text_buffer_cursor_line_home(text_buffer *buffer);
void text_buffer_cursor_line_end(text_buffer *buffer);

#endif /* !_SYSTEM_LIB_TEXT_H_ */