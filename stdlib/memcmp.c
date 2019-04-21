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

#include <libk.h>
int memcmp(const void* s1, const void* s2, size_t n)
{
	unsigned char *b_p1 = (unsigned char*)s1;
	unsigned char *b_p2 = (unsigned char*)s2;
	
	for(;((uintptr_t)b_p1 & (sizeof(long)-1)) && n > 0; ++b_p1, ++b_p2, --n)
	{
		if(*b_p1 != *b_p2)
		{
			return *b_p1 > *b_p2 ? 1 : -1;
		}
	}
	
	unsigned long *w_p1 = (unsigned long *)b_p1;
    unsigned long *w_p2 = (unsigned long *)b_p2;
    for (;n >= sizeof(unsigned long); ++w_p1, ++w_p2, n -= sizeof(unsigned long))
    {
        if (*w_p1 != *w_p2)
        {
            return *w_p1 > *w_p2 ? 1 : -1;
        }
	}
	
	b_p1 = (unsigned char *)w_p1;
    b_p2 = (unsigned char *)w_p2;
    for (; n > 0; ++b_p1, ++b_p2, --n)
    {
        if (*b_p1 != *b_p2)
        {
            return *b_p1 > *b_p2 ? 1 : -1;
        }
	}
	
	return 0;
}