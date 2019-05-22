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
#include "memory.h"
#include "game.h"


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
      func_valid=-1;
      printf("ERRO: Numero de argumentos inválido\n");
  }

  if (func_valid == -1) exit(-1);
  else if (cmd_flag->init==0 && cmd_flag->hist==0 && cmd_flag->ord==0) return 1;
  else if (cmd_flag->init == 0  &&  cmd_flag->hist != 0  &&  cmd_flag->ord != 0) return 2;
  else if (cmd_flag->init==0 && ((cmd_flag->hist != 0  &&  cmd_flag->ord == 0) || (cmd_flag->hist == 0  &&  cmd_flag->ord != 0))) return 3;
  else if (cmd_flag->init!=0) return 4;
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




void modo_ordenacao(char const *argv[], flags cmd_flag, char *file){
  game_reg *registo_jogo;

  read_hist(argv, cmd_flag.hist, &registo_jogo, file, cmd_flag.hist);
  sort_registry(&registo_jogo, cmd_flag.ord, argv);
  write_file_ord(registo_jogo, argv, file, cmd_flag.hist);
  free_game_registry(&registo_jogo);
}



void modo_auto(char const *argv[], flags cmd_flag, char *file){
  defs defs_jogo={'\0',0,0,0,0,0,0,-1};
  hist_data last_game={0, 0, NULL};
  letras **lista_cores=NULL;
  tentativas *lista_tentativas=NULL;
  char **nome_jogadores=NULL;
  int rep=0, win=0, tempo=0, num_total_tent=0;

  read_init(argv[cmd_flag.init], &defs_jogo, &nome_jogadores);
  hist_max_values(argv, cmd_flag.hist, &last_game, file);


  if(tolower(defs_jogo.repeticao_cores) == 's') rep=1;
  activate_oracle(defs_jogo.tamanho_chave, defs_jogo.num_cores, rep);

  for (int i = 0; i < defs_jogo.num_jogos; i++) {
    win = 0;
    tempo=0;
    num_total_tent = 0;
    printf("\nJogo %d\n", i+1);
    printf("Chave: ");
    generate_key(1);
    printf("\n");

    lista_cores = listaCores(defs_jogo.tamanho_chave, defs_jogo.num_cores);
    lista_tentativas = tentativasAlea(defs_jogo, &num_total_tent, &lista_cores, &win, &tempo, 1);

    if(win == 0) win = keyFinder(defs_jogo, defs_jogo.tamanho_chave, &lista_cores, &lista_tentativas, &num_total_tent, &tempo, 1);

    printf("\nNumero de tentativas: %d\n", num_total_tent);

    write_file_unord(lista_tentativas, argv, file, cmd_flag.hist, &last_game, nome_jogadores, num_total_tent, tempo, defs_jogo);
    clear(defs_jogo.tamanho_chave, &lista_tentativas, &lista_cores);
    sleep(1);
  }

  terminate_oracle();
  free(nome_jogadores[0]);
  free(nome_jogadores);

  if (cmd_flag.ord != 0) modo_ordenacao(argv, cmd_flag, file);
}



void modo_inter_pc(char const *argv[], flags cmd_flag, char *file){
  defs defs_jogo={'\0',0,0,0,0,0,0,-1};
  hist_data last_game={0, 0, NULL};
  letras **lista_cores=NULL;
  tentativas *lista_tentativas=NULL;
  char **nome_jogadores=NULL;
  int combo_possivel=0, rep=0, win=0, tempo=0, num_total_tent=0;

  hist_max_values(argv, cmd_flag.hist, &last_game, file);

  defs_jogo.num_jogadores=1;
  //nome dos jogadores
  nome_jogadores=calloc(1,sizeof(char*));
  nome_jogadores[0]=calloc(strlen("computer")+1,sizeof(char));
  strcpy(nome_jogadores[0],"computer");
  //numero de jogos
  initialization(&defs_jogo.num_jogos, 1, 5, "o numero de jogos");
  //numero maximo de tentivas por jogo
  initialization(&defs_jogo.tentativas, 10, 20, "o numero maximo de tentativas");
  //numero maximo de tentivas aleatorias por jogo
  initialization(&defs_jogo.tentativas_alea, 0, (20-defs_jogo.tentativas), "o numero maximo de tentativas aleatorias");
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

  if(tolower(defs_jogo.repeticao_cores)=='s') rep=1;
  activate_oracle(defs_jogo.tamanho_chave, defs_jogo.num_cores, rep);

  for(int i=0;i<defs_jogo.num_jogos;i++){
    win = 0;
    tempo=0;
    num_total_tent = 0;
    printf("\nJogo %d\n",i);
    lista_cores = listaCores(defs_jogo.tamanho_chave, defs_jogo.num_cores);
    lista_tentativas = tentativasAlea(defs_jogo, &num_total_tent, &lista_cores, &win, &tempo, 2);

    if (win==0) win = keyFinder(defs_jogo, defs_jogo.tamanho_chave, &lista_cores, &lista_tentativas, &num_total_tent, &tempo, 2);

    printf("\nNumero de tentativas: %d\n", num_total_tent);

    write_file_unord(lista_tentativas, argv, file, cmd_flag.hist, &last_game, nome_jogadores, num_total_tent, tempo, defs_jogo);

    clear(defs_jogo.tamanho_chave, &lista_tentativas, &lista_cores);
    sleep(1);
  }

  terminate_oracle();
  free(nome_jogadores[0]);
  free(nome_jogadores);
}