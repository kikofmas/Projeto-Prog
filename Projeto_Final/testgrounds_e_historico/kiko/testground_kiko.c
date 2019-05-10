/****************************
*       testground KIKO    *
****************************/



int main(int argc, char const *argv[]) {

/*falta implementar isto e testar a minha copia.........*/


void read_hist_file_2(char const *argv[], int arg_num);


  if (cmd_flag->hist != 0) {
    read_hist_file_1(argv, *flags->hist, &last_game);
    if (cmd_flag->ord != 0) read_hist_file_2(argv, *flags->hist);
  }

void read_hist_file_2(char const *argv[], int arg_num, game_reg **registo_jogo) {
  game_reg *current;
  char name[50]="\0", key[10]="\0";
  FILE *fptr=fopen(argv[arg_num], "r");
  *registo_jogo=calloc(1, sizeof(game_reg));
  current=*registo_jogo;
  fscanf(fptr, "%d %s %s %d %d %c %s %d %f\n", current->game_ID, current->player_ID, name, current->colors,
        current->key_size, current->repet, key, current->tentativas, current->game_time);
  current->key=calloc(strlen(key)+1, sizeof(char));
  current->player_name=calloc(strlen(name)+1, sizeof(char));
  strcpy(current->key, key);
  strcpy(current->player_name, name);
  while(!feof(fptr)){
    current->next=calloc(1, sizeof(game_reg));
    fscanf(fptr, "%d %s %s %d %d %c %s %d %f\n", current->next->game_ID, current->next->player_ID, name, current->next->colors,
          current->next->key_size, current->next->repet, key, current->next->tentativas, current->next->game_time);
    current->key=calloc(strlen(key)+1, sizeof(char));
    current->player_name=calloc(strlen(name)+1, sizeof(char));
    strcpy(current->key, key);
    strcpy(current->player_name, name);
    current->next->next=NULL;
    current=current->next;
  }
}






  if (cmd_flag->ord != 0) {
    sort_registry(&registo_jogo, cmd_flag->ord, argv);
  }







  return 0;
}







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



void save_game_ini(game_reg *registo_jogo, int hist_file);
void save_key(int k, game_reg *registo_jogo, char jogada[]);
void save_guess_ini(game_reg *top);
void sort_registry(game_reg **registo_jogo, int pos, char *argv[]);
game_reg *recursive_bubble_sort_fast(game_reg *current, game_reg *limit);
game_reg *recursive_bubble_sort_short(game_reg *current, game_reg *limit);
void reord_2_elements(game_reg *ptr);

void free_guess_list(guess_list *current);
void free_game_registry(game_reg *current);





void save_game_ini (game_reg *registo_jogo, int hist_file) {
  int pid=0;
  static int k=0; //se houver ficheiro hmmmmm
  game_reg *current_game; //chama-se current mas isso so e vdd para a primeira vez, a partir dai e o anterior
  //inicio de jogo
  /*isto so funciona se leres o ficheiro -h antes e meteres o pointer a apontar para a lista
  caso se implemente de maneira diferente tenho de mudar isto*/
  current_game=registo_jogo;
  while (current_game->next != NULL){
    current_game = current_game->next;
    k=1;
  }
  if (k==0 && hist_file==0) {  //verifica se primeiro elemento da lista esta preenchido
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
    last_game->ID=current_game->ID;
    strcpy(last_game->player_ID, current_game->player_ID);
    last_game->last=current_game;
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
    last_game->ID=current_game->next->ID;
    strcpy(last_game->player_ID, current_game->next->player_ID);
    last_game->last=current_game->next;
  }
}


void read_hist_file_1(char const *argv[], int arg_num, hist_data *last_game){

  int k=0, a=0, b=0, a1=0, a2=0;

  FILE *fptr=fopen(argv[arg_num], "r");

  while(!feof(fptr)){
    fscanf(fptr, "%d J%d %* %* %* %* %* %d %*[^\n]\n", a, b, NULL, NULL, NULL, NULL, NULL, NULL, &k, NULL);
    for (int i = 0; i < k; i++) {
      fscanf(fptr, "%*[^\n]\n", NULL);
    }
    if (a>a1) a1=a;
    if (b>b1) b1=b;
  }
  if (b1>998) b1=0;
  sprintf(last_game->ID, "J%03d", a1);
  sprintf(last_game->player_ID, "J%03d", b1);
}


void save_key(int k, game_reg *registo_jogo, char jogada[]){
  current_game = registo_jogo;
  char travessao[] = "-";
  while (current_game->next != NULL){
    current_game = current_game->next;
  }
  /*onde se grava a vitoria*/
  if(k==1) strcpy(current_game->key, jogada);
  /*onde se mete a derrota*/
  if(k==0) strcpy(current_game->key, travessao);
}


void save_guess_ini(game_reg *top) {
  int k=0;//flag que verifica se existe o primeiro elemento da lista
  game_reg current_game=top;
  guess_list *current_guess;

  while (current_game->next != NULL){
    current_game = current_game->next;
  }
  current_guess=current_game->first;
  while (current_guess->next != NULL){
    current_guess = current_guess->next;
    k=1;
  }
  if (k==0) {  //verifica se primeiro elemento da lista esta preenchido
    current_game->tentativas=tentativa+1;
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
    current_game->next->tentativas=tentativa+1;
    current_guess->next=calloc(1, sizeof(guess_list));
    current_guess->next->guess_ID=tentativa+1;
    current_guess->next->guess=calloc((defs_jogo->tamanho_chave)+1, sizeof(char));
    strcpy(current_guess->next->guess, jogada);
    sprintf(current_guess->next->result, "P%1dB%1d", lugar_certo, lugar_errado);
    current_guess->next->prev=current_guess;
    current_guess->next->next=NULL;
  }
}


void sort_registry(game_reg **registo_jogo, int pos, char *argv[]){
  if (strcmp(fast, argv[pos]) == 0) {
    *registo_jogo=recursive_bubble_sort_fast(registo_jogo, NULL);
  } else if (strcmp(short, argv[pos]) == 0) {
    registo_jogo=recursive_bubble_sort_short(registo_jogo, NULL);
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
