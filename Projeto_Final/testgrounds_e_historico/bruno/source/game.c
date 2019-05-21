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

  printf("MODO TESTE\nAPENAS REORDENAÇAO\n\n");
  read_hist(argv, cmd_flag.hist, &registo_jogo, "", cmd_flag.hist);
  sort_registry(&registo_jogo, cmd_flag.ord, argv);
  write_file(registo_jogo, argv, file, cmd_flag.hist);
  free_game_registry(&registo_jogo);
}