#include "io/stdout.h"
#include "io/ansi.h"

#ifndef _SATORI_KERNEL_INFO_H_
#define _SATORI_KERNEL_INFO_H_

#define pr_info(src, fmt, ...)       \
    {                                \
        save_cursor_color();         \
        set_color(ANSI_COLOR_GREEN); \
        printf("[#src] | INFO | ");  \
        printf(fmt, ##__VA_ARGS__);  \
        printf("\n");                \
        restore_cursor_color();      \
    }

#define pr_warn(src, fmt, ...)        \
    {                                 \
        save_cursor_color();          \
        set_color(ANSI_COLOR_YELLOW); \
        printf("[#src] | WARN | ");   \
        printf(fmt, ##__VA_ARGS__);   \
        printf("\n");                 \
        restore_cursor_color();       \
    }

#define pr_error(src, fmt, ...)      \
    {                                \
        save_cursor_color();         \
        set_color(ANSI_COLOR_RED);   \
        printf("[#src] | ERROR | "); \
        printf(fmt, ##__VA_ARGS__);  \
        printf("\n");                \
        restore_cursor_color();      \
    }

#define pr_debug(src, fmt, ...)      \
    {                                \
        save_cursor_color();         \
        set_color(ANSI_COLOR_BLUE);  \
        printf("[#src] | DEBUG | "); \
        printf(fmt, ##__VA_ARGS__);  \
        printf("\n");                \
        restore_cursor_color();      \
    }

#endif /* !_SATORI_KERNEL_INFO_H_ */