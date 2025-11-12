include make.rules

all: boot.o interrupt.o main.o


	$(LD) $(LDFLAGS) -e _start --oformat binary -o markix.bin boot/start.o main.o interrupt/*.o -Ttext 0x10000 -Map kernel.map

	cat boot/boot.bin markix.bin > kernel.bin

interrupt.o:
	$(MAKE) -C interrupt/ all

boot.o:
	$(MAKE) -C boot/ all


hdisk: cleanhdisk
	dd if=/dev/zero of=30M.sample bs=512 count=62730

cleanhdisk:
	@ rm -f 30M.sample

qemu:
	qemu-system-i386 -fda kernel.bin -boot a -m 32

run: all
	bochs -q 'ata0: enabled=1, ioaddr1=0x1f0, ioaddr2=0x3f0, irq=14'  'ata0-master: type=disk, path="30M.sample", mode=flat, cylinders=615, heads=6, spt=17, translation=lba' 'floppya: 1_44="./kernelbin", status=inserted' 'boot: floppy'

.PHONY: clean install

clean:
	@ rm -f boot/boot.bin
	@ rm -f *.img *.bin *.map *.iso *~ kernelbin
	@ rm -f $(OBJ)

install: boot.bin
	dd if=image.iso of=/dev/fd0


.S.o:
	@ echo "$<: Assembly AT&T"
	@ $(CC) $(CFLAGS) -I ./include/ -o $@ $< $(shell if test "$(DEBUG)" = "yes" ; then echo "-DDEBUG"; fi)
	@ echo " "

.c.o:
	@ echo "$<: Codice C"
	@ $(CC) $(CFLAGS) -I ./include/ -o $@ $< $(shell if test "$(DEBUG)" = "yes"; then echo "-DDEBUG"; fi)
	@ echo " "
