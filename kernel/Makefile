include ../make.rules

OBJ	= main.o screen.o string.o math.o utils.o

all: $(OBJ) arch.o

arch.o:
	@ make  -C arch/ all
clean:
	cd arch && $(MAKE) clean
	@ rm -f *.img *.bin *.map *.iso *.o
	@ rm -f $(OBJ)


.S.o:
	@ $(CC) $(CFLAGS) -I ../include/ -o $@ $< $(shell if test "$(DEBUG)" = "yes" ; then echo "-DDEBUG"; fi)

.c.o:
	@ $(CC) $(CFLAGS) -I ../include/ -o $@ $< $(shell if test "$(DEBUG)" = "yes" ; then echo "-DDEBUG"; fi)
