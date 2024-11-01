#ifndef __GDT_H
#define __GDT_H


#define GDT_MAX_ENTRY 	8192
#define USE_N_ENTRY 6
#define GDT_ENTRY_DIM	8

/** Attributi per i descrittori della GDT **/
#define D_PRESENT	0x80

#define DPL_0		0x00		//Descriptor Privilege Livel 0 (massimo privilegio).
#define DPL_1		0x20		//Descriptor Privilege Level 1.
#define DPL_2		0x40		//Descriptor Privilege Level 2.
#define DPL_3		0x60		//Descriptor Privilege Level 3 (minimo privilegio).

#define S			0x10

#define EXECUTABLE 0x8

#define EXPANSION 0x4

#define WRITE_READ 0x2

#define GRANULARITY 0x8
#define DEFAULT_SIZE 0x4

#define K_CODE_ATTR ((D_PRESENT | S | EXECUTABLE | WRITE_READ ) | DPL_0)
#define K_DATA_ATTR  ((D_PRESENT | S  | WRITE_READ ) | DPL_0)

#define USR_CODE_ATTR ((D_PRESENT | S | EXECUTABLE | WRITE_READ ) | DPL_3)
#define USR_DATA_ATTR  ((D_PRESENT | S  | WRITE_READ ) | DPL_3)

#define TSS_ATTR ( D_PRESENT | DPL_0 | EXECUTABLE | 1)

#define FLAGS (GRANULARITY | DEFAULT_SIZE)
#define TSS_FLAGS 0

#define K_CS		0x08
#define K_DS		0x10

#define USR_CS		0x18 | USER_PRIVILEGE
#define USR_DS		0x20 | USER_PRIVILEGE

#define SUPERVISOR_PRIVILEGE 0
#define USER_PRIVILEGE 3

/* Formato della entry all'interno della GDT */
typedef struct __gdt_entry{
  unsigned short int limit0_15;
  unsigned short int base0_15;
  unsigned char base16_23;
  unsigned char access;
  unsigned int limit16_19:4;
  unsigned int flags:4;
  unsigned char base24_31;
} __attribute__((packed)) gdt;

//Struttura della TSS. Una TSS e' di 103 byte + la bitmap_io_permission
typedef struct x86_TSS
{
	unsigned int	link;
	unsigned int	esp0;
	unsigned short	ss0, __ss0h;
	unsigned int	esp1;
	unsigned short	ss1, __ss1h;
	unsigned int	esp2;
	unsigned short	ss2, __ss2h;
	unsigned int	cr3;
	unsigned int	eip;
	unsigned int	eflags;
	unsigned int	eax, ecx, edx, ebx;
	unsigned int	esp;
	unsigned int	ebp;
	unsigned int	esi;
	unsigned int	edi;
	unsigned short	es, __esh;
	unsigned short	cs, __csh;
	unsigned short	SS, __ssh;
	unsigned short	ds, __dsh;
	unsigned short	fs, __fsh;
	unsigned short	gs, __gsh;
	unsigned short	ldtr, __ldtrh;
	unsigned short	trace, IO_bitmap_offset;
	
	unsigned int	bitmap_io_permission[8192/32];
}tss;


/* TSS Segment 
typedef volatile struct __tss_segment {
    unsigned short   link;
    unsigned short   link_h;

    unsigned int   esp0;
    unsigned short   ss0;
    unsigned short   ss0_h;

    unsigned int   esp1;
    unsigned short   ss1;
    unsigned short   ss1_h;

    unsigned int   esp2;
    unsigned short   ss2;
    unsigned short   ss2_h;

    unsigned int   cr3;
    unsigned int   eip;
    unsigned int   eflags;

    unsigned int   eax;
    unsigned int   ecx;
    unsigned int   edx;
    unsigned int    ebx;

    unsigned int   esp;
    unsigned int   ebp;

    unsigned int   esi;
    unsigned int   edi;

    unsigned short   es;
    unsigned short   es_h;

    unsigned short   cs;
    unsigned short   cs_h;

    unsigned short   ss;
    unsigned short   ss_h;

    unsigned short   ds;
    unsigned short   ds_h;

    unsigned short   fs;
    unsigned short   fs_h;

    unsigned short   gs;
    unsigned short   gs_h;

    unsigned short   ldt;
    unsigned short   ldt_h;

    unsigned short   trap;
    unsigned short   iomap;
} tss;

*/

extern tss tss_segment;

extern void init_gdt(void);
extern void switch_mode();
extern void load_tr(char task_register);
extern void load_gdt(char *gdt);
extern void setup_seg();
#endif
