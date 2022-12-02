#ifndef _VIRTUAL_PROCESSOR_UNIT_H_
#define _VIRTUAL_PROCESSOR_UNIT_H_

#define GENERAL_REGISTERS 16
#define SYSCALL_REGISTERS 8
#define SEGMENT_REGISTERS 6
#define CSP_STACK_SIZE 1024

typedef struct vpu
{
    int general_registers[GENERAL_REGISTERS];
    int syscall_registers[SYSCALL_REGISTERS];
    int segment_registers[SEGMENT_REGISTERS];
    byte flags;
    void *stack_pointer;
    void *program_counter;
} vpu;

typedef struct csp_stack
{
    void *stack_pointer;
    void *stack_base;
    void *stack_top;
} csp_stack;

typedef struct csp_exec
{
    csp_cpu *cpu;
    csp_stack *stack;
} csp_exec;

#endif /* !_VIRTUAL_PROCESSOR_UNIT_H_ */