#include "vpu/vpu.h"

#ifndef _PROCESS_CONTROL_BLOCK_H_
#define _PROCESS_CONTROL_BLOCK_H_

typedef struct pcb {
    vpu vpu;
    int pid;
    int ppid;
    int prior;
    int state;
    void *stack;
    void *heap;
    void *heap_end;
    void *code;
    void *data;
} pcb;

#endif /* !_PROCESS_CONTROL_BLOCK_H_ */