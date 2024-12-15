CC = i686-elf-gcc
AS = i686-elf-as
LD = i686-elf-gcc
GRUB = grub-mkrescue
CFLAGS = -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -nostdlib

all: gamaOS.iso

boot.o: boot.s
	$(AS) boot.s -o boot.o

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

gamaOS.bin: boot.o kernel.o
	$(LD) $(LDFLAGS) boot.o kernel.o -o gamaOS.bin -lgcc

gamaOS.iso: gamaOS.bin
	mkdir -p isodir/boot/grub
	cp gamaOS.bin isodir/boot/gamaOS.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	$(GRUB) -o gamaOS.iso isodir

clean:
	rm -rf *.o gamaOS.bin gamaOS.iso isodir

