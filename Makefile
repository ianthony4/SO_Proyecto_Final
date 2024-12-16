CC = i686-elf-gcc
AS = i686-elf-as
LD = i686-elf-gcc
GRUB = grub-mkrescue
CFLAGS = -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -nostdlib

SRC = src
INCLUDE = include
BUILD = build

OBJS = $(BUILD)/boot.o $(BUILD)/kernel.o $(BUILD)/memoria.o $(BUILD)/dispositivo.o $(BUILD)/archivo.o

all: $(BUILD)/gamaOS.iso

$(BUILD)/boot.o: $(SRC)/boot.s
	$(AS) $(SRC)/boot.s -o $(BUILD)/boot.o

$(BUILD)/kernel.o: $(SRC)/kernel.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $(SRC)/kernel.c -o $(BUILD)/kernel.o

$(BUILD)/memoria.o: $(SRC)/memoria.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $(SRC)/memoria.c -o $(BUILD)/memoria.o

$(BUILD)/dispositivo.o: $(SRC)/dispositivo.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $(SRC)/dispositivo.c -o $(BUILD)/dispositivo.o

$(BUILD)/archivo.o: $(SRC)/archivo.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $(SRC)/archivo.c -o $(BUILD)/archivo.o

$(BUILD)/gamaOS.bin: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(BUILD)/gamaOS.bin -lgcc

$(BUILD)/gamaOS.iso: $(BUILD)/gamaOS.bin
	mkdir -p isodir/boot/grub
	cp $(BUILD)/gamaOS.bin isodir/boot/gamaOS.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	$(GRUB) -o $(BUILD)/gamaOS.iso isodir

clean:
	rm -rf $(BUILD)/*.o $(BUILD)/*.bin $(BUILD)/*.iso isodir

