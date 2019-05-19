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

int main(int argc, char const *argv[]) {
  FILE *fptr = fopen("historico.dat","rb");
  if(fptr==NULL) exit(-1);
  

  return 0;
}
