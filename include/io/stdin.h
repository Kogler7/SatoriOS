#include "io/buffer.h"
#include "drivers/kbd.h"

#ifndef _SATORI_STD_IN_H_
#define _SATORI_STD_IN_H_

#define STDIN_BUFFER_SIZE 256

extern std_buffer *stdin_buffer;

void stdin_init();

void stdin_kbd_cbk(char c, int state);

void stdin_clear();

void stdin_enable();
void stdin_disable();

char getc();
int gets(char *str, int size);

int scanf(const char *format, ...);

#endif /* !_SATORI_STD_IN_H_ */