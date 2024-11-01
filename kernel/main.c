#include <screen.h>

#include <interrupt/keyb8042.h>
#include <interrupt/pic8259.h>
#include <interrupt/pit8253.h>
#include <interrupt/idt.h>

#include <memory/memory.h>
#include <scheduler/proc.h>
#include <filesystem/fat.h>

int main(){
  int i;

  init_screen();
 
  puts("------------------------------------------------------\n");
  puts("|                      Markix                        |\n");
  puts("------------------------------------------------------\n");
  
  puts("\n\nSistema operativo opensource, \ncreato da Marco Paviotti\n\n\n");

  puts("\nCreazione della tabella di allocazione della memoria...");
  
  init_memory();

  init_gdt();
  
  puts("\nMemoria riconosciuta: 0x");
  putex(phys_mem_size);
  puts(". OK.");
    
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
    /*
  puts("\nAbilitazione dell'handler del timer..");
  init_pit8253();
  puts("OK.");
  puts("\nVerifica del disco IDE primario..");
  if(check_fat() < 0){
    puts(" NON TROVATO.");    
    puts("\nCreazione del filesystem...");
    init_fat();    
  }
  puts("OK.");

  char str[10000];
  char *str1 = "aaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbcccccccccccc";
  for(i = 0; i < 10; i++){
    write_file("ciao1.txt", str1, strlen(str1));
  }

  read_file("ciao1.txt",str, 10000);

  str[9999] = '\0';

  puts("\n");
  puts(str);
  puts("\n");

  read_file("ciao2.txt",str, 10000);

  str[9999] = '\0';

  puts("\n");
  puts(str);
  puts("\n");

  fat_entry entry[100];

  list_files(entry);
  i=0;
  puts("\n\nLista dei file nella root:");
  while((entry+i)->name[0] != '\0'){
    puts("\n");
    puts((entry+i)->name);
    puts(".");
    puts((entry+i)->ext);
    i++;
  }
  */
  asm("sti");
  while(1){
    if(i % 1000 == 0){
      //puts("0");
      i=0;
    }
    i++;
  }
  return 0;
}
