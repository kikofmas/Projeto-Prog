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

void fill(tentativas *ptr);

int main(int argc, char const *argv[]) {
  tentativas *aux = calloc(1,sizeof(tentativas));
  printf("%d\n", aux->tent_ID);
  fill(aux);
  printf("%d\n", aux->tent_ID);
  return 0;
}

void fill(tentativas *ptr, int size, int colors, int *count){
  ptr->tentativa = calloc(size+1,sizeof(char));
  for(int a=0;a<size;a++){
    ptr->tentativa[a] = 'A'+(rand()%colors);
  }
  answer = validate_key(ptr->tentativa);
  (*count)++;
  ptr->tent_ID = *count;
  ptr->pretas = get_blacks(answer);
  ptr->brancas = get_whites(answer);
  sprintf(ptr->resultado,"P%dB%d", ptr->pretas, ptr->brancas);
  ptr->next=NULL;
}
