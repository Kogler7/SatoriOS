#include "types.h"

#ifndef _VPU_EXECUTOR_H_
#define _VPU_EXECUTOR_H_

typedef struct exec_header
{
    u32 magic;
    u32 version;
    u32 entry;
    u32 flags;
    u32 reserved[4];
} exec_header_t;

typedef struct exec_file
{
    exec_header_t header;
    void *text;
    void *data;
    void *bss;
} exec_file_t;

extern void *syscall_table[256];

int syscall(int syscall_number);

int execute(void *code, void *data, void *stack, void *heap, void *heap_end);

#endif /* !_VPU_EXECUTOR_H_ */