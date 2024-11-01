#include <gdt.h>
#include <proc.h>

proc proc_table[NR_PROCS];
pid_t cur_proc;

/* Inizializza lo stack per un nuovo processo*/
unsigned int *init_stack(unsigned int *stack_frame, 
			 void (*func) ()){

  stackframe *stack = (stackframe *)(stack_frame + STACK_MAX_SIZE-100);
  stack->eip = (unsigned int) func;
  stack->cs = CS_SELECTOR;
  stack->eflags = DEF_EFLAGS;

  return (unsigned int *)stack;
}

/* Un processo di esempio */
void fittizio(void){
  int i = 0;
  while(1){
    if(i % 1000 == 0){
      puts("1");
      i=0;
    }
    i++;
  }
}

/* Un altro processo di esempio */
void fittizio1(void){
  int i = 0;
  while(1){
    if(i % 1000==0){
      puts("2");
      i=0;
    }
    i++;
  }
}

/* Fa la scansione della tabella dei processi per 
   trovare uno che sia pronto (READY) ad essere eseguito*/
pid_t pickup_proc(){
  pid_t i;
  i=cur_proc;

  do{

    i++;
    i = i % NR_PROCS;

    if(proc_table[i].state == READY){
      return i;
    }
    
  } while(i == cur_proc);

  return 0;
}

/* Passo cruciale del cambio di contesto:

sostituisce lo stack passato da 
interrupt/idt.c: _irq_handler(unsigned int stack) 
con quello del nuovo processo selezionato 
da pickup_proc()

*/
void schedule(unsigned int *stack){

  pid_t temp;
  proc_table[cur_proc].quantum--;

  if(proc_table[cur_proc].quantum <= 0){

    temp = pickup_proc();
    
    //salva lo stack corrente
    proc_table[cur_proc].esp = *stack;
    proc_table[cur_proc].state = READY;
    proc_table[cur_proc].quantum = DEF_QUANTUM;

    cur_proc = temp;
    
    //imposta lo stack del nuovo processo
    *stack = proc_table[cur_proc].esp;
    proc_table[cur_proc].state = RUNNING;
  }
}

/* Trova una entry libera nella tabella dei processi,
   l'indice della tabella è anche il PID */
pid_t free_pid(){
  int i = 0;

  for(i = 0; i < NR_PROCS; i++){    
    if(proc_table[i].state == FREE){
      return i;
    }
  }
  return -1;
}

/* Inserisce nella tabella un nuovo processo */
int enqueue(void (*proc)(void), char *name){
  pid_t pid = free_pid();

  unsigned int esp = (unsigned int)init_stack(
			    proc_table[pid].stack_frame, proc);
  proc_table[pid].esp = esp;
  proc_table[pid].quantum = DEF_QUANTUM;
  proc_table[pid].state = READY;

  strcpy(proc_table[pid].name, name);
}

/* Inizializza lo scheduler */
void init_scheduler(void){
  pid_t i;
  for(i = 0; i < NR_PROCS; i++){
    proc_table[i].state = FREE;
  }
  cur_proc = KERNEL_PROC;
  proc_table[cur_proc].state = RUNNING;
  proc_table[cur_proc].quantum = DEF_QUANTUM;

}

