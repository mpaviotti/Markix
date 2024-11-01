include make.rules

OBJ	= start.o

all:  kernel.o boot.o
	ld -T linker.ld -o kernel.bin boot/loader.o kernel/*.o kernel/arch/*.o kernel/interrupt/*.o kernel/scheduler/*.o kernel/memory/*.o kernel/filesystem/*.o -Map kernel.map
	cat  stage1 stage2 pad kernel.bin > kernelbin

run:	all 
	bochs -q $(BCHFLAGS)

hdisk: cleanhdisk
	dd if=/dev/zero of=30M.sample bs=512 count=62730

cleanhdisk:
	@ rm -f 30M.sample

kernel.o: 
	$(MAKE) -C kernel/ all

boot.o:
	$(MAKE) -C boot/ all

clean:
	cd kernel && $(MAKE) clean
	@ rm -f boot/boot.bin	
	@ rm -f *.img *.bin *.map *.iso *.o
	@ rm -f $(OBJ)
	@ rm -f kernelbin kernelbin2
install: all
	dd if=kernelbin of=/dev/fd0

.S.o:
	@ $(CC) $(CFLAGS) -I ./include/ -o $@  $< 

.c.o:
	@ $(CC) $(CFLAGS) -I ./include/ -o $@  $< 