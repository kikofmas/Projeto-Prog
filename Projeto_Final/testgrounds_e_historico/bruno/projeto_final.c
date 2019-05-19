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


//DECLARACAO DE FUNCOES

int mode_check(int argc, char const *argv[], flags *cmd_flag);
int test_mode_config(int k, char const *argv[], flags **cmd_flag);


int main(int argc, char const *argv[]) {

//declaracao das variaveis para o modo de funcionamento do programa
  int error=0, mod_inter=0;
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

//inicializacao da funcao srand:
  time_t t;
  srand((unsigned) time(&t)); //inicializa o gerador aleatorio

  error=mode_check(argc, argv, &cmd_flag);
  if (error==-1) exit(-1);

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

      clear_memory(nome_jogadores, defs_jogo.num_jogadores, ptr_dados, mediaTempos, numVitorias);
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

} else if (cmd_flag.init == 0  &&  cmd_flag.hist != 0  &&  cmd_flag.ord != 0) {
    printf("MODO TESTE\nAPENAS REORDENAÇAO\n\n");
    /* fazer so o algoritmo de reordenaçao */
    /* load -h file and reord*/
  } else if (cmd_flag.init==0 && ((cmd_flag.hist != 0  &&  cmd_flag.ord == 0) || (cmd_flag.hist == 0  &&  cmd_flag.ord != 0))) {
    printf("ERRO: Falta o ficheiro das inicializações\n");
    exit(-1);
  } else if (cmd_flag.init!=0) {
    printf("MODO TESTE\n\n");
    /* jogar EvE */
    /*load init files and others if needed -- use ifs to allow or not passage*/
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
