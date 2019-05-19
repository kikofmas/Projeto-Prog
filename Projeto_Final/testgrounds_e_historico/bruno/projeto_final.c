/******************************************************************************
*
* Projeto intermedio de programacao - MASTERMIND
*
* Bruno Miguel da Silva Cebola - 93030
* Frederico Maria Almeida Santos - 93065
*
******************************************************************************/

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
#include "oraculo.h"
#include "intermedio.h"
#include "key.h"
#include "files.h"



typedef struct guess_t {
  int guess_ID;
  char *guess;
  char result[5];
  struct guess_t *next;
  struct guess_t *prev;
}guess_list;

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

typedef struct {
  int ID;
  char player_ID[5];
  game_reg *last;
}hist_data;


//DECLARACAO DE FUNCOES

int mode_check(int argc, char const *argv[], flags *cmd_flag);
int test_mode_config(int k, char const *argv[], flags **cmd_flag);



void read_hist_file_1(char const *argv[], int arg_num, hist_data *last_game);
void read_hist_file_2(char const *argv[], int arg_num, game_reg **registo_jogo);

void save_game_ini(game_reg **registo_jogo, int hist_file, int ord, hist_data last_game, char **nome_jogadores, defs defs_jogo, int jogador);
void save_key(int k, game_reg *registo_jogo, char jogada[]);
void save_guess_ini(game_reg *top, int lugar_certo, int lugar_errado, int tentativa, defs defs_jogo, char jogada[]);
void sort_registry(game_reg **registo_jogo, int pos, char const *argv[]);
game_reg *recursive_bubble_sort_fast(game_reg *current, game_reg *limit);
game_reg *recursive_bubble_sort_short(game_reg *current, game_reg *limit);
void reord_2_elements(game_reg *ptr);

void clear_memory(char **vect1, int v1, dados **ptr_dados, float *vect3, int *vect4, game_reg *registo_jogo);
void free_guess_list(guess_list *current);
void free_game_registry(game_reg *current);


int main(int argc, char const *argv[]) {

//declaracao das variaveis para o modo de funcionamento do programa
  int mod_inter=0;
  flags cmd_flag={0, 0, 0};

//declaracao das variaveis da inicializacao:
  char **nome_jogadores=NULL;
  int combo_possivel=0, rep=0, num_total_tent=0, win=0, tempo=0;
  defs defs_jogo={'\0',0,0,0,0,0,0,0};
  letras **lista_cores=NULL;
  tentativas *lista_tentativas=NULL;

//declaracao das variaveis das estatisticas:
  dados **ptr_dados=NULL; //[][][0]=tempo, [][][1]=tentativas, [][][2]=vitoria
  int *numVitorias=NULL;
  float *mediaTempos=NULL;
  game_reg *registo_jogo;
  hist_data last_game={0, "J000", NULL};

//inicializacao da funcao srand:
  time_t t;
  srand((unsigned) time(&t)); //inicializa o gerador aleatorio

  mode_check(argc, argv, &cmd_flag);

  if (cmd_flag.init==0 && cmd_flag.hist==0 && cmd_flag.ord==0) {
    printf("MODO INTERATIVO\n\n");
    printf("1) Jogador Vs. Jogador\n");
    printf("2) Jogador Vs. Computador\n\n");
    printf("Opcao: ");
    scanf("%d", &mod_inter);
    printf("\n");

    cleanslate();

    if (mod_inter==1) {
    //INICIALIZACAO DAS VARIAVEIS DE JOGO
      introducao();
      //numero de jogadores
      initialization(&defs_jogo.num_jogadores, 1, 4, "o numero de jogadores");
      //nome dos jogadores
      nome_jogadores=initializationNames(defs_jogo.num_jogadores);
      //numero de jogos
      initialization(&defs_jogo.num_jogos, 1, 5, "o numero de jogos");
      //numero maximo de tentivas por jogo
      initialization(&defs_jogo.tentativas, 10, 20, "o numero maximo de tentativas");
      //duracao de cada jogo
      initialization(&defs_jogo.duracao_jogo, 60, 300, "o tempo de jogo (em segundos)");
      do {
      //dimensao da chave
        initialization(&defs_jogo.tamanho_chave, 4, 8, "a dimensao da chave com que deseja jogar");
      //numero de cores em jogo
        initialization(&defs_jogo.num_cores, 6, 12, "o numero de cores com que deseja jogar");
      //repeticao de cores
        initializationRepetitions(&defs_jogo.repeticao_cores);
      //verificacao de que a combinacao de parametros e possivel
        combo_possivel=checkCombinacao(&defs_jogo);
      } while(combo_possivel == -1);
      if(tolower(defs_jogo.repeticao_cores) == 's') rep=1;
      clearScreen(1);

    //JOGO
      //activate_oracle(defs_jogo.tamanho_chave, defs_jogo.num_cores, rep);
      ptr_dados=jogo(defs_jogo, nome_jogadores);
    //ESTATISTICAS: calculo dos resultados e apresentacao das estatisticas

      criaDados(defs_jogo.num_jogadores, defs_jogo.num_jogos, ptr_dados, &mediaTempos, &numVitorias);
      vencedor(mediaTempos, nome_jogadores, defs_jogo.num_jogadores, numVitorias);
      resultados(defs_jogo.num_jogadores, defs_jogo.num_jogos, ptr_dados, 0, "mais rapido", nome_jogadores);
      resultados(defs_jogo.num_jogadores, defs_jogo.num_jogos, ptr_dados, 1, "mais curto", nome_jogadores);
      showData(ptr_dados, mediaTempos, defs_jogo.num_jogadores, numVitorias, defs_jogo.num_jogos, nome_jogadores);

      printf("\nESPERAMOS QUE SE TENHA DIVERTIDO!!!\n");

      clear_memory_intermedio(nome_jogadores, defs_jogo.num_jogadores, ptr_dados, mediaTempos, numVitorias);
    } else if(mod_inter == 2) {
      read_init(argv[cmd_flag.init], &defs_jogo, &nome_jogadores);

      if(tolower(defs_jogo.repeticao_cores)=='s') rep=1;
      activate_oracle(defs_jogo.tamanho_chave, defs_jogo.num_cores, rep);

      //for(int i=0;i<defs_jogo.num_jogos;i++){
        //printf("\nJogo %d\n",i);
        lista_cores = listaCores(defs_jogo.tamanho_chave, defs_jogo.num_cores);
        lista_tentativas = tentativasAlea(defs_jogo.tentativas_alea, defs_jogo.tamanho_chave, defs_jogo.num_cores, &num_total_tent, &lista_cores, &win, &tempo, mod_inter);

        if (win==0) {
          win = keyFinder(defs_jogo.tamanho_chave, &lista_cores, &lista_tentativas, &num_total_tent, &tempo, mod_inter);
        }
        printf("\nNumero de tentativas: %d\n", num_total_tent);
        clear(defs_jogo.tamanho_chave, &lista_tentativas, &lista_cores);
        num_total_tent = 0;
        //sleep(1);
      //}

      printf("%d\n", tempo);
      terminate_oracle();
      free(nome_jogadores[0]);
      free(nome_jogadores);

    }
  }
  else if (cmd_flag.init == 0  &&  cmd_flag.hist != 0  &&  cmd_flag.ord != 0) {
    printf("MODO TESTE\nAPENAS REORDENAÇAO\n\n");
    read_hist_file_2(argv, cmd_flag.hist, &registo_jogo);
    sort_registry(&registo_jogo, cmd_flag.ord, argv);
    return 0;
  }
  else if (cmd_flag.init==0 && ((cmd_flag.hist != 0  &&  cmd_flag.ord == 0) || (cmd_flag.hist == 0  &&  cmd_flag.ord != 0))) {
    printf("ERRO: Falta o ficheiro das inicializações\n");
    exit(-1);}
  else if (cmd_flag.init!=0) {
    printf("MODO TESTE\n\n");
    /* jogar EvE */
    /*load init files and others if needed -- use ifs to allow or not passage*/


    if (cmd_flag.hist != 0) {
      read_hist_file_1(argv, cmd_flag.hist, &last_game);
      if (cmd_flag.ord != 0) read_hist_file_2(argv, cmd_flag.hist, &registo_jogo);
    }



    read_init("init.dat", &defs_jogo, &nome_jogadores);
    if(tolower(defs_jogo.repeticao_cores) == 's') rep=1;

    activate_oracle(defs_jogo.tamanho_chave, defs_jogo.num_cores, rep);

    for (int i = 0; i < defs_jogo.num_jogos; i++) {
      printf("\nJogo %d\n", i);
      printf("Chave: ");
      generate_key(1);
      printf("\n");

      lista_cores = listaCores(defs_jogo.tamanho_chave, defs_jogo.num_cores);
      lista_tentativas = tentativasAlea(defs_jogo.tentativas_alea, defs_jogo.tamanho_chave, defs_jogo.num_cores, &num_total_tent, &lista_cores, &win, &tempo, 1);
      if(win == 0) {
        win = keyFinder(defs_jogo.tamanho_chave, &lista_cores, &lista_tentativas, &num_total_tent, &tempo, 1);
      }
      printf("\nNumero de tentativas: %d\n", num_total_tent);
      clear(defs_jogo.tamanho_chave, &lista_tentativas, &lista_cores);
      num_total_tent = 0;
      sleep(1);
    }

    printf("%d\n", tempo);
    terminate_oracle();
    free(nome_jogadores[0]);
    free(nome_jogadores);
  }

  if (cmd_flag.ord != 0) {
    sort_registry(&registo_jogo, cmd_flag.ord, argv);
  }

  return 0;
}

int mode_check (int argc, char const *argv[], flags *cmd_flag) {
  int func_valid=0;

  switch (argc) {
    case 1:
      cmd_flag->init=0;
      cmd_flag->hist=0;
      cmd_flag->ord=0;
      break;
    case 3:
      func_valid = test_mode_config(3, argv, &cmd_flag);
      break;
    case 5:
      func_valid = test_mode_config(5, argv, &cmd_flag);
      break;
    case 7:
      func_valid = test_mode_config(7, argv, &cmd_flag);
      break;
    default:
      printf("ERRO: Numero de argumentos inválido\n");
  }

  if (func_valid == -1) exit(-1);




  return 0;
}

int test_mode_config (int k, char const *argv[], flags **cmd_flag) {
  char ini[] = "-i", hist[] = "-h", ord[] = "-o";

  for (int i = 1; i < k; i += 2) {
    if (strcmp(ini, argv[i]) == 0) {
      (*cmd_flag)->init = i+1;
    } else if (strcmp(hist, argv[i]) == 0) {
      (*cmd_flag)->hist = i+1;
    } else if (strcmp(ord, argv[i]) == 0) {
      (*cmd_flag)->ord = i+1;
    } else {
      printf("ERRO: Argumentos incorretos ou não identificados\n");
      exit(-1);
    }
  }

  return 0;
}






void read_hist_file_1(char const *argv[], int arg_num, hist_data *last_game){

  int k=0, a=0, b=0, a1=0, b1=0;

  FILE *fptr=fopen(argv[arg_num], "r");

  while(!feof(fptr)){
    fscanf(fptr, "%d J%d %*s %*s %*s %*s %*s %d %*[^\n]\n", &a, &b, &k);
    for (int i = 0; i < k; i++) {
      fscanf(fptr, "%*[^\n]\n");
    }
    if (a>a1) a1=a;
    if (b>b1) b1=b;
  }
  if (b1>998) b1=0;
  last_game->ID=a1;
  sprintf(last_game->player_ID, "J%03d", b1);
  fclose(fptr);
}


void read_hist_file_2(char const *argv[], int arg_num, game_reg **registo_jogo) {
  game_reg *current;
  char name[50]="\0", key[10]="\0";
  FILE *fptr=fopen(argv[arg_num], "r");
  *registo_jogo=calloc(1, sizeof(game_reg));
  current=*registo_jogo;
  fscanf(fptr, "%d %s %s %d %d %c %s %d %f\n", &current->game_ID, current->player_ID, name, &current->colors,
        &current->key_size, &current->repet, key, &current->tentativas, &current->game_time);
  current->key=calloc(strlen(key)+1, sizeof(char));
  current->player_name=calloc(strlen(name)+1, sizeof(char));
  strcpy(current->key, key);
  strcpy(current->player_name, name);
  while(!feof(fptr)){
    current->next=calloc(1, sizeof(game_reg));
    fscanf(fptr, "%d %s %s %d %d %c %s %d %f\n", &current->next->game_ID, current->next->player_ID, name, &current->next->colors,
          &current->next->key_size, &current->next->repet, key, &current->next->tentativas, &current->next->game_time);
    current->key=calloc(strlen(key)+1, sizeof(char));
    current->player_name=calloc(strlen(name)+1, sizeof(char));
    strcpy(current->key, key);
    strcpy(current->player_name, name);
    current->next->next=NULL;
    current=current->next;
  }
  fclose(fptr);
}


void save_game_ini(game_reg **registo_jogo, int hist_file, int ord, hist_data last_game, char **nome_jogadores, defs defs_jogo, int jogador){
  int pid=0;
  static int k=0; //se houver ficheiro hmmmmm
  game_reg *current_game=*registo_jogo; //chama-se current mas isso so e vdd para a primeira vez, a partir dai e o anterior
  //inicio de jogo
  /*isto so funciona se leres o ficheiro -h antes e meteres o pointer a apontar para a lista
  caso se implemente de maneira diferente tenho de mudar isto*/
  while (current_game->next != NULL){
    current_game = current_game->next;
  }
  if (k==0 && !(hist_file!=0 && ord!=0)) {  //verifica se primeiro elemento da lista esta preenchido
    registo_jogo=calloc(1, sizeof(game_reg));
    current_game=*registo_jogo; //se e a primeira vez que se passa aqui estrutura esta nao esta alocada, dai voltar a fazer isto

    current_game->game_ID=((last_game.ID)+1);
    current_game->player_name=calloc(strlen(*(nome_jogadores+jogador))+1, sizeof(char));
    strcpy(current_game->player_name, *(nome_jogadores+jogador));
    last_game.player_ID[0]='0';
    pid=atoi(last_game.player_ID);
    pid++;
    sprintf(current_game->player_ID, "J%03d", pid);
    current_game->player_ID[0]='J';
    current_game->colors=defs_jogo.num_cores;
    current_game->key_size=defs_jogo.tamanho_chave;
    current_game->repet=defs_jogo.repeticao_cores;
    current_game->game_time=defs_jogo.duracao_jogo;
    current_game->prev=last_game.last;
    current_game->next=NULL;
    k=1;
  } else {
    current_game->next=calloc(1, sizeof(game_reg));
    current_game->next->game_ID=((last_game.ID)+1);
    current_game->next->player_name=calloc(strlen(*(nome_jogadores+jogador))+1, sizeof(char));
    strcpy(current_game->next->player_name, *(nome_jogadores+jogador));
    if (strcmp(current_game->player_name, current_game->next->player_name) == 0) {
      strcpy(current_game->next->player_ID, current_game->player_ID);
    } else {
      last_game.player_ID[0]='0';
      pid=atoi(last_game.player_ID);
      pid++;
      sprintf(current_game->next->player_ID, "J%03d", pid);
    }
    current_game->next->colors=defs_jogo.num_cores;
    current_game->next->key_size=defs_jogo.tamanho_chave;
    current_game->next->repet=defs_jogo.repeticao_cores;
    current_game->next->game_time=defs_jogo.duracao_jogo;
    current_game->next->prev=last_game.last;
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
  if(k==1) strcpy(current_game->key, jogada);
  /*onde se mete a derrota*/
  if(k==0) strcpy(current_game->key, travessao);
}


void save_guess_ini(game_reg *top, int lugar_certo, int lugar_errado, int tentativa, defs defs_jogo, char jogada[]) {
  int k=0;//flag que verifica se existe o primeiro elemento da lista
  game_reg *current_game=top;
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
    current_game->key=calloc((defs_jogo.tamanho_chave)+1, sizeof(char));
    current_game->first=calloc(1, sizeof(guess_list));
    current_guess=current_game->first; //se e a primeira vez que se passa aqui estrutura esta nao esta alocada, dai voltar a fazer isto

    current_guess->guess_ID=tentativa+1;
    current_guess->guess=calloc((defs_jogo.tamanho_chave)+1, sizeof(char));
    strcpy(current_guess->guess, jogada);
    sprintf(current_guess->result, "P%1dB%1d", lugar_certo, lugar_errado);
    current_guess->prev=NULL;
    current_guess->next=NULL;
  } else {
    current_game->next->tentativas=tentativa+1;
    current_guess->next=calloc(1, sizeof(guess_list));
    current_guess->next->guess_ID=tentativa+1;
    current_guess->next->guess=calloc((defs_jogo.tamanho_chave)+1, sizeof(char));
    strcpy(current_guess->next->guess, jogada);
    sprintf(current_guess->next->result, "P%1dB%1d", lugar_certo, lugar_errado);
    current_guess->next->prev=current_guess;
    current_guess->next->next=NULL;
  }
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


game_reg *recursive_bubble_sort_fast(game_reg *current, game_reg *limit){
  game_reg *top=current;
  if (current == limit) { //base case
    while (current->prev != NULL) {
      current=current->prev;
    }
    return current;
  } else if (current->next == limit) {
    top=recursive_bubble_sort_fast(top, current);//recursion
  } else if (current->key_size > current->next->key_size) {
    reord_2_elements(current);
  } else if (current->colors > current->next->colors && current->key_size == current->next->key_size) {
    reord_2_elements(current);
  } else if (tolower(current->repet)=='s' && tolower(current->next->repet)=='s' &&\
            current->colors == current->next->colors && current->key_size == current->next->key_size) {
    reord_2_elements(current);
  } else if (current->game_time > current->next->game_time && tolower(current->repet)=='s' &&\
            tolower(current->next->repet)=='s' && current->colors == current->next->colors &&\
            current->key_size == current->next->key_size) {
    reord_2_elements(current);
  } else {
    current=current->next;
  }

  return top;//return "new" first element of list
}


game_reg *recursive_bubble_sort_short(game_reg *current, game_reg *limit){
  game_reg *top=current;
  if (current == limit) { //base case
    while (current->prev != NULL) {
      current=current->prev;
    }
    return current;
  } else if (current->next == limit) {
    top=recursive_bubble_sort_short(top, current);//recursion
  } else if (current->key_size > current->next->key_size) {
    reord_2_elements(current);
  } else if (current->colors > current->next->colors && current->key_size == current->next->key_size) {
    reord_2_elements(current);
  } else if (tolower(current->repet)=='s' && tolower(current->next->repet)=='n' &&
            current->colors == current->next->colors && current->key_size == current->next->key_size) {
    reord_2_elements(current);
  } else if (current->tentativas > current->next->tentativas && tolower(current->repet)==tolower(current->next->repet) &&
            current->colors == current->next->colors && current->key_size == current->next->key_size) {
    reord_2_elements(current);
  } else {
    current=current->next;
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


void clear_memory(char **vect1, int v1, dados **ptr_dados, float *vect3, int *vect4, game_reg *registo_jogo){
  for (int i = 0; i < v1; i++) {
    free(vect1[i]);
  }
  free(vect1);
  for (int i = 0; i < v1; i++) {
    free(ptr_dados[i]);
  }
  free(ptr_dados);
  free(vect3);
  free(vect4);
  free_game_registry(registo_jogo);
}


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
