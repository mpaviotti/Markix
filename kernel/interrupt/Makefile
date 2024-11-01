include ../../make.rules

OBJ	= pic8259.o pit8253.o keyb8042.o idt.o

all: $(OBJ)

clean:

	@ rm -f *.img *.bin *.map *.iso *.o *~
	@ rm -f $(OBJ)

.S.o:
	@ $(CC) $(CFLAGS) -I ../../include/ -I ../../include/interrupt/ -o $@ $< $(shell if test "$(DEBUG)" = "yes" ; then echo "-DDEBUG"; fi)

.c.o:
	@ $(CC) $(CFLAGS) -I ../../include/ -I ../../include/interrupt/ -o $@ $< $(shell if test "$(DEBUG)" = "yes" ; then echo "-DDEBUG"; fi)

