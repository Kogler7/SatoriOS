#ifndef _VPU_INSTRUCTIONS_H_
#define _VPU_INSTRUCTIONS_H_

typedef enum csp_opcode
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
} csp_opcode;

#endif /* !_VPU_INSTRUCTIONS_H_ */