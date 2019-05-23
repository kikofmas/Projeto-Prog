/******************************************************************************
* Projeto intermedio de programacao - MASTERMIND
*
* Bruno Miguel da Silva Cebola - 93030
* Frederico Maria Almeida Santos - 93065
*
******************************************************************************/
//LIBRARIES
#include <stdlib.h>
#include <stdio.h>

#include "estruturas.h"
#include "game.h"

//DECLARACAO DE MACROS
#define DEFAULT_FILE "game_history.dat"

int main(int argc, char const *argv[]) {
//declaracao das variaveis para o modo de funcionamento do programa
  int mod=0, mod_inter=0;
  flags cmd_flag={0, 0, 0};

  mod = mode_check(argc, argv, &cmd_flag);

  if (mod == 1) {
    printf("MODO INTERATIVO\n\n");
    printf(" 1) Jogador Vs. Jogador\n");
    printf(" 2) Jogador Vs. Computador\n\n");
    printf("Opcao: ");
    scanf("%d", &mod_inter);
    printf("\n");
    if (mod_inter==1) modo_inter_intermedio(argv, cmd_flag, DEFAULT_FILE);
    else if(mod_inter == 2) modo_inter_pc(argv, cmd_flag, DEFAULT_FILE);
  }
  else if (mod == 2) {
    printf("MODO TESTE\nAPENAS REORDENAÇAO\n\n");
    modo_ordenacao(argv, cmd_flag, DEFAULT_FILE);
  }
  else if (mod == 3) {
    printf("MODO TESTE\n\n");
    modo_auto(argv, cmd_flag, DEFAULT_FILE);
  }
  return 0;
}