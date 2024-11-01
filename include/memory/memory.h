#ifndef __MEMORY_H
#define __MEMORY_H

#define START_EXT_MEM 0x1000000 //start from 16MB
#define TOTAL_MEM 0x200000 //Total memory

#define MEM_BITMAP_SIZE 4096
#define PAGE_SIZE 4096

extern void init_memory(void);
extern void *kmalloc(int size);

extern unsigned int phys_mem_size;
#endif

