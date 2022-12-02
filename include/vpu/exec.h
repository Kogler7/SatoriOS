#include "types.h"

#ifndef _VPU_EXECUTOR_H_
#define _VPU_EXECUTOR_H_



extern void *syscall_table[256];

int syscall(int syscall_number);

int execute(void *code, void *data, void *stack, void *heap, void *heap_end);

#endif /* !_VPU_EXECUTOR_H_ */