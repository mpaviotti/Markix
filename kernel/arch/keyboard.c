#include "intel.h"
#include "idt.h"
#include "pic8259.h"
#include "keyboard.h"

/* Disabilita la tastiera */
void disable_keyb(){
  int temp = inportb(0x61);
  outportb(temp | 0x80, 0x61);  /* Disable */
}

/* Abilita la tastiera */
void enable_keyb(){
  unsigned char ch;
  ch = inportb(0x61);
  outportb(ch & 0x7F, 0x61);
}

/* Interrupt handler : legge il codice 
   del tasto quando arriva l'interrupt */
void keyboard_handler(void){
  unsigned int flags;
  unsigned char ch;
  char scancode, temp;

  save(flags);
  cli();
  puts("\n");
  scancode = inportb(0x60);
  putc(scancode);
  puts("\n");
  eofi(PIC1_COMMAND);
  restore(flags); 
  sti();
}

/* Inizializza l'interrupt della tastiera */
void keyboard_init(void){
  ins_handler(1, keyboard_handler);
  enable_keyb();
  enable_irq(1, PIC1_DATA);
}
