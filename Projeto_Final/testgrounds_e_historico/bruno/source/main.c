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
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo

#include "estruturas.h"
#include "intermedio.h"
#include "memory.h"
#include "game.h"


//DECLARACAO DE MACROS
#define DEFAULT_FILE "game_history.dat"


//DECLARACAO DE FUNCOES
void save_game_ini(game_reg **registo_jogo, int hist_file, int ord, hist_data last_game, char **nome_jogadores, defs defs_jogo, int jogador);
void save_key(int k, game_reg *registo_jogo, char jogada[]);
void save_guess_ini(game_reg *top, int lugar_certo, int lugar_errado, int tentativa, defs defs_jogo, char jogada[]);



void clear_memory(char **vect1, int v1, dados **ptr_dados, float *vect3, int *vect4, game_reg **registo_jogo);
void free_guess_list(tentativas *current);


int main(int argc, char const *argv[]) {

//declaracao das variaveis para o modo de funcionamento do programa
  int mod=0, mod_inter=0;
  flags cmd_flag={0, 0, 0};

//declaracao das variaveis da inicializacao:
  char **nome_jogadores=NULL;
  int combo_possivel=0;
  defs defs_jogo={'\0',0,0,0,0,0,0,-1};

//declaracao das variaveis das estatisticas:
  dados **ptr_dados=NULL; //[][][0]=tempo, [][][1]=tentativas, [][][2]=vitoria
  int *numVitorias=NULL;
  float *mediaTempos=NULL;

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

      clear_memory_intermedio(nome_jogadores, defs_jogo.num_jogadores, ptr_dados, mediaTempos, numVitorias); //esta funcao ta aqui bem a toa....
    }
    else if(mod_inter == 2) {
      modo_inter_pc(argv, cmd_flag, DEFAULT_FILE);
    }
  }
  else if (mod == 2) {
    printf("MODO TESTE\nAPENAS REORDENAÇAO\n\n");
    modo_ordenacao(argv, cmd_flag, DEFAULT_FILE);
    return 0;
  }
  else if (mod == 3) {
    printf("ERRO: Falta o ficheiro das inicializações\n");
    exit(-1);
  }
  else if (mod == 4) {
    printf("MODO TESTE\n\n");
    modo_auto(argv, cmd_flag, DEFAULT_FILE);
  return 0;
  }

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







void clear_memory(char **vect1, int v1, dados **ptr_dados, float *vect3, int *vect4, game_reg **registo_jogo){
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

void free_guess_list(tentativas *current){
  if (current->next != NULL) {
    free_guess_list(current->next);
  }
  free(current);
}
