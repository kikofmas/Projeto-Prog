//LIBRARIES
#include <stdlib.h>
#include <errno.h>    //library de error handling
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions
#include <unistd.h>   //permite usar a funcao sleep
#include <termios.h>  //permite usar a funcao tcflush

#include "estruturas.h"
#include "files.h"

void read_init(char const * file, defs *ptr, char ***nome){
  char *text=NULL, *token=NULL, c='\0';
  int counter=1;
  FILE *fptr = fopen(file,"rb");

  if(fptr!=NULL){
    text = (char *)malloc(sizeof(char));
    while((c=fgetc(fptr))!=EOF){
      text = (char *)realloc(text,counter);
      text[counter-1]=c;
      counter++;
    }
    fclose(fptr);

    token = strtok(text,"\n");
    *nome = (char **)malloc(sizeof(char*));
    if(*nome==NULL) exit(-1);
    **nome = (char *)malloc((strlen(token)+1)*sizeof(char));
    if(**nome==NULL) exit(-1);
    strcpy(**nome,token);
    token = strtok(NULL,"\n");
    ptr->num_jogos = atoi(token);
    token = strtok(NULL,"\n");
    ptr->num_cores = atoi(token);
    token = strtok(NULL,"\n");
    ptr->tamanho_chave = atoi(token);
    token = strtok(NULL,"\n");
    ptr->repeticao_cores = token[0];
    token = strtok(NULL,"\n");
    ptr->tentativas_alea = atoi(token);
    token = strtok(NULL,"\n");
    ptr->tentativas = atoi(token);
    free(text);
  }
  else{
    perror("ERRO (ficheiro init)");
    exit(-1);
  }
}


void hist_max_values(char const *argv[], int arg_num, hist_data *last_game, char *file){
  int err_num;
  char err[10];

  int a=0,b=0,a1=0,b1=0,k=0;

  FILE *fptr;
  if(arg_num!=0){
    fptr = fopen(argv[arg_num],"ab"); //no caso do ficheiro nao existir este e criado
    fclose(fptr);
    fptr=fopen(argv[arg_num], "rb");
  }
  else if(arg_num==0){
    fptr = fopen(file,"ab"); //no caso do ficheiro nao existir este e criado
    fclose(fptr);
    fptr=fopen(file, "rb");
  }

  if(fptr==NULL){
    perror("ERRO (ficheiro hist)");
    exit(-1);
  }

  while(feof(fptr)==0){
    fscanf(fptr, "%d J%d %*s %*s %*s %*s %*s %d %*[^\n]", &a, &b, &k);
    for (int i = 0; i < k; i++) {
      fscanf(fptr, "%d %s %s", &err_num, err, err);
    }
    if(a1<a) a1=a;
    if(b1<b) b1=b;
  }
  if (b1>998) b1=0;
  last_game->ID=a1;
  last_game->player_ID = b1;
  fclose(fptr);
}

void read_hist(char const *argv[], int arg_num, game_reg **registo_jogo, char *file, int mode){
  game_reg *current;
  tentativas *aux;
  char name[50]="\0", key[10]="\0", tentativa[10]="\0";

  FILE *fptr;
  if(mode==0) fptr=fopen(file, "rb");
  else if(mode!=0) fptr=fopen(argv[arg_num], "rb");

  if(fptr==NULL){
    perror("ERRO (ficheiro hist)");
    exit(-1);
  }

  *registo_jogo=calloc(1, sizeof(game_reg));
  if(*registo_jogo==NULL) exit(-1);

  current=*registo_jogo;

  fscanf(fptr, "%d %s %s %d %d %c %s %d %f\n", &(current->game_ID), current->player_ID, name, &(current->colors), &(current->key_size),
                                               &(current->repet), key, &(current->tentativas), &(current->game_time));

  current->key=calloc(strlen(key)+1, sizeof(char));
  current->player_name=calloc(strlen(name)+1, sizeof(char));
  strcpy(current->key, key);
  strcpy(current->player_name, name);
  current->next=NULL;
  current->prev=NULL;
  current->first = calloc(1,sizeof(tentativas));
  fscanf(fptr, "%d %s %s\n", &(current->first->tent_ID), tentativa, current->first->resultado);
  current->first->tentativa = calloc(strlen(tentativa)+1,sizeof(char));
  strcpy(current->first->tentativa, tentativa);
  current->first->next = NULL;
  current->first->prev = NULL;
  aux = current->first;
  for(int i=1;i<(current->tentativas);i++){
    aux->next = calloc(1,sizeof(tentativas));
    fscanf(fptr, "%d %s %s\n", &(aux->next->tent_ID), tentativa, aux->next->resultado);
    aux->next->tentativa = calloc(strlen(tentativa)+1,sizeof(char));
    strcpy(aux->next->tentativa, tentativa);
    aux->next->next = NULL;
    aux->next->prev = aux;
    aux=aux->next;
  }

  while(!feof(fptr)){
    current->next=calloc(1, sizeof(game_reg));
    fscanf(fptr, "%d %s %s %d %d %c %s %d %f\n", &(current->next->game_ID), current->next->player_ID, name, &(current->next->colors),
                                                 &(current->next->key_size), &(current->next->repet), key, &(current->next->tentativas),
                                                 &(current->next->game_time));
    current->next->key=calloc(strlen(key)+1, sizeof(char));
    current->next->player_name=calloc(strlen(name)+1, sizeof(char));
    strcpy(current->next->key, key);
    strcpy(current->next->player_name, name);
    current->next->next=NULL;
    current->next->prev=current;
    current->next->first = calloc(1,sizeof(tentativas));
    fscanf(fptr, "%d %s %s\n", &(current->next->first->tent_ID), tentativa, current->next->first->resultado);
    current->next->first->tentativa = calloc(strlen(tentativa)+1,sizeof(char));
    strcpy(current->next->first->tentativa, tentativa);
    current->next->first->next = NULL;
    current->next->first->prev = NULL;
    aux = current->next->first;
    for(int i=1;i<(current->next->tentativas);i++){
      aux->next = calloc(1,sizeof(tentativas));
      fscanf(fptr, "%d %s %s\n", &(aux->next->tent_ID), tentativa, aux->next->resultado);
      aux->next->tentativa = calloc(strlen(tentativa)+1,sizeof(char));
      strcpy(aux->next->tentativa, tentativa);
      aux->next->next = NULL;
      aux->next->prev = aux;
      aux=aux->next;
    }

    current=current->next;
  }
  fclose(fptr);
}




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


void write_file_unord(tentativas *lista_tentativas, char const *argv[], char *file, int mode, hist_data *last_game, char **nome, int tent, int tempo, defs defs_jogo){
  tentativas *aux=lista_tentativas;
  FILE *fptr;

  if (mode!= 0) fptr = fopen(argv[mode],"ab");
  else fptr = fopen(file,"ab");

  if(fptr==NULL){
    perror("Erro (ficheiro hist)");
    exit(-1);
  }

  while(aux->next!=NULL) aux=aux->next;

  fprintf(fptr, "%d J%03d %s %d %d %c %s %d %.3f\n", ++(last_game->ID), last_game->player_ID, nome[0], defs_jogo.num_cores,
                                                   defs_jogo.tamanho_chave, defs_jogo.repeticao_cores, aux->tentativa, tent, (float)tempo/1000);
  aux=lista_tentativas;
  while(aux!=NULL){
    fprintf(fptr, "%d %s %s\n", aux->tent_ID, aux->tentativa, aux->resultado);
    aux=aux->next;
  }

  fclose(fptr);

}


void write_file_ord(game_reg *reg, char const *argv[], char *file, int mode){
  FILE *fptr;
  game_reg *current = reg;
  tentativas *aux;

  if(mode==0) fptr= fopen(file,"wb");
  else fptr= fopen(argv[mode],"wb");

  if(fptr==NULL){
    perror("Erro (ficheiro hist)");
    exit(-1);
  }

  while(current!=NULL){
    fprintf(fptr, "%d %s %s %d %d %c %s %d %.3f\n", current->game_ID, current->player_ID, current->player_name,
                                                    current->colors, current->key_size, current->repet,
                                                    current->key, current->tentativas, current->game_time);
    aux = current->first;
    while(aux!=NULL){
      fprintf(fptr, "%d %s %s\n", aux->tent_ID, aux->tentativa, aux->resultado);
      aux=aux->next;
    }
    current=current->next;
  }
  fclose(fptr);
}





void save_game_ini(game_reg **registo_jogo, int hist_file, int ord, hist_data *last_game, char **nome_jogadores, defs defs_jogo, int jogador){
  static int k=0; //se houver ficheiro hmmmmm
  game_reg *current_game=*registo_jogo; //chama-se current mas isso so e vdd para a primeira vez, a partir dai e o anterior
  //inicio de jogo
  /*isto so funciona se leres o ficheiro -h antes e meteres o pointer a apontar para a lista
  caso se implemente de maneira diferente tenho de mudar isto*/
  if (k==0 && !(hist_file!=0 && ord!=0)) {  //verifica se primeiro elemento da lista esta preenchido
    registo_jogo=calloc(1, sizeof(game_reg));
    current_game=*registo_jogo; //se e a primeira vez que se passa aqui estrutura esta nao esta alocada, dai voltar a fazer isto

    current_game->game_ID=((last_game->ID)+1);
    (last_game->ID)++;
    current_game->player_name=calloc(strlen(*(nome_jogadores+jogador))+1, sizeof(char));
    strcpy(current_game->player_name, *(nome_jogadores+jogador));
    sprintf(current_game->player_ID, "J%03d", (last_game->player_ID)+1);
    (last_game->player_ID)++;
    current_game->colors=defs_jogo.num_cores;
    current_game->key_size=defs_jogo.tamanho_chave;
    current_game->repet=defs_jogo.repeticao_cores;
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

void save_key(int k, game_reg *registo_jogo, char jogada[]){
  game_reg *current_game = registo_jogo;
  char travessao[] = "-";
  while (current_game->next != NULL){
    current_game = current_game->next;
  }
  /*onde se grava a vitoria*/
  if(k==1) {
    current_game->key=calloc((strlen(jogada))+1, sizeof(char));
    strcpy(current_game->key, jogada);
  }
  /*onde se mete a derrota*/
  if(k==0) {
    current_game->key=calloc((strlen(travessao))+1, sizeof(char));
    strcpy(current_game->key, travessao);
  }
}

void save_guess_ini(game_reg *top, int lugar_certo, int lugar_errado, int tentativa, defs defs_jogo, char jogada[]) {
  game_reg *current_game=top;
  tentativas *current_guess;

  while (current_game->next != NULL){
    current_game = current_game->next;
  }
  if (tentativa==0) {  //verifica se primeiro elemento da lista esta preenchido
    current_game->tentativas=tentativa+1;
    current_game->first=calloc(1, sizeof(tentativas));
    current_guess=current_game->first; //se e a primeira vez que se passa aqui estrutura esta nao esta alocada, dai voltar a fazer isto

    current_guess->tent_ID=tentativa+1;
    current_guess->tentativa=calloc((strlen(jogada))+1, sizeof(char));
    strcpy(current_guess->tentativa, jogada);
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
    current_guess->next->tent_ID=tentativa+1;
    current_guess->next->tentativa=calloc((strlen(jogada))+1, sizeof(char));
    strcpy(current_guess->next->tentativa, jogada);
    sprintf(current_guess->next->resultado, "P%1dB%1d", lugar_certo, lugar_errado);
    current_guess->next->prev=current_guess;
    current_guess->next->next=NULL;
  }
}