#include <screen.h>

#include <interrupt/keyb8042.h>
#include <interrupt/pic8259.h>
#include <interrupt/pit8253.h>
#include <interrupt/idt.h>

#include <memory/memory.h>
#include <scheduler/proc.h>


int main(){
  int i;
  init_screen();
  puts("------------------------------------------------------\n");
  puts("|                      Markix                        |\n");
  puts("------------------------------------------------------\n");
  
  puts("\n\nSistema operativo opensource, \ncreato da Marco Paviotti\n\n\n");

  puts("\nCreazione della tabella di allocazione della memoria...");
  init_memory();
  puts("OK.");

  puts("\nInizializzazione della tabella dei processi...");
  init_scheduler();
  puts("OK.");

  enqueue(fittizio, "fittizio");
  enqueue(fittizio1, "fittizio1");
  
  puts("\nImpostazione del PIC...");
  init_pic8259();
  puts("OK.");

  puts("\nInizializzazione degli handler nella IDT...");
  init_idt();
  puts("OK.");

  puts("\nAbilitazione dell'handler della tastiera..");
  init_keyb8042();
  puts("OK.");

  puts("\nAbilitazione dell'handler del timer..");
  init_pit8253();
  puts("OK.");

  while(1){
    if(i % 1000 == 0){
      //      puts("0");
      i=0;
    }
    i++;
  }
  return 0;

}
