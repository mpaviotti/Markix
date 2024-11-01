#include <gdt.h>

gdt gdt_table[GDT_MAX_ENTRY];
tss tss_segment;

void gdt_insert(int entry, unsigned int base, 
			   unsigned int limit, 
			   unsigned char access, 
			   unsigned char flags){

  gdt_table[entry].limit0_15 = limit & 0xFFFF;
  gdt_table[entry].limit16_19 = (limit >> 16) & 0x0F;
  gdt_table[entry].base0_15 = base & 0xFFFF;
  gdt_table[entry].base16_23 = (base >> 16) & 0xFF;
  gdt_table[entry].base24_31 = (base >> 24) & 0xFF;
  gdt_table[entry].access = access;
  gdt_table[entry].flags = flags;

}

void init_gdt(void){
  int i;
  long flags;

  asm("cli"); //Disabilito gli interrupt
 
  for(i = 0; i < GDT_MAX_ENTRY; i++){
    gdt_table[i].limit0_15 = 0;
    gdt_table[i].limit16_19 =	0;
    gdt_table[i].base0_15 = 0;
    gdt_table[i].base16_23 = 0;
    gdt_table[i].base24_31 = 0;
    gdt_table[i].access = 0;
    gdt_table[i].flags = 0;
 }
  
  gdt_insert(1, 0, 0xFFFFFF, K_CODE_ATTR, FLAGS);
  gdt_insert(2, 0, 0xFFFFFF, K_DATA_ATTR, FLAGS);
  gdt_insert(3, 0, 0xFFFFFF, USR_CODE_ATTR, FLAGS);
  gdt_insert(4, 0, 0xFFFFFF, USR_DATA_ATTR, FLAGS);
  gdt_insert(5, (unsigned)&tss_segment, sizeof(tss), TSS_ATTR, TSS_FLAGS);

  memset(&tss_segment, 0x11, sizeof(tss_segment));

  tss_segment.ss0 = K_DS;
  //tss_segment.iomap = (unsigned short) sizeof(tss);
  tss_segment.IO_bitmap_offset = 104;

  for(i=0; i<(8192/32);i++){
    tss_segment.bitmap_io_permission[i] = 0x00000000;
  }

  gdt_install(gdt_table, GDT_MAX_ENTRY);
  setup_seg();
  return;
}

void gdt_install(gdt* base, unsigned int num_desc) {

  unsigned int GDT_reg[2];
	
  GDT_reg[0]=(num_desc*8-1) << 16;
  GDT_reg[1]=(unsigned int)base;

  load_gdt((char *)GDT_reg+2);
  load_tr(0x28);

}



