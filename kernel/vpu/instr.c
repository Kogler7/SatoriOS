#include "vpu/instr.h"
#include "vpu/vpu.h"
#include "sys/syscall.h"

static inline u32 get_op_value(vpu_operand_t *op)
{
    u32 op_val = 0;
    switch (op->type)
    {
    case REGISTER:
        op_val = cur_vpu->gpr[op->reg];
        break;
    case SYSCALL_REG:
        op_val = cur_vpu->scr[op->reg];
        break;
    case IMMEDIATE:
        op_val = op->imm;
        break;
    case MEMORY:
        op_val = *(u32 *)get_phys_addr(op->mem);
        break;
    }
    return op_val;
}

static inline void set_op_value(vpu_operand_t *op, u32 val)
{
    switch (op->type)
    {
    case REGISTER:
        cur_vpu->gpr[op->reg] = val;
        break;
    case SYSCALL_REG:
        cur_vpu->scr[op->reg] = val;
        break;
    case IMMEDIATE:
        vpu_error("Invalid operand type.");
        break;
    case MEMORY:
        *(u32 *)get_phys_addr(op->mem) = val;
        break;
    }
}

#define _sgl_op(op1, op)                 \
    do                                   \
    {                                    \
        vpu_switch_seg(SEG_DS);          \
        u32 op1_val = get_op_value(op1); \
        set_op_value(op1, op op1_val);   \
    } while (0)

#define _calc_op(op1, op2, op3, op)            \
    do                                         \
    {                                          \
        vpu_switch_seg(SEG_DS);                \
        u32 op2_val = get_op_value(op2);       \
        u32 op3_val = get_op_value(op3);       \
        set_op_value(op1, op2_val op op3_val); \
    } while (0)

void vpu_instr_add(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3)
{
    _calc_op(op1, op2, op3, +);
}

void vpu_instr_sub(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3)
{
    _calc_op(op1, op2, op3, -);
}

void vpu_instr_mul(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3)
{
    _calc_op(op1, op2, op3, *);
}

void vpu_instr_div(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3)
{
    _calc_op(op1, op2, op3, /);
}

void vpu_instr_inc(vpu_operand_t *op1)
{
    _sgl_op(op1, ++);
}

void vpu_instr_dec(vpu_operand_t *op1)
{
    _sgl_op(op1, --);
}

void vpu_instr_mod(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3)
{
    _calc_op(op1, op2, op3, %);
}

void vpu_instr_and(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3)
{
    _calc_op(op1, op2, op3, &);
}

void vpu_instr_or(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3)
{
    _calc_op(op1, op2, op3, |);
}

void vpu_instr_xor(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3)
{
    _calc_op(op1, op2, op3, ^);
}

void vpu_instr_not(vpu_operand_t *op1)
{
    _sgl_op(op1, ~);
}

void vpu_instr_shl(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3)
{
    _calc_op(op1, op2, op3, <<);
}

void vpu_instr_shr(vpu_operand_t *op1, vpu_operand_t *op2, vpu_operand_t *op3)
{
    _calc_op(op1, op2, op3, >>);
}

void vpu_instr_cmp(vpu_operand_t *op1, vpu_operand_t *op2)
{
    vpu_switch_seg(SEG_DS);
    u32 op1_val = get_op_value(op1);
    u32 op2_val = get_op_value(op2);
    if (op1_val == op2_val)
    {
        cur_vpu->flags.zf = 1;
    }
    else
    {
        cur_vpu->flags.zf = 0;
    }
    if (op1_val < op2_val)
    {
        cur_vpu->flags.cf = 1;
    }
    else
    {
        cur_vpu->flags.cf = 0;
    }
}

void vpu_instr_test(vpu_operand_t *op1, vpu_operand_t *op2)
{
    vpu_switch_seg(SEG_DS);
    u32 op1_val = get_op_value(op1);
    u32 op2_val = get_op_value(op2);
    if (op1_val & op2_val)
    {
        cur_vpu->flags.zf = 0;
    }
    else
    {
        cur_vpu->flags.zf = 1;
    }
}

void vpu_instr_jmp(vpu_operand_t *op1)
{
    vpu_switch_seg(SEG_DS);
    u32 op1_val = get_op_value(op1);
    cur_vpu->ip = op1_val;
}

void vpu_instr_jz(vpu_operand_t *op1)
{
    if (cur_vpu->flags.zf)
    {
        vpu_instr_jmp(op1);
    }
}

void vpu_instr_jnz(vpu_operand_t *op1)
{
    if (!cur_vpu->flags.zf)
    {
        vpu_instr_jmp(op1);
    }
}

void vpu_instr_jg(vpu_operand_t *op1)
{
    if (!cur_vpu->flags.zf && !cur_vpu->flags.cf)
    {
        vpu_instr_jmp(op1);
    }
}

void vpu_instr_jl(vpu_operand_t *op1)
{
    if (cur_vpu->flags.cf)
    {
        vpu_instr_jmp(op1);
    }
}

void vpu_instr_jge(vpu_operand_t *op1)
{
    if (!cur_vpu->flags.cf)
    {
        vpu_instr_jmp(op1);
    }
}

void vpu_instr_jle(vpu_operand_t *op1)
{
    if (cur_vpu->flags.zf || cur_vpu->flags.cf)
    {
        vpu_instr_jmp(op1);
    }
}

void vpu_instr_call(vpu_operand_t *op1)
{
    vpu_switch_seg(SEG_DS);
    u32 op1_val = get_op_value(op1);
    cur_vpu->sp -= 4;
    if (cur_vpu->sp < 0)
    {
        vpu_error("Stack overflow");
    }
    vpu_switch_seg(SEG_SS);
    *(u32 *)get_phys_addr(cur_vpu->sp) = cur_vpu->ip;
    cur_vpu->ip = op1_val;
}

void vpu_instr_ret()
{
    if (cur_vpu->sp + 4 > cur_vpu->bp)
    {
        vpu_error("Stack underflow");
    }
    vpu_switch_seg(SEG_SS);
    cur_vpu->ip = *(u32 *)get_phys_addr(cur_vpu->sp);
    cur_vpu->sp += 4;
}

void vpu_instr_loop(vpu_operand_t *op1, vpu_operand_t *op2)
{
    vpu_instr_dec(op1);
    if (get_op_value(op1))
    {
        vpu_instr_jmp(op2);
    }
}

void vpu_instr_push(vpu_operand_t *op1)
{
    u32 op1_val = get_op_value(op1);
    cur_vpu->sp -= 4;
    if (cur_vpu->sp < 0)
    {
        vpu_error("Stack overflow");
    }
    vpu_switch_seg(SEG_SS);
    *(u32 *)get_phys_addr(cur_vpu->sp) = op1_val;
}

void vpu_instr_pop(vpu_operand_t *op1)
{
    if (cur_vpu->sp + 4 > cur_vpu->bp)
    {
        vpu_error("Stack underflow");
    }
    vpu_switch_seg(SEG_SS);
    u32 op1_val = *(u32 *)get_phys_addr(cur_vpu->sp);
    cur_vpu->sp += 4;
    set_op_value(op1, op1_val);
}

void vpu_instr_mov(vpu_operand_t *op1, vpu_operand_t *op2)
{
    vpu_switch_seg(SEG_DS);
    u32 op2_val = get_op_value(op2);
    set_op_value(op1, op2_val);
}

void vpu_instr_lea(vpu_operand_t *op1, vpu_operand_t *op2)
{
    vpu_switch_seg(SEG_DS);
    if (op2->type != MEMORY)
    {
        vpu_error("Invalid operand type.");
    }
    set_op_value(op1, op2->mem);
}

void vpu_instr_syscall(vpu_operand_t *op1)
{
    syscall_entry(get_op_value(op1), cur_vpu->scr);
}