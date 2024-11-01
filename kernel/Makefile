include ../make.rules

OBJ	= kmain.o main.o screen.o string.o math.o utils.o

all: $(OBJ) interrupt.o arch.o scheduler.o \
	memory.o filesystem.o

interrupt.o:
	@ make -C interrupt/ all

arch.o:
	@ make  -C arch/ all

scheduler.o:
	@ make -C scheduler/ all

memory.o:
	@ make -C memory/ all

filesystem.o:
	@ make -C filesystem/ all

clean:
	cd arch && $(MAKE) clean
	cd interrupt && $(MAKE) clean
	cd scheduler && $(MAKE) clean
	cd memory && $(MAKE) clean
	cd filesystem && $(MAKE) clean

	@ rm -f *.img *.bin *.map *.iso *.o
	@ rm -f $(OBJ)


.S.o:
	@ $(CC) $(CFLAGS) -I ../include/ -o $@ $< $(shell if test "$(DEBUG)" = "yes" ; then echo "-DDEBUG"; fi)

.c.o:
	@ $(CC) $(CFLAGS) -I ../include/ -o $@ $< $(shell if test "$(DEBUG)" = "yes" ; then echo "-DDEBUG"; fi)
