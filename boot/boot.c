#include "elf.h"
#include "x86.h"

#define SECTSIZE    512
#define ELFHDR      ((struct elfhdr*) 0x10000)

void disk_read_sector(void *, unsigned int);
void disk_read(unsigned int, unsigned int, unsigned int);
void disk_wait_ready(void);

void loader(void)
{
    struct proghdr *ph, *eph;
    
    disk_read((unsigned int) ELFHDR, SECTSIZE*8, 0);

    if(ELFHDR->magic != ELF_MAGIC)
        goto bad;
    
    ph = (struct proghdr*) ((unsigned char*) ELFHDR + ELFHDR->phoff);
    eph = ph + ELFHDR->phnum;
    for(; ph < eph; ph++)
        disk_read(ph->va, ph->memsz, ph->offset);

  ((void(*)(void)) (ELFHDR->entry))();

bad:
    while(1);
}
