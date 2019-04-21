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

#include "shell.h"
#include <drivers/input/kbd.h>
#include <drivers/power.h>
#include <drivers/timer.h>
#include <libk.h>

static bool debug = false;

extern uint64_t total_mem;
extern uint32_t __kernel_end;
 
 static const char* prefix = "ByeOS> ";
 
void run_shell(void)
{
	while(true)
	{
		printf(prefix);
		char* input = read_line();
		
		
		
		
	
		if(strcmp(input, "clear") == 0)
			display_clear();
		else if(strcmp(input, "debug") == 0)
		{
			debug = !debug;
			printf("Turning debug ");
			puts(debug?"on":"off");
		}
		else if(strcmp(input, "restart") == 0)
			restart();
		else if(strcmp(input, "timer") == 0)
			printf("Timer ticks: %d\n", get_tick());
		
		else if(strcmp(input, "help") == 0)
		{
			puts("ByeOS v0.0.1");
			puts("Commands list");
			puts("-------------------");
			puts("Command               Function");
			puts("clear:                Clears the current text on shell.");
			puts("debug:                Toggles debug mode on and off.");
			puts("restart:              Reboots the system.");
			puts("timer:                Debug command that displays how many ticks have passed since boot.");
			puts("memory:               Displays how much memory is in the system.");
			puts("pagefault:            Purposefully cause a page fault");
		}
		else if(strcmp(input, "memory") == 0)
		{
			printf("You have %dMB of memory\n", total_mem); 
		}
		else if(strcmp(input, "pagefault") == 0)
		{
			*((char*)0xDEADBEEF) = 0;
		}
		else
		{
			printf("Unknown command: %s\n", input);
		}
		
		if(debug)
		{
			if(input == NULL)
			{
				puts("Buffer contents: NULL");
				continue;
			}
			printf("Buffer contents: %s\n", input);
		}
		
		
		
		
	}
}