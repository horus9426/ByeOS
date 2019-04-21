#ifndef ISR_H
#define ISR_H

#define IRQ0  32
#define IRQ1  33
#define IRQ2  34
#define IRQ3  35
#define IRQ4  36
#define IRQ5  37
#define IRQ6  38
#define IRQ7  39
#define IRQ8  40
#define IRQ9  41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

#define DEBUG_REGS 1

#include <libk.h>

typedef struct registers
{
	uint32_t ds;
	uint32_t edi, esi, ebp, current_esp, ebx, edx, ecx, eax;
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, esp, ss;
} registers_t;
//enables callbacks
typedef void (*isr_t)(registers_t*);

#define ISR_ENTRY_NUM 256

isr_t interrupt_handlers[ISR_ENTRY_NUM];

void register_interrupt_handler(uint8_t n, isr_t handler);

#ifdef DEBUG_REGS
void register_dump(registers_t* regs);
#endif

#endif