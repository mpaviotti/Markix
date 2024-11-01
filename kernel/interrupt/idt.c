
#include <gdt.h>
#include <arch/asm.h>

#include <interrupt/idt.h>
#include <interrupt/pic8259.h>
#include <scheduler/proc.h>

static int nestexc = 0;

/* IDT */
idt_table idt[DIM_IDT];

/* Contiene gli handler per gli interrupt di tipo HW */
void (*irq_handlers[N_IRQ])(void);

/*Descrizione delle exceptions */
char exceptions[19][100] = {"Division by zero\n",
		     "Debug Exception\n",
		     "Non-maskable interrupt\n",
		     "Breakpoint\n",
		     "Overflow\n",
		     "Bounds check\n",
		     "Invalid opcode\n",
		     "Coprocessor not avaiable\n",
		     "Double fault\n",
		     "Coprocessor segment overrun\n",
		     "Invalid TSS\n",
		     "Segment not present\n",
		     "Stack exception\n",
		     "General Protection\n",
		     "Page fault\n",
		     "\n",
		     "Coprocessor error\n",
		     "Alignment check exception\n",
		     "Machine check exception\n"
		     };

/* Imposta la IDT passando l'indirizzo 
   dei valori (size+indirizzo) 
   da mettere nel IDTR */
void set_idt(idt_table *base, int number){
  unsigned int idt_reg[2];
  idt_reg[0] = (number * 8) << 16;
  idt_reg[1] = (unsigned int)base;
  
  load_idt((char *)idt_reg+2);
}


/* Stampa lo stato dello stack
   per aiutare il debugging */
void default_exception(char *str){
  #ifdef DEBUG
  unsigned int *stack, *i;

  if (nestexc > 1){
    return;
  }

  nestexc++;

  stack = stack_dump(0x00000000);
  putex(stack);
  for(i = 0x0009FFF0; i >= stack; i--){
    puts("\n0x");
    putex(i);
    puts(" 0x");
    putex(*i);
    if(i== stack+4){
      puts(str);
    }
  }

  nestexc--;

#endif
  while(1);
  return;
}

/* Default handler per gli interrupt*/
void default_handler(void){
  //puts("\n\n Default handler\n");
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
  irq_handlers[irq] = handler;
}

/* Preleva il numero dell'interrupt 
dallo stack, e chiama il relativo handler*/
void _irq_handler(unsigned int stack){
  unsigned int *stck;
  int irq;

  stck = (unsigned int *)stack;
  irq = *(stck+8);

  /*Exception*/
  if(irq > 0 && irq < 32){
    puts(exceptions[irq]);
    while(1);
    /* Interrupt Hardware */
  } else if(irq >= 32){
    irq -= 32;

    (*irq_handlers[irq])(); 
  
    if(irq == 1){
      schedule(&stack);
    }
  }
}


/* Inizializza la IDT impostando EXCEPTIONS 
   e INTERRUPT HARDWARE, alla fine chiama set_idt
   per impostare il registro IDTR.
 */
void init_idt(void){
  int i, j;

  cli();

  for(i = 0; i < 16; i++){
    irq_handlers[i] = default_handler;
  }

  init_descr(isr_0, 0, EXCEPTION_OPT);  
  init_descr(isr_1, 1, EXCEPTION_OPT);  
  init_descr(isr_2, 2, EXCEPTION_OPT);  
  init_descr(isr_3, 3, EXCEPTION_OPT);  
  init_descr(isr_4, 4, EXCEPTION_OPT);  
  init_descr(isr_5, 5, EXCEPTION_OPT);  
  init_descr(isr_6, 6, EXCEPTION_OPT);  
  init_descr(isr_7, 7, EXCEPTION_OPT);  
  init_descr(isr_8, 8, EXCEPTION_OPT);  
  init_descr(isr_9, 9, EXCEPTION_OPT);  
  init_descr(isr_10, 10, EXCEPTION_OPT);  
  init_descr(isr_11, 11, EXCEPTION_OPT);  
  init_descr(isr_12, 12, EXCEPTION_OPT);  
  init_descr(isr_13, 13, EXCEPTION_OPT);  
  init_descr(isr_14, 14, EXCEPTION_OPT);  
  init_descr(isr_15, 15, EXCEPTION_OPT);  
  init_descr(isr_16, 16, EXCEPTION_OPT);  
  init_descr(isr_17, 17, EXCEPTION_OPT);  
  init_descr(isr_18, 18, EXCEPTION_OPT);  
  for(i = 19; i < 32; i++){
    init_descr(isr_default, i, EXCEPTION_OPT);
  }
  init_descr(isr_32, 32, IRQ_OPT);
  init_descr(isr_33, 33, IRQ_OPT);
  init_descr(isr_34, 34, IRQ_OPT);
  init_descr(isr_35, 35, IRQ_OPT);
  init_descr(isr_36, 36, IRQ_OPT);
  init_descr(isr_37, 37, IRQ_OPT);
  init_descr(isr_38, 38, IRQ_OPT);
  init_descr(isr_39, 39, IRQ_OPT);
  init_descr(isr_40, 40, IRQ_OPT);
  init_descr(isr_41, 41, IRQ_OPT);
  init_descr(isr_42, 42, IRQ_OPT);
  init_descr(isr_43, 43, IRQ_OPT);
  init_descr(isr_44, 44, IRQ_OPT);
  init_descr(isr_45, 45, IRQ_OPT);
  init_descr(isr_46, 46, IRQ_OPT);
  init_descr(isr_47, 47, IRQ_OPT);
  init_descr(isr_48, 48, IRQ_OPT);

  for(i = 49; i < 256; i++){
    init_descr(isr_default, i, IRQ_OPT);
  }
  set_idt(idt, DIM_IDT);

}

