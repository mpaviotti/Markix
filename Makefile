include make.rules

all:

	@ make clean	

	nasm -fbin boot/boot.asm -o boot/boot.bin

	$(LD) $(LDFLAGS) -e _start --oformat binary -o markix.bin $(OBJ) interrupt/*.o -Ttext 0x10000 -Map kernel.map

	@ make -I ../include/ $(OBJ)

	@ ld $(LDFLAGS) -e _start --oformat binary -o kernel.bin $(OBJ) -Ttext 0x10000 -Map kernel.map

	cat boot/boot.bin kernel.bin > kernelbin

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
