#include "types.h"

#ifndef _MM_TYPES_H_
#define _MM_TYPES_H_

#define CONFIG_PHYS_ADDR_T_64BIT //一般定义在config中，这里为了方便直接定义

#ifdef CONFIG_PHYS_ADDR_T_64BIT
typedef u64 phys_addr_t;
#else
typedef u32 phys_addr_t;
#endif

#define MAX_PHYSMEM_BITS 40

#endif /* !_MM_TYPES_H_ */