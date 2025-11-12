
#include <memory/memory.h>
#include <interrupt/gdt.h>
#include <proc.h>

proc proc_table[NR_PROCS];
pid_t cur_proc;

/* Inizializza lo stack per un nuovo processo */
unsigned int *init_stack(void (*func) ()){

  stackframe *stack = (stackframe *)(kmalloc(STACK_MAX_SIZE) + STACK_MAX_SIZE-sizeof(stackframe)-1);
  stack->gs = (unsigned int)USR_DS;
  stack->fs = (unsigned int)USR_DS;
  stack->es = (unsigned int)USR_DS;
  stack->ds = (unsigned int)USR_DS;

  stack->eip = (unsigned int) func;
  stack->cs = USR_CS;
  stack->eflags = DEF_EFLAGS;

  stack->esp = (unsigned int)(kmalloc(STACK_MAX_SIZE) + STACK_MAX_SIZE);
  stack->ss = USR_DS;
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

/*
   Fa la scansione della tabella dei processi per
   trovare uno che sia pronto (READY) ad essere eseguito
*/
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
    proc_table[cur_proc].k_esp = *stack;
    proc_table[cur_proc].state = READY;
    proc_table[cur_proc].quantum = DEF_QUANTUM;

    cur_proc = temp;

    tss_segment.esp = (unsigned int)proc_table[cur_proc].k_esp;
    tss_segment.esp0 = (unsigned int)proc_table[cur_proc].k_esp;
    tss_segment.esp1 = (unsigned int)proc_table[cur_proc].k_esp;
    tss_segment.esp2 = (unsigned int)proc_table[cur_proc].k_esp;

    //imposta lo stack del nuovo processo
    *stack = proc_table[cur_proc].k_esp;
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

  proc_table[pid].stack = init_stack(proc);
  proc_table[pid].k_esp = (unsigned int)proc_table[pid].stack;
  proc_table[pid].quantum = DEF_QUANTUM;
  proc_table[pid].state = READY;
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

/* TODO: implementare con l'uso del clock */
void sleep(long mills){
  int i;
  for(i = 0; i < mills*1000; i++){
    io_wait();
  }
}
