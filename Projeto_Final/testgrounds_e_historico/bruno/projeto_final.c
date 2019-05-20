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
#include "mode.h"

//DECLARACAO DE FUNCOES

void save_game_ini(game_reg **registo_jogo, int hist_file, int ord, hist_data last_game, char **nome_jogadores, defs defs_jogo, int jogador);
void save_key(int k, game_reg *registo_jogo, char jogada[]);
void save_guess_ini(game_reg *top, int lugar_certo, int lugar_errado, int tentativa, defs defs_jogo, char jogada[]);
void sort_registry(game_reg **registo_jogo, int pos, char const *argv[]);
//game_reg *recursive_bubble_sort_fast(game_reg *current, game_reg *limit);
game_reg *recursive_bubble_sort_short(game_reg *current, game_reg *limit);
game_reg * reord_2_elements(game_reg *ptr, game_reg *top);

void clear_memory(char **vect1, int v1, dados **ptr_dados, float *vect3, int *vect4, game_reg *registo_jogo);
void free_guess_list(tentativas *current);
void free_game_registry(game_reg *current);


int main(int argc, char const *argv[]) {

//declaracao das variaveis para o modo de funcionamento do programa
  int mod=0, mod_inter=0;
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
  hist_data last_game={0, 0, NULL};

//inicializacao da funcao srand:
  time_t t;
  srand((unsigned) time(&t)); //inicializa o gerador aleatorio

  mod = mode_check(argc, argv, &cmd_flag);

  if (mod == 1) {
    printf("MODO INTERATIVO\n\n");
    printf("1) Jogador Vs. Jogador\n");
    printf("2) Jogador Vs. Computador\n\n");
    printf("Opcao: ");
    scanf("%d", &mod_inter);
    printf("\n");
    cleanslate();

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

    if (mod_inter==1) {
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

      clear_memory_intermedio(nome_jogadores, defs_jogo.num_jogadores, ptr_dados, mediaTempos, numVitorias); //esta funcao ta aqui bem a toa....
    }
    else if(mod_inter == 2) {

      //esta merda esta mal feita estupido de merda

      if(tolower(defs_jogo.repeticao_cores)=='s') rep=1;
      activate_oracle(defs_jogo.tamanho_chave, defs_jogo.num_cores, rep);

      //for(int i=0;i<defs_jogo.num_jogos;i++){
        //printf("\nJogo %d\n",i);
        lista_cores = listaCores(defs_jogo.tamanho_chave, defs_jogo.num_cores);
        lista_tentativas = tentativasAlea(defs_jogo, &num_total_tent, &lista_cores, &win, &tempo, mod_inter);

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
  else if (mod == 2) {
    printf("MODO TESTE\nAPENAS REORDENAÇAO\n\n");
    read_hist(argv, cmd_flag.hist, &registo_jogo, "", cmd_flag.hist);
    //sort_registry(&registo_jogo, cmd_flag.ord, argv);
    return 0;
  }
  else if (mod == 3) {
    printf("ERRO: Falta o ficheiro das inicializações\n");
    exit(-1);}
  else if (mod == 4) {
    FILE *fptr;
    tentativas *aux;
    printf("MODO TESTE\n\n");
    /* jogar EvE */
    /*load init files and others if needed -- use ifs to allow or not passage*/

    if (cmd_flag.hist != 0) {
      hist_max_values(argv, cmd_flag.hist, &last_game, "", 0);
      fptr = fopen(argv[cmd_flag.hist],"ab");
    }
    else{
      fptr = fopen("game_history.dat","ab");
      fclose(fptr);
      hist_max_values(argv, cmd_flag.hist, &last_game, "game_history.dat", 1);
      fptr = fopen("game_history.dat","ab");
    }

    printf("1\n");

    read_init("init.dat", &defs_jogo, &nome_jogadores);
    if(tolower(defs_jogo.repeticao_cores) == 's') rep=1;

    activate_oracle(defs_jogo.tamanho_chave, defs_jogo.num_cores, rep);

    for (int i = 0; i < defs_jogo.num_jogos; i++) {
      win = 0;
      tempo=0;
      num_total_tent = 0;
      printf("\nJogo %d\n", i);
      printf("Chave: ");
      generate_key(1);
      printf("\n");

      lista_cores = listaCores(defs_jogo.tamanho_chave, defs_jogo.num_cores);
      lista_tentativas = tentativasAlea(defs_jogo, &num_total_tent, &lista_cores, &win, &tempo, 1);
      if(win == 0) {
        win = keyFinder(defs_jogo.tamanho_chave, &lista_cores, &lista_tentativas, &num_total_tent, &tempo, 1);
      }
      printf("\nNumero de tentativas: %d\n", num_total_tent);

      aux=lista_tentativas;
      while(aux->next!=NULL){
        aux=aux->next;
      }

      fprintf(fptr, "%d J%03d %s %d %d %c %s %d %.3f\n", ++last_game.ID, ++last_game.player_ID, nome_jogadores[0], defs_jogo.num_cores,
                                                       defs_jogo.tamanho_chave, defs_jogo.repeticao_cores, aux->tentativa, num_total_tent, (float)tempo/1000);
      aux=lista_tentativas;
      while(aux!=NULL){
        fprintf(fptr, "%d %s %s\n", aux->tent_ID, aux->tentativa, aux->resultado);
        aux=aux->next;
      }

      clear(defs_jogo.tamanho_chave, &lista_tentativas, &lista_cores);
      sleep(1);
    }

    terminate_oracle();
    fclose(fptr);
    free(nome_jogadores[0]);
    free(nome_jogadores);
  }

  if (cmd_flag.ord != 0) {
    read_hist(argv, cmd_flag.hist, &registo_jogo, "game_history.dat", cmd_flag.hist);
    //sort_registry(&registo_jogo, cmd_flag.ord, argv);


    FILE *fptr = fopen("game_history.dat","wb");
    game_reg *current = registo_jogo;
    while(current!=NULL){
      fprintf(fptr, "%d %s %s %d %d %c %s %d %.3f\n", current->game_ID, current->player_ID, current->player_name,
                                                      current->colors, current->key_size, current->repet,
                                                      current->key, current->tentativas, current->game_time);
      tentativas *aux = current->first;
      while(aux!=NULL){
        fprintf(fptr, "%d %s %s\n", aux->tent_ID, aux->tentativa, aux->resultado);
        aux=aux->next;
      }
      current=current->next;
    }
    fclose(fptr);

  }

  return 0;
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
    pid=last_game.player_ID;
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
      pid=last_game.player_ID;
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
  tentativas *current_guess;

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
    current_game->first=calloc(1, sizeof(tentativas));
    current_guess=current_game->first; //se e a primeira vez que se passa aqui estrutura esta nao esta alocada, dai voltar a fazer isto

    current_guess->tent_ID=tentativa+1;
    current_guess->tentativa=calloc((defs_jogo.tamanho_chave)+1, sizeof(char));
    strcpy(current_guess->tentativa, jogada);
    sprintf(current_guess->resultado, "P%1dB%1d", lugar_certo, lugar_errado);
    current_guess->prev=NULL;
    current_guess->next=NULL;
  } else {
    current_game->next->tentativas=tentativa+1;
    current_guess->next=calloc(1, sizeof(tentativas));
    current_guess->next->tent_ID=tentativa+1;
    current_guess->next->tentativa=calloc((defs_jogo.tamanho_chave)+1, sizeof(char));
    strcpy(current_guess->next->tentativa, jogada);
    sprintf(current_guess->next->resultado, "P%1dB%1d", lugar_certo, lugar_errado);
    current_guess->next->prev=current_guess;
    current_guess->next->next=NULL;
  }
}



void sort_registry(game_reg **registo_jogo, int pos, char const *argv[]){
  char shrt[]="short", fst[]="fast";
  if (strcmp(fst, argv[pos]) == 0) {
  //  *registo_jogo=recursive_bubble_sort_fast(*registo_jogo, NULL);
  } else if (strcmp(shrt, argv[pos]) == 0) {
    *registo_jogo=recursive_bubble_sort_short(*registo_jogo, NULL);
  } else {
    printf("ERRO: impossivel ordenar. Instrucao errada\n");
  }
}


game_reg *recursive_bubble_sort_short(game_reg *top, game_reg *limit){
  game_reg *current=top;
  if (current == limit) { //base case
    while (top->prev != NULL) {
      top=top->prev;
    }
    return top;
  }
  while (current->next != limit) {
    if (current->key_size > current->next->key_size) {
      top=reord_2_elements(current, top);
    } else if (current->colors > current->next->colors && current->key_size == current->next->key_size) {
      top=reord_2_elements(current, top);
    } else if (tolower(current->repet)=='s' && tolower(current->next->repet)=='n' &&
            current->colors == current->next->colors && current->key_size == current->next->key_size) {
      top=reord_2_elements(current, top);
    } else if (current->tentativas > current->next->tentativas && tolower(current->repet)==tolower(current->next->repet) &&
            current->colors == current->next->colors && current->key_size == current->next->key_size) {
      top=reord_2_elements(current, top);
    } else {
      current=current->next;
    }
  }
  top=recursive_bubble_sort_short(top, current);//recursion
  return top;//return "new" first element of list
}


game_reg *reord_2_elements(game_reg *ptr, game_reg *top) {
  game_reg *aux = ptr->next;
  ptr->next=aux->next;
  aux->prev=ptr->prev;
  ptr->prev=aux;
  aux->next=ptr;
  if (ptr->next != NULL) ptr->next->prev=ptr;
  if (aux->prev != NULL) {
    aux->prev->next=aux;
  } else {
    while (top->prev != NULL) {
      top=top->prev;
    }
  }
  return top;
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


void free_guess_list(tentativas *current){
  if (current->next != NULL) {
    free_guess_list(current->next);
  }
  free(current);
}
