[GLOBAL gdt_flush]

gdt_flush:
	mov eax, [esp+4] ; get GDT pointer, passed as parameter
	lgdt [eax] ; load the GDT pointer
	
	mov ax,0x10 ; 0x10 is the offset in the GDT to our data segment
	mov ds, ax ; load all data segment selectors
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush ; 0x08 is he offset to our code segment. far jump
	
.flush:
	ret
	
[GLOBAL idt_flush]
idt_flush:
	mov eax, [esp+4]
	lidt [eax]
	ret