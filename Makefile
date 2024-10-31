CC=gcc -c
LD=ld
CFLAGS=-fomit-frame-pointer -O -nostdlib -fno-builtin -march=i386 -nostdinc 
LDFLAGS=-Bstatic -nostdlib -nostartfiles -nodefaultlibs
OBJ=boot/start.o main.o interrupt/pic8259.o 
SOURCES=boot/boot.asm

all: $(SOURCES)

	@ make clean	

	nasm -fbin boot/boot.asm -o boot/boot.bin
	cp boot/boot.bin kernelbin

hdisk: cleanhdisk
	dd if=/dev/zero of=30M.sample bs=512 count=62730

cleanhdisk:
	@ rm -f 30M.sample

run: all

	bochs -q 'ata0: enabled=1, ioaddr1=0x1f0, ioaddr2=0x3f0, irq=14'  'ata0-master: type=disk, path="30M.sample", mode=flat, cylinders=615, heads=6, spt=17, translation=lba' 'floppya: 1_44="./kernelbin", status=inserted' 'boot: floppy'

.PHONY: clean install

clean:
	@ rm -f boot/boot.bin
	@ rm -f *.img *.bin *.map *.iso *~ kernelbin
	@ rm -f $(OBJ)

install: all
	dd if=kernelbin of=/dev/fd0