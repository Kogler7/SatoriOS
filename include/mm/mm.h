#include "types.h"
#include "lib/string.h"

#ifndef _MM_H_
#define _MM_H_

#define _SATORI_DEBUG_

#define NULL ((void *)0)
#define PAGE_SIZE 4096

#define SYSTEM_RAM 1
#define MEM_RESERVED 2
#define ACPI_TABLE 3
#define ACPI_NVS 4

#define SYS_HEAP_SIZE 0x4000000 // 64MB

#define USER_START_ADDR 0x90000000
#define KMEM_START_ADDR 0xD0000000

#define MAX_ORDER 18 // 2^19 = 512 Pages = 2GB

#ifndef __PRINTF_H__
#define __PRINTF_H__

#include "io/kinfo.h"

#endif // __PRINTF_H__

#define mm_info(fmt, ...) pr_info(MM, fmt, ##__VA_ARGS__)

#define mm_warn(fmt, ...) pr_warn(MM, fmt, ##__VA_ARGS__)

#define mm_error(fmt, ...) pr_error(MM, fmt, ##__VA_ARGS__)

#ifdef _SATORI_DEBUG_
#define mm_debug(fmt, ...) pr_debug(MM, fmt, ##__VA_ARGS__)

#else
#define mm_debug(fmt, ...)

#endif /* !_SATORI_DEBUG_ */

void mem_init();

void set_dead_beef(void *addr);
int check_dead_beef(void *addr);

#endif /* !_MM_H_ */