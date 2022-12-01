#include "drivers/rtx.h"
#include "mm/kmalloc.h"

#define malloc(size) kmalloc(size)
#define free(ptr, size) kfree(ptr, size)

#define new(type) (type *)malloc(sizeof(type))
#define del(obj, type) free(obj, sizeof(type))

char _rtx_buffer[RTX_BUFFER_LINES][RTX_MAX_WIDTH] = {0};

void rtx_init()
{
    clear_screen();
}

rtx_buffer *rtx_create_buffer(rtx_align align)
{
    rtx_buffer *buffer = new (rtx_buffer);
    if (hit_align(align, rtx_align_exp))
    {
        buffer->width = RTX_MAX_WIDTH;
        buffer->height = RTX_MAX_HEIGHT;
    }
    else
    {
        if (hit_align(align, rtx_align_mid))
            buffer->width = RTX_MAX_WIDTH;
        else
            buffer->width = RTX_MAX_WIDTH / 2;
        if (hit_align(align, rtx_align_ctr))
            buffer->height = RTX_MAX_HEIGHT - 2;
        else
            buffer->height = 1;
    }
    buffer->active = false;
    buffer->cursor_x = 0;
    buffer->cursor_y = 0;
    int buffer_size = buffer->width * buffer->height;
    // buffer->buffer = (char **)malloc(buffer_size * sizeof(char));
    return buffer;
}

void rtx_destroy_buffer(rtx_buffer *buffer)
{
    int buffer_size = buffer->width * buffer->height;
    // free(buffer->buffer, buffer_size * sizeof(char));
    del(buffer, rtx_buffer);
}

void rtx_render_buffer(rtx_buffer *buffer)
{
    if (buffer->active)
    {
        int buffer_size = buffer->width * buffer->height;
        for (int i = 0; i < buffer_size; i++)
        {
            int x = i % buffer->width;
            int y = i / buffer->width;
            char ch = _rtx_buffer[y][x];
            if (ch == 0)
                ch = ' ';
            // print_char(ch, x, y);
        }
    }
}

void rtx_render_all()
{
    cursor_reset();
    char ch;
    for (int i = 0; i < RTX_MAX_HEIGHT; i++)
    {
        for (int j = 0; j < RTX_MAX_WIDTH; j++)
        {
            ch = _rtx_buffer[i][j];
            if (ch == 0) break;
            putc(ch);
        }
    }
}
