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

#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <drivers/display/display.h>
#include "printf.h"



#include <kernel/debug.h>

#define PANIC(x) bochs_debug_message(x);\
				 display_setcolor(COLOR_RED); 	\
				 printf("KERNEL PANIC: "); 								\
				 puts(x);																\
				 while(true) 															\
				 { 																		\
					asm volatile("cli\n\t"); 											\
					asm volatile("hlt\n\t"); 											\
				 }
				
#define debug_breakpoint() asm volatile("xchgw %bx, %bx")

void outb(uint16_t port, uint8_t value);
void outw(uint16_t port, uint16_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

void *memset(void *s, int c, size_t n);
void *memcpy(void *s, const void *s2, size_t n);
void *memmove(void *s1, const void *s2, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

int strcmp(const char *s1, const char *s2);
int isprint(int c);
size_t strlen(const char* str);

int putchar(int c);
int puts(const char *s);

#endif