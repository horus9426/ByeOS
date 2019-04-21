#include "kheap.h"

extern uint32_t KERNEL_END;

static uint32_t placement_address;

uint32_t* kmalloc(uint32_t size)
{
	size_t maxint = sizeof(uintmax_t);
	if(placement_address & ~maxint)
	{
		placement_address &= ~maxint;
		placement_address += maxint;
	}
	
	uint32_t tmp = placement_address;
			
	placement_address += size;
	return (uint32_t*)tmp;
}

uint32_t* kmalloc_a(uint32_t size)
{
	if(placement_address & 0xFFFFF000) // inverse of 0x1000
	{
		placement_address &= 0xFFFFF000;
		placement_address += 0x1000;
	}
	uint32_t tmp = placement_address;
	placement_address += size;
	return (uint32_t*)tmp;
}
uint32_t* kmalloc_p(uint32_t size, uint32_t* phys)
{
	*phys = placement_address; // TODO: actually calculate physical address
	return kmalloc(size);
}
uint32_t* kmalloc_ap(uint32_t size, uint32_t* phys)
{
	*phys = placement_address;
	return kmalloc_a(size);
}

