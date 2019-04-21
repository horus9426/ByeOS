export DEFINES = -DVGA_VRAM_ADDR=0xC03FF000 -D__is_byeos_kernel__ -DARCH_X86

export CC	= i686-elf-gcc
export CFLAGS	=	-std=gnu99 -ffreestanding -Wall -Wextra -Werror=implicit-function-declaration -g -c $(DEFINES)

export AS		= nasm
export ASFLAGS	= -w+orphan-labels -f elf32 $(DEFINES)

export LD				= i686-elf-gcc
export LDFLAGS	= -T linker.ld -ffreestanding -nostdlib -g

CRTI_OBJ=obj/stdlib/crti.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ=obj/stdlib/crtn.o

C_SOURCES:=$(shell find * -iname "*.c") 
C_OBJS=$(C_SOURCES:%.c=%.o) 

ASM_SOURCES:=$(shell find * -iname "*.asm" ! -iname "crti.asm" ! -iname "crtn.asm")
ASM_OBJS=$(ASM_SOURCES:%.asm=%.o)

OBJS = $(C_OBJS) $(ASM_OBJS)

MAKEFLAGS = -rR --no-print-directory

%.o: %.c 

	mkdir -p obj/$(@D)
	$(CC) $(CFLAGS) $< -I./stdlib -I./ -o ./obj/$@ 
	
%.o: %.asm

	mkdir -p obj/$(@D)
	$(AS) $(ASFLAGS) $< -o ./obj/$@

default: $(OBJS)
	
	$(LD) $(LDFLAGS) $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(addprefix obj/, $(OBJS)) $(CRTEND_OBJ) $(CRTN_OBJ) -o final.bin 
									 
	cp final.bin grubimg/boot/final.bin
	grub-mkrescue -o final.iso grubimg
	
	
all: clean default


clean:
	@find . \( -name '*.o' -o -name '*.SYS' -o -name '*.bin' \) -print -exec rm -f '{}' \;
