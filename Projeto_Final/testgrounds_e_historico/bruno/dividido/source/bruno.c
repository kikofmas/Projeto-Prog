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
#include "key.h"

int main(int argc, char const *argv[]) {
  time_t t;
  srand((unsigned) time(&t));

  int colors=0, size=0, num_alea=0, count=0, win=0;
  letras **lista_cores;
  tentativas *lista_tentativas=NULL;

  printf("Indique a dimensao da chave: ");
  scanf("%d", &size);
  printf("Indique o numero de cores da chave: ");
  scanf("%d", &colors);
  printf("Indique o numero de tentativas aleatorias: ");
  scanf("%d", &num_alea);

  printf("\n");
  activate_oracle(size, colors, 1);
  printf("Chave: ");
  generate_key(1);
  printf("\n");

  lista_cores = listaCores(size, colors);
  lista_tentativas = tentativasAlea(num_alea, size, colors, &count, &lista_cores, &win);
  if(win==0){
    win = keyFinder(size, &lista_cores, &lista_tentativas, &count);
  }

  printf("\nNumero de tentativas: %d\n", count);

  clear(size, &lista_tentativas, &lista_cores);
  return 0;
}
