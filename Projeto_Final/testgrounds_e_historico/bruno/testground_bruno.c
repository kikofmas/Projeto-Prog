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

typedef struct tentativas_t{
  char *tentativa;
  int pretas, brancas;
  struct tentativas_t * next, *prev;
} tentativas;

void reset(letras **index, letras **lista_cores, int size);

int main(int argc, char const *argv[]) {

  time_t t;
  srand((unsigned) time(&t));

  int colors=12;
  int size=8;
  letras **lista_cores, **index;
  char *tentativa;
  int num_alea = 0;
  tentativas *lista_tentativas=NULL, *aux=NULL;
  reply * answer;
  int pretas;
  int brancas;
  int valid=0, count=0;



  activate_oracle(size, colors, 1);
  printf("\n\n\n");
  generate_key(1);
  //printf("LLLLLLLL\n");
  printf("\n\n\n");

  lista_cores = (letras **)calloc(size,sizeof(letras*));
  index = (letras **)calloc(size,sizeof(letras*));
  tentativa = (char *)calloc(size,sizeof(char));

  if(num_alea>0){
    lista_tentativas = calloc(1,sizeof(tentativas));
    aux = lista_tentativas;

    aux -> tentativa = calloc(size,sizeof(char));
    for(int a=0;a<size;a++){
      aux -> tentativa[a] = 'A'+(rand()%colors);
    }

    answer = validate_key(aux->tentativa);
    //answer = compare_keys("LLLLLLLL",aux->tentativa);

    pretas = get_blacks(answer);
    brancas = get_whites(answer);
    aux->pretas = pretas;
    aux->brancas = brancas;
    aux->next=NULL;
    aux->prev=NULL;

    printf("%s P%dB%d\n", aux->tentativa, aux->pretas, aux->brancas);

    for(int i=1;i<num_alea;i++){

      aux->next = calloc(1,sizeof(tentativas));
      aux->next-> tentativa = calloc(size,sizeof(char));
      for(int a=0;a<size;a++){
        aux -> next -> tentativa[a] = 'A'+(rand()%colors);
      }

      answer = validate_key(aux->next->tentativa);
      //answer = compare_keys("LLLLLLLL",aux->next->tentativa);

      pretas = get_blacks(answer);
      brancas = get_whites(answer);
      aux->next->pretas = pretas;
      aux->next->brancas = brancas;
      aux->next->next = NULL;
      aux->next->prev = aux;
      printf("%s P%dB%d\n", aux->next->tentativa, aux->next->pretas, aux->next->brancas);
      aux = aux->next;
    }
  }

  printf("\n\n");

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
    valid = 0;

    if(lista_tentativas==NULL){

      printf("%s\n", tentativa);

      lista_tentativas = calloc(1,sizeof(tentativas));
      lista_tentativas -> tentativa = calloc(size,sizeof(char));
      strcpy(lista_tentativas -> tentativa, tentativa);

      answer = validate_key(tentativa);
      //answer = compare_keys("LLLLLLLL",tentativa);

      lista_tentativas -> pretas = get_blacks(answer);
      lista_tentativas -> brancas = get_whites(answer);
      lista_tentativas -> next = NULL;
      lista_tentativas -> prev = NULL;
      count++;

      if(lista_tentativas -> pretas==size){
        printf("%s\n", tentativa);
        break;
      }

      if(lista_tentativas -> pretas == 0 && lista_tentativas -> brancas==0){
        for(int i=0;i<size;i++){
          index[i] = index[i]->next;
          lista_cores[i] = lista_cores[i] -> next;
        }

      }
      else{
        index[size-1] = index[size-1]->next;
      }

    }
    else{
      aux = lista_tentativas;
      while(aux->next!=NULL){
        aux = aux->next;
      }
      while(aux != NULL){
        answer = compare_keys(aux->tentativa,tentativa);
        pretas = get_blacks(answer);
        brancas = get_whites(answer);
        if(pretas != aux->pretas || brancas != aux->brancas){
          valid = 0;
          break;
        }
        valid = 1;
        aux=aux->prev;
      }

      if(valid == 1){

        printf("%s\n", tentativa);

        aux = lista_tentativas;
        while(aux->next!=NULL) aux = aux->next;

        aux->next = calloc(1,sizeof(tentativas));

        answer = validate_key(tentativa);
        //answer = compare_keys("LLLLLLLL",tentativa);

        aux->next->pretas = get_blacks(answer);
        aux->next->brancas = get_whites(answer);
        aux->next->tentativa = calloc(size,sizeof(char));
        strcpy(aux->next->tentativa,tentativa);
        aux->next->next = NULL;
        aux->next->prev=aux;
        count++;
        if(aux->next->pretas == size){
          break;
        }
        if(aux->next->pretas == 0 && aux->next->brancas==0){
          for(int i=0;i<size;i++){
            index[i] = index[i]->next;
            lista_cores[i] = lista_cores[i] -> next;
          }

        }
        else{
          index[size-1] = index[size-1]->next;
        }
      }
      else index[size-1] = index[size-1]->next;
    }

    reset(index,lista_cores,size-1);
  }

  printf("done\n");
  printf("%d\n", count);
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
