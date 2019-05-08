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
  struct letras_t * next;
} letras;

void reset(letras **index, letras **lista_cores, int size);

int main(int argc, char const *argv[]) {

  int colors=12;
  int size=8;
  letras **lista_cores, **index;
  char *tentativa;
  reply * answer;
  int pretas;
  //int brancas;

  activate_oracle(size, colors, 1);
  printf("\n\n\n");
  generate_key(1);
  printf("\n\n\n");

  lista_cores = (letras **)calloc(size,sizeof(letras*));
  index = (letras **)calloc(size,sizeof(letras*));
  tentativa = (char *)calloc(size,sizeof(char));

  for(int i=0;i<size;i++){
    letras *aux;
    lista_cores[i] = calloc(1,sizeof(letras));
    aux=lista_cores[i];
    aux->letra = 'A';
    aux->next = NULL;
    for(int a=1;a<colors;a++){
      aux->next = calloc(1,sizeof(letras));
      aux->next->letra = 'A'+a;
      aux->next->next = NULL;
      aux = aux->next;
    }
  }

  for(int i=0;i<size;i++){
    index[i] = lista_cores[i];
  }

  while(index[0]!=NULL){
    for(int i=0;i<size;i++){
      tentativa[i] = index[i]->letra;
    }
    answer = validate_key(tentativa);
    pretas = get_blacks(answer);
    if(pretas == 8) printf("done\n");
    index[size-1] = index[size-1]->next;
    reset(index,lista_cores,size-1);
  }


  return 0;
}

void reset(letras **index, letras **lista_cores, int size){
  if(size==0) return;
  else{
    if(index[size]==NULL){
      index[size] = lista_cores[size];
      index[size-1] = index[size-1]->next;
      reset(index, lista_cores, size-1);
    }
  }
}
