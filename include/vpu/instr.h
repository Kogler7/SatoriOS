#include "types.h"

#ifndef _VPU_INSTRUCTIONS_H_
#define _VPU_INSTRUCTIONS_H_

typedef enum vpu_opcode
{
    // Arithmetic
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    INC,
    DEC,
    // Bitwise
    AND,
    OR,
    XOR,
    NOT,
    SHL,
    SHR,
    // Logical
    CMP,
    TEST,
    // Control
    JMP,
    JZ,
    JNZ,
    JG,
    JGE,
    JL,
    JLE,
    CALL,
    RET,
    LOOP,
    // Stack
    PUSH,
    POP,
    // Memory
    MOV,
    LEA,
    // System
    SYSCALL,
    // Misc
    NOP,
    HALT
} vpu_opcode_t;

typedef enum vpu_operand_type
{
    REGISTER,
    SYSCALL_REG,
    IMMEDIATE,
    MEMORY,
} vpu_operand_type_t;

typedef struct vpu_operand
{
    vpu_operand_type_t type;
    union
    {
        u32 reg;
        u32 imm;
        u32 mem;
    };
} vpu_operand_t;

typedef struct vpu_instr
{
    vpu_opcode_t opcode;
    vpu_operand_t operands[3];
} vpu_instr_t;

void vpu_instr_add(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3);

void vpu_instr_sub(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3);

void vpu_instr_mul(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3);

void vpu_instr_div(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3);

void vpu_instr_inc(vpu_operand_t *op1);

void vpu_instr_dec(vpu_operand_t *op1);

void vpu_instr_mod(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3);

void vpu_instr_and(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3);

void vpu_instr_or(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3);

void vpu_instr_xor(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3);

void vpu_instr_not(vpu_operand_t *op1);

void vpu_instr_shl(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3);

void vpu_instr_shr(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3);

void vpu_instr_cmp(vpu_operand_t *op1, vpu_operand_t *op2);

void vpu_instr_test(vpu_operand_t *op1, vpu_operand_t *op2);

void vpu_instr_jmp(vpu_operand_t *op1);

void vpu_instr_jz(vpu_operand_t *op1);

void vpu_instr_jnz(vpu_operand_t *op1);

void vpu_instr_jg(vpu_operand_t *op1);

void vpu_instr_jl(vpu_operand_t *op1);

void vpu_instr_jge(vpu_operand_t *op1);

void vpu_instr_jle(vpu_operand_t *op1);

void vpu_instr_call(vpu_operand_t *op1);

void vpu_instr_ret();

void vpu_instr_loop(vpu_operand_t *op1, vpu_operand_t *op2);

void vpu_instr_push(vpu_operand_t *op1);

void vpu_instr_pop(vpu_operand_t *op1);

void vpu_instr_mov(vpu_operand_t *op1, vpu_operand_t *op2);

void vpu_instr_lea(vpu_operand_t *op1, vpu_operand_t *op2);

void vpu_instr_syscall(vpu_operand_t *op1);

#endif /* !_VPU_INSTRUCTIONS_H_ */