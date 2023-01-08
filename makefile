SRCS := $(shell find kernel/ -name '*.cpp') 
OBJS := $(SRCS:.cpp=.o)
CC = gcc
LD = ld

CFLAGS :=                  \
    -Ikernel/src	        \
	-fpermissive			\
    -ffreestanding          \
    -fno-stack-protector    \
    -fno-pic                \
	-w						\
    -O1                     \
    -m32                    \
    -g                      \

ASM_FLAGS :=                \
    -f elf32

LD_FLAGS :=                 \
    -nostdlib               \
    -Tkernel/link.ld        \
	-m elf_i386				\
    -z max-page-size=0x1000

.SUFFIXE: .cpp
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

kernel.elf: $(OBJS)
	make asm
	$(LD) $(LD_FLAGS) $(OBJS) entry.o interrupts.o gdt.o idt.o -o $@


$(KERNEL_DISK): kernel.elf 
	rm -f $(KERNEL_DISK)
	dd if=/dev/zero bs=8M count=0 seek=64 of=$(KERNEL_DISK)
	parted -s $(KERNEL_DISK) mklabel msdos
	parted -s $(KERNEL_DISK) mkpart primary 1 100%
	echfs/echfs-utils -g -p0 $(KERNEL_DISK) quick-format 4096
	echfs-utils -g -p0 $(KERNEL_DISK) import kernel.elf kernel.elf
	echfs-utils -g -p0 $(KERNEL_DISK) import limine.cfg .limine.cfg
	echfs-utils -m -p0 $(KERNEL_DISK) import ./limine/limine.sys limine.sys
	./limine/limine-install-linux-x86_32 $(KERNEL_DISK)

clean:
	rm -f $(OBJS)
	rm -rf iso_root/*
	rmdir iso_root/
	rm -f kernel.elf
	rm *.o
	rm -f tesseract.iso

iso:
	sh scripts/iso.sh

asm:
	nasm -f elf32 kernel/src/entry.asm -o entry.o
	nasm kernel/src/arch/i386/gdt.asm -f elf32 -o gdt.o
	nasm kernel/src/arch/i386/interrupts.asm -f elf32 -o interrupts.o
	nasm kernel/src/arch/i386/idt.asm -f elf32 -o idt.o

run:
	make iso
	qemu-system-i386 -m 128M -s -device pvpanic -enable-kvm -serial stdio -d cpu_reset -cdrom ./tesseract.iso
