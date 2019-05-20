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






void ordena(game_reg **reg){
  game_reg *atual, *check;
  atual = *reg;
  check = *reg;
  while(atual!=NULL){
    while(check!=NULL){
      if(atual->key_size > check->key_size){
        swap(&atual,&check);
      }
      else if(atual->key_size == check->key_size &&
              atual->colors > check->colors){
        swap(&atual,&check);
      }
      else if(atual->key_size == check->key_size &&
              atual->colors == check->colors &&
              atual->repet=='S' && check->repet=='N'){
        swap(&atual,&check);
      }
      else if(atual->key_size == check->key_size &&
              atual->colors == check->colors &&
              atual->repet == check->repet &&
              atual->tentativas > check->tentativas){
        swap(&atual,&check);
      }
      else if(atual->key_size == check->key_size &&
              atual->colors == check->colors &&
              atual->repet == check->repet &&
              atual->tentativas == check->tentativas &&
              atual->game_time == check->game_time){
        swap(&atual,&check);
      }
      check = check->next;
    }
    atual=atual->next;
  }
}


void swap(game_reg **ptr1, game_reg **ptr2){
  (*ptr2)->prev = (*ptr1)->prev;
  (*ptr1)->next = (*ptr2)->next;

}
