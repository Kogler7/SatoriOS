#include "types.h"
#include "gcc.h"

#ifndef _VPU_DESCRIPTOR_TABLE_H_
#define _VPU_DESCRIPTOR_TABLE_H_

#define VDT_ENTRY_SIZE 8

typedef struct selector
{
    u16 rpl : 2;  // Requested Privilege Level
    u16 tbl : 1;  // Table Indicator (0 = GDT, 1 = LDT)
    u16 idx : 13; // Index
} selector_t;

typedef struct descriptor_attrs
{
    u8 accessed : 1;        // 表明该段是否被访问过，将选择子装入寄存器时，该位被置1
    u8 writeable : 1;       // 代码段：0表示只执行，1表示可读；数据段：0表示只读，1表示可读写
    u8 direction : 1;       // 代码段：0表示非一致码段，1表示一致码段；数据段：0表示向高位扩展，1表示向低位扩展
    u8 executable : 1;      // 表明该段是否可执行，如果该位为1，则表示该段是代码段，否则是数据段
    u8 descriptor_type : 1; // 表明该段描述符是系统段（0）描述符还是存储段（代码或数据）描述符
    u8 privilege_level : 2; // 表明该段的特权级别，0表示最高级别，3表示最低级别
    u8 present : 1;         // 表明该段是否存在内存中，如果该位为0，则表示该段不存在内存中
} descriptor_attrs_t;

typedef struct descriptor_flags
{
    u8 limit_high : 4;  // 段界限的高4位
    u8 available : 1;   // 供系统软件使用
    u8 zero : 1;        // 必须为0
    u8 size : 1;        // 在代码段中，0表示16位地址，1表示32位地址；在数据段中，0表示16位段界限，1表示32位段界限
    u8 granularity : 1; // 表明段界限的单位（粒度），0表示1字节，1表示4KB
} descriptor_flags_t;

typedef struct descriptor
{
    u16 limit_low;            // 段界限的低16位
    u16 base_low;             // 段基地址的低16位
    u8 base_mid;              // 段基地址的中8位
    descriptor_attrs_t attrs; // 段属性
    descriptor_flags_t flags; // 段标志
    u8 base_high;             // 段基地址的高8位
} descriptor_t;

typedef struct virtual_descriptor
{
    addr entry;
    u32 limit;
    descriptor_attrs_t attrs;
} attr_packed virtual_descriptor_t;

typedef struct vdt_entry
{
    int limit;                 // 表界限
    virtual_descriptor_t base; // 基地址
} vdt_entry_t;

#endif /* !_VPU_DESCRIPTOR_TABLE_H_ */