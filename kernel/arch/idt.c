#include <glo.h>
#include "idt.h"
#include "intel.h"
#include "pic8259.h"

static int nestexc = 0;
idt_table idt[DIM_IDT];
void (*irq_handlers[N_IRQ])(void);

/* Imposta la IDT passando l'indirizzo 
   dei valori (size+indirizzo) 
   da mettere nel IDTR */
void set_idt(idt_table *base, int number){
  unsigned int idt_reg[2];
  idt_reg[0] = (number * 8) << 16;
  idt_reg[1] = (unsigned int)base;
  
  load_idt((char *)idt_reg+2);
}

/* Panic */
void panic(){
  puts("\n\nPanic.\n");
}

/* Stampa lo stato dello stack
   per aiutare il debugging */
void default_exception(void){
  int i;
  unsigned int *stack;
  if (nestexc > 1){
    panic();
    return;
  }

  nestexc++;

  stack = stack_dump();
  
  for(i = stack; i <= 0xFFFF; i++){
    putex(*(stack+i));
  }

  nestexc--;
  return;
}


void exception0(void){
  puts("\n\n #Exception0#: Division By Zero\n");
  default_exception();
}


void exception1(void){
  puts("\n\n #Exception1#: Exception of Debug\n");
  default_exception();
}


void exception2(void){
  puts("\n\n #Exception2#: NMI !!!\n");
  default_exception();
}


void exception3(void){
  puts("\n\n #Exception3#: Breakpoint\n");
  default_exception();
}



void exception4(void){
  puts("\n\n #Exception4#: Overflow\n");
  default_exception();
}


void exception5(void){
  puts("\n\n #Exception5#: Bound Range Exceeded\n");
  default_exception();

}


void exception6(void){
  puts("\n\n #Exception6#: Invalid Opcode\n");
  //default_exception();
  //iret();
}


void exception7(void){
  puts("\n\n #Exception7#: Coprocessor Not Available\n");
  default_exception();
}



void exception8(void){
  puts("\n\n #Exception8#: Double Fault\n");
  default_exception();
}


void exception9(void){
  puts("\n\n #Exception9#: Coprocessor Segment Overrun\n");
  default_exception();
}


void exception10(void){
  puts("\n\n #Exception10#: Invalid Task State Segment\n");
  default_exception();
}


void exception11(void){
  puts("\n\n #Exception11#: Segment Not Present\n");
  default_exception();
}


void exception12(void){
  puts("\n\n #Exception12#: Stack Fault\n");
  default_exception();
}


void exception13(void){
  puts("\n\n #Exception13#: General Protection\n");
  default_exception();

}


void exception14(void){
  puts("\n\n #Exception14#: Page Fault\n");
  default_exception();

}


void exception15(void){
  puts("\n\n #Exception15#: UNKNOWN ?????\n");
  default_exception();

}

/* Default handler per gli interrupt HARDWARE */
void default_handler(void){
  puts("\n\n Default handler\n");
}

/* Funzione generica per inizializzare il descrittore
   all'indice 'index' della IDT*/
void init_descr(void (*handler)(void), int index, unsigned short opt){
  if(index < DIM_IDT){
    idt[index].offset0_15 = (unsigned int)handler & 0xFFFF;
    idt[index].offset16_31 = (unsigned int)handler >> 16;
    idt[index].segment = CS_SELECTOR;
    idt[index].options = opt;
  } else {
    puts("Interrupt non valido");
  }
}

/* Funzione specifica per gli IRQ */
void ins_handler(char irq, void (*handler)(void)){
  init_descr(handler, irq+32, IRQ_OPT);
}

/* Inizializza la IDT impostanto EXCEPTIONS 
   e INTERRUPT HARDWARE, alla fine chiama set_idt
   per impostare il registro IDTR.
 */
void init_int(void){
  int i, j;
  long flags;

  save(flags); 
  cli();

  init_pic8259();

  init_descr(exception0, 0, EXCEPTION_OPT);
  init_descr(exception1, 1, EXCEPTION_OPT);
  init_descr(exception2, 2, EXCEPTION_OPT);
  init_descr(exception3, 3, EXCEPTION_OPT);
  init_descr(exception4, 4, EXCEPTION_OPT);
  init_descr(exception5, 5, EXCEPTION_OPT);
  init_descr(exception6, 6, EXCEPTION_OPT);
  init_descr(exception7, 7, EXCEPTION_OPT);
  init_descr(exception8, 8, EXCEPTION_OPT);
  init_descr(exception9, 9, EXCEPTION_OPT);
  init_descr(exception10, 10, EXCEPTION_OPT);
  init_descr(exception11, 11, EXCEPTION_OPT);
  init_descr(exception12, 12, EXCEPTION_OPT);
  init_descr(exception13, 13, EXCEPTION_OPT);
  init_descr(exception14, 14, EXCEPTION_OPT);
  init_descr(exception15, 15, EXCEPTION_OPT);

  for(i = 0; i < 16; i++){
    irq_handlers[i] = default_handler;
    init_descr(irq_handlers[i], i+32, IRQ_OPT);
  }

  set_idt(idt, DIM_IDT);

  restore(flags);
}


