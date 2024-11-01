include make.rules

OBJ	= start.o

all:  kernel.o boot.o $(OBJ)

	$(LD) $(LDFLAGS) -e _start --oformat binary \
		-o kernel.bin $(OBJ) kernel/*.o \
		kernel/arch/*.o -Ttext 0x10000 \
		-Map kernel.map

	cat boot/boot.bin kernel.bin > kernelbin

hdisk: cleanhdisk
	dd if=/dev/zero of=30M.sample bs=512 count=62730

cleanhdisk:
	@ rm -f 30M.sample

run: all
	bochs -q 'ata0: enabled=1, ioaddr1=0x1f0, ioaddr2=0x3f0, irq=14'  'ata0-master: type=disk, path="30M.sample", mode=flat, cylinders=615, heads=6, spt=17, translation=lba' 'floppya: 1_44="./kernelbin", status=inserted' 'boot: floppy'


kernel.o: 
	$(MAKE) -C kernel/ all

boot.o:
	$(MAKE) -C boot/ all

clean:
	cd kernel && $(MAKE) clean

	@ rm -f boot/boot.bin
	@ rm -f *.img *.bin *.map *.iso *.o kernelbin
	@ rm -f $(OBJ)

install: all
	dd if=kernelbin of=/dev/fd0

.S.o:
	@ $(CC) $(CFLAGS) -I ./include/ -o $@ $< $(shell if test "$(DEBUG)" = "yes" ; then echo "-DDEBUG"; fi)

.c.o:
	@ $(CC) $(CFLAGS) -I ./include/ -o $@ $< $(shell if test "$(DEBUG)" = "yes" ; then echo "-DDEBUG"; fi)
