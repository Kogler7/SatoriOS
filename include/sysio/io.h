#pragma once
#ifndef __ECHO_OS_io_h_
#define __ECHO_OS_io_h_

void putc(char c);
void puts(char *str);
void printf(char *fmt, ...);
char getc();
void gets(char *str, int len);
void newline();

#endif
