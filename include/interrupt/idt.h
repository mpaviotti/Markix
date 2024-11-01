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

extern void isr_default(void);
extern void isr_common(void);
extern void isr_0(void);
extern void isr_1(void);
extern void isr_2(void);
extern void isr_3(void);
extern void isr_4(void);
extern void isr_5(void);
extern void isr_6(void);
extern void isr_7(void);
extern void isr_8(void);
extern void isr_9(void);
extern void isr_10(void);
extern void isr_11(void);
extern void isr_12(void);
extern void isr_13(void);
extern void isr_14(void);
extern void isr_15(void);
extern void isr_16(void);
extern void isr_17(void);
extern void isr_18(void);
extern void isr_32(void);
extern void isr_33(void);
extern void isr_34(void);
extern void isr_35(void);
extern void isr_36(void);
extern void isr_37(void);
extern void isr_38(void);
extern void isr_39(void);
extern void isr_40(void);
extern void isr_41(void);
extern void isr_42(void);
extern void isr_43(void);
extern void isr_44(void);
extern void isr_45(void);
extern void isr_46(void);
extern void isr_47(void);
extern void isr_48(void);


/*Inizializza la IDT */
extern void init_idt(void);
extern void ins_handler(char irq, void (*handler)(void));

#endif
