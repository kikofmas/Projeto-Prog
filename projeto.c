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
  int numJog;//numero de jogos
  int temp;//tempo de jogo
}jogadores;


int main() {
  setlocale(LC_ALL,""); //aceita caracteres espiciais e acentos

//declaração das variaveis
  jogadores jogador[4];//definir 4 jogadores a partir da estrutura
  int jog;//numero de jogadores
  int colors, keySize, tent; //número de cores em jogo, tamanho da chave, numero de tentativas
  char repet;//variavel que permite ou nao a existencia de repetições na chave

  char err;//variavel para flush do scanf quando input inesperado
  int err1;//variavel para flush do scanf quando input inesperado


//INICIO
  printf("Vamos jogar um jogo de mastermind!\n");


//numero de jogadores?
  while (jog<1 || jog>4) {
    int aux;
    printf("Insira o numero de jogadores (1 a 4):  ");
    aux=scanf("%d", &jog);
    if (aux==0) {
      fflush(stdin);
      scanf("%s", &err);
      printf("Erro: numero de jogadores inválido\n");
      continue;
    }
    if (jog<1 || jog>4) {
    printf("Erro: numero de jogadores inválido\n");
    }
  }

//nome dos jogadores?
  for (int i = 0; i < jog; i++) {
    printf("Insira nome do jogador %d (maximo de 20 caracteres):  ", i+1);
    scanf("%20s", jogador[i].name);
    while(1) { //loop para eliminar o input extra do utilizador
      err1 = getchar();
      if (err1 == ' ' || err1 == '\n' || err1 == EOF) break;
    }
  }


//tempo de jogo por jogador?
  for (int i = 0; i < jog; i++) {
    int aux;
    while (jogador[i].temp<60 || jogador[i].temp>300) {
      printf("Insira o tempo maximo por jogo (em segundos) do jogador %s (60 a 300):  ", jogador[i].name);
      aux=scanf("%d", &jogador[i].temp);
      if (aux==0) {
        fflush(stdin);
        scanf("%s", &err);
        printf("Erro: tempo de jogo invalido\n");
        continue;
      }
      if (jogador[i].temp<60 || jogador[i].temp>300) {
        printf("Erro: tempo de jogo invalido\n");
      }
    }
  }

//numero de cores em jogo?
  while (colors<6 || colors>12) {
    int aux;
    printf("Insira o número de cores com que deseja jogar (6-12): ");
    aux=scanf("%d", &colors);
    if (aux==0) {
      fflush(stdin);
      scanf("%s", &err);
      printf("Erro: numero de cores inválido\n");
      continue;
    }
    if (colors<6 || colors>12) {
      printf("Erro: numero de cores inválido\n");
    }
  }

//dimensao da chave?
  while (keySize<4 || keySize>8) {
    int aux;
    printf("Insira a dimensão da chave com que deseja jogar (4-8):  ");
    aux=scanf("%d", &keySize);
    if (aux==0) {
      fflush(stdin);
      scanf("%s", &err);
      printf("Erro: tamaho da chave inválido\n");
      continue;
    }
    if (keySize<4 || keySize>8) {
      printf("Erro: tamaho da chave inválido\n");
    }
  }


//numero de jogos por jogador?
  for (int i = 0; i < jog; i++) {
    int aux;
    while (jogador[i].numJog<1 || jogador[i].numJog>5) {
      printf("Insira o numero de jogos a realizar pelo jogador %s (1 a 5):  ", jogador[i].name);
      aux=scanf("%d", &jogador[i].numJog);
      if (aux==0) {
        fflush(stdin);
        scanf("%s", &err);
        printf("Erro: numero de jogos invalido\n");
        continue;
      }
      if (jogador[i].numJog<1 || jogador[i].numJog>5) {
        printf("Erro: numero de jogos invalido\n");
      }
    }
  }

//repetiçao de cores na chave?
  while (repet!='s' && repet!='n' && repet!='S' && repet!='N') {
    int aux;
    printf("A chave pode ter cores repetidas? [S/N]:  ");
    aux=scanf(" %c", &repet);
    while(1) { //loop para eliminar o input extra do utilizador
      err1 = getchar();
      if (err1 == ' ' || err1 == '\n' || err1 == EOF) break;
    }
    if (repet!='s' && repet!='n' && repet!='S' && repet!='N') {
      printf("Erro: input invalido\n");
    }
  }

//numero maximo de tentivas por jogo?
  while (tent<10 || tent>20) {
    int aux;
    printf("Insira o numero maximo de tentativas (10 a 20):  ");
    aux=scanf("%d", &tent);
    if (aux==0) {
      fflush(stdin);
      scanf("%s", &err);
      printf("Erro: numero de tentativas invalido\n");
      continue;
    }
    if (tent<10 || tent>20) {
      printf("Erro: numero de tentativas invalido\n");
    }
  }

  return 0;
}
