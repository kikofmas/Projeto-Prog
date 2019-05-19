/****************************
       testground BRUNO
****************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions
#include <unistd.h>   //permite usar a funcao sleep
#include <termios.h>  //permite usar a funcao tcflush

#include "oraculo.h"
#include "estruturas.h"


typedef struct{
  int a;
} aaa;

int main(int argc, char const *argv[]) {
  aaa b={0};

  b.a++;
  printf("%d\n", ++b.a);


  return 0;
}
