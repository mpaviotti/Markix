include ../../make.rules

OBJ	= memory.o

all: $(OBJ)

clean:

	@ rm -f *.img *.bin *.map *.iso *.o *~
	@ rm -f $(OBJ)

.S.o:
	@ $(CC) $(CFLAGS) -I ../../include/ -I ../../include/memory/ -o $@ $< 

.c.o:
	@ $(CC) $(CFLAGS) -I ../../include/ -I ../../include/memory/ -o $@ $< 

