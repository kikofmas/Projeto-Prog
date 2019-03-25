//NAO MEXAS EM NADA DO QUE ESTA AQUI FEITO PLZ

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int aaa();
void bbb(int *num);

int main () {
  int numero = aaa();
  printf("%d\n", numero);
}

int aaa(){
  int i=1;
  bbb(&i);
  return i;
}

void bbb(int *num){
  *num = *num + *num;
}
