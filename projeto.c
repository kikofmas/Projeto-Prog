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
  int temp;//tempo de jogo
}jogadores;


int main() {
<<<<<<< HEAD
  setlocale(LC_ALL,"");//acentos
=======
  setlocale(LC_ALL,"");
  
  int colors,keySize; //número de cores em jogo/tamanho da chave
>>>>>>> f20c405c8026772a48946039a7958c609bab9eb5

  jogadores jogador[4];//estrura dos jogadores

  char err[1];//variavel para flush do scanf quando input inesperado
  int jog;//numero de jogadores
  printf("Vamos jogar um jogo de mastermind!\n");


//numero de jogadores?
  while (jog<1 || jog>4) {
<<<<<<< HEAD
    printf("Insira o numero de jogadores (1 a 4):  ");
=======
    printf("Insira o numero de jogadores (1-4):  ");
>>>>>>> f20c405c8026772a48946039a7958c609bab9eb5
    if (scanf("%d", &jog)==0) {
      fflush(stdin);
      scanf("%s", err);
      printf("Erro: numero de jogadores inválido\n");
      continue;
    }
  }

//nome dos jogadores?
  for (int i = 0; i < jog; i++) {
    printf("Insira nome do jogador %d (maximo de 20 caracteres):  ", i+1);
    fgets(jogador[i].name, 20, stdin);
    printf("%s", jogador[i].name);
  }

//tempo de jogo por jogador?
  for (int i = 0; i < jog; i++) {
<<<<<<< HEAD
    while (jogador[i].temp<60 || jogador[i].temp>300) {
      printf("Insira o tempo maximo por jogo (em segundos) do jogador %s", jogador[i].name);
      if (scanf("%d", &jogador[i].temp)==0) {
        fflush(stdin);
        scanf("%s", err);
        printf("Erro: tempo de jogo invalido\n");
        continue;
      }
    }
=======
    printf("Insira o tempo maximo por jogo do jogador %s", );
>>>>>>> f20c405c8026772a48946039a7958c609bab9eb5
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
