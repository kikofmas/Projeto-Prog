/****************************
*       testground KIKO    *
****************************/


/*podemos chamar esta parte em funcao ou so msm dentro do jogo*/



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
  guess_list *first;
}game_reg;




int main(int argc, char const *argv[]) {
  game_reg *registo_jogo;
  hist_data *last_game;
  int pid=0;
  char travessao[]="-";

  if (flags->hist != 0) {
    /*carregar os dados para a pequena estrutura  *
    * ******************************************* *
    * ******************************************* *
    * ****************************************** */
  }

  (**registo_jogo) //argumento funcoes
  (&registo_jogo) //argumento main


  //coisas fucao
  game_reg *current_player;
  current_player=*registo_jogo;

  //inicio de jogador
  current_player->game_ID=((last_game->ID)+1);
  last_game->player_ID[0]="0";
  pid=atoi(last_game->player_ID);
  pid++;
  sprintf(current_player->player_ID, "%d", pid);
  current_player->player_ID[0]="J";
  current_player->colors=defs_jogo->num_cores;
  current_player->key_size=defs_jogo->tamanho_chave;
  current_player->repet=defs_jogo->repeticao_cores;
  current_player->game_time=defs_jogo->duracao_jogo;
  current_player->next=NULL;

  //inicio de jogo
  current_player->key=calloc((defs_jogo->tamanho_chave)+1, sizeof(char));
  current_player->first=calloc(1, sizeof(guess_list));
  guess_list *current_guess;
  current_guess=current_player->first;

  //inicio de tentativa
  current_guess->guess_ID=tentativa+1;
  current_guess->guess=calloc((defs_jogo->tamanho_chave)+1, sizeof(char));
  strcpy(current_guess->guess, jogada);
  current_guess->result[0]="P";
  sprintf(current_guess->result[1], "%c", lugar_certo);
  current_guess->result[2]="B";
  sprintf(current_guess->result[3], "%c", lugar_errado);
  current_guess->next=NULL;

  //fim do jogo
  /*onde se grava a vitoria*/
  strcpy(current_player->key, current_guess->guess);

  /*onde se mete a derrota*/
  strcpy(current_player->key, travessao);

  /*no fim*/
  last_game->ID=current_player->ID;
  strcpy(last_game->player_ID, current_player->player_ID);

  return 0;
}
