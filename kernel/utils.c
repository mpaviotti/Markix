#include <utils.h>

/* Convere un numero in carattere 
esadecimale */
char num2ex(unsigned char num){
  char nibble;
  if(num > 9 & num < 16){
    nibble='A'+(num-10);
  } else if(num >= 0 && num <=9){
    nibble='0'+num;
  }
  return nibble;
}

/* Converte 8 bit in stringa esadecimale */
void ch2ex(unsigned char c, char *ex){
  char binary[8];
  char msn=0,lsn=0;
  int i = 0;
  ch2bin(c, binary);


  for(i = 0; i < 4; i++){
    msn += (binary[i]=='1')?exp(2, 3-i):0;
  }

  for(i = 4; i < 8; i++){
    lsn += (binary[i]=='1')?exp(2, 3-(i-4)):0;
  }

  ex[0] = num2ex(msn);
  ex[1] = num2ex(lsn);
}

/* Converte 32 bit in una stringa esadecimale */
void i2ex(unsigned int i, char *ex){
  char first, second, third, fourth;

  first = (i >> 24) & 0x00FF;
  second = (i >> 16) & 0x00FF;
  third = (i >> 8) & 0x00FF;
  fourth = i & 0x00FF;

  ch2ex(first, ex);  
  ch2ex(second, ex+2);
  ch2ex(third, ex+4);
  ch2ex(fourth, ex+6);
}

/* Converte 8 bit in una stringa binaria */
void ch2bin(unsigned char c, char *bin){
  int i; 
  int rest=0;

  for(i = 0; i < 8; i++){
    rest = c % 2;

    if(rest == 1){
      bin[7-i] = '1';
    } else if(rest == 0){
      bin[7-i] = '0';
    }

    rest=0;
    c = c / 2;
  }
}
