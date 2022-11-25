#include "arch/loongarch.h"
#include "arch/ls7a.h"

//拓展IO中断使能寄存器/中断路由寄存器/中断目标处理器核路由寄存器地址/中断目标结点映射方式配置
void extioi_init(void)
{
    iocsr_writeq((0x1UL << UART0_IRQ) | (0x1UL << KEYBOARD_IRQ) | 
                 (0x1UL << MOUSE_IRQ) | (0x1UL << DISK_IRQ), 
                 LOONGARCH_IOCSR_EXTIOI_EN_BASE);

    /* extioi[31:0] map to cpu irq pin INT1, other to INT0 */
    iocsr_writeq(0x01UL,LOONGARCH_IOCSR_EXTIOI_MAP_BASE);

    /* extioi IRQ 0-7 route to core 0, use node type 0 */
    iocsr_writeq(0x0UL,LOONGARCH_IOCSR_EXTIOI_ROUTE_BASE);

    /* nodetype0 set to 1, always trigger at node 0 */
    iocsr_writeq(0x1,LOONGARCH_IOCSR_EXRIOI_NODETYPE_BASE);
}

// ask the extioi what interrupt we should serve.
//拓展IO中断状态寄存器
unsigned long extioi_claim(void)
{
    return iocsr_readq(LOONGARCH_IOCSR_EXTIOI_ISR_BASE);
}

void extioi_complete(unsigned long irq)
{
    iocsr_writeq(irq, LOONGARCH_IOCSR_EXTIOI_ISR_BASE);
}
