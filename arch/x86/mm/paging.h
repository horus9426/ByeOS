#ifndef PAGE_DIRECTORY_H
#define PAGE_DIRECTORY_H

#include <libk.h>

#define X86_PAGETABLE_SIZE 1024
#define X86_PAGE_SIZE 4096

#define PAGE_ALIGN_MASK 0xFFFFF000

typedef struct page_table_entry
{
	uint32_t present : 1;
	uint32_t rw : 1; //0=r, 1=rw
	uint32_t user : 1; //0=sup, 1=sup+user
	uint32_t writethrough : 1;
	uint32_t cache_disabled : 1;
	uint32_t accessed : 1; 
	uint32_t dirty : 1;
	uint32_t unused : 5;
	uint32_t addr : 20;
} page_table_entry_t;

typedef struct page_table
{
	page_table_entry_t pages[X86_PAGETABLE_SIZE];
} page_table_t;

typedef struct page_directry
{
	page_table_t* tables[X86_PAGETABLE_SIZE];
	//physical addresses of page tables to use
	uint32_t* tables_phys[X86_PAGETABLE_SIZE];
	uint32_t* addr_phys;
} page_directory_t;

 

 

void set_page_directory(page_directory_t* pd);

void init_paging_kernel();

extern uint32_t KERNEL_VIRTUAL_BASE;

#endif