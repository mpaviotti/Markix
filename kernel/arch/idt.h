#ifndef __IDT_H
#define __IDT_H

/* Dimensione ed altre variabili che 
   riguardano la IDT */
#define DIM_IDT 256
#define N_IRQ 16
#define N_TRAP 16

/* Opzioni per il campo options
   del descrittore della IDT */
#define EXCEPTION_OPT 0x470
#define IRQ_OPT  0x470

/* Questo è il formato del 
   descrittore della IDT */
typedef struct idt_descr{
  unsigned short int offset0_15;
  unsigned short int segment;
  unsigned short int not_used: 5;
  unsigned short int options: 11;
  unsigned short int offset16_31;
} idt_table;

/* Definite in intel.S e scritte in ASM*/
extern void save(int flags);
extern void restore(int flags);

/*Inizializza la IDT */
void init_int(void);


#endif
