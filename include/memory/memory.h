#ifndef __MEMORY_H
#define __MEMORY_H

#define START_EXT_MEM 0x100000
#define TOTAL_MEM 0x200000

#define MEM_BITMAP_SIZE 4096
#define PAGE_SIZE 4096

extern void init_memory(void);
extern void *kmalloc(int size);
#endif
