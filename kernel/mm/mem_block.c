#include "mm/mem_block.h"

// int __init_memblock memblock_add(phys_addr_t base, phys_addr_t size)
// {
// 	phys_addr_t end = base + size - 1;

// 	memblock_dbg("%s: [%pa-%pa] %pS\n", __func__,
// 		     &base, &end, (void *)_RET_IP_);

// 	return memblock_add_range(&memblock.memory, base, size, MAX_NUMNODES, 0);
// }
