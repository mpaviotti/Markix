
#include <math.h>

long exp(int base, int exp){
  int i;
  long result=base;

  for(i = 0; i < exp-1; i++){
    result *= base;
  }

  return (exp >= 1)?result:1;
}
