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

#include "kbd.h"

static char res[256];

char read_char();

static size_t buffer_pos;

char* read_line()
{
	memset(res, 0, sizeof(res));
	state = WAITING;
	size_t index = 0;
	while(state != NEWLINE_RECEIVED)
	{
		char c = read_char();
		//if we have a backspace, clear out the previous buffer entry and print a backspace
		if(c == '\b')
		{
			if(index != 0)
			{
				res[--index] = 0; 
				putchar(c);
				
			}
				
		}
		//if we have a normal char, add it to the buffer and print it
		else if(c && c != '\n')
		{
			res[index++] = c;
			putchar(c);
		}
		//if we have a newline, print it out 
		else if(c == '\n')
		{
			putchar(c);
		}
	}
	
	
	
	return res;
}



char read_char()
{
	size_t index = buffer_pos % BUFFER_SIZE;
	
	while(scancode_buffer[index] == 0) ;
	uint8_t code = scancode_buffer[index];
	
	scancode_buffer[index] = 0;
	buffer_pos++;
	char res = 0;
	if(!(code & 0x80))
	{		
		if(state == BREAK_CODE_RECEIVED)
		{
			state = WAITING;
			return 0;
		}
		
		res = scancodes[code];
		
		if(res == '\n')
		{
			state = NEWLINE_RECEIVED;
		}
		else
		{
			state = WAITING;
		}
		
		

	}
	else
	{
		state = BREAK_CODE_RECEIVED;
	}
	
	
	
	return res;
}

void init_keyboard()
{
	buffer_pos = 0;
	init_keyboard_interrupt_handler();
}