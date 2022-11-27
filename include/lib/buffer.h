#include "types.h"

#ifndef _SATORI_STD_BUFFER_H_
#define _SATORI_STD_BUFFER_H_

typedef struct std_buffer {
    byte *data;
    int size;
    int capacity;
    int head;
    int tail;
    int peek;
} std_buffer;

std_buffer *std_buffer_create(int capacity);
void std_buffer_destroy(std_buffer *buffer);
void std_buffer_clear(std_buffer *buffer);

void std_buffer_put(std_buffer *buffer, const byte data);
void std_buffer_puts(std_buffer *buffer, const char *data);

byte std_buffer_pop(std_buffer *buffer);
byte std_buffer_get(std_buffer *buffer);

int std_buffer_gets(std_buffer *buffer, char *data, int size);

byte std_buffer_peek(std_buffer *buffer);
void std_buffer_back(std_buffer *buffer);

int std_buffer_wait_line(std_buffer *buffer, char *data, int size);

inline int std_buffer_full(std_buffer *buffer);
inline int std_buffer_full_p(std_buffer *buffer);
inline int std_buffer_empty(std_buffer *buffer);
inline int std_buffer_empty_p(std_buffer *buffer);

#endif /* !_SATORI_STD_BUFFER_H_ */