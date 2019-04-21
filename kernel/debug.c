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

#include "debug.h"
#include <libk.h>
inline void bochs_debug_message(const char* message)
{
	size_t i = 0;
	while(message[i] != 0)
		outb(0xE9, message[i++]);
	outb(0xE9, '\n');
}