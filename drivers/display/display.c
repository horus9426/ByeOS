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

#include "display.h"
#include "vga.h"

//TODO: add support for other display types other than vga textmode

void display_init()
{
	//if we dont otherwise specify, support vga textmode
	#ifndef DISPLAY_INTERFACE
	#define DISPLAY_INTERFACE VGA_TEXTMODE
	#endif
	
	#if DISPLAY_INTERFACE == VGA_TEXTMODE
	vga_initialize();
	vga_setcolor(vga_entry_color(COLOR_GREEN, COLOR_BLACK));
	#endif
	

}
//these functions are just inline wreappers to the true functions that do the work depending on the display mode
inline void display_putchar(char c)
{
	#if DISPLAY_INTERFACE == VGA_TEXTMODE
	vga_putchar(c);
	#endif
}
inline void display_putstr(const char* str)
{
	#if DISPLAY_INTERFACE == VGA_TEXTMODE
	vga_putstr(str);
	#endif
}
inline int display_setcolor(int color)
{
	#if DISPLAY_INTERFACE == VGA_TEXTMODE
	vga_setcolor(vga_entry_color(color, COLOR_BLACK));
	#else
		return 1;
	#endif
	return 0;
}

inline void display_clear()
{
	vga_clear();
}