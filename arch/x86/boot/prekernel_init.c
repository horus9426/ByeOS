/*
	Copyright (C) 2019 Zachary Yosick

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "multiboot.h"


#include <libk.h>
#include <arch/x86/descriptor_tables.h>
#include <arch/x86/exceptions.h>



#include <drivers/display/display.h> 
#include <drivers/input/ps2.h>
#include <drivers/timer.h>

extern uint32_t total_mem;
extern uint32_t KERNEL_VIRTUAL_BASE;
extern bool is_multiboot;
static multiboot_info_t* boot_info; 

static void load_multiboot_info()
{
	if(boot_info->flags & (1<<0))
	{
		total_mem = boot_info->mem_upper + boot_info->mem_lower;
	}
	if(boot_info->flags & (1<<6))
	{

		uint32_t mmap_addr = boot_info->mmap_addr + KERNEL_VIRTUAL_BASE;
		multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)(mmap_addr);
		while((unsigned int)mmap < boot_info->mmap_addr + boot_info->mmap_length)
		{
						
			mmap = (multiboot_memory_map_t*) ((unsigned int)mmap + mmap->size + sizeof(mmap->size));
		}
	}

}

void preboot_init_x86(multiboot_info_t* mboot, uint32_t magic)
{

	display_init();
	init_descriptor_tables();
	enable_exception_handling();
	//overwrite asm paging, need it just to get into kernel, here we set up proper pagetables
//	init_paging_kernel();
	

	
	//check to see if the kernel was booted using a multiboot bootloader.
	//if so, load relevant structures
	if(magic == 0x2BADB002 && mboot != NULL)
	{
		boot_info = mboot;
		printf("Multiboot structure address: %x\n", (uint32_t*)mboot);
		is_multiboot = true;
//		load_multiboot_info();
	}
	else
		is_multiboot = false;
	
	


}	