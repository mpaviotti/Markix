#ifndef __IDT_H
#define __IDT_H

typedef struct idt_descr{
  unsigned short int offset0_15;
  unsigned short int segment;
  unsigned short int not_used: 5;
  unsigned short int options: 11;
  unsigned short int offset16_31;
} idt_table;

extern void save(int flags);
extern void restore(int flags);
extern void load_idt(int* reg);

void init_int(void);

void trap0();
void trap1();
void trap2(void);
void trap3(void);
void trap4(void);
void trap5(void);
void trap6(void);
void trap7(void);
void trap8(void);
void trap9(void);
void trap10(void);
void trap11(void);
void trap12(void);
void trap13(void);
void trap14(void);
void trap15(void);

void default_handler(void);
#endif
