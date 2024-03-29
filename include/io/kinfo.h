#include "gcc.h"
#include "io/stdout.h"
#include "drivers/ansi.h"
#include "config/config.h"

#ifndef _SATORI_KERNEL_INFO_H_
#define _SATORI_KERNEL_INFO_H_

#define pr_info(src, fmt, ...)          \
    {                                   \
        save_cursor_color();            \
        set_cursor_color(ANSI_GREEN);   \
        printf("[" #src "] | INFO | "); \
        printf(fmt, ##__VA_ARGS__);     \
        put_char('\n');                 \
        restore_cursor_color();         \
    }

#define pr_warn(src, fmt, ...)          \
    {                                   \
        save_cursor_color();            \
        set_cursor_color(ANSI_YELLOW);  \
        printf("[" #src "] | WARN | "); \
        printf(fmt, ##__VA_ARGS__);     \
        put_char('\n');                 \
        restore_cursor_color();         \
    }

#define pr_error(src, fmt, ...)          \
    {                                    \
        save_cursor_color();             \
        set_cursor_color(ANSI_RED);      \
        printf("[" #src "] | ERROR | "); \
        printf(fmt, ##__VA_ARGS__);      \
        put_char('\n');                  \
        restore_cursor_color();          \
        die();                           \
    }

#ifdef CONFIG_DEBUG

#define pr_debug(src, fmt, ...)          \
    {                                    \
        save_cursor_color();             \
        set_cursor_color(ANSI_BLUE);     \
        printf("[" #src "] | DEBUG | "); \
        printf(fmt, ##__VA_ARGS__);      \
        put_char('\n');                  \
        restore_cursor_color();          \
    }

#else

#define pr_debug(src, fmt, ...) \
    {                           \
    }

#endif /* !CONFIG_DEBUG */

#endif /* !_SATORI_KERNEL_INFO_H_ */