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

void free_game_registry(game_reg **reg){
  game_reg *aux_reg;
  tentativas *aux_tent1, *aux_tent2;
  while(*reg!=NULL){
    aux_tent1 = (*reg)->first;
    while(aux_tent1!=NULL){
      aux_tent2 = aux_tent1;
      free(aux_tent1->tentativa);
      aux_tent1 = aux_tent1->next;
      free(aux_tent2);
    }
    aux_reg = *reg;
    *reg=(*reg)->next;
    free(aux_reg->key);
    free(aux_reg->player_name);
    free(aux_reg);
  }
}