#include <arch/asm.h>
#include <interrupt/pic8259.h>

/* Iniziliazza opportunamente il PIC
   e disabilita preventivamente 
   tutti gli interrupt*/
void init_pic8259(){
  int i;
  long flags;

  cli();

  //ICW1 - Comando per inizializzare la sequenza 
  //di inizializzazione  - 00010001
  outb(0x11, PIC1_COMMAND);
  outb(0x11, PIC2_COMMAND);

  //ICW2 - Offset nella IDT da cui partire
  outb(IRQ0, PIC1_DATA);
  outb(IRQ8, PIC2_DATA);

  //ICW3 - Pin sul quale è collegato lo Slave
  outb(0x04, PIC1_DATA);
  outb(0x02, PIC2_DATA);

  //ICW4 - Modalità IA
  outb(0x01, PIC1_DATA);
  outb(0x01, PIC2_DATA);
	
	
  for(i=0; i <= 7; i++){
    disable_irq(i, PIC1_DATA);
  }	

  for(i=0; i <= 7; i++){
    disable_irq(i, PIC2_DATA);
  }

}

/* Abilita l'IRQ */
void enable_irq(char irq, char port){
  cli();
  char byte;
  
  byte = inb(port);
  byte = byte & ~(0x01 << irq);
  outb(byte, port);
  sti();
}

/* Disabilita l'IRQ */
void disable_irq(char irq, char port){
  char byte;
  
  byte = inb(port);
  byte = byte | (0x01 << irq);
  outb(byte, port);
}

void eofi(char port){
  outb(END_OF_INT, port);
}
