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


#include "oraculo.h"


#include "estruturas.h"
#include "funcoes_intermedio.h"
#include "test_mode_init.h"
#include "test_mode_registry.h"
#include "test_mode_ord.h"
#include "clear_memory.h"



int main(int argc, char const *argv[]) {

//declaracao das variaveis para o modo de funcionamento do programa
  int error=0;
  flags cmd_flag={0, 0, 0};

//declaracao das variaveis da inicializacao:
  defs defs_jogo={'\0',0,0,0,0,0,0,0};
  char **nome_jogadores=NULL;
  int combo_possivel=0;
  int rep=0;
//declaracao das variaveis das estatisticas:
  dados **ptr_dados=NULL; //[][][0]=tempo, [][][1]=tentativas, [][][2]=vitoria
  int *numVitorias=NULL;
  float *mediaTempos=NULL;
  game_reg *registo_jogo;
  hist_data last_game={0, "J000", NULL};

//inicializacao da funcao srand:
  time_t t;
  srand((unsigned) time(&t)); //inicializa o gerador aleatorio

  error=mode_check(argc, argv, &cmd_flag);
  if (error==-1) exit(-1);


  //passar para funcao??
  if (cmd_flag.init==0 && cmd_flag.hist==0 && cmd_flag.ord==0) {
    printf("MODO INTERATIVO\n");

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

      do{
      //dimensao da chave
        initialization(&defs_jogo.tamanho_chave, 4, 8, "a dimensao da chave com que deseja jogar");

      //numero de cores em jogo
        initialization(&defs_jogo.num_cores, 6, 12, "o numero de cores com que deseja jogar");

      //repeticao de cores
        initializationRepetitions(&defs_jogo.repeticao_cores);

      //verificacao de que a combinacao de parametros e possivel
        combo_possivel=checkCombinacao(&defs_jogo.num_cores, &defs_jogo.tamanho_chave, &defs_jogo.repeticao_cores);
      }while(combo_possivel==-1);

      if(tolower(defs_jogo.repeticao_cores)=='s') rep=1;

      clearScreen(1);


    //JOGO

      activate_oracle(defs_jogo.tamanho_chave, defs_jogo.num_cores, rep);

      ptr_dados=jogo(defs_jogo.num_jogadores, defs_jogo.num_jogos, defs_jogo.num_cores, defs_jogo.tamanho_chave,
                     defs_jogo.duracao_jogo, defs_jogo.tentativas, defs_jogo.repeticao_cores, nome_jogadores, &registo_jogo, cmd_flag, defs_jogo, &last_game);


    //ESTATISTICAS: calculo dos resultados e apresentacao das estatisticas

      criaDados(defs_jogo.num_jogadores, defs_jogo.num_jogos, ptr_dados, &mediaTempos, &numVitorias);
      vencedor(mediaTempos, nome_jogadores, defs_jogo.num_jogadores, numVitorias);
      resultados(defs_jogo.num_jogadores, defs_jogo.num_jogos, ptr_dados, 0, "mais rapido", nome_jogadores);
      resultados(defs_jogo.num_jogadores, defs_jogo.num_jogos, ptr_dados, 1, "mais curto", nome_jogadores);
      showData(ptr_dados, mediaTempos, defs_jogo.num_jogadores, numVitorias, defs_jogo.num_jogos, nome_jogadores);

      printf("\nESPERAMOS QUE SE TENHA DIVERTIDO!!!\n");

      clear_memory(nome_jogadores, defs_jogo.num_jogadores, ptr_dados, mediaTempos, numVitorias, registo_jogo);
}
  else if(cmd_flag.init==0 && cmd_flag.hist!=0 && cmd_flag.ord!=0){
    printf("MODO TESTE\n\nAPENAS REORDENAÇAO");
    read_hist_file_2(argv, cmd_flag.hist, &registo_jogo);
    sort_registry(&registo_jogo, cmd_flag.ord, argv);
    return 0;
    }
    /* fazer so o algoritmo de reordenaçao */
    /* load -h file and reord*/
  else if(cmd_flag.init==0 && ((cmd_flag.hist!=0 && cmd_flag.ord==0) || (cmd_flag.hist==0 && cmd_flag.ord!=0))){
    printf("ERRO: Falta o ficheiro das inicializações\n");
    exit(-1);
  }
  else if(cmd_flag.init!=0){
    printf("MODO TESTE\n\n");
    /* jogar EvE */
    /*load init files and others if needed -- use ifs to allow or not passage*/

    //passar esta merda para funcao

    if (cmd_flag.hist != 0) {
      read_hist_file_1(argv, cmd_flag.hist, &last_game);
      if (cmd_flag.ord != 0) read_hist_file_2(argv, cmd_flag.hist, &registo_jogo);
    }

    FILE *fptr = fopen(argv[cmd_flag.init],"rb");
    if(fptr!=NULL){
      defs defs_jogo={'\0',0,0,0,0,0,0,0};
      char *nome_jogadores=NULL;
      char c;
      char *text = (char *)malloc(sizeof(char));
      int counter=1;
      while((c=fgetc(fptr))!=EOF){
        text = (char *)realloc(text,counter);
        text[counter-1]=c;
        counter++;
      }
      fclose(fptr);
      char *token;
      token = strtok(text,"\n");
      nome_jogadores = (char *)malloc((strlen(token)+1)*sizeof(char));
      strcpy(nome_jogadores,token);
      token = strtok(NULL,"\n");
      defs_jogo.num_jogos = atoi(token);
      token = strtok(NULL,"\n");
      defs_jogo.num_cores = atoi(token);
      token = strtok(NULL,"\n");
      defs_jogo.tamanho_chave = atoi(token);
      token = strtok(NULL,"\n");
      defs_jogo.repeticao_cores = token[0];
      token = strtok(NULL,"\n");
      defs_jogo.tentativas_alea = atoi(token);
      token = strtok(NULL,"\n");
      defs_jogo.tentativas = atoi(token);

      //esta aqui so para nao dar warning de var nao usada e confirmacao
      printf("%s\n", nome_jogadores);
      printf("%d\n", defs_jogo.num_jogos);
      printf("%d\n", defs_jogo.num_cores);
      printf("%d\n", defs_jogo.tamanho_chave);
      printf("%c\n", defs_jogo.repeticao_cores);
      printf("%d\n", defs_jogo.tentativas_alea);
      printf("%d\n", defs_jogo.tentativas);

      free(text);
    }
    else{
      perror("ERRO:");
      exit(-1);
    }
  }

  if (cmd_flag.ord != 0) {
    sort_registry(&registo_jogo, cmd_flag.ord, argv);
  }

  return 0;

}
