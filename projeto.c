/*Projeto de programação de
*Bruno Cebola - 93030
*Frederico Maria Almeida Santos - 93065*/

#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>


void cleanslate(void);//limpa o buffer = loop para eliminar o input extra do utilizador
void initialization(int *var, int min, int max, char frase[10]); //inicializações efetuadas com while



int main() {
  setlocale(LC_ALL,""); //aceita caracteres especiais e acentos

//declaração das variaveis
  char name[4][21];//definir 4 jogadores a partir da estrutura
  int jog, tempo, games;//numero de jogadores, tempo de jogo, numero de jogos
  int colors, keySize, tent; //número de cores em jogo, tamanho da chave, numero de tentativas
  char repet;//variavel que permite ou nao a existencia de repetições na chave
  char err[1];

//INICIO
  printf("Vamos jogar um jogo de mastermind!\n");

//numero de jogadores?
  initialization(&jog, 1, 4, "o numero de jogadores");
  cleanslate();

//nome dos jogadores?
  for (int i = 0; i < jog; i++) {
    printf("Insira nome do jogador %d (maximo de 20 caracteres):  ", i+1);
    scanf("%20s", name[i]);
    cleanslate();
  }

//tempo de jogo por jogador?
  initialization(&tempo, 60, 300, "o tempo de jogo");
  cleanslate();

//numero de cores em jogo?
  initialization(&colors, 6, 12, "o número de cores com que deseja jogar");
  cleanslate();

//dimensao da chave?
  initialization(&keySize, 4, 8, "a dimensão da chave com que deseja jogar");
  cleanslate();


//numero de jogos por jogador?
  initialization(&games, 1, 4, "o numero de jogos");
  cleanslate();

//repetiçao de cores na chave?
  while (repet!='s' && repet!='n' && repet!='S' && repet!='N') {
    char buffer[100];
    printf("A chave pode ter cores repetidas? [S/N]:  ");
    fgets(buffer, 1, stdin);
    sscanf(buffer, "%s", repet);
    if (repet!='s' && repet!='n' && repet!='S' && repet!='N') {
      cleanslate();
      printf("Erro: input invalido\n");

    }
  }
  cleanslate();

//numero maximo de tentivas por jogo?
  initialization(&tent, 10, 20, "o numero maximo de tentativas");
  cleanslate();

  return 0;
}

void initialization(int *var, int min, int max, char frase[30]){
  char err;
  while (*var<min || *var>max) {
    int aux;
    printf("Insira %s (%d a %d):  ",frase,min,max);
    aux=scanf("%d", var);
    if (aux==0) {
      fflush(stdin);
      scanf("%s", &err);
      printf("Erro: valor introduzido inválido\n");
      continue;
    }
    if (*var<min || *var>max) {
    printf("Erro: valor introduzido inválido\n");
    }
  }
}

void cleanslate(void){
  int err1;
  while(1) {
    err1 = getchar();
    if (err1 == '\n' || err1 == EOF) break;
  }
}
