#include <utils.h>
#include <screen.h>


/* Puntatore alla memoria video */
static char *memory;

/* Cursore corrente identificato
dalle coordinate 'row' e 'column'
*/
static struct cursor{
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
  cur.row=0;
  cur.column=0;
}

/* Converte il cursore corrente 
   in un indirizzo di memoria, il quale 
   è l'offset a partire da MEMORY_ADDRESS
*/
int cur2add(struct cursor tmp){
  return tmp.row * 80 * 2 + (tmp.column * 2);

}

void stepdown(){
  int row, column;
  unsigned char *mem;
  struct cursor tmp,tmp2;

  mem = MEMORY_ADDRESS;

  for(row = 1; row < NR_ROWS; row++){
    for(column = 0; column < NR_COLS; column++){
      tmp.row = row-1;
      tmp.column = column;
      tmp2.row = row;
      tmp2.column = column;
      mem[cur2add(tmp)] = mem[cur2add(tmp2)];
    }
  }

  cur.row = NR_ROWS - 1;
  cur.column=0;
  for(column = 0; column < NR_COLS; column++){
    putc(' ');
  }
  cur.row = NR_ROWS - 1;
  cur.column=0;
}

/* Stampa un byte */
void putc(char c){
  int offset = cur2add(cur);
  
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

    stepdown();    

    cur.row--;
    cur.column=0;
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
