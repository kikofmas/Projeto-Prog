//LIBRARIES
#include <stdlib.h>
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions

#include "estruturas.h"
#include "sort.h"


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
game_reg *recursive_bubble_sort_fast(game_reg *top, game_reg *limit){
  game_reg *current=top;
  if (current == limit) { //base case
    return current;
  }
  while (current->next != limit) {
    if (current->key_size > current->next->key_size) {
      reord_2_elements(current);
    } else if (current->colors > current->next->colors && current->key_size == current->next->key_size) {
      reord_2_elements(current);
    } else if (tolower(current->repet)=='s' && tolower(current->next->repet)=='n' &&
            current->colors == current->next->colors && current->key_size == current->next->key_size) {
      reord_2_elements(current);
    } else if (current->game_time > current->next->game_time && tolower(current->repet)==tolower(current->next->repet) &&
            current->colors == current->next->colors && current->key_size == current->next->key_size) {
      reord_2_elements(current);
    } else if (current->tentativas > current->next->tentativas && current->game_time == current->next->game_time && tolower(current->repet)==tolower(current->next->repet) &&
            current->colors == current->next->colors && current->key_size == current->next->key_size) {
      reord_2_elements(current);
    } else {
      current=current->next;
    }
  }
  while (top->prev!=NULL) {
    top=top->prev;
  }
  recursive_bubble_sort_fast(top, current);//recursion
  while (top->prev!=NULL) {
    top=top->prev;
  }
  return top;//return "new" first element of list
}
game_reg *recursive_bubble_sort_short(game_reg *top, game_reg *limit){
  game_reg *current=top;
  if (current == limit) { //base case
    return current;
  }
  while (current->next != limit) {
    if (current->key_size > current->next->key_size) {
      reord_2_elements(current);
    } else if (current->colors > current->next->colors && current->key_size == current->next->key_size) {
      reord_2_elements(current);
    } else if (tolower(current->repet)=='s' && tolower(current->next->repet)=='n' &&
            current->colors == current->next->colors && current->key_size == current->next->key_size) {
      reord_2_elements(current);
    } else if (current->tentativas > current->next->tentativas && tolower(current->repet)==tolower(current->next->repet) &&
            current->colors == current->next->colors && current->key_size == current->next->key_size) {
      reord_2_elements(current);
    } else if (current->game_time > current->next->game_time && current->tentativas == current->next->tentativas && tolower(current->repet)==tolower(current->next->repet) &&
            current->colors == current->next->colors && current->key_size == current->next->key_size) {
      reord_2_elements(current);
    } else {
      current=current->next;
    }
  }
  while (top->prev!=NULL) {
    top=top->prev;
  }
  recursive_bubble_sort_short(top, current);//recursion
  while (top->prev!=NULL) {
    top=top->prev;
  }
  return top;//return "new" first element of list
}
void reord_2_elements(game_reg *ptr) {
  game_reg *aux = ptr->next;
  ptr->next=aux->next;
  aux->prev=ptr->prev;
  ptr->prev=aux;
  aux->next=ptr;
  if (ptr->next != NULL) ptr->next->prev=ptr;
  if (aux->prev != NULL) aux->prev->next=aux;
}






void save_game_ini(game_reg **registo_jogo, hist_data *last_game, char **nome_jogadores, defs defs_jogo, int jogador){
  static int k=0; //se houver ficheiro hmmmmm
  game_reg *current_game=*registo_jogo; //chama-se current mas isso so e vdd para a primeira vez, a partir dai e o anterior
  //inicio de jogo
  /*isto so funciona se leres o ficheiro -h antes e meteres o pointer a apontar para a lista
  caso se implemente de maneira diferente tenho de mudar isto*/
  if (k==0) {  //verifica se primeiro elemento da lista esta preenchido
    *registo_jogo=calloc(1, sizeof(game_reg));
    current_game=*registo_jogo; //se e a primeira vez que se passa aqui estrutura esta nao esta alocada, dai voltar a fazer isto

    current_game->game_ID=((last_game->ID)+1);
    (last_game->ID)++;
    current_game->player_name=calloc(strlen(*(nome_jogadores+jogador))+1, sizeof(char));
    strcpy(current_game->player_name, *(nome_jogadores+jogador));
    sprintf(current_game->player_ID, "J%03d", (last_game->player_ID)+1);
    (last_game->player_ID)++;
    current_game->colors=defs_jogo.num_cores;
    current_game->key_size=defs_jogo.tamanho_chave;
    current_game->repet=toupper(defs_jogo.repeticao_cores);
    current_game->game_time=defs_jogo.duracao_jogo;
    current_game->prev=last_game->last;
    last_game->last=current_game;
    current_game->next=NULL;
    k=1;
  } else {
    while (current_game->next != NULL){
      current_game = current_game->next;
    }
    current_game->next=calloc(1, sizeof(game_reg));
    current_game->next->game_ID=((last_game->ID)+1);
    (last_game->ID)++;
    current_game->next->player_name=calloc(strlen(*(nome_jogadores+jogador))+1, sizeof(char));
    strcpy(current_game->next->player_name, *(nome_jogadores+jogador));
    if (strcmp(current_game->player_name, current_game->next->player_name) == 0) {
      strcpy(current_game->next->player_ID, current_game->player_ID);
    } else {
      sprintf(current_game->next->player_ID, "J%03d", (last_game->player_ID)+1);
      (last_game->player_ID)++;
    }
    current_game->next->colors=defs_jogo.num_cores;
    current_game->next->key_size=defs_jogo.tamanho_chave;
    current_game->next->repet=defs_jogo.repeticao_cores;
    current_game->next->game_time=defs_jogo.duracao_jogo;
    current_game->next->prev=last_game->last;
    last_game->last=current_game->next;
    current_game->next->next=NULL;
  }
}

void save_key(int k, game_reg *registo_jogo, char jogada[], time_t tempo_jogo, defs def){
  game_reg *current_game = registo_jogo;
  char travessao[] = "-";
  while (current_game->next != NULL){
    current_game = current_game->next;
  }
  /*onde se grava a vitoria*/
  if(k==1) {
    current_game->game_time=tempo_jogo;
    current_game->key=calloc(strlen(jogada), sizeof(char));
    strncpy(current_game->key, jogada, strlen(jogada));
  }
  /*onde se mete a derrota*/
  if(k==0) {
    current_game->game_time=def.duracao_jogo;
    current_game->key=calloc((strlen(travessao))+1, sizeof(char));
    strcpy(current_game->key, travessao);
  }
}

void save_guess_ini(game_reg *top, int lugar_certo, int lugar_errado, int tentativa, char jogada[]) {
  game_reg *current_game=top;
  tentativas *current_guess;

  while (current_game->next != NULL){
    current_game = current_game->next;
  }
  if (tentativa==0) {  //verifica se primeiro elemento da lista esta preenchido
    current_game->tentativas=tentativa+1;
    current_game->first=calloc(1, sizeof(tentativas));
    if(current_game->first==NULL){
      perror("Erro");
      exit(-1);
    }
    current_guess=current_game->first; //se e a primeira vez que se passa aqui estrutura esta nao esta alocada, dai voltar a fazer isto

    current_guess->tent_ID=tentativa+1;
    current_guess->tentativa=calloc(strlen(jogada), sizeof(char));
    if(current_guess->tentativa==NULL){
      perror("Erro");
      exit(-1);
    }
    strncpy(current_guess->tentativa, jogada, strlen(jogada));
    sprintf(current_guess->resultado, "P%1dB%1d", lugar_certo, lugar_errado);
    current_guess->prev=NULL;
    current_guess->next=NULL;
  } else {
    current_guess=current_game->first;
    while (current_guess->next != NULL){
      current_guess = current_guess->next;
    }
    current_game->tentativas=tentativa+1;
    current_guess->next=calloc(1, sizeof(tentativas));
    if(current_guess->next==NULL){
      perror("Erro");
      exit(-1);
    }
    current_guess->next->tent_ID=tentativa+1;
    current_guess->next->tentativa=calloc(strlen(jogada), sizeof(char));
    if(current_guess->next->tentativa==NULL){
      perror("Erro");
      exit(-1);
    }
    strncpy(current_guess->next->tentativa, jogada, strlen(jogada));
    sprintf(current_guess->next->resultado, "P%1dB%1d", lugar_certo, lugar_errado);
    current_guess->next->prev=current_guess;
    current_guess->next->next=NULL;
  }
}