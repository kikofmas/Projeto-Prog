/*Projeto de programação de
*Bruno Cebola - 93030
*Frederico Maria Almeida Santos - 93065*/

#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

//estrutura para os jogadores
typedef struct{
  char name[21];//nome do jogador
  int numjog;//numero de jogos
  int temp;//tempo de jogo
}jogadores;


int main() {
  setlocale(LC_ALL,""); //aceita caracteres espiciais e acentos

//declaração das variaveis
  int colors, keySize; //número de cores em jogo, tamanho da chave

  jogadores jogador[4];//definir 4 jogadores a partir da estrutura

  char err[1];//variavel para flush do scanf quando input inesperado
  int jog;//numero de jogadores


//INICIO
  printf("Vamos jogar um jogo de mastermind!\n");


//numero de jogadores?
  while (jog<1 || jog>4) {
    int aux;
    printf("Insira o numero de jogadores (1 a 4):  ");
    aux=scanf("%d", &jog);
    if (jog<1 || jog>4) {
    printf("Erro: numero de jogadores inválido\n");
    }
    if (aux==0) {
      fflush(stdin);
      scanf("%s", err);
      printf("Erro: numero de jogadores inválido\n");
      continue;
    }
  }

//nome dos jogadores?
  for (int i = 0; i < jog; i++) {
    printf("Insira nome do jogador %d (maximo de 20 caracteres):  ", i+1);
    scanf("%20s", jogador[i].name);
  }



//tempo de jogo por jogador?
  for (int i = 0; i < jog; i++) {
    int aux;
    while (jogador[i].temp<60 || jogador[i].temp>300) {
      printf("Insira o tempo maximo por jogo (em segundos) do jogador %s:  ", jogador[i].name);
      aux=scanf("%d", &jogador[i].temp);
      if (jogador[i].temp<60 || jogador[i].temp>300) {
        printf("Erro: tempo de jogo invalido\n");
      }
      if (aux==0) {
        fflush(stdin);
        scanf("%s", err);
        printf("Erro: tempo de jogo invalido\n");
        continue;
      }
    }
  }

//numero de cores em jogo?
  while (colors<6 || colors>12) {
    int aux;
    printf("Insira o número de cores com que deseja jogar (6-12): ");
    aux=scanf("%d", &colors);
    if (colors<6 || colors>12) {
      printf("Erro: numero de cores inválido\n");
    }
    if (aux==0) {
      fflush(stdin);
      scanf("%s", err);
      printf("Erro: numero de cores inválido\n");
      continue;
    }
  }

//dimensao da chave?
  while (keySize<4 || keySize>8) {
    int aux;
    printf("Insira a dimensão da chave com que deseja jogar (6-12):  ");
    aux=scanf("%d", &keySize);
    if (keySize<4 || keySize>8) {
      printf("Erro: tamaho da chave inválido\n");
    }
    if (aux==0) {
      fflush(stdin);
      scanf("%s", err);
      printf("Erro: tamaho da chave inválido\n");
      continue;
    }
  }

  return 0;
}
