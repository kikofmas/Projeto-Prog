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

typedef struct letras_t{
  char letra;
  struct letras_t *next;
} letras;

typedef struct tentativas_t{
  int tent_ID;
  char *tentativa;
  char resultado[5];
  int pretas, brancas;
  struct tentativas_t *next, *prev;
} tentativas;

void fill(tentativas **ptr);

void try(tentativas **ptr);

int main(int argc, char const *argv[]) {
  tentativas *aux = calloc(1,sizeof(tentativas));;

  fill(&aux);
  printf("%d\n", aux->next->next->tent_ID);
  return 0;
}

void fill(tentativas **ptr){
  tentativas *aux;
  (*ptr)->next = calloc(1,sizeof(tentativas));
  aux = (*ptr)->next;
  aux -> next = calloc(1,sizeof(tentativas));
  try(&(aux->next));
}

void try(tentativas **ptr){
  (*ptr)->tent_ID=1;
}
