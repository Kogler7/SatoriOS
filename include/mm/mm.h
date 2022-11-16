#ifndef _MM_H_
#define _MM_H_

#define NULL            ((void *)0)
#define PAGE_SIZE        4096

#define SYSTEM_RAM      1
#define MEM_RESERVED    2
#define ACPI_TABLE      3
#define ACPI_NVS        4

#define SYS_HEAP_SIZE   0x4000000  // 64MB 

#define START_ADDR      0x90000000
#define END_ADDR        0x160000000
#define MAX_SPACE       (END_ADDR - START_ADDR)

#define MAX_ORDER       11
#define LIST_LEN        100

#include "types.h"

#ifndef __PRINTF_H__
#define __PRINTF_H__

#include "satio/printf.h"

#define mm_warn(fmt, ...) \
    printf("mm warning: " fmt, ##__VA_ARGS__)

#define mm_error(fmt, ...) \
    printf("mm error: " fmt, ##__VA_ARGS__)

#endif // __PRINTF_H__
#endif  // _MM_H_