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

#include "timer.h"

#include <arch/x86/isr.h>



uint32_t tick = 0;

static void timer_callback(registers_t* regs)
{
	(void)regs;
	tick++;
}

uint32_t get_tick()
{
	return tick;
}

void init_timer(uint32_t frequency)
{
	register_interrupt_handler(IRQ0, &timer_callback);
	
	uint32_t divisor = 1193180 / frequency;
	
	outb(0x43, 0x36);
	
	uint8_t low = (uint8_t)(divisor & 0xFF);
	uint8_t high = (uint8_t)( (divisor>>8) & 0xFF);
	
	outb(0x40, low);
	outb(0x40, high);
}