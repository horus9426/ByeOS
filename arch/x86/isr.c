#include "isr.h"

#include <kernel/debug.h>


void register_interrupt_handler(uint8_t n, isr_t handler)
{
	interrupt_handlers[n] = handler;
}


#ifdef DEBUG_REGS
void register_dump(registers_t* regs)
{

	printf("REGISTER DUMP:\nEAX: 0x%x\nEBX: 0x%x\nECX: 0x%x\nEDX: 0x%x\nEDI: 0x%x\nESI: 0x%x\nEBP: 0x%x\nESP: 0x%x\nEIP: 0x%x\nEFLAGS: 0x%x\nCPU ERRCODE: 0x%x\nCS: 0x%x\nDS: 0x%x\nSS: 0x%x\n",
			regs->eax, regs->ebx, regs->ecx, regs->edx, 
			regs->edi, regs->esi, regs->ebp, regs->esp,
			regs->eip, regs->eflags, regs->err_code,
			regs->cs, regs->ds, regs->ss
		);
	

}
#endif
void isr_handler(registers_t* regs)
{

	if (interrupt_handlers[regs->int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs->int_no];
        handler(regs);
    }
	else
	{
		bochs_debug_message("unhandled int");
		printf("Unhandled interrupt caught: %x\n", regs->int_no);
		
		register_dump(regs);
		
		asm volatile("cli");
		for(;;) asm volatile("hlt");
		
	}
}

void irq_handler(registers_t* regs)
{
	if(regs->int_no >= 40)
	{
		outb(0xA0, 0x20);
	}
	outb(0x20, 0x20);

	if(interrupt_handlers[regs->int_no] != 0)
	{
		isr_t handler = interrupt_handlers[regs->int_no];
		handler(regs);
	}
}