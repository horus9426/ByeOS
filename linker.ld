ENTRY(start)

SECTIONS
{
	
	. = 0xC0100000;
	__kernel_start = .;
	KERNEL_VIRTUAL_BASE = 0xC0000000;
	.text ALIGN(4K) : AT(ADDR(.text) - KERNEL_VIRTUAL_BASE)
	{
		*(.multiboot)
		*(.text)
	}

	.rodata ALIGN(4K) : AT(ADDR(.rodata) - KERNEL_VIRTUAL_BASE)
	{
		*(.rodata)
	}

	.data ALIGN(4K) : AT(ADDR(.data) - KERNEL_VIRTUAL_BASE)
	{
		*(.data)
	}

	.bss ALIGN(4K) : AT(ADDR(.bss) - KERNEL_VIRTUAL_BASE)
	{
		*(COMMON)
		*(.bss)
		*(.kstack)
	}
	__kernel_end = .;
}