/*Projeto de programação de
*Bruno Cebola - 93030
*Frederico Maria Almeida Santos - 93065*/

#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>


typedef struct{
  char name[21];
  int numjog;
  int t;
}jogadores;


int main() {
  setlocale(LC_ALL,"");

  jogadores jogador[4];

  char err[1];
  int jog;
  printf("Vamos jogar um jogo de mastermind!\n");

  while (jog<1 || jog>4) {
    printf("Insira o numero de jogadores:  ");
    if (scanf("%d", &jog)==0) {
      fflush(stdin);
      scanf("%s", err);
      printf("Erro: numero de jogadores invalido\n");
      continue;
    }
  }
  for (int i = 0; i < jog; i++) {
    fgets(jogador[i].name, 20, stdin);
  }
  for (int i = 0; i < jog; i++) {

  }

  return 0;
}
