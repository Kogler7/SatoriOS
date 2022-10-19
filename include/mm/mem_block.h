#include "mm/mm_types.h"
int mem_block_add_node(phys_addr_t base, phys_addr_t size, int nid, enum memblock_flags flags);
int mem_block_add(phys_addr_t base, phys_addr_t size);
int mem_block_remove(phys_addr_t base, phys_addr_t size);
int mem_block_phys_free(phys_addr_t base, phys_addr_t size);
int mem_block_reserve(phys_addr_t base, phys_addr_t size);