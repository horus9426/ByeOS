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

#ifdef __linux__
#error "Must compile using a GCC cross compiler targeting i386-elf"
#endif

#include <drivers/input/ps2.h>
#include <drivers/timer.h>

#include <libk.h>
#include "shell.h"
 
uint32_t total_mem; 

bool is_multiboot;

void kmain() 
{	

	if(is_multiboot)
		puts("Booted from multiboot-compliant bootloader");
	else
		puts("Booted from non-multiboot compliant bootloader. Is this an error?");

	puts("Welcome to ByeOS v0.0.2!\nBuilt by Zachary Yosick\nType 'help' to begin.");
	
	init_ps2();
	
	init_timer(60);
	
	asm volatile("sti");
	
	run_shell();
	
	while(1) 
		asm volatile("hlt\n\t");
}
