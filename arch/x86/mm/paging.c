/* #include "paging.h"
#include "page_bitmap.h"

#include <kernel/debug.h>

extern uint32_t KERNEL_VIRTUAL_BASE;
static page_directory_t* kernel_pagedir;
static page_directory_t* current_pagedir;

extern uint32_t placement_address;

//osdev.org recommends the "self-referencing pd trick" so i'm going to use it here
static void* get_addr_phys(void* addr_virt)
{
	uint32_t pd_index = (uint32_t)addr_virt >> 22;
	uint32_t pt_index = (uint32_t)addr_virt >> 12 & 0x03FF;
	
	uint32_t* pd = (uint32_t*)0xFFFFF000;
	uint32_t* pt = (uint32_t*)(0xFFC00000) + (0x400 * pd_index);
	
	return (void*)((pt[pt_index] & ~0xFFF) + ((uint32_t)addr_virt & 0xFFF));
}

static uint32_t* create_kernel_pd()
{
	kernel_pagedir = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
	memset(kernel_pagedir, 0, sizeof(kernel_pagedir)); //null out page dir
	current_pagedir = kernel_pagedir;
	
	int i = 0;
	while(i < placement_address)
	{
		alloc_page(get_page(i + KERNEL_VIRTUAL_BASE, true, kernel_pagedir), 0, 1);
		i += X86_PAGE_SIZE;
	}
	
	kernel_pagedir->addr_phys = (uint32_t*)(&kernel_pagedir.tables_phys - KERNEL_VIRTUAL_BASE);
	
	kernel_pagedir->tables[X86_PAGETABLE_SIZE-1] = (page_table_t*)(kernel_pagedir - KERNEL_VIRTUAL_BASE);
	kernel_pagedir->tables_phys[X86_PAGETABLE_SIZE-1] = (uint32_t)(kernel_pagedir - KERNEL_VIRTUAL_BASE);
	
 
	
	return kernel_pagedir->addr_phys;
}

static void alloc_page(page_table_entry_t* page, bool user, bool rw)
{
	if(page->addr != 0)
		return;
	
	uint32_t index = find_first_frame();
	if(index == (uint32_t)-1)
	{
		PANIC("ERROR: No more free page frames");
	}
	
	set_frame(index*0x1000);
	page->present = 1;
	page->rw = rw;
	page->user = user;
	page->addr = index;
	
}

static void free_page(page_table_entry_t* page)
{
	uint32_t addr;
	if( !(addr=page->addr))
	{
		return;
	}
	clear_frame(addr);
	page->addr = 0;
}

//creates a page table mapping addr_virt to addr_phys. returns a page table pt
static page_t* get_page(uint32_t addr, bool make, page_directory_t* dir)
{
	addr /= X86_PAGE_SIZE;
	uint32_t table_index = addr / X86_PAGETABLE_SIZE;
	if(dir->tables[table_index])
	{
		return &dir->tables[table_index]->pages[addr%X86_PAGETABLE_SIZE];
	}
	else if(make)
	{
		uint32_t phys_addr;
		dir->tables[table_index] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &phys_addr);
		memset(dir->tables[table_index], 0, X86_PAGE_SIZE);
		dir->tables_phys[table_index] = phys_addr | 0x7;
		return &dir->tables[table_index]->pages[addr%X86_PAGETABLE_SIZE];
	}
	return (page_t*)0;
}

static inline void invalidate_page(uint32_t addr)
{
	asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
}

void enable_paging()
{
	uint32_t cr0;
	asm volatile ("mov %%cr0, %0": "=r" (cr0));
	cr0 |= 0x80010001;
	
	asm volatile ("mov %0, %%cr0" :: "r" (cr0));
	if(cr0 % 2) //branch to flush fetch cache
	{
		asm volatile ("nop");
	}
}

void set_page_dir(uint32_t* page_dir)
{
	asm volatile ("mov %0, %%cr3" :: "r" (page_dir));	
}

void disable_paging()
{
	uint32_t cr0;
	asm volatile("mov %%cr0, %0": "=r"(cr0));
	cr0 &= ~0x80000000;
	asm volatile("mov %0, %%cr0":: "r"(cr0));
}
void init_paging_kernel()
{
	uint32_t* pagedir_phys = create_kernel_pd();
	
	create_mapping(0x100000, 0xC0100000, false, true);
	create_mapping(0xB8000, 0xC03FF00, false, true);
	set_page_dir(pagedir_phys);
	
	
	enable_paging();
	
} */
void init_paging_kernel(){}