/****************************
*       testground KIKO    *
****************************/

#include <stdlib.h>
#include <errno.h>    //library de error handling
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions
#include <unistd.h>   //permite usar a funcao sleep
#include <termios.h>  //permite usar a funcao tcflush


typedef struct guess_t {
  int guess_ID;
  char *guess;
  char result[5];
  guess_t *next;
}guess_list;


typedef struct {
  int ID;
  char player_ID[5];
}hist_data;



typedef struct game_registry {
  int game_ID;
  char player_ID[5];
  char *player_name;
  int colors;
  int key_size;
  char repet;
  char *key;
  int game_time;
  struct game_registry *next;
  try *first;
}game_reg;




int main(int argc, char const *argv[]) {
  game_reg *registo_jogo;
  hist_data *last_game;
  int pid=0;


  (**registo_jogo) //argumento funcoes
  (&registo_jogo) //argumento main

  game_reg *current_player;
  current_player=*registo_jogo;


  current->game_ID=((last_game->ID)+1);
  last_game->player_ID[0]="0";
  pid=atoi(last_game->player_ID);
  pid++;
  current->player_ID=pid; //FALTA POR PA STRING
  current->player_ID[0]="J";




  return 0;
}
