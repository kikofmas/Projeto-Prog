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

void reset(letras **index, letras **lista_cores, int size);

int main(int argc, char const *argv[]) {

  time_t t;
  srand((unsigned) time(&t));

  int colors=0;
  int size=0;
  letras **lista_cores, **index, *color_aux=NULL, *aux_rm=NULL;
  char *tentativa;
  int num_alea = 0;
  tentativas *lista_tentativas=NULL, *aux=NULL;
  reply *answer;
  int pretas;
  int brancas;
  int valid=0, count=0;

  printf("Indique a dimensao da chave: ");
  scanf("%d", &size);
  printf("Indique o numero de cores da chave: ");
  scanf("%d", &colors);
  printf("Indique o numero de tentativas aleatorias: ");
  scanf("%d", &num_alea);
  count = num_alea;

  printf("\n");
  activate_oracle(size, colors, 1);
  printf("Chave: ");
  generate_key(1);
  printf("\n");

  lista_cores = (letras **)calloc(size,sizeof(letras*));
  index = (letras **)calloc(size,sizeof(letras*));
  tentativa = (char *)calloc(size+1,sizeof(char));

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

  if(num_alea>0){
    printf("Tentativas aleatorias:\n");
    lista_tentativas = calloc(1,sizeof(tentativas));
    aux = lista_tentativas;

    aux -> tentativa = calloc(size+1,sizeof(char));
    for(int a=0;a<size;a++){
      aux -> tentativa[a] = 'A'+(rand()%colors);
    }

    answer = validate_key(aux->tentativa);

    aux->tent_ID = 1;
    aux->pretas = get_blacks(answer);
    aux->brancas = get_whites(answer);
    sprintf(aux->resultado,"P%dB%d", aux->pretas, aux->brancas);
    aux->next=NULL;
    aux->prev=NULL;

    printf("%d: %s %s\n", aux->tent_ID, aux->tentativa, aux->resultado);

    if(aux->pretas==size) exit(0);
    else if(aux->pretas==0 && aux->brancas==0){





    }
    else if(aux->pretas==0){
      for(int i=0;i<size;i++){
        color_aux = lista_cores[i];
        if(color_aux->letra == aux->tentativa[i]){
          lista_cores[i] = lista_cores[i]->next;
          free(color_aux);
        }
        else{
          while(color_aux->next->letra!=aux->tentativa[i]){
            color_aux = color_aux->next;
          }
          aux_rm = color_aux->next;
          color_aux->next=color_aux->next->next;
          free(aux_rm);
        }
      }
    }

    for(int i=1;i<num_alea;i++){

      aux->next = calloc(1,sizeof(tentativas));
      aux->next->tentativa = calloc(size+1,sizeof(char));
      for(int a=0;a<size;a++){
        aux -> next -> tentativa[a] = 'A'+(rand()%colors);
      }

      answer = validate_key(aux->next->tentativa);

      aux->next->tent_ID = i+1;
      aux->next->pretas = get_blacks(answer);
      aux->next->brancas = get_whites(answer);
      sprintf(aux->next->resultado,"P%dB%d", aux->next->pretas, aux->next->brancas);
      aux->next->next = NULL;
      aux->next->prev = aux;
      printf("%d: %s %s\n", aux->next->tent_ID, aux->next->tentativa, aux->next->resultado);

      if(aux->next->pretas==size) exit(0);
      else if(aux->next->pretas==0 && aux->next->brancas==0){





      }
      else if(aux->next->pretas==0){
        for(int index=0;index<size;index++){
          color_aux = lista_cores[index];
          if(color_aux->letra == aux->next->tentativa[index]){
            lista_cores[index] = lista_cores[index]->next;
            free(color_aux);
          }
          else{
            while(color_aux->next->letra != aux->next->tentativa[index]){
              color_aux = color_aux->next;
              if(color_aux->next==NULL) break;
            }
            if(color_aux->next!=NULL){
              aux_rm = color_aux->next;
              color_aux->next=color_aux->next->next;
              free(aux_rm);
            }
          }
        }
      }

      aux = aux->next;
    }

    printf("\n");
  }

  for(int i=0;i<size;i++){
    index[i] = lista_cores[i];
  }

  printf("Tentativas logicas:\n");

  while(index[0]!=NULL){

    for(int i=0;i<size;i++){
      tentativa[i] = index[i]->letra;
    }

    valid = 0;

    if(lista_tentativas==NULL){

      lista_tentativas = calloc(1,sizeof(tentativas));
      lista_tentativas -> tentativa = calloc(size+1,sizeof(char));
      strcpy(lista_tentativas -> tentativa, tentativa);

      answer = validate_key(tentativa);

      lista_tentativas -> pretas = get_blacks(answer);
      lista_tentativas -> brancas = get_whites(answer);
      sprintf(lista_tentativas->resultado,"P%dB%d",lista_tentativas->pretas, lista_tentativas->brancas);
      lista_tentativas -> next = NULL;
      lista_tentativas -> prev = NULL;
      count++;
      lista_tentativas -> tent_ID = count;

      printf("%d: %s %s\n", count, tentativa, lista_tentativas->resultado);

      if(lista_tentativas -> pretas==size) break;
      else if(lista_tentativas -> pretas == 0 && lista_tentativas -> brancas==0){
        for(int i=0;i<size;i++){
          index[i] = index[i]->next;
          aux_rm = lista_cores[i];
          lista_cores[i] = lista_cores[i] -> next;
          free(aux_rm);
        }
      }
      else index[size-1] = index[size-1]->next;
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

        aux = lista_tentativas;
        while(aux->next!=NULL) aux = aux->next;

        aux->next = calloc(1,sizeof(tentativas));

        answer = validate_key(tentativa);

        aux->next->pretas = get_blacks(answer);
        aux->next->brancas = get_whites(answer);
        sprintf(aux->next->resultado,"P%dB%d", aux->next->pretas, aux->next->brancas);
        aux->next->tentativa = calloc(size+1,sizeof(char));
        strcpy(aux->next->tentativa,tentativa);
        aux->next->next = NULL;
        aux->next->prev=aux;
        count++;
        aux->next->tent_ID = count;

        printf("%d: %s %s\n", count, tentativa, aux->next->resultado);

        if(aux->next->pretas == size) break;
        else if(aux->next->pretas == 0 && aux->next->brancas==0){
          index[0] = index[0]->next;
          for(int i=1;i<size;i++){
            if(index[0]->letra == tentativa[i]){
              index[0] = index[0]->next;
            }
          }

          for(int i=0;i<size;i++){
            for(int a=0;a<size;a++){
              color_aux = lista_cores[a];
              if(color_aux->letra == tentativa[i]){
                lista_cores[a] = lista_cores[a]->next;
                free(color_aux);
              }
              else{
                while(color_aux->next->letra != tentativa[i]){
                  color_aux = color_aux->next;
                  if(color_aux->next==NULL) break;
                }
                if(color_aux->next!=NULL){
                  aux_rm = color_aux->next;
                  color_aux->next=color_aux->next->next;
                  free(aux_rm);
                }
              }
            }
          }
          for(int i=1;i<size;i++){
            index[i] = lista_cores[i];
          }
        }
        else if(aux->next->pretas == 0){
          index[0] = index[0]->next;
          for(int i=0;i<size;i++){
            color_aux = lista_cores[i];
            if(color_aux->letra == tentativa[i]){
              lista_cores[i] = lista_cores[i]->next;
              free(color_aux);
            }
            else{
              while(color_aux->next->letra != tentativa[i]){
                color_aux = color_aux->next;
                if(color_aux->next==NULL) break;
              }
              if(color_aux->next!=NULL){
                aux_rm = color_aux->next;
                color_aux->next=color_aux->next->next;
                free(aux_rm);
              }
            }
          }

          for(int i=1;i<size;i++){
            index[i] = lista_cores[i];
          }

        }
        else index[size-1] = index[size-1]->next;

      }
      else index[size-1] = index[size-1]->next;
    }

    reset(index,lista_cores,size-1);

  }

  printf("\nNumero de tentativas: %d\n", count);



  for(int i=0;i<size;i++){
    while(lista_cores[i]!=NULL){
      aux_rm = lista_cores[i];
      lista_cores[i]=lista_cores[i]->next;
      free(aux_rm);
    }
  }
  while (lista_tentativas!=NULL) {
    aux=lista_tentativas;
    lista_tentativas=lista_tentativas->next;
    free(aux->tentativa);
    free(aux);
  }
  free(lista_cores);
  free(index);
  free(tentativa);
  free(lista_tentativas);


  return 0;
}

void reset(letras **index, letras **lista_cores, int size){
  if(size>0){
    if(index[size]==NULL){
      index[size] = lista_cores[size];
      index[size-1] = index[size-1]->next;
      reset(index, lista_cores, size-1);
    }
  }
}
