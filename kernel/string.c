#include <string.h>

int strlen(char *str){
  int i = 0;
  while(str[i] != '\0'){
    i++;
  }

  return i;
}

int strcmp(char *one, char *two){
  int i = 0;

  while(one[i] != '\0' && two[i] != '\0' && one[i] == two[i]){
    i++;
  }
  
  if(one[i] == two[i] && two[i] == '\0'){
    return 0;
  } else if((one[i] == '\0' && two[i] != '\0') || one[i] < two[i]){
    return 1;
  } else {
    return -1;
  }
}


void strcpy(char *from, char *to){
  int i = 0;

  while(from[i] != '\0'){
    to[i] = from[i];
    i++;
  }
}
