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

#include "ps2.h"

#define PS2_CMD 0x64
#define PS2_DATA 0x60

#define PS2_P1 0x60
#define PS2_P2 0x60

#define MAX_PS2 2

static bool ps2_channels[MAX_PS2] = {0,0};

void ps2_wait_in()
{
	while(!(inb(PS2_CMD) & (1<<0))) ;
}

void ps2_wait_out()
{
	while(inb(PS2_CMD) & (1<<1)) ;
}


uint16_t init_ps2()
{

	//disable
	outb(PS2_CMD, 0xAD);
	outb(PS2_CMD, 0xA7);
	
	inb(PS2_DATA); //flush buffer
	//set config
	outb(PS2_CMD, 0x20);
	ps2_wait_in();
	uint8_t config = inb(PS2_DATA);
	
	if(((config >> 5) & 1) == 0)
		ps2_channels[0] = 1;
	
	config &= ~(1<<0);
	config &= ~(1<<1);
	config &= ~(1<<6);
	
	outb(PS2_CMD, 0x60);
	ps2_wait_out();
	outb(PS2_DATA, config);
	
	ps2_wait_out();
	
	//controller self test
	outb(PS2_CMD, 0xAA);
	ps2_wait_in();
	if(inb(PS2_DATA) != 0x55) return 1;
	//channel test (1 or 2?)
	if(!ps2_channels[0])
	{
		outb(PS2_CMD, 0xA8);
		ps2_wait_out();
		outb(PS2_CMD, 0x20);
		ps2_wait_in();
		uint8_t configNew = inb(PS2_DATA);
		if(((configNew >> 5) & 1) == 0)
		{
			ps2_channels[0] = 1;
			
		}
		else
		{
			outb(PS2_CMD, 0xA7);
			ps2_channels[0] = 1;
			ps2_channels[1] = 1;
		}	
		config = configNew;
	}
	//interface tests
	ps2_wait_out();
	outb(PS2_CMD, 0xAB);
	ps2_wait_in();
	uint8_t port1 = inb(PS2_DATA);
	uint8_t port2 = 55;
	if(port1) ps2_channels[0] = 0;
	if(ps2_channels[1])
	{
		ps2_wait_out();
		outb(PS2_CMD, 0xA9);
		ps2_wait_in();
		port2 = inb(PS2_DATA);
		if(port2) ps2_channels[1] = 0;
	}
	if(!(ps2_channels[0]) && !(ps2_channels[1])) return (port1<<8) | port2;
	
	//enable devices
	
	if(ps2_channels[0])
		config |= 1 << 0;
	if(ps2_channels[1])
		config |= 1 << 1;
	
	
	
	
	if(ps2_channels[0])
		outb(PS2_CMD, 0xAE);
	ps2_wait_out();
	if(ps2_channels[1])
		outb(PS2_CMD, 0xA8); 
	
	ps2_wait_out();
	outb(PS2_CMD, 0x60);
	ps2_wait_out();
	outb(PS2_DATA, config);
	ps2_wait_out();
	
	
	//reset devices
	uint8_t p1Res, p2Res = 0;
	
	if(ps2_channels[0])
	{
		ps2_wait_out();
		outb(PS2_P1, 0xFF);
		ps2_wait_in();
		p1Res = inb(PS2_P1);
	}
	ps2_wait_out();
	if(ps2_channels[1])
	{
		outb(PS2_CMD, 0xD4);
		ps2_wait_out();
		outb(PS2_P2, 0xFF);
		ps2_wait_in();
		p2Res = inb(PS2_P1);
	}
	init_keyboard();
	inb(PS2_DATA);
	return ((uint16_t)p2Res<<8) | p1Res;
}