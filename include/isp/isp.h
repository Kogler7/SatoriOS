#ifndef _INSTRUCTION_SEMANTIC_PARSER_H_
#define _INSTRUCTION_SEMANTIC_PARSER_H_

typedef struct asm_instruction
{
    byte opcode;
    byte operand1;
    byte operand2;
    byte operand3;
} asm_instruction;

typedef struct bin_instruction
{
    byte opcode;
    byte operand1;
    byte operand2;
    byte operand3;
} bin_instruction;

int pre_process(char *text);

int assemble(char *text);

int execute(char *text);

#endif /* !_INSTRUCTION_SEMANTIC_PARSER_H_ */