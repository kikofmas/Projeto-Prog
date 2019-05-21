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
#include "memory.h"
#include "game.h"

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

  hist_max_values(argv, cmd_flag.hist, &last_game, file);
  read_init(argv[cmd_flag.init], &defs_jogo, &nome_jogadores);

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

    if(win == 0) win = keyFinder(defs_jogo.tamanho_chave, &lista_cores, &lista_tentativas, &num_total_tent, &tempo, 1);

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