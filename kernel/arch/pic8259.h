#ifndef __PIC8259_H
#define __PIC8259_H

#define PIC1		0x20
#define PIC2		0xA0
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

#define IRQ0 PIC1
#define IRQ8 (PIC1+8)

void init_pic8259();
void enable_irq(char irq, char port);
void disable_irq(char irq, char port);
void eofi(char port);
#endif

