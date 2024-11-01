#ifndef __PROC_H
#define __PROC_H

#define NR_PROCS 256

/* Indici nella tabella dei processi */
#define KERNEL_PROC 0
#define NO_PROC -1

/* Stati del processo */
#define FREE -1
#define READY 0
#define RUNNING 1
#define BLOCKED 2

#define DEF_QUANTUM 40

#define STACK_MAX_SIZE 0x5000
#define DEF_EFLAGS 0x202

typedef long pid_t;

typedef struct task_state{
  unsigned int edi;	//+0
  unsigned int esi;	//+1
  unsigned int ebp;	//+2
  unsigned int null;	//+3
  unsigned int ecx;	//+4
  unsigned int edx;	//+5
  unsigned int ebx;	//+6
  unsigned int eax;	//+7
  unsigned int isr;
  unsigned int eip;	//+8
  unsigned int cs;	//+9
  unsigned int eflags;	//+10
} stackframe;

typedef struct process{
  unsigned int esp;
  unsigned int stack_frame[STACK_MAX_SIZE];
  
  /* Scheduler-Related informations */
  char name[20];
  int quantum;
  char state:2;

} proc;


extern void init_scheduler(void);
extern void schedule(unsigned int *stack);

extern int enqueue(void (*proc)(void), char *name);

extern void fittizio(void);
extern void fittizio1(void);
#endif
