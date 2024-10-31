#include <screen.h>
#include <glo.h>

PRIVATE char *memory;

PRIVATE struct cursor{
  int row;
  int column;
} cur;


void init_screen(){
  int i, y;
  memory = (char *)MEMORY_ADDRESS;

  cur.row=0;
  cur.column=0;

  for(i = 0; i < (NR_COLS * 2 * NR_ROWS); i++){
    putc(' ');
  }
}


int cur2add(){
  return cur.row * 80 * 2 + (cur.column * 2);
}

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

void puts(char *str){
  int i = 0;
  
  while(str[i] != '\0'){
    putc(str[i]);
    i++;
  }
}
