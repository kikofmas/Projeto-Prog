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




void clear_memory(char **vect1, int v1, dados **ptr_dados, float *vect3, int *vect4, game_reg **registo_jogo);
void free_guess_list(tentativas *current);


int main(int argc, char const *argv[]) {

//declaracao das variaveis para o modo de funcionamento do programa
  int mod=0, mod_inter=0;
  flags cmd_flag={0, 0, 0};
  hist_data last_game={0, 0, NULL};

//declaracao das variaveis da inicializacao:
  char **nome_jogadores=NULL;
  int combo_possivel=0;
  defs defs_jogo={'\0',0,0,0,0,0,0,-1};

//declaracao das variaveis das estatisticas:
  dados **ptr_dados=NULL; //[][][0]=tempo, [][][1]=tentativas, [][][2]=vitoria
  int *numVitorias=NULL;
  float *mediaTempos=NULL;

  game_reg = *registo_jogo;

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
      ptr_dados=jogo(defs_jogo, nome_jogadores, &registo_jogo, &last_game);
    //ESTATISTICAS: calculo dos resultados e apresentacao das estatisticas

      criaDados(defs_jogo.num_jogadores, defs_jogo.num_jogos, ptr_dados, &mediaTempos, &numVitorias);
      vencedor(mediaTempos, nome_jogadores, defs_jogo.num_jogadores, numVitorias);
      resultados(defs_jogo.num_jogadores, defs_jogo.num_jogos, ptr_dados, 0, "mais rapido", nome_jogadores);
      resultados(defs_jogo.num_jogadores, defs_jogo.num_jogos, ptr_dados, 1, "mais curto", nome_jogadores);
      showData(ptr_dados, mediaTempos, defs_jogo.num_jogadores, numVitorias, defs_jogo.num_jogos, nome_jogadores);

      printf("\nESPERAMOS QUE SE TENHA DIVERTIDO!!!\n");

      clear_memory_intermedio(nome_jogadores, defs_jogo.num_jogadores, ptr_dados, mediaTempos, numVitorias); //esta funcao ta aqui bem a toa....
    }
    else if(mod_inter == 2) modo_inter_pc(argv, cmd_flag, DEFAULT_FILE);
  }
  else if (mod == 2) {
    printf("MODO TESTE\nAPENAS REORDENAÇAO\n\n");
    modo_ordenacao(argv, cmd_flag, DEFAULT_FILE);
  }
  else if (mod == 3) {
    printf("ERRO: Falta o ficheiro das inicializações\n");
  }
  else if (mod == 4) {
    printf("MODO TESTE\n\n");
    modo_auto(argv, cmd_flag, DEFAULT_FILE);
  }
  return 0;
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

