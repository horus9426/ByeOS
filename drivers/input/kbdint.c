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

#include "kbdint.h"

static volatile size_t current_scancode_pos;

static void keyboard_callback(registers_t* regs)
{
	(void)regs;
	uint8_t status = inb(0x64);
    uint8_t scancode = inb(0x60);
	
	scancode_buffer[current_scancode_pos++ % BUFFER_SIZE] = scancode;
}

void init_keyboard_interrupt_handler()
{
	memset((uint8_t*)scancode_buffer, 0, BUFFER_SIZE);
	current_scancode_pos = 0;	
	register_interrupt_handler(IRQ1, &keyboard_callback);
}