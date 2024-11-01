include ../make.rules

OBJ	= main.o screen.o string.o math.o utils.o

all: $(OBJ) interrupt.o arch.o scheduler.o

interrupt.o:
	@ make -C interrupt/ all

arch.o:
	@ make  -C arch/ all

scheduler.o:
	@ make -C scheduler/ all

clean:
	cd arch && $(MAKE) clean
	cd interrupt && $(MAKE) clean
	cd scheduler && $(MAKE) clean
	@ rm -f *.img *.bin *.map *.iso *.o
	@ rm -f $(OBJ)


.S.o:
	@ $(CC) $(CFLAGS) -I ../include/ -o $@ $< $(shell if test "$(DEBUG)" = "yes" ; then echo "-DDEBUG"; fi)

.c.o:
	@ $(CC) $(CFLAGS) -I ../include/ -o $@ $< $(shell if test "$(DEBUG)" = "yes" ; then echo "-DDEBUG"; fi)
