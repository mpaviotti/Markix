#include <arch/asm.h>
#include <interrupt/idt.h>
#include <interrupt/pic8259.h>
#include <interrupt/keyb8042.h>


/* Disabilita la tastiera */
void disable_keyb(){
  int temp = inb(0x61);
  outb(temp | 0x80, 0x61);  /* Disable */
}

/* Abilita la tastiera */
void enable_keyb(){
  unsigned char ch;
  ch = inb(0x61);
  outb(ch & 0x7F, 0x61);
}

/* Interrupt handler : legge il codice 
   del tasto quando arriva l'interrupt */
void keyboard_handler(void){
  char scancode;
  char temp;

  scancode = inb(0x60);
  putc(scancode);
  /*
  do{
    temp = inb(0x64);
    if((temp & 0x01) != 0){
      (void)inb(0x60);
      continue;
    }
  } while((temp & 0x02) != 0);
  */		
  eoi(PIC1_COMMAND);
}

/* Inizializza l'interrupt della tastiera */
void init_keyb8042(void){
  ins_handler(KEYBOARD_IRQ, keyboard_handler );
  enable_keyb();
  enable_irq(KEYBOARD_IRQ, PIC1_DATA);
  eoi(PIC1_COMMAND);
  eoi(PIC1_COMMAND);

  int valore, numport=0x60;
  __asm__ volatile ("inb %%dx, %%al ":"=a" (valore):"d" (numport));
}
