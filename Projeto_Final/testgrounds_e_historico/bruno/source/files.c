//LIBRARIES
#include <stdlib.h>
#include <stdio.h>
#include <string.h>   //funcoes de strings

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
void write_file_raw(tentativas *lista_tentativas, char const *argv[], char *file, int mode, hist_data *last_game, char **nome, int tent, int tempo, defs defs_jogo, int win){
  tentativas *aux=lista_tentativas;
  FILE *fptr;
  char copy[10];

  if (mode!= 0) fptr = fopen(argv[mode],"ab");
  else fptr = fopen(file,"ab");

  if(fptr==NULL){
    perror("Erro (ficheiro hist)");
    exit(-1);
  }

  while(aux->next!=NULL) aux=aux->next;

  strcpy(copy, aux->tentativa);
  if(win==0){
    strcpy(aux->tentativa, "-");
  }

  fprintf(fptr, "%d J%03d %s %d %d %c %s %d %.3f\n", ++(last_game->ID), last_game->player_ID, nome[0], defs_jogo.num_cores,
                                                   defs_jogo.tamanho_chave, defs_jogo.repeticao_cores, aux->tentativa, tent, (float)tempo/1000);

  strcpy(aux->tentativa, copy);
  aux=lista_tentativas;
  while(aux!=NULL){
    fprintf(fptr, "%d %s %s\n", aux->tent_ID, aux->tentativa, aux->resultado);
    aux=aux->next;
  }

  fclose(fptr);

}
void write_file(game_reg *reg, char const *argv[], char *file, int mode){
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






