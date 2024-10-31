CC=gcc -c
LD=ld
CFLAGS=-fomit-frame-pointer -O -nostdlib -fno-builtin -march=i386 -nostdinc 
LDFLAGS=-Bstatic -nostdlib -nostartfiles -nodefaultlibs
OBJ=boot/start.o main.o kernel/screen.o kernel/string.o interrupt/pic8259.o 
SOURCES=boot/start.S main.c kernel/screen.c kernel/string.c interrupt/pic8259.c

all: $(SOURCES)

	@ make clean	

	nasm -fbin boot/boot.asm -o boot/boot.bin

	@ make -I ../include/ $(OBJ)

	@ ld $(LDFLAGS) -e _start --oformat binary -o kernel.bin $(OBJ) -Ttext 0x10000 -Map kernel.map

	cat boot/boot.bin kernel.bin > kernelbin

hdisk: cleanhdisk
	dd if=/dev/zero of=30M.sample bs=512 count=62730

cleanhdisk:
	@ rm -f 30M.sample

run:	all 
	bochs -q 'ata0: enabled=1, ioaddr1=0x1f0, ioaddr2=0x3f0, irq=14'  'ata0-master: type=disk, path="30M.sample", mode=flat, cylinders=615, heads=6, spt=17, translation=lba' 'floppya: 1_44="./kernelbin", status=inserted' 'boot: floppy'


.PHONY: clean install

clean:

	@ rm -f *.img *.bin *.map *.iso *~ kernelbin
	@ rm -f $(OBJ)

install: boot.bin
	dd if=kernelbin of=/dev/fd0

.S.o:
	@ echo "$<: Assembly AT&T"
	@ $(CC) $(CFLAGS) -I ./include/ -o $@ $< $(shell if test "$(DEBUG)" = "yes" ; then echo "-DDEBUG"; fi)
	@ echo " "

.c.o:
	@ echo "$<: Codice C"
	@ $(CC) $(CFLAGS) -I ./include/ -o $@ $< $(shell if test "$(DEBUG)" = "yes"; then echo "-DDEBUG"; fi)
	@ echo " "
