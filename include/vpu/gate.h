#include "types.h"

#ifndef _VPU_GATE_H_
#define _VPU_GATE_H_

typedef struct gate
{
    u32 offset_low : 16;
    u32 selector : 16;
    u32 zero : 8;
    u32 type : 4;
    u32 dpl : 2;
    u32 present : 1;
    u32 offset_high : 16;
} gate_t;

#endif /* !_VPU_GATE_H_ */