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

#include "test_mode_init.h"


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


int mode_check(int argc, char const *argv[], flags *cmd_flag){
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


int test_mode_config(int k, char const *argv[], flags **cmd_flag) {
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
