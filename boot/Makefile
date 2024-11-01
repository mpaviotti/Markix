
all: 
	nasm -f elf -o loader.o loader.S
	nasm -fbin boot.asm -o boot.bin

clean: 

	rm -f *.o
	rm -f *.bin
