#include "lib/buffer.h"
#include "mm/kmalloc.h"

#define step_next(x, size) (x = (x + 1) % size)
#define step_back(x, size) (x = (x - 1 + size) % size)

std_buffer *std_buffer_create(int capacity)
{
    std_buffer *buffer = (std_buffer *)kmalloc(sizeof(std_buffer));
    buffer->capacity = capacity;
    buffer->data = (byte *)kmalloc(capacity);
    std_buffer_clear(buffer);
    return buffer;
}

void std_buffer_destroy(std_buffer *buffer)
{
    kfree(buffer->data, buffer->capacity);
    kfree(buffer, sizeof(std_buffer));
}

void std_buffer_clear(std_buffer *buffer)
{
    buffer->size = 0;
    buffer->head = 0;
    buffer->tail = 0;
    buffer->peek = 0;
}

void std_buffer_put(std_buffer *buffer, const byte data)
{
    if (std_buffer_full(buffer))
        return;
    buffer->data[buffer->tail] = data;
    step_next(buffer->tail, buffer->capacity);
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

byte std_buffer_pop(std_buffer *buffer)
{
    if (std_buffer_empty(buffer))
        return 0;
    byte data = buffer->data[buffer->tail];
    if (std_buffer_empty_p(buffer))
        step_back(buffer->peek, buffer->capacity);
    step_back(buffer->tail, buffer->capacity);
    buffer->size--;
    return data;
}

byte std_buffer_get(std_buffer *buffer)
{
    if (std_buffer_empty(buffer))
        return 0;
    byte data = buffer->data[buffer->head];
    if (std_buffer_full_p(buffer))
        step_next(buffer->peek, buffer->capacity);
    step_next(buffer->head, buffer->capacity);
    buffer->size--;
    return data;
}

int std_buffer_gets(std_buffer *buffer, char *data, int size)
{
    int i = 0;
    while (i < size)
    {
        data[i] = std_buffer_get(buffer);
        if (data[i] == '\n')
        {
            data[i] = 0;
            return i;
        }
        i++;
    }
    if (i == size)
        data[i - 1] = 0;
    return i;
}

byte std_buffer_peek(std_buffer *buffer)
{
    if (std_buffer_empty_p(buffer))
        return 0;
    byte c = buffer->data[buffer->peek];
    step_next(buffer->peek, buffer->capacity);
    return c;
}

void std_buffer_back(std_buffer *buffer)
{
    if (std_buffer_full_p(buffer))
        return;
    step_back(buffer->peek, buffer->capacity);
}

char std_buffer_wait_char(std_buffer *buffer)
{
    while (std_buffer_empty(buffer))
        asm volatile("nop");
    return std_buffer_get(buffer);
}

// 从缓冲区中获取一行，以换行符结束，换行符被替换为0，若缓冲区为空，则等待
int std_buffer_wait_line(std_buffer *buffer, char *data, int size)
{
    int i = 0;
    while (i < size)
    {
        while (std_buffer_empty_p(buffer))
        {
            asm volatile("nop");
        }
        if (std_buffer_peek(buffer) == '\n')
            break;
        i++;
    }
    return std_buffer_gets(buffer, data, size);
}