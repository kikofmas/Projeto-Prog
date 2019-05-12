#include <stdlib.h>
#include <errno.h>    //library de error handling
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions
#include <unistd.h>   //permite usar a funcao sleep
#include <termios.h>  //permite usar a funcao tcflush
#include "oraculo.h"
#include "estruturas.h"

#include "test_mode_ord.h"




void sort_registry(game_reg **registo_jogo, int pos, char const *argv[]){
  char shrt[]="short", fst[]="fast";
  if (strcmp(fst, argv[pos]) == 0) {
    *registo_jogo=recursive_bubble_sort_fast(*registo_jogo, NULL);
  } else if (strcmp(shrt, argv[pos]) == 0) {
    *registo_jogo=recursive_bubble_sort_short(*registo_jogo, NULL);
  } else {
    printf("ERRO: impossivel ordenar. Instrucao errada\n");
  }
}


game_reg *recursive_bubble_sort_fast(game_reg *current, game_reg *limit){
  game_reg *top=current;
  if (current == limit) { //base case
    while (current->prev != NULL) {
      current=current->prev;
    }
    return current;
  }
  while (current->game_time > current->next->game_time) {
    reord_2_elements(current);
    while (current->game_time < current->game_time && current->next != limit) {
      current=current->next;
    }
  }
  top=recursive_bubble_sort_fast(top, current);//recursion
  return top;//return "new" first element of list
}


game_reg *recursive_bubble_sort_short(game_reg *current, game_reg *limit){
  game_reg *top=current;
  if (current == limit) { //base case
    while (current->prev != NULL) {
      current=current->prev;
    }
    return current;
  }
  while (current->tentativas > current->next->tentativas) {
    reord_2_elements(current);
    while (current->tentativas < current->next->tentativas && current->next != limit) {
      current=current->next;
    }
  }
  top=recursive_bubble_sort_fast(top, current);//recursion
  return top;//return "new" first element of list
}


void reord_2_elements(game_reg *ptr){
  game_reg *aux = ptr->next;
  ptr->next=aux->next;
  aux->prev=ptr->prev;
  ptr->prev=aux;
  aux->next=ptr;
  if (ptr->next != NULL) ptr->next->prev=ptr;
  if (aux->prev != NULL) aux->prev->next=aux;
}
