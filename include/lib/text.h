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

typedef struct text
{
    char *name;
    char *data;
    int size;
}

text_buffer *
text_buffer_create();
void text_buffer_destroy(text_buffer *buffer);

void text_buffer_insert_line(text_buffer *buffer);
void text_buffer_insert_char(text_buffer *buffer, char c);
void text_buffer_insert_string(text_buffer *buffer, char *str);

void text_buffer_new_line(text_buffer *buffer);

void text_buffer_delete_char(text_buffer *buffer);
void text_buffer_delete_line(text_buffer *buffer);

void text_buffer_move_up(text_buffer *buffer);
void text_buffer_move_down(text_buffer *buffer);
void text_buffer_move_left(text_buffer *buffer);
void text_buffer_move_right(text_buffer *buffer);

void text_buffer_move_to_line(text_buffer *buffer, int line);
void text_buffer_move_to_col(text_buffer *buffer, int col);

void text_buffer_move_to_start(text_buffer *buffer);
void text_buffer_move_to_end(text_buffer *buffer);

void text_buffer_move_to_start_of_line(text_buffer *buffer);
void text_buffer_move_to_end_of_line(text_buffer *buffer);

#endif /* !_SYSTEM_LIB_TEXT_H_ */