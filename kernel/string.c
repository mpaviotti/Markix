#include <string.h>

int strcat(char *str1, char* str2, char* res){
  strcpy(res, str1);
  strcpy(res+strlen(str1), str2);
  res[strlen(str1)+strlen(str2)]='\0';
  return 0;
}

int strlen(char *str){
  int i = 0;
  while(str[i] != '\0'){
    i++;
  }

  return i;
}

int strcmp(char *one, char *two){
  int i = 0;

  while(one[i] != '\0' && two[i] != '\0' 
	&& one[i] == two[i]){
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

void strcpy(char *destination, char *source){
  int i = 0;

  while(source[i] != '\0'){
    destination[i] = source[i];
    i++;
  }
  destination[i]='\0';
}

void memcpy(void *destination, const void *source, int num){
  long i;
  char *dest;
  char *src;

  dest = destination;
  src = source;

  for(i = 0; i < num; i++){
    *(dest+i) = *(src+i);
  }
  return;
}

void memset(void *buffer, int ch, int count ){
  int i;
  char *buf;

  buf = buffer;
  for(i = 0; i < count; i++){
    *(buf+i) = (char)ch;
  }
  return;
}

int split(char *str, char ch){
  int i = 0;
  while(str[i] != '\0' && str[i] != ch){
    i++;
  }
  return i;
}

int min(int one, int two){
  return (one < two)?one:two;
}
