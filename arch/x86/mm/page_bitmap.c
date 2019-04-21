#include "page_bitmap.h"
void set_frame(uint32_t addr)
{
	uint32_t page = addr/0x1000;
	uint32_t index = INDEX_FROM_BIT(page);
	uint32_t offset = OFFSET_FROM_BIT(page);
	page_bitmap[index] |= (0x1 << offset);
	
}
void clear_frame(uint32_t addr)
{
	uint32_t page = addr/0x1000;
	uint32_t index = INDEX_FROM_BIT(page);
	uint32_t offset = OFFSET_FROM_BIT(page);
	page_bitmap[index] &= ~(0x1 << offset);
}
bool test_frame(uint32_t addr)
{
	uint32_t page = addr/0x1000;
	uint32_t index = INDEX_FROM_BIT(page);
	uint32_t offset = OFFSET_FROM_BIT(page);
	return page_bitmap[index] & (0x1 << offset);
}

uint32_t find_first_frame()
{
	for(unsigned int i = 0; i < INDEX_FROM_BIT(bitmap_size); i++)
	{
		if(page_bitmap[i] != 0xFFFFFFFF)
		{
			for(unsigned int j = 0; j < 32; j++)
			{
				if(!(page_bitmap[i] & (0x1 << j)))
					return i*32+j;
			}
		}
	}
	return (uint32_t)-1;
}