#include "exceptions.h"
#include <kernel/debug.h>
#include <drivers/display/display.h>
static void pagefault_callback(registers_t* regs)
{
	
	
	uint32_t faulting_address;
	asm volatile("mov %%cr2, %0" : "=r" (faulting_address));
	bool present = !(regs->err_code & 0x1);
	bool rw = regs->err_code & 0x2;
	bool us = regs->err_code & 0x4;
	bool reserved = regs->err_code & 0x8;
	
	display_setcolor(COLOR_RED);
	
	printf("Page fault! (");
	if(present) {printf("present ");}
	if(rw) {printf("read-only ");}
	if(us) {printf("user-mode ");}
	if(reserved) {printf("reserved ");}
	printf(") at %x\n", faulting_address);;
	
	#ifdef DEBUG_REGS
	register_dump(regs);
	#endif
	
	//hang forever
	asm volatile("cli");
	for(;;) asm volatile("hlt");
}

static void gpf_callback(registers_t* regs)
{
	(void)regs;
	bochs_debug_message("gpf");
	asm volatile("nop");
	#ifdef DEBUG_REGS
	register_dump(regs);
	#endif
	
	PANIC("GPF");
}

static void doublefault_callback(registers_t* regs)
{
	(void)regs;
	outb(0xE9, 'e');
	for(;;);
}

void enable_exception_handling()
{
	register_interrupt_handler(8, &doublefault_callback);
	register_interrupt_handler(13, &gpf_callback);
	register_interrupt_handler(14, &pagefault_callback);
}

