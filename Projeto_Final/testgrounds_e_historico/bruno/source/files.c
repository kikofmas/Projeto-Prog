//LIBRARIES
#include <stdlib.h>
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <ctype.h>

#include "estruturas.h"
#include "files.h"


/******************************************************************************
* Nome da funcao: read_init()
*
* Argumentos: *file - ficheiro de inicializacao
*             *ptr - ponteiro para a estrutura que guarda as definicoes de jogo
*             ***nome - ponteiro para o(s) nome(s) do(s) jogadore(s)
*
* Return: none
*
* Side-effects: forca a saida caso nao seja possivel abrir o ficheiro ou
*               a alocacao de memoria nao for bem sucedida
*
* Descricao: le o ficheiro de inicializacao e guarda os dados numa estrutura
*
******************************************************************************/
void read_init (char const * file, defs *ptr, char ***nome) {
  char *text = NULL, *token = NULL, c = '\0';
  int counter = 1;
  FILE *fptr = fopen(file,"rb");

  if (fptr != NULL) { //confirma que o ficheiro foi corretamente aberto
    text = (char *) malloc(sizeof(char));
    if (text==NULL) exit(-1);  //confirma a correta alocacao de memoria
    while((c=fgetc(fptr))!=EOF){  //loop para guarda o conteudo do ficheiro de init
      text = (char *)realloc(text,counter);
      if(text==NULL) exit(-1);  //confirma a correta alocacao de memoria
      text[counter-1]=c;
      counter++;
    }
    fclose(fptr);

    token = strtok(text,"\n");
    *nome = (char **)malloc(sizeof(char*));
    if(*nome==NULL) exit(-1); //confirma a correta alocacao de memoria
    **nome = (char *)malloc((strlen(token)+1)*sizeof(char));
    if(**nome==NULL) exit(-1);  //confirma a correta alocacao de memoria
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


/******************************************************************************
* Nome da funcao: hist_max_values()
*
* Argumentos: *argv[] - valores inseridos atraves da linha de comandos
*             arg_num - indica o argumento a ler (ficheiro a abrir)
*             *last_game - ponteiro para a estrutura que guarda os valores
*                          descobertos na execucao da funcao
*             *file - ficheiro secundario a abrir
*
* Return: none
*
* Side-effects: se o ficheiro passado pela linha de comandos nao existir,
*               este e criado
*               forca a saida caso nao seja possivel abrir o ficheiro
*
* Descricao: encontra os valores mais elevados do ID de jogador e ID de jogo
*
******************************************************************************/
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

  if(fptr==NULL){ //confirma que o ficheiro foi bem aberto
    perror("ERRO (ficheiro hist)");
    exit(-1);
  }

  while(feof(fptr)==0){ //scan do ficheiro de historico
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


/******************************************************************************
* Nome da funcao: read_hist()
*
* Argumentos: *argv[] - valores inseridos atraves da linha de comandos
*             arg_num - indica o argumento a ler (ficheiro a abrir)
*             *last_game - ponteiro para a estrutura que guarda os valores
*                          descobertos na execucao da funcao
*             *file - ficheiro secundario a abrir
*
* Return: none
*
* Side-effects: forca a saida caso nao seja possivel abrir o ficheiro ou
*               a alocacao de memoria nao for bem sucedida
*
* Descricao: le o ficheiro de historico e cria a lista que contem o registo de jogo
*
******************************************************************************/
void read_hist(char const *argv[], int arg_num, game_reg **registo_jogo, char *file, int mode){
  game_reg *current;
  tentativas *aux;
  char name[50]="\0", key[10]="\0", tentativa[10]="\0";

  FILE *fptr;
  if(mode==0) fptr=fopen(file, "rb");
  else if(mode!=0) fptr=fopen(argv[arg_num], "rb");

  if(fptr==NULL){ //confirma se o ficheiro foi bem aberto
    perror("ERRO (ficheiro hist)");
    exit(-1);
  }

  *registo_jogo=calloc(1, sizeof(game_reg));
  if(*registo_jogo==NULL) exit(-1); //confirma a correta alocacao de memoria

  current=*registo_jogo;

  fscanf(fptr, "%d %s %s %d %d %c %s %d %f\n", &(current->game_ID), current->player_ID, name, &(current->colors), &(current->key_size),
                                               &(current->repet), key, &(current->tentativas), &(current->game_time));

  current->key=calloc(strlen(key)+1, sizeof(char));
  if(current->key==NULL) exit(-1); //confirma a correta alocacao de memoria
  strcpy(current->key, key);
  current->player_name=calloc(strlen(name)+1, sizeof(char));
  if(current->player_name==NULL) exit(-1); //confirma a correta alocacao de memoria
  strcpy(current->player_name, name);
  current->next=NULL;
  current->prev=NULL;
  current->first = calloc(1,sizeof(tentativas));
  if(current->first==NULL) exit(-1);//confirma que a correta alocacao de memoria
  fscanf(fptr, "%d %s %s\n", &(current->first->tent_ID), tentativa, current->first->resultado);
  current->first->tentativa = calloc(strlen(tentativa)+1,sizeof(char));
  if(current->first->tentativa==NULL) exit(-1); //confirma a correta alocacao de memoria
  strcpy(current->first->tentativa, tentativa);
  current->first->next = NULL;
  current->first->prev = NULL;
  aux = current->first;
  for(int i=1;i<(current->tentativas);i++){
    aux->next = calloc(1,sizeof(tentativas));
    if(aux->next==NULL) exit(-1); //confirma a correta alocacao de memoria
    fscanf(fptr, "%d %s %s\n", &(aux->next->tent_ID), tentativa, aux->next->resultado);
    aux->next->tentativa = calloc(strlen(tentativa)+1,sizeof(char));
    if(aux->next->tentativa==NULL) exit(-1);  //confirma a correta alocacao de memoria
    strcpy(aux->next->tentativa, tentativa);
    aux->next->next = NULL;
    aux->next->prev = aux;
    aux=aux->next;
  }

  while(!feof(fptr)){ //loop ate chegar ao final do ficheiro
    current->next=calloc(1, sizeof(game_reg));
    if(current->next==NULL) exit(-1); //confirma a correta alocacao de memoria

    fscanf(fptr, "%d %s %s %d %d %c %s %d %f\n", &(current->next->game_ID), current->next->player_ID, name, &(current->next->colors),
                                                 &(current->next->key_size), &(current->next->repet), key, &(current->next->tentativas),
                                                 &(current->next->game_time));

    current->next->key=calloc(strlen(key)+1, sizeof(char));
    if(current->next->key==NULL) exit(-1);  //confirma a correta alocacao de memoria
    strcpy(current->next->key, key);
    current->next->player_name=calloc(strlen(name)+1, sizeof(char));
    if(current->next->player_name==NULL) exit(-1);  //confirma a correta alocacao de memoria
    strcpy(current->next->player_name, name);
    current->next->next=NULL;
    current->next->prev=current;
    current->next->first = calloc(1,sizeof(tentativas));
    if(current->next->first==NULL) exit(-1);  //confirma a correta alocacao de memoria
    fscanf(fptr, "%d %s %s\n", &(current->next->first->tent_ID), tentativa, current->next->first->resultado);
    current->next->first->tentativa = calloc(strlen(tentativa)+1,sizeof(char));
    if(current->next->first->tentativa==NULL) exit(-1); //confirma a correta alocacao de memoria
    strcpy(current->next->first->tentativa, tentativa);
    current->next->first->next = NULL;
    current->next->first->prev = NULL;
    aux = current->next->first;
    for(int i=1;i<(current->next->tentativas);i++){
      aux->next = calloc(1,sizeof(tentativas));
      if(aux->next==NULL) exit(-1); //confirma a correta alocacao de memoria
      fscanf(fptr, "%d %s %s\n", &(aux->next->tent_ID), tentativa, aux->next->resultado);
      aux->next->tentativa = calloc(strlen(tentativa)+1,sizeof(char));
      if(aux->next->tentativa==NULL) exit(-1);  //confirma a correta alocacao de memoria
      strcpy(aux->next->tentativa, tentativa);
      aux->next->next = NULL;
      aux->next->prev = aux;
      aux=aux->next;
    }

    current=current->next;
  }
  fclose(fptr);
}


/******************************************************************************
* Nome da funcao: write_file_raw()
*
* Argumentos: *lista_tentativas - lista das tentativas efetuadas ao longo do jogo
*             *argv[] - valores inseridos atraves da linha de comandos
*             *file - ficheiro secundario a abrir
*             mode - indica o ficheiro a abrir
*             *last_game - estrutura com os dados maximos dos jogos anteriores
*             **nome - ponteiro para o nome dos jogadores
*             tent - numero de tentativas efetuadas
*             tempo - duracao do jogo (em milissegundos)
*             defs_jogo - estrutura com as definicoes de jogo
*             win - variavel que indica se a chave foi descoberta
*
* Return: none
*
* Side-effects: forca a saida caso nao seja possivel abrir o ficheiro
*
* Descricao: escreve os dados de jogo no ficheiro de historico
*
******************************************************************************/
void write_file_raw(tentativas *lista_tentativas, char const *argv[], char *file, int mode, hist_data *last_game, char **nome, int tent, int tempo, defs defs_jogo, int win){
  tentativas *aux=lista_tentativas;
  FILE *fptr;
  char copy[10];

  if (mode!= 0) fptr = fopen(argv[mode],"ab");
  else fptr = fopen(file,"ab");

  if(fptr==NULL){ //confirma se o ficheiro foi bem aberto
    perror("Erro (ficheiro hist)");
    exit(-1);
  }

  while(aux->next!=NULL) aux=aux->next; //loop para chegar a ultima tentativa efetuada

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


/******************************************************************************
* Nome da funcao: write_file()
*
* Argumentos: *reg - lista com o registo de jogo
*             *argv[] - valores inseridos atraves da linha de comandos
*             *file - ficheiro secundario a abrir
*             mode - indica o ficheiro a abrir
*
* Return: none
*
* Side-effects: forca a saida caso nao seja possivel abrir o ficheiro
*
* Descricao: escreve os dados de jogo no ficheiro de historico
*
******************************************************************************/
void write_file(game_reg *reg, char const *argv[], char *file, int mode){
  FILE *fptr;
  game_reg *current = reg;
  tentativas *aux;

  if(mode==-1) fptr= fopen(file,"ab");
  else if(mode==0) fptr= fopen(file,"wb");
  else fptr= fopen(argv[mode],"wb");

  if(fptr==NULL){ //confirma se o ficheiro foi bem aberto
    perror("Erro (ficheiro hist)");
    exit(-1);
  }

  while(current!=NULL){
    fprintf(fptr, "%d %s %s %d %d %c %s %d %.3f\n", current->game_ID, current->player_ID, current->player_name,
                                                    current->colors, current->key_size, toupper(current->repet),
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
