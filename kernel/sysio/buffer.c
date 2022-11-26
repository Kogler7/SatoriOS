#include "io/buffer.h"

std_buffer *std_buffer_create(int capacity)
{
    std_buffer *buffer = (std_buffer *)kmalloc(sizeof(std_buffer));
    buffer->capacity = capacity;
    buffer->data = (char *)kmalloc(capacity);
    buffer->size = 0;
    return buffer;
}

void std_buffer_destroy(std_buffer *buffer)
{
    kfree(buffer->data);
    kfree(buffer);
}

void std_buffer_clear(std_buffer *buffer)
{
    buffer->size = 0;
    buffer->head = buffer->data;
    buffer->tail = buffer->data;
}

void std_buffer_put(std_buffer *buffer, const byte data)
{
    if (buffer->size == buffer->capacity)
        return;
    *(buffer->tail) = data;
    buffer->tail = (buffer->tail + 1) % buffer->capacity;
    buffer->size++;
}

void std_buffer_puts(std_buffer *buffer, const char *data)
{
    while (*data != 0)
    {
        std_buffer_put(buffer, *data);
        data++;
    }
}

byte std_buffer_get(std_buffer *buffer)
{
    if (buffer->size == 0)
        return 0;
    byte data = *(buffer->head);
    buffer->head = (buffer->head + 1) % buffer->capacity;
    buffer->size--;
    return data;
}

void std_buffer_gets(std_buffer *buffer, char *data, int size)
{
    int i = 0;
    while (i < size)
    {
        data[i] = std_buffer_get(buffer);
        if (data[i] == 0)
            break;
        i++;
    }
}

byte std_buffer_peek(std_buffer *buffer)
{
    if (buffer->size == 0)
        return 0;
    return *(buffer->head);
}

// 从缓冲区中获取一行，以换行符结束，换行符被替换为0，若缓冲区为空，则等待
void std_buffer_wait_line(std_buffer *buffer, char *data)
{
    int i = 0;
    while (1)
    {
        while (std_buffer_empty(buffer))
        {
            asm volatile("nop");
        }
        data[i] = std_buffer_get(buffer);
        if (data[i] == '\n')
            break;
        i++;
    }
}

int std_buffer_full(std_buffer *buffer)
{
    return buffer->size == buffer->capacity;
}

int std_buffer_empty(std_buffer *buffer)
{
    return buffer->size == 0;
}
