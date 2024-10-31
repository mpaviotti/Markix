#include <screen.h>

int main()
{
  char *hello = "Hello world, i am the Markix kernel!"; 
  init_screen();

  puts(hello);

  char *hello2= "\nCiao mondo, sono il kernel Markix e gestisco la memoria video a caratteri.";
  puts(hello2);

  while(1);
  return 0;
}
