
#include "intel.h"
#include "pic8259.h"


/* Iniziliazza opportunamente il PIC
   e disabilita preventivamente 
   tutti gli interrupt*/
void init_pic8259(){
  int i;
  long flags;

  cli();

  //ICW1 - Comando per inizializzare la sequenza 
  //di inizializzazione  - 00010001
  outportb(0x11, PIC1_COMMAND);
  outportb(0x11, PIC2_COMMAND);

  //ICW2 - Offset nella IDT da cui partire
  outportb(IRQ0, PIC1_DATA);
  outportb(IRQ8, PIC2_DATA);

  //ICW3 - Pin sul quale è collegato lo Slave
  outportb(0x04, PIC1_DATA);
  outportb(0x02, PIC2_DATA);

  //ICW4 - Modalità IA
  outportb(0x01, PIC1_DATA);
  outportb(0x01, PIC2_DATA);
	
	
  for(i=0; i <= 7; i++){
    disable_irq(i, PIC1_DATA);
  }	

  for(i=0; i <= 7; i++){
    disable_irq(i, PIC2_DATA);
  }
}

/* Abilita l'IRQ */
void enable_irq(char irq, char port){
    char byte;

    byte = inportb(port);
    byte = byte & 0xFD;
    outportb(byte, port);
    sti();
}

/* Disabilita l'IRQ */
void disable_irq(char irq, char port){
    char byte;

    byte = inportb(port);
    byte = byte | ~0xFF;
    outportb(0xFF, port);
}

void eofi(char port){
  outportb(0x20, port);
}
