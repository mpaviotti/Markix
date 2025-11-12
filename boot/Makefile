include ../make.rules

OBJ	= start.o

all: $(OBJ)
	nasm -f bin boot.asm -o boot.bin

clean:
	@ rm -f *.img *.bin *.map *.iso *.o
	@ rm -f $(OBJ)

.S.o:
	@ $(CC) $(CFLAGS) -I ../include/ -o $@ $< $(shell if test "$(DEBUG)" = "yes" ; then echo "-DDEBUG"; fi)

.c.o:
	@ $(CC) $(CFLAGS) -I ../include/ -o $@ $< $(shell if test "$(DEBUG)" = "yes" ; then echo "-DDEBUG"; fi)
