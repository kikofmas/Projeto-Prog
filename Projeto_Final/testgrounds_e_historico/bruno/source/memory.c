#include <stdlib.h>
#include <errno.h>    //library de error handling
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions
#include <unistd.h>   //permite usar a funcao sleep
#include <termios.h>  //permite usar a funcao tcflush

#include "estruturas.h"
#include "memory.h"

void free_game_registry(game_reg *reg){
  if (reg->next != NULL) {
    free_game_registry(reg->next);
  }
  free_guess_list(reg->first);
  free(reg->key);
  free(reg->player_name);
  free(reg);
}

void free_guess_list(tentativas *current){
  if (current->next != NULL) {
    free_guess_list(current->next);
  }
  free(current->tentativa);
  free(current);
}

void clear_memory(char **vect1, int v1, dados **ptr_dados, float *vect3, int *vect4, game_reg *registo_jogo){
  for (int i = 0; i < v1; i++) {
    free(vect1[i]);
  }
  free(vect1);
  for (int i = 0; i < v1; i++) {
    free(ptr_dados[i]);
  }
  free(ptr_dados);
  free(vect3);
  free(vect4);
  free_game_registry(registo_jogo);
}