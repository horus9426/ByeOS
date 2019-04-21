#include "memory_manager.h"
#include "kheap.h"
#include "paging.h"

memory_map_t first_mmap_entry;
memory_map_t* cur;
void init_memory_manager()
{
	memset(&first_mmap_entry, 0, sizeof(first_mmap_entry));
	cur = &first_mmap_entry;
	init_paging_kernel();
}

void add_usable_address_range(uint32_t addr, uint32_t len)
{
	cur->addr = addr;
	cur->len = len;
	cur->next = (memory_map_t*)kmalloc(sizeof(memory_map_t));
	cur = cur->next;
}

