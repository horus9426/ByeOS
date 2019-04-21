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

#include "vga.h"
#include <libk.h>
 

 

 
void vga_initialize() 
{
	cursor_y = 0;
	cursor_x = 0;
	vga_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	#ifndef VGA_VRAM_ADDR
	#define VGA_VRAM_ADDR 0xB8000
	#endif
	
	vga_buffer = (uint16_t*) VGA_VRAM_ADDR;
	vga_clear();
}
 
void vga_setcolor(uint8_t color) 
{
	vga_color = color;
}
 
void vga_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	vga_buffer[index] = vga_entry(c, color);
}


static void move_cursor()
{
	uint16_t cursorLoc = cursor_y * VGA_WIDTH + cursor_x;
	outb(0x3D4, 14); //vga high cursor byte
	outb(0x3D5, cursorLoc >> 8);
	outb(0x3D4, 15); //vga low cursor byte
	outb(0x3D5, cursorLoc);
}
 
static void vga_scroll()
{
	uint16_t blank = vga_entry(' ', vga_color);
	
	if(cursor_y >= VGA_HEIGHT)
	{
		size_t i;
		for(i = 0*VGA_WIDTH; i < (VGA_HEIGHT-1)*VGA_WIDTH; i++)
		{
			vga_buffer[i] = vga_buffer[i + VGA_WIDTH];
		}
		
		for(i = (VGA_HEIGHT-1)*VGA_WIDTH; i < VGA_HEIGHT*VGA_WIDTH; i++)
		{
			vga_buffer[i] = blank;
		}
		
		cursor_y = (VGA_HEIGHT-1);

	}
}

void vga_putchar(char c) 
{
	if(c == '\0')
	#ifdef DISPLAY_NULLS_VGA
		vga_writestring("NUL");
	#else
		return;
	#endif
	if(c == '\b')
	{
		if(cursor_x-- <= 0)
		{
			cursor_y--;
			cursor_x = VGA_WIDTH-1;
		}
		vga_putentryat(' ', vga_color, cursor_x, cursor_y);
		
	}
	else if(c == '\t')
	{
		cursor_x = (cursor_x+8);
	}
	else if(c == '\r')
	{
		cursor_x = 0;
	}
	if(c == '\n')
	{
		cursor_y++;
		cursor_x = 0;
	}
	else if(c >= ' ')
	{
		vga_putentryat(c, vga_color, cursor_x, cursor_y);
		cursor_x++;
	}
	if (cursor_x >= VGA_WIDTH) 
	{
		cursor_y++;
		cursor_x=0;
	}
	vga_scroll();
	move_cursor();
	
}
 
void vga_putdata(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		vga_putchar(data[i]);
}
 
void vga_putstr(const char* data) 
{
	vga_putdata(data, strlen(data));
}

void vga_clear()
{
	for (size_t y = 0; y < VGA_HEIGHT; y++) 
	{
		for (size_t x = 0; x < VGA_WIDTH; x++) 
		{
			const size_t index = y * VGA_WIDTH + x;
			vga_buffer[index] = vga_entry(' ', vga_color);
		}
	}
	cursor_y = 0;
	cursor_x = 0;
	move_cursor();
}

