%macro ISR_NOERRORCODE 1 
	[GLOBAL isr%1] 
	isr%1:
		push byte 0
		push %1
		jmp isr_common_stub
%endmacro

%macro ISR_ERRORCODE 1
	[GLOBAL isr%1]
	isr%1:
		push %1
		jmp isr_common_stub
%endmacro

ISR_NOERRORCODE 0
ISR_NOERRORCODE 1
ISR_NOERRORCODE 2
ISR_NOERRORCODE 3
ISR_NOERRORCODE 4
ISR_NOERRORCODE 5
ISR_NOERRORCODE 6
ISR_NOERRORCODE 7
ISR_ERRORCODE 8
ISR_NOERRORCODE 9
ISR_ERRORCODE 10
ISR_ERRORCODE 11
ISR_ERRORCODE 12
ISR_ERRORCODE 13
ISR_ERRORCODE 14
ISR_NOERRORCODE 15
ISR_NOERRORCODE 16
ISR_ERRORCODE 17
ISR_NOERRORCODE 18
ISR_NOERRORCODE 19
ISR_NOERRORCODE 20
ISR_NOERRORCODE 21
ISR_NOERRORCODE 22
ISR_NOERRORCODE 23
ISR_NOERRORCODE 24
ISR_NOERRORCODE 25
ISR_NOERRORCODE 26
ISR_NOERRORCODE 27
ISR_NOERRORCODE 28
ISR_NOERRORCODE 29
ISR_ERRORCODE 30
ISR_NOERRORCODE 31


[extern isr_handler]

isr_common_stub:
	pusha ; pushes eax, ecx, edx, ebx, original esp, ebp, esi, edi 
	
	mov ax, ds ; lower 16 bits of eax = ds
	push word 0 ; we expect a 32bit value in our regs struct so we have to pad out ax 
	push word ax ; save the data segment descriptor to return to user mode if we have to
	
	mov ax, 0x10 ; load the kernel data segment descriptor in case we came from user mode
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	cld ; sysv abi requires df to be clear on function enter
	push esp ; push a pointer to the stack which we will interpret in C as struct registers_t*
	
	call isr_handler
	
	pop ebx
	
	pop ebx
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx
	
	popa
	add esp, 8
	iret

%macro IRQ 2
	global irq%1
	irq%1:

		push BYTE 0
		push BYTE %2
		jmp irq_common_stub
%endmacro

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

[extern irq_handler]

; basically the same as isr_common_stub except we call the irq handler in C instead
irq_common_stub:
	pusha
	
	mov ax, ds
	push word 0
	push word ax
	
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	cld
	push esp
	
	call irq_handler
	
	pop ebx
	
	pop ebx
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx
	
	popa
	add esp, 8
	iret
