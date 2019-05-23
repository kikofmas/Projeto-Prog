//LIBRARIES
#include <stdlib.h>
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions

#include "estruturas.h"
#include "sort.h"


/******************************************************************************
* Nome da funcao: sort_registry()
*
* Argumentos: **registo_jogo - pointer para a lista com o registo de jogo
*             pos - posicao do argumento de ordenacao
*             *argv[] - valores passados atraves da linha de comandos
*
* Return: none
*
* Side-effects: forca a saida caso a instrucao esteja incorreta
*
* Descricao: escolhe o tipo de ordenacao fast/short dependendo do input do user
*
******************************************************************************/
void sort_registry (game_reg **registo_jogo, int pos, char const *argv[]) {
  char shrt[] = "short", fst[] = "fast";
  if (strcmp(fst, argv[pos]) == 0) {
    *registo_jogo = recursive_bubble_sort_fast(*registo_jogo, NULL);
  } else if (strcmp(shrt, argv[pos]) == 0) {
    *registo_jogo = recursive_bubble_sort_short(*registo_jogo, NULL);
  } else {
    printf("ERRO: impossivel ordenar. Instrucao errada\n");
    exit(-1);
  }
}


/******************************************************************************
* Nome da funcao: recursive_bubble_sort_fast()
*
* Argumentos: *top - .....
*             *limit - ....
*
* Return: ponteiro para o inicio da lista com o registo de jogo ja organizada
*
* Side-effects: none
*
* Descricao: ordena o registo de jogo do menor tempo para o maior e
*            agrupa os jogos por classes
*
******************************************************************************/
game_reg *recursive_bubble_sort_fast (game_reg *top, game_reg *limit) {
  game_reg *current = top;
  if (current == limit) { //base case
    return current;
  }
  while (current->next != limit) {
    if (current->key_size > current->next->key_size) {
      reord_2_elements(current);
    } else if (current->colors > current->next->colors  &&  current->key_size == current->next->key_size) {
      reord_2_elements(current);
    } else if (tolower(current->repet)=='s'  &&  tolower(current->next->repet)=='n'  &&
            current->colors == current->next->colors  &&  current->key_size == current->next->key_size) {
      reord_2_elements(current);
    } else if (current->game_time > current->next->game_time  &&  tolower(current->repet)==tolower(current->next->repet)  &&
            current->colors == current->next->colors  &&  current->key_size == current->next->key_size) {
      reord_2_elements(current);
    } else if (current->tentativas > current->next->tentativas  &&  current->game_time == current->next->game_time  &&
              tolower(current->repet)==tolower(current->next->repet)  &&  current->colors == current->next->colors  &&
              current->key_size == current->next->key_size) {
      reord_2_elements(current);
    } else {
      current = current->next;
    }
  }
  while (top->prev != NULL) {
    top = top->prev;
  }
  recursive_bubble_sort_fast(top, current);//recursion
  while (top->prev != NULL) { //poe o ponteiro a apontar para o inicio da lista
    top = top->prev;
  }
  return top;//return "new" first element of list
}


/******************************************************************************
* Nome da funcao: recursive_bubble_sort_short()
*
* Argumentos: *top - .....
*             *limit - ....
*
* Return: ponteiro para o inicio da lista com o registo de jogo ja organizada
*
* Side-effects: none
*
* Descricao: Ordena o registo de jogo do menor numero de jogadas
*            para o maior e agrupa os jogos por classes
*
******************************************************************************/
game_reg *recursive_bubble_sort_short (game_reg *top, game_reg *limit) {
  game_reg *current = top;
  if (current == limit) { //base case
    return current;
  }
  while (current->next != limit) {
    if (current->key_size > current->next->key_size) {
      reord_2_elements(current);
    } else if (current->colors > current->next->colors  &&  current->key_size == current->next->key_size) {
      reord_2_elements(current);
    } else if (tolower(current->repet)=='s'  &&  tolower(current->next->repet)=='n'  &&
            current->colors == current->next->colors  &&  current->key_size == current->next->key_size) {
      reord_2_elements(current);
    } else if (current->tentativas > current->next->tentativas  &&  tolower(current->repet)==tolower(current->next->repet)  &&
            current->colors == current->next->colors  &&  current->key_size == current->next->key_size) {
      reord_2_elements(current);
    } else if (current->game_time > current->next->game_time  &&  current->tentativas == current->next->tentativas  &&
              tolower(current->repet)==tolower(current->next->repet)  &&  current->colors == current->next->colors  &&
              current->key_size == current->next->key_size) {
      reord_2_elements(current);
    } else {
      current = current->next;
    }
  }
  while (top->prev != NULL) {
    top = top->prev;
  }
  recursive_bubble_sort_short(top, current);//recursion
  while (top->prev != NULL) { //poe o ponteiro a apontar para o inicio da lista
    top = top->prev;
  }
  return top;//return "new" first element of list
}


/******************************************************************************
* Nome da funcao: recursive_bubble_sort_short()
*
* Argumentos: *ptr - elemento a trocar (troca de posicao com o seguinte)
*
* Return: none
*
* Side-effects: none
*
* Descricao: troca a posicao de dois elementos consecutivos
*
******************************************************************************/
void reord_2_elements (game_reg *ptr) {
  game_reg *aux = ptr->next;
  ptr->next = aux->next;
  aux->prev = ptr->prev;
  ptr->prev = aux;
  aux->next = ptr;
  if (ptr->next != NULL) ptr->next->prev = ptr;
  if (aux->prev != NULL) aux->prev->next = aux;
}


/******************************************************************************
* Nome da funcao: save_game_ini()
*
* Argumentos: **registo_jogo - ponteiro para a lista do registo de jogo
*             *last_game - estrutura que guarda os valores mais elevados de jogos
*             **nome_jogadores - ponteiro para o nome dos jogadores
*             defs_jogo - definicoes de jogo
*             jogador - numero do jogador atual
*
* Return: none
*
* Side-effects: forca a saida caso a alocacao de memoria nao for bem sucedida
*
* Descricao: cria/guarda na lista do registo de jogo os dados do jogo a decorrer
*
******************************************************************************/
void save_game_ini (game_reg **registo_jogo, hist_data *last_game, char **nome_jogadores, defs defs_jogo, int jogador) {
  static int k = 0; //flag que verifica se o primeiro elemento da lista ja existe
  game_reg *current_game = *registo_jogo;
  //inicio de jogo
  if (k == 0) {  //verifica se primeiro elemento da lista esta preenchido
    *registo_jogo = (game_reg *) calloc(1, sizeof(game_reg));
    if (*registo_jogo == NULL) exit(-1); //confirma a correta alocacao de memoria
    current_game = *registo_jogo; //se e a primeira vez que se passa aqui estrutura esta nao esta alocada, dai voltar a fazer isto

    current_game->game_ID = ((last_game->ID)+1);
    (last_game->ID)++;
    current_game->player_name = (char *) calloc(strlen(*(nome_jogadores+jogador))+1, sizeof(char));
    if (current_game->player_name == NULL) exit(-1); //confirma a correta alocacao de memoria
    strcpy(current_game->player_name, *(nome_jogadores+jogador));
    sprintf(current_game->player_ID, "J%03d", (last_game->player_ID)+1);
    (last_game->player_ID)++;
    current_game->colors = defs_jogo.num_cores;
    current_game->key_size = defs_jogo.tamanho_chave;
    current_game->repet = toupper(defs_jogo.repeticao_cores);
    current_game->game_time = defs_jogo.duracao_jogo;
    current_game->prev = last_game->last;
    last_game->last = current_game;
    current_game->next = NULL;
    current_game->prev = NULL;
    k = 1;
  } else {
    while (current_game->next != NULL) {
      current_game = current_game->next;
    }
    current_game->next = (game_reg *) calloc(1, sizeof(game_reg));
    if (current_game->next == NULL) exit(-1); //confirma a correta alocacao de memoria
    current_game->next->game_ID = ((last_game->ID)+1);
    (last_game->ID)++;
    current_game->next->player_name = (char *) calloc(strlen(*(nome_jogadores+jogador))+1, sizeof(char));
    if (current_game->next->player_name == NULL) exit(-1); //confirma a correta alocacao de memoria
    strcpy(current_game->next->player_name, *(nome_jogadores+jogador));
    if (strcmp(current_game->player_name, current_game->next->player_name) == 0) {
      strcpy(current_game->next->player_ID, current_game->player_ID);
    } else {
      sprintf(current_game->next->player_ID, "J%03d", (last_game->player_ID)+1);
      (last_game->player_ID)++;
    }
    current_game->next->colors = defs_jogo.num_cores;
    current_game->next->key_size = defs_jogo.tamanho_chave;
    current_game->next->repet = defs_jogo.repeticao_cores;
    current_game->next->game_time = defs_jogo.duracao_jogo;
    current_game->next->prev = last_game->last;
    last_game->last = current_game->next;
    current_game->next->next = NULL;
    current_game->next->prev = current_game;
  }
}


/******************************************************************************
* Nome da funcao: save_key()
*
* Argumentos: k - indica se a chave de jogo foi acertada
*             *registo_jogo - ponteiro para a lista do registo de jogo
*             jogada[] - tentativa do jogador de acertar a chave
*             tempo_jogo - tempo que o
*             defs_jogo - definicoes de jogo
*             jogador - numero do jogador atual
*
* Return: none
*
* Side-effects: forca a saida caso a alocacao de memoria nao for bem sucedida
*
* Descricao: guarda na lista do registo de jogo a chave de jogo (no caso de ser descoberta)
*
******************************************************************************/
void save_key (int k, game_reg *registo_jogo, char jogada[], time_t tempo_jogo, defs def) {
  game_reg *current_game = registo_jogo;
  char travessao[] = "-";
  while (current_game->next != NULL) {
    current_game = current_game->next;
  }
  /*onde se grava a vitoria*/
  if (k == 1) {
    current_game->game_time = tempo_jogo;
    current_game->key = (char *) calloc(strlen(jogada)+1, sizeof(char));
    if (current_game->key == NULL) exit(-1); //confirma a correta alocacao de memoria
    strcpy(current_game->key, jogada);
  }
  /*onde se mete a derrota*/
  if (k == 0) {
    current_game->game_time = def.duracao_jogo;
    current_game->key = (char *) calloc((strlen(travessao))+1, sizeof(char));
    if (current_game->key == NULL) exit(-1); //confirma a correta alocacao de memoria
    strcpy(current_game->key, travessao);
  }
}


/******************************************************************************
* Nome da funcao: save_guess_ini
*
* Argumentos: *top - .......
*             lugar_certo - numero de cores certas na posicao correta
*             lugar_errado - numero de cores certas na posicao errada
*             tentativa - numero da tentativa do user
*             jogada[] - tentativa para adivinhar a chave efetuada pelo user
*
* Return: none
*
* Side-effects: forca a saida caso a alocacao de memoria nao for bem sucedida
*
* Descricao: cria/guarda na lista de tentativas as tentativas do utilizador
*
******************************************************************************/
void save_guess_ini (game_reg *top, int lugar_certo, int lugar_errado, int tentativa, char jogada[]) {
  game_reg *current_game = top;
  tentativas *current_guess;

  while (current_game->next != NULL) {
    current_game = current_game->next;
  }
  if (tentativa == 0) {  //verifica se primeiro elemento da lista esta preenchido
    current_game->tentativas = tentativa+1;
    current_game->first = (tentativas *) calloc(1, sizeof(tentativas));
    if (current_game->first == NULL) {  //confirma a correta alocacao de memoria
      perror("Erro");
      exit(-1);
    }
    current_guess = current_game->first; //se e a primeira vez que se passa aqui estrutura esta nao esta alocada, dai voltar a fazer isto

    current_guess->tent_ID = tentativa+1;
    current_guess->tentativa = (char *) calloc(strlen(jogada)+1, sizeof(char));
    if (current_guess->tentativa == NULL) { //confirma a correta alocacao de memoria
      perror("Erro");
      exit(-1);
    }
    strcpy(current_guess->tentativa, jogada);
    sprintf(current_guess->resultado, "P%1dB%1d", lugar_certo, lugar_errado);
    current_guess->prev = NULL;
    current_guess->next = NULL;
  } else {
    current_guess = current_game->first;
    while (current_guess->next != NULL) {
      current_guess = current_guess->next;
    }
    current_game->tentativas = tentativa+1;
    current_guess->next = (tentativas *) calloc(1, sizeof(tentativas));
    if (current_guess->next == NULL) {  //confirma a correta alocacao de memoria
      perror("Erro");
      exit(-1);
    }
    current_guess->next->tent_ID = tentativa+1;
    current_guess->next->tentativa = (char *) calloc(strlen(jogada)+1, sizeof(char));
    if (current_guess->next->tentativa == NULL) { //confirma a correta alocacao de memoria
      perror("Erro");
      exit(-1);
    }
    strcpy(current_guess->next->tentativa, jogada);
    sprintf(current_guess->next->resultado, "P%1dB%1d", lugar_certo, lugar_errado);
    current_guess->next->prev = current_guess;
    current_guess->next->next = NULL;
  }
}
