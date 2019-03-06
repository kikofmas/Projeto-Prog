/*Projeto de programação de
*Bruno Cebola - 93030
*Frederico Maria Almeida Santos - 93065*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main() {
  int jog;
  printf("Vamos jogar um jogo de mastermind!\n");

  while (jog<1 || jog>4) {
    printf("Insira o numero de jogadores:  ");
    if (scanf("%d", &jog)==0) {
      fflush(stdin);
      scanf("%s", &jog);
      printf("Erro: numero de jogadores invalido\n");
      continue;
    }
  }
  printf("%d", jog);

  return 0;
}
