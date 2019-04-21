#ifndef PAGE_BITMAP_H
#define PAGE_BITMAP_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define INDEX_FROM_BIT(x) (x/32)
#define OFFSET_FROM_BIT(x) (x%32)

uint32_t* page_bitmap;
size_t bitmap_size;

void set_frame(uint32_t addr);
void clear_frame(uint32_t addr);
bool test_frame(uint32_t addr);

uint32_t find_first_frame();

#endif