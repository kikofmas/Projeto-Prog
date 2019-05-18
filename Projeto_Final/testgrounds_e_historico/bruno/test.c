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

int main(int argc, char const *argv[]) {
  activate_oracle(4,6,1);
  generate_key(1);
  sleep(3);
  generate_key(1);
  terminate_oracle();

  return 0;
}
