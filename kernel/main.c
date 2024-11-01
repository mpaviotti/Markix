#include <screen.h>
#include "arch/idt.h"
#include "arch/keyboard.h"
#include "arch/intel.h"

int main(){

  init_screen();
  int i;

  puts("Markix ");
  puts("\n");
  puts("Impostazione degli interrupt..");
  init_int();
  puts("OK.\n");

  puts("Abilitazione della tastiera..");
  keyboard_init();
  puts("OK.\n");

  while(1);

  return 0;

}
