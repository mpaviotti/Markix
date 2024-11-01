
#include <arch/asm.h>
#include <interrupt/pic8259.h>
#include <interrupt/pit8253.h>

/* Handler del timer */
void timer_handler(void){
  static long ticks;

  ticks++;

  eoi(PIC1_COMMAND);
}

/* Inizializza il PIT */ 
void init_pit8253(void){

  unsigned char low_byte, high_byte;

  low_byte = TIMER_CTRL_COMMAND;
  high_byte = TIMER_CTRL_COMMAND >> 8;

  ins_handler(CLOCK_IRQ, timer_handler);
  
  outb(TIMER_CTRL_COMMAND, TIMER_CTRL);
  outb(low_byte, TIMER_CHAN_0);
  outb(high_byte, TIMER_CHAN_0);

  enable_irq(CLOCK_IRQ, PIC1_DATA);

  eoi(PIC1_COMMAND);
  eoi(PIC1_COMMAND);
}
