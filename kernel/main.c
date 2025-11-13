#include <screen.h>

#include <interrupt/keyb8042.h>
#include <interrupt/pic8259.h>
#include <interrupt/pit8253.h>
#include <interrupt/idt.h>

#include <scheduler/proc.h>


/* Un processo di esempio */
void thread1(void){
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
void thread2(void){
  int i = 0;
  while(1){
    if(i % 1000==0){
      puts("2");
      i=0;
    }
    i++;
  }
}

int main(){
  int i;
  init_screen();

  init_scheduler();

  puts("----------------------------------- \n");
  puts("|            Markix OS             | \n");
  puts("----------------------------------- \n");

  init_pic8259();
  puts("Impostazione degli iterrupt..");
  init_idt();
  puts("OK.\n");

  puts("Abilitazione della tastiera..");
  init_keyb8042();
  puts("OK.\n");

  puts("Abilitazione del timer..");
  init_pit8253();
  puts("OK.\n");

  enqueue(thread1, "Thread 1");
  enqueue(thread2, "Thread 2");

  while(1){
    if(i % 1000 == 0){
      i=0;
    }
    i++;
  }
  return 0;

}

