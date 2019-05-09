/****************************
*       testground KIKO    *
****************************/


/* -podemos chamar esta parte em funcao ou so msm dentro do jogo
** - isto so grava a lista de listas -- it should work */



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
  struct guess_t *next;
  struct guess_t *prev;
}guess_list;


typedef struct {
  int ID;
  char player_ID[5];
  game_reg *last;
}hist_data;


typedef struct game_registry {
  int game_ID;
  char player_ID[5];
  char *player_name;
  int colors;
  int key_size;
  char repet;
  char *key;
  int tentativas;
  float game_time;
  struct game_registry *next;
  struct game_registry *prev;
  guess_list *first;
}game_reg;



void free_guess_list(guess_list *current);
void free_game_registry(game_reg *current);
game_reg *recursive_bubble_sort_fast(game_reg *current, game_reg *limit);
game_reg *recursive_bubble_sort_short(game_reg *current, game_reg *limit);
void reord_2_elements(game_reg *ptr);



int main(int argc, char const *argv[]) {
  game_reg *registo_jogo;
  hist_data *last_game={0, "J000", NULL};
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
  int a=0; //se houver ficheiro hmmmmm
  game_reg *current_game; //chama-se current mas isso so e vdd para a primeira vez, a partir dai e o anterior
  //inicio jogador?????

  /*SOU BURRO COMO O CRL*/


  //inicio de jogo

  /*isto so funciona se leres o ficheiro -h antes e meteres o pointer a apontar para a lista
  caso se implemente de maneira diferente tenho de mudar isto*/
  current_game=registo_jogo;
  while (current_game->next != NULL){
    current_game = current_game->next;
  }
  if (a==0 && flags->hist==0) {  //verifica se primeiro elemento da lista esta preenchido
    registo_jogo=calloc(1, sizeof(game_reg));
    current_game=registo_jogo; //se e a primeira vez que se passa aqui estrutura esta nao esta alocada, dai voltar a fazer isto

    current_game->game_ID=((last_game->ID)+1);
    current_game->player_name=calloc(strlen((nome_jogadores+jogador)+1, sizeof(char));
    strcpy(current_game->player_name, *(nome_jogadores+jogador));
    last_game->player_ID[0]='0';
    pid=atoi(last_game->player_ID);
    pid++;
    sprintf(current_game->player_ID, "J%03d", pid);
    current_game->player_ID[0]='J';
    current_game->colors=defs_jogo->num_cores;
    current_game->key_size=defs_jogo->tamanho_chave;
    current_game->repet=defs_jogo->repeticao_cores;
    current_game->game_time=defs_jogo->duracao_jogo;
    current_game->prev=last_game->last;
    current_game->next=NULL;
    a=1;
  } else {
    current_game->next=calloc(1, sizeof(game_reg));
    current_game->next->game_ID=((last_game->ID)+1);
    current_game->next->player_name=calloc(strlen((nome_jogadores+jogador)+1, sizeof(char));
    strcpy(current_game->next->player_name, *(nome_jogadores+jogador));
    if (strcmp(current_game->player_name, current_game->next->player_name) == 0) {
      strcpy(current_game->next->player_ID, current_game->player_ID);
    } else {
      last_game->next->player_ID[0]='0';
      pid=atoi(last_game->player_ID);
      pid++;
      sprintf(current_game->next->player_ID, "J%03d", pid);
    }
    current_game->next->colors=defs_jogo->num_cores;
    current_game->next->key_size=defs_jogo->tamanho_chave;
    current_game->next->repet=defs_jogo->repeticao_cores;
    current_game->next->game_time=defs_jogo->duracao_jogo;
    current_game->next->prev=last_game->last;
    current_game->next->next=NULL;
  }





  //inicio de jogo
  guess_list *current_guess;
  current_guess=current_game->first;
  //inicio de tentativa

  while (current_guess->next != NULL){
    current_guess = current_guess->next;
  }
  if (tentativa==0) {  //verifica se primeiro elemento da lista esta preenchido
    current_game->key=calloc((defs_jogo->tamanho_chave)+1, sizeof(char));
    current_game->first=calloc(1, sizeof(guess_list));
    current_guess=current_game->first; //se e a primeira vez que se passa aqui estrutura esta nao esta alocada, dai voltar a fazer isto

    current_guess->guess_ID=tentativa+1;
    current_guess->guess=calloc((defs_jogo->tamanho_chave)+1, sizeof(char));
    strcpy(current_guess->guess, jogada);
    sprintf(current_guess->result, "P%1dB%1d", lugar_certo, lugar_errado);
    current_guess->prev=NULL;
    current_guess->next=NULL;
  } else {
    current_guess->next=calloc(1, sizeof(guess_list));
    current_guess->next->guess_ID=tentativa+1;
    current_guess->next->guess=calloc((defs_jogo->tamanho_chave)+1, sizeof(char));
    strcpy(current_guess->next->guess, jogada);
    sprintf(current_guess->next->result, "P%1dB%1d", lugar_certo, lugar_errado);
    current_guess->next->prev=current_guess;
    current_guess->next->next=NULL;
  }

  //fim do jogo
  /*onde se grava a vitoria*/
  strcpy(current_game->key, current_guess->guess);

  /*onde se mete a derrota*/
  strcpy(current_game->key, travessao);

  /*no fim*/
  last_game->ID=current_game->ID;
  strcpy(last_game->player_ID, current_game->player_ID);
  last_game->last=current_game;



  registo_jogo=recursive_bubble_sort_fast(registo_jogo, NULL);
  registo_jogo=recursive_bubble_sort_short(registo_jogo, NULL);

  return 0;
}


//funcao recursiva para libertar as listas de listas
void free_game_registry(game_reg *current){
  if (current->next != NULL) {
    free_game_registry(current->next);
  }
  free_guess_list(current->first);
  free(current);
}


void free_guess_list(guess_list *current){
  if (current->next != NULL) {
    free_guess_list(current->next);
  }
  free(current);
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
    while (current->tentativas < current->tentativas && current->next != limit) {
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
