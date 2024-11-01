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

/* Magic numbers for interrupt controller. */
#define END_OF_INT      0x20	/* code used to re-enable after an interrupt */

/* Fixed system call vector. */
#define SYS_VECTOR        32	/* system calls are made with int SYSVEC */
#define SYS386_VECTOR     33	/* except 386 system calls use this */
#define LEVEL0_VECTOR     34	/* for execution of a function at level 0 */

/* Hardware interrupt numbers. */
#define NR_IRQ_VECTORS    16
#define CLOCK_IRQ          0
#define KEYBOARD_IRQ       1
#define CASCADE_IRQ        2	/* cascade enable for 2nd AT controller */
#define ETHER_IRQ          3	/* default ethernet interrupt vector */
#define SECONDARY_IRQ      3	/* RS232 interrupt vector for port 2 */
#define RS232_IRQ          4	/* RS232 interrupt vector for port 1 */
#define XT_WINI_IRQ        5	/* xt winchester */
#define FLOPPY_IRQ         6	/* floppy disk */
#define PRINTER_IRQ        7
#define CMOS_CLOCK_IRQ     8
#define KBD_AUX_IRQ       12	/* AUX (PS/2 mouse) port in kbd controller */
#define AT_WINI_0_IRQ     14	/* at winchester controller 0 */
#define AT_WINI_1_IRQ     15	/* at winchester controller 1 */

void init_pic8259();
void enable_irq(char irq, char port);
void disable_irq(char irq, char port);
void eofi(char port);
#endif

