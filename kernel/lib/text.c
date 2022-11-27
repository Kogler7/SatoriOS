#include "lib/text.h"

#define nullptr 0

#define malloc(size) kmalloc(size)
#define free(ptr, size) kfree(ptr, size)

#define new(type) (type *)malloc(sizeof(type))
#define del(obj, type) free(obj, sizeof(type))

#define is_isolated(obj) (obj->prev == nullptr && obj->next == nullptr)
#define is_reserved(obj) (obj->prev == nullptr)
#define is_the_last(obj) (obj->next == nullptr)
#define is_the_first(obj) (is_reserved(obj->prev))

static inline text_char *create_isolate_char()
{
    text_char *new_char = new(text_char);
    new_char->ch = 0;
    new_char->next = nullptr;
    new_char->prev = nullptr;
    return new_char;
}

static inline text_line *create_isolate_line()
{
    text_line *new_line = new (text_line);
    new_line->nr_chars = 0;
    new_line->prev = nullptr;
    new_line->next = nullptr;
    new_line->fst_char = create_isolate_char();
    new_line->lst_char = new_line->fst_char;
    return new_line;
}

text_buffer *text_buffer_create();
{
    text_buffer *new_buffer = new (text_buffer);
    new_buffer->nr_lines = 0;
    text_line *new_line = create_isolate_line();
    new_buffer->fst_line = new_line;
    new_buffer->lst_line = new_line;
    new_buffer->cur_line = new_line;
    new_buffer->cur_char = new_line->fst_char;
    new_buffer->cursor.x = 0;
    new_buffer->cursor.y = 0;
    return new_buffer;
}

void text_buffer_destroy(text_buffer *buffer)
{
    text_line *line = buffer->fst_line;
    while (line != nullptr)
    {
        text_line *next = line->next;
        text_char *ch = line->fst_char;
        while (ch != nullptr)
        {
            text_char *next_ch = ch->next;
            del(ch, text_char);
            ch = next_ch;
        }
        del(line, text_line);
        line = next;
    }
    del(buffer, text_buffer);
}

void text_buffer_insert_line(text_buffer *buffer)
{
    text_line *cur_line = buffer->cur_line;
    text_line *new_line = create_isolate_line();
    if (is_isolated(cur_line))
    {
        buffer->lst_line = new_line;
        buffer->cur_line = new_line;
        buffer->cur_char = new_line->fst_char;
        buffer->nr_lines = 1;
        buffer->cursor.y = 1;
        return;
    }
    new_line->prev = cur_line;
    if (is_the_last(cur_line))
    {
        cur_line->next = new_line;
        buffer->lst_line = new_line;
    }
    else
    {
        new_line->next = cur_line->next;
        cur_line->next->prev = new_line;
        cur_line->next = new_line;
    }
    buffer->cur_line = new_line;
    buffer->cur_char = new_line->fst_char;
    buffer->nr_lines++;
    buffer->cursor.x = 0;
    buffer->cursor.y++;
}

void text_buffer_insert_char(text_buffer *buffer, char c)
{
    text_line *cur_line = buffer->cur_line;
    if (is_reserved(cur_line))
    {
        text_line *new_line = create_isolate_line();
        new_line->nr_chars = 1;
        new_line->lst_char = create_isolate_char();
        new_line->fst_char->next = new_line->lst_char;
        new_line->lst_char->prev = new_line->fst_char;
        new_line->next = nullptr;
        new_line->prev = cur_line;
        cur_line->next = new_line;
        buffer->fst_line = new_line;
        buffer->lst_line = new_line;
        buffer->cur_line = new_line;
        buffer->cur_char = new_line->fst_char;
        buffer->nr_lines = 1;
        buffer->cursor.x = 1;
        buffer->cursor.y = 1;
        return;
    }
    if (buffer->cur_char == nullptr)
    {
        text_char *ch = (text_char *)malloc(sizeof(text_char));
        ch->ch = c;
        ch->next = nullptr;
        ch->prev = buffer->cur_line->lst_char;
        buffer->cur_line->lst_char->next = ch;
        buffer->cur_line->lst_char = ch;
        buffer->cur_char = ch;
        buffer->cur_line->nr_chars++;
        buffer->cursor.x++;
        return;
    }
    text_char *ch = (text_char *)malloc(sizeof(text_char));
    ch->ch = c;
    ch->prev = buffer->cur_char;
    if (buffer->cur_char->next == nullptr)
    {
        ch->next = nullptr;
        buffer->cur_char->next = ch;
        buffer->cur_line->lst_char = ch;
    }
    else
    {
        ch->next = buffer->cur_char->next;
        buffer->cur_char->next->prev = ch;
        buffer->cur_char->next = ch;
    }
    buffer->cur_line->nr_chars++;
    buffer->cur_char = ch;
    buffer->cursor.x++;
}

void text_buffer_insert_string(text_buffer *buffer, char *str)
{
    while (*str != '\0')
    {
        if (*str == '\n')
        {
            text_buffer_insert_line(buffer);
        }
        else
        {
            text_buffer_insert_char(buffer, *str);
        }
        str++;
    }
}

void text_buffer_new_line(text_buffer *buffer)
{
    text_line *line = buffer->cur_line;
    text_char *ch = buffer->cur_char;
    text_buffer_insert_line(buffer);
    if (line == nullptr || ch == nullptr)
    {
        return;
    }
    line->lst_char = ch;
    buffer->cur_char = ch->next;
    buffer->cur_line->fst_char = ch->next;
    if (ch->next != nullptr)
    {
        ch->next->prev = nullptr;
        ch->next = nullptr;
        buffer->cursor->x = 1;
    }
    int nr_chars = 0;
    ch = buffer->cur_char;
    while (ch != nullptr)
    {
        nr_chars++;
        ch = ch->next;
    }
    buffer->cur_line->nr_chars = nr_chars;
    line->nr_chars -= nr_chars;
}

void text_buffer_delete_char(text_buffer *buffer)
{
    if (buffer->cur_line == nullptr)
    {
        return;
    }
    if (buffer->cur_char == nullptr)
    {
        if (buffer->cur_line->prev == nullptr)
        {
            return;
        }
        text_line *line = buffer->cur_line;
        buffer->cur_line = line->prev;
        buffer->cur_line->next = line->next;
        if (line->next != nullptr)
        {
            line->next->prev = buffer->cur_line;
        }
        else
        {
            buffer->lst_line = buffer->cur_line;
        }
        buffer->cur_char = buffer->cur_line->lst_char;
        buffer->cur_line->nr_chars += line->nr_chars;
        buffer->nr_lines--;
        buffer->cursor.y--;
        free(line, sizeof(text_line));
        return;
    }
    text_char *ch = buffer->cur_char;
    if (ch->prev == nullptr)
    {
        buffer->cur_line->fst_char = ch->next;
    }
    else
    {
        ch->prev->next = ch->next;
    }
    if (ch->next == nullptr)
    {
        buffer->cur_line->lst_char = ch->prev;
    }
    else
    {
        ch->next->prev = ch->prev;
    }
    buffer->cur_char = ch->prev;
    buffer->cur_line->nr_chars--;
    free(ch, sizeof(text_char));
}

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
