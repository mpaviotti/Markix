#ifndef __STRING_H
#define __STRING_H

int strlen(char *str);
int strcmp(char *one, char *two);
void strcpy(char *destination, char *source);
void memcpy(void *destination, const void *source, int num);
int split(char *str, char ch);

#endif
