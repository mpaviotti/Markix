#include <screen.h>

#include <interrupt/keyb8042.h>
#include <interrupt/pic8259.h>
#include <interrupt/pit8253.h>
#include <interrupt/idt.h>

#include <scheduler/proc.h>


int main(){
  int i;
  init_screen();

  init_scheduler();
  enqueue(fittizio, "fittizio");
  enqueue(fittizio1, "fittizio1");

  puts("Markix \n");

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

  while(1){
    if(i % 1000 == 0){
      puts("0");
      i=0;
    }
    i++;
  }
  return 0;

}
