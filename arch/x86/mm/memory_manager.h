#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stdint.h>

void init_memory_manager();
void add_usable_address_range(uint32_t addr, uint32_t len);

typedef struct memory_map
{
	uint32_t addr;
	uint32_t len;
	struct memory_map* next;
} memory_map_t;

#endif