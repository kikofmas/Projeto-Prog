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
  char name[21];//nome do jogador
  int numjog;//numero de jogos
  int t;//tempo de jogo
}jogadores;


int main() {
  setlocale(LC_ALL,"");
  
  int colors,keySize; //número de cores em jogo/tamanho da chave

  jogadores jogador[4];//estrura dos jogadores

  char err[1];
  int jog;//numero de jogadores
  printf("Vamos jogar um jogo de mastermind!\n");


//numero de jogadores?
  while (jog<1 || jog>4) {
    printf("Insira o numero de jogadores (1-4):  ");
    if (scanf("%d", &jog)==0) {
      fflush(stdin);
      scanf("%s", err);
      printf("Erro: numero de jogadores inválido\n");
      continue;
    }
  }
//nome dos jogadores?
  for (int i = 0; i < jog; i++) {
    printf("Insira nome do jogador %d:  ", i);
    fgets(jogador[i].name, 20, stdin);
  }

//tempo de jogo por jogador?
  for (int i = 0; i < jog; i++) {
    printf("Insira o tempo maximo por jogo do jogador %s", );
  }
  
//numero de cores em jogo?
  while (colors<6 || colors>12) {
    printf("Insira o número de cores com que deseja jogar (6-12): ");
    if (scanf("%d", &colors)==0) {
      fflush(stdin);
      scanf("%s", err);
      printf("Erro: numero de cores inválido\n");
      continue;
    }
  }
  
//dimensao da chave?
  while (keySize<4 || keySize>8) {
    printf("Insira a dimensão da chave com que deseja jogar (6-12): ");
    if (scanf("%d", &keySize)==0) {
      fflush(stdin);
      scanf("%s", err);
      printf("Erro: tamaho da chave inválido\n");
      continue;
    }
  }
  
  return 0;
}
