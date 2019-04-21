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
void* memmove(void* s1, const void* s2, size_t n)
{
	unsigned char *dest = (unsigned char*)s1;
	unsigned char *src = (unsigned char*)s2;
	
	if(dest < src + n && dest > src)
	{
		src += n;
		dest += n;
		
		for(;((uintptr_t)dest & (sizeof(unsigned long)-1)) && n > 0; )
		{
			src--, dest--, n--;
			*dest = *src;
		}
		
		unsigned long *w_src = (unsigned long*)src;
		unsigned long *w_dest = (unsigned long*)dest;
		for(; n >= sizeof(unsigned long); )
		{
			w_src--, w_dest--, n -= sizeof(unsigned long);
			*w_dest = *w_src;
		}
		
		src = (unsigned char*)w_src;
		dest = (unsigned char*)w_dest;
		for(; n>0;)
		{
			src--, dest--, n--;
			*dest = *src;
		}
	}
	else
	{
		for (;((uintptr_t)dest & (sizeof(unsigned long)-1)) && n > 0; src++, dest++, n--)
        {
            *dest = *src;
        }

        
        unsigned long *w_src  = (unsigned long *)src;
        unsigned long *w_dst = (unsigned long *)dest;
        for (;n >= sizeof(unsigned long); w_src++, w_dst++, n -= sizeof(unsigned long))
        {
            *w_dst = *w_src;
        }

       
        src  = (unsigned char *)w_src;
        dest = (unsigned char *)w_dst;
        for (; n > 0; src++, dest++, n--)
        {
            *dest = *src;
		}
	}
	return (void*)s2;
}