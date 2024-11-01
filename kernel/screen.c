#include <utils.h>
#include <screen.h>
#include <glo.h>

/* Puntatore alla memoria video */
PRIVATE char *memory;

/* Cursore corrente identificato
dalle coordinate 'row' e 'column'
*/
PRIVATE struct cursor{
  int row;
  int column;
} cur;


/* Inizializza lo schermo 
   azzerando i valori nella memoria */
void init_screen(){
  int i, y;
  memory = (char *)MEMORY_ADDRESS;

  cur.row=0;
  cur.column=0;

  for(i = 0; i < (NR_COLS * 2 * NR_ROWS); i++){
    putc(' ');
  }
}

/* Converte il cursore corrente 
   in un indirizzo di memoria, il quale 
   è l'offset a partire da MEMORY_ADDRESS
*/
int cur2add(){
  return cur.row * 80 * 2 + (cur.column * 2);
}

/* Stampa un byte */
void putc(char c){
  int offset = cur2add();
  
  if(c == '\n'){
    cur.row++;
    cur.column=0;
  } else {
    memory[offset] = c;
    memory[offset+1] = 0x0F;

    cur.column++;
  }
  
  if(cur.column >= NR_COLS * 2){
    cur.column=0;
    cur.row++;
  }

  if(cur.row >= NR_ROWS){ 
    cur.row = 0;
    cur.column = 0;
  }
}

/* Stampa una stringa */
void puts(char *str){
  int i = 0;
  
  while(str[i] != '\0'){
    putc(str[i]);
    i++;
  }
}

/* Stampa un byte in binario */
void putb(unsigned char c){
  char binary[9];

  ch2bin(c, binary);
  binary[8]='\0';
  puts(binary);
}

/* Stampa 32 bit in esadecimale */
void putex(unsigned int n){
  char ex[9];
  i2ex(n, ex);
  ex[8]='\0';
  puts(ex);
}
