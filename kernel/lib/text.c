#include "lib/text.h"

#define nullptr 0

#define malloc(size) kmalloc(size)
#define free(ptr, size) kfree(ptr, size)

#define new(type) (type *)malloc(sizeof(type))
#define del(obj, type) free(obj, sizeof(type))

#define is_isolated(obj) (obj->prev == nullptr && obj->next == nullptr)
#define is_reserved(obj) (obj->prev == nullptr)
#define is_the_last(obj) (obj->next == nullptr)

static inline text_char *create_isolate_char()
{
    // 创建一个孤立的字符
    text_char *new_char = new (text_char);
    new_char->ch = 0;
    new_char->next = nullptr;
    new_char->prev = nullptr;
    return new_char;
}

static inline text_line *create_isolate_line()
{
    // 创建一个孤立的行
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
    // 创建一个文本缓冲区
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

int text_buffer_count_lines(text_buffer *buffer)
{
    // 计算文本缓冲区中的行数
    return buffer->nr_lines;
}

int text_buffer_count_chars(text_buffer *buffer)
{
    // 计算文本缓冲区中的字符数
    int nr_chars = 0;
    text_line *line = buffer->fst_line;
    while (line != nullptr)
    {
        nr_chars += line->nr_chars;
        line = line->next;
    }
    return nr_chars;
}

void text_buffer_load(text_buffer *buffer, char *str)
{
    // 从字符串中加载文本缓冲区
    while (*str != '\0')
    {
        if (*str == '\n')
        {
            text_buffer_new_line(buffer);
        }
        else
        {
            text_buffer_insert_char(buffer, *str);
        }
        str++;
    }
}

char *text_buffer_save(text_buffer *buffer)
{
    // 保存文本缓冲区到字符串
    int nr_lines = text_buffer_count_lines(buffer);
    int nr_chars = text_buffer_count_chars(buffer);
    char *str = (char *)malloc(nr_chars + nr_lines + 1); // +1 for '\0'
    char *ptr = str;
    text_line *line = buffer->fst_line->next;
    while (line != nullptr)
    {
        text_char *chr = line->fst_char->next;
        while (chr != nullptr)
        {
            *ptr = chr->ch;
            ptr++;
            chr = chr->next;
        }
        *ptr = '\n';
        ptr++;
        line = line->next;
    }
    *ptr = '\0';
    return str;
}

void text_buffer_destroy(text_buffer *buffer)
{
    // 销毁文本缓冲区
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

void text_buffer_write_char(text_buffer *buffer, char c)
{
    // 在光标位置写入字符，光标位置后移
    if (is_reserved(buffer->cur_char))
    {
        text_buffer_insert_char(buffer, c);
    }
    buffer->cur_char->ch = c;
    text_buffer_cursor_next(buffer);
}

void text_buffer_insert_line(text_buffer *buffer)
{
    // 在当前行之后插入新行
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
    // 在光标位置插入字符（所在字符后面）
    text_line *cur_line = buffer->cur_line;
    if (is_reserved(cur_line))
    {
        text_buffer_insert_line(buffer);
        cur_line = buffer->cur_line;
    }
    text_char *new_char = create_isolate_char();
    new_char->ch = c;
    if (is_the_last(buffer->cur_char))
    {
        buffer->cur_char->next = new_char;
        cur_line->lst_char = new_char;
    }
    else
    {
        new_char->next = buffer->cur_char->next;
        buffer->cur_char->next->prev = new_char;
        buffer->cur_char->next = new_char;
    }
    new_char->prev = buffer->cur_char;
    buffer->cur_char = new_char;
    cur_line->nr_chars++;
    buffer->cursor.x++;
}

void text_buffer_split_line(text_buffer *buffer)
{
    // 在光标位置拆分当前行，光标位置之后的字符将被移到新行
    text_line *pre_line = buffer->cur_line;
    text_char *pre_char = buffer->cur_char;
    text_buffer_insert_line(buffer);
    if (is_the_last(pre_line) || is_the_last(pre_char))
    {
        return;
    }
    buffer->cur_line->lst_char = pre_line->lst_char;
    pre_line->lst_char = pre_char;
    text_char *nl_fst_char = pre_char->next;
    buffer->cur_char->next = nl_fst_char;
    nl_fst_char->prev = buffer->cur_char;
    pre_char->next = nullptr;
    while (nl_fst_char != nullptr)
    {
        buffer->cur_line->nr_chars++;
        nl_fst_char = nl_fst_char->next;
    }
    pre_line->nr_chars -= buffer->cur_line->nr_chars;
}

void text_buffer_merge_line(text_buffer *buffer)
{
    // 将所在行的下一行内容合并到所在行，并删除下一行，光标跳转到合并位置
    if (is_the_last(buffer->cur_line))
    {
        return;
    }
    text_line *cur_line = buffer->cur_line;
    text_line *next_line = cur_line->next;
    text_char *cur_char = buffer->cur_char;
    if (is_the_last(cur_char))
    {
        cur_char->next = next_line->fst_char->next;
        next_line->fst_char->next->prev = cur_char;
    }
    else
    {
        cur_char->next->prev = next_line->lst_char;
        next_line->lst_char->next = cur_char->next;
        cur_char->next = next_line->fst_char->next;
        next_line->fst_char->next->prev = cur_char;
    }
    cur_line->nr_chars += next_line->nr_chars;
    buffer->cur_line = next_line;
    text_buffer_delete_line(buffer);
}

void text_buffer_delete_char(text_buffer *buffer)
{
    text_line *cur_line = buffer->cur_line;
    text_char *cur_char = buffer->cur_char;
    if (is_isolated(cur_line))
    {
        return;
    }
    if (is_isolated(cur_char))
    {
        if (!is_the_last(cur_line))
        {
            text_buffer_delete_line(buffer);
        }
        return;
    }
    if (is_the_last(cur_char))
    {
        text_buffer_merge_line(buffer);
    }
    else
    {
        text_char *del_char = cur_char->next;
        if (is_the_last(del_char))
        {
            cur_char->next = nullptr;
            cur_line->lst_char = cur_char;
        }
        else
        {
            cur_char->next = del_char->next;
            del_char->next->prev = cur_char;
        }
        del(del_char, text_char);
        cur_line->nr_chars--;
    }
}

void text_buffer_delete_line(text_buffer *buffer)
{
    // 删除当前行，光标跳转到上一行末尾
    text_line *cur_line = buffer->cur_line;
    if (is_isolated(cur_line))
    {
        return;
    }
    if (is_the_last(cur_line))
    {
        buffer->lst_line = cur_line->prev;
        buffer->lst_line->next = nullptr;
        buffer->cur_line = buffer->lst_line;
        buffer->cur_char = buffer->lst_line->lst_char;
        buffer->cursor.y--;
        buffer->cursor.x = buffer->cur_line->nr_chars;
    }
    else
    {
        cur_line->next->prev = cur_line->prev;
        cur_line->prev->next = cur_line->next;
        buffer->cur_line = cur_line->next;
        buffer->cur_char = cur_line->next->fst_char;
        buffer->cursor.x = 0;
    }
    del(cur_line, text_line);
    buffer->nr_lines--;
}

void text_buffer_backspace(text_buffer *buffer)
{
    // 删除光标前的字符
    text_line *cur_line = buffer->cur_line;
    text_char *cur_char = buffer->cur_char;
    if (is_isolated(cur_line))
    {
        return;
    }
    if (is_isolated(cur_char))
    {
        if (!is_reserved(cur_line))
        {
            buffer->cur_line = cur_line->prev;
            buffer->cur_char = cur_line->prev->lst_char;
            text_buffer_merge_line(buffer);
        }
        return;
    }
    if (is_reserved(cur_char))
    {
        text_buffer_delete_line(buffer);
    }
    else
    {
        text_char *del_char = cur_char;
        if (is_the_last(del_char))
        {
            cur_line->lst_char = cur_char->prev;
            cur_char->prev->next = nullptr;
        }
        else
        {
            cur_char->prev->next = cur_char->next;
            cur_char->next->prev = cur_char->prev;
        }
        del(del_char, text_char);
        cur_line->nr_chars--;
        buffer->cursor.x--;
    }
}

void text_buffer_cursor_up(text_buffer *buffer)
{
    // 光标上移
    if (buffer->cursor.y == 0)
    {
        return;
    }
    buffer->cursor.y--;
    if (buffer->cursor.x > buffer->cur_line->prev->nr_chars)
    {
        buffer->cursor.x = buffer->cur_line->prev->nr_chars;
    }
    buffer->cur_line = buffer->cur_line->prev;
    buffer->cur_char = buffer->cur_line->fst_char;
    for (int i = 0; i < buffer->cursor.x; i++)
    {
        buffer->cur_char = buffer->cur_char->next;
    }
}

void text_buffer_cursor_down(text_buffer *buffer)
{
    // 光标下移
    if (buffer->cursor.y == buffer->nr_lines)
    {
        return;
    }
    buffer->cursor.y++;
    if (buffer->cursor.x > buffer->cur_line->next->nr_chars)
    {
        buffer->cursor.x = buffer->cur_line->next->nr_chars;
    }
    buffer->cur_line = buffer->cur_line->next;
    buffer->cur_char = buffer->cur_line->fst_char;
    for (int i = 0; i < buffer->cursor.x; i++)
    {
        buffer->cur_char = buffer->cur_char->next;
    }
}

void text_buffer_cursor_prev(text_buffer *buffer)
{
    // 光标前移，如果是行首则跳转到上一行末尾
    if (buffer->cursor.x == 0)
    {
        if (buffer->cursor.y == 0)
        {
            return;
        }
        buffer->cursor.y--;
        buffer->cursor.x = buffer->cur_line->prev->nr_chars;
        buffer->cur_line = buffer->cur_line->prev;
        buffer->cur_char = buffer->cur_line->lst_char;
    }
    else
    {
        buffer->cursor.x--;
        buffer->cur_char = buffer->cur_char->prev;
    }
}

void text_buffer_cursor_next(text_buffer *buffer)
{
    // 光标后移，如果是行尾则跳转到下一行首
    if (buffer->cursor.x == buffer->cur_line->nr_chars)
    {
        if (buffer->cursor.y == buffer->nr_lines)
        {
            return;
        }
        buffer->cursor.y++;
        buffer->cursor.x = 0;
        buffer->cur_line = buffer->cur_line->next;
        buffer->cur_char = buffer->cur_line->fst_char;
    }
    else
    {
        buffer->cursor.x++;
        buffer->cur_char = buffer->cur_char->next;
    }
}

void text_buffer_cursor_move_to(text_buffer *buffer, int x, int y)
{
    // 光标移动到指定位置
    if (x < 0 || x > buffer->cur_line->nr_chars || y < 0 || y > buffer->nr_lines)
    {
        return;
    }
    buffer->cursor.x = x;
    buffer->cursor.y = y;
    buffer->cur_line = buffer->fst_line;
    buffer->cur_char = buffer->fst_line->fst_char;
    for (int i = 0; i < y; i++)
    {
        buffer->cur_line = buffer->cur_line->next;
    }
    for (int i = 0; i < x; i++)
    {
        buffer->cur_char = buffer->cur_char->next;
    }
}

void text_buffer_cursor_to_line(text_buffer *buffer, int line)
{
    // 光标移动到指定行
    if (line < 0 || line > buffer->nr_lines)
    {
        return;
    }
    buffer->cursor.y = line;
    buffer->cur_line = buffer->fst_line;
    buffer->cur_char = buffer->fst_line->fst_char;
    for (int i = 0; i < line; i++)
    {
        buffer->cur_line = buffer->cur_line->next;
    }
    if (buffer->cursor.x > buffer->cur_line->nr_chars)
    {
        buffer->cursor.x = buffer->cur_line->nr_chars;
    }
    for (int i = 0; i < buffer->cursor.x; i++)
    {
        buffer->cur_char = buffer->cur_char->next;
    }
}

void text_buffer_cursor_to_col(text_buffer *buffer, int col)
{
    // 光标移动到指定列
    if (col < 0 || col > buffer->cur_line->nr_chars)
    {
        return;
    }
    buffer->cursor.x = col;
    buffer->cur_char = buffer->cur_line->fst_char;
    for (int i = 0; i < col; i++)
    {
        buffer->cur_char = buffer->cur_char->next;
    }
}

void text_buffer_cursor_home(text_buffer *buffer)
{
    // 光标移动到首行首列
    buffer->cur_line = buffer->fst_line;
    buffer->cur_char = buffer->cur_line->fst_char;
    buffer->cursor.x = 0;
    buffer->cursor.y = 0;
}

void text_buffer_cursor_end(text_buffer *buffer)
{
    // 光标移动到末行末列
    buffer->cur_line = buffer->lst_line;
    buffer->cur_char = buffer->cur_line->lst_char;
    buffer->cursor.x = buffer->cur_line->nr_chars;
    buffer->cursor.y = buffer->nr_lines;
}

void text_buffer_cursor_line_home(text_buffer *buffer)
{
    // 光标移动到当前行首
    buffer->cur_char = buffer->cur_line->fst_char;
    buffer->cursor.x = 0;
}

void text_buffer_cursor_line_end(text_buffer *buffer)
{
    // 光标移动到当前行末
    buffer->cur_char = buffer->cur_line->lst_char;
    buffer->cursor.x = buffer->cur_line->nr_chars;
}
