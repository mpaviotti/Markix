#ifndef __SCREEN_H
#define __SCREEN_H

#define MEMORY_ADDRESS 0xB8000
#define NR_COLS 80
#define NR_ROWS 25

extern void init_screen();
extern void putc(char c);
extern void puts(char *str);
extern void putb(unsigned char c);
extern void putex(unsigned int n);
#endif
