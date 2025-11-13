include make.rules

OBJ	= start.o

all:  kernel.o boot.o $(OBJ)

	$(LD) $(LDFLAGS) -e _start --oformat binary \
		-o markix.bin $(OBJ) kernel/*.o \
		kernel/arch/*.o kernel/interrupt/*.o kernel/scheduler/*.o \
		-Ttext 0x10000 -Map kernel.map

	cat boot/boot.bin markix.bin > kernel.bin

run: all
	bochs -q -f bochsrc.txt

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
	@ rm -f *.img *.bin *.map *.iso *.o kernelbin kernel.bin
	@ rm -f $(OBJ)

install: all
	dd if=kernelbin of=/dev/fd0

.S.o:
	@ $(CC) $(CFLAGS) -I ./include/ -o $@  $< 

.c.o:
	@ $(CC) $(CFLAGS) -I ./include/ -o $@  $<
