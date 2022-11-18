#ifndef _MM_H_
#define _MM_H_

#define __SATORI_DEBUG_

#define NULL            ((void *)0)
#define PAGE_SIZE        4096

#define SYSTEM_RAM      1
#define MEM_RESERVED    2
#define ACPI_TABLE      3
#define ACPI_NVS        4

#define SYS_HEAP_SIZE   0x4000000  // 64MB 

#define USER_START_ADDR 0x90000000
#define KMEM_START_ADDR 0xD0000000

#define MAX_ORDER       18  // 2^19 = 512 Pages = 2GB

#include "types.h"
#include "utils.h"

#ifndef __PRINTF_H__
#define __PRINTF_H__

#include "satio/printf.h"

#define mm_info(fmt, ...) \
    printf("[MM] | INFO | ");    \
    printf(fmt, ##__VA_ARGS__);  \
    printf("\n");

#define mm_warn(fmt, ...) \
    printf("[MM] | WARN | ");   \
    printf(fmt, ##__VA_ARGS__); \
    printf("\n");

#define mm_error(fmt, ...) \
    printf("[MM] | ERROR | ");  \
    printf(fmt, ##__VA_ARGS__); \
    printf("\n");

#ifdef __SATORI_DEBUG_
#define mm_debug(fmt, ...) \
    printf("[MM] | DEBUG | ");  \
    printf(fmt, ##__VA_ARGS__); \
    printf("\n");

#else
#define mm_debug(fmt, ...)

#endif // __SATORI_DEBUG_

#endif // __PRINTF_H__

void mem_init();


#endif  // _MM_H_