include ../../make.rules
OBJ	= intel.o ioport.o interrupt_handlers.o

all: $(OBJ)

clean:

	@ rm -f *.img *.bin *.map *.iso *.o *~
	@ rm -f $(OBJ)

.S.o:
	@ $(CC) $(CFLAGS) -I ../../include/arch/ -I ../../include/ -o $@ $< $(shell if test "$(DEBUG)" = "yes" ; then echo "-DDEBUG"; fi)

.c.o:
	@ $(CC) $(CFLAGS) -I ../../include/arch/ -I ../../include/ -o $@ $< $(shell if test "$(DEBUG)" = "yes" ; then echo "-DDEBUG"; fi)
