/*Projeto de programação de
*Bruno Cebola - 93030
*Frederico Maria Almeida Santos - 93065*/

#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>


void cleanslate(void); //limpa o buffer = loop para eliminar o input extra do utilizador
void initialization(int *var, int min, int max, char frase[10]); //inicializações efetuadas com while

int main() {
  setlocale(LC_ALL,""); //aceita caracteres especiais e acentos

//declaração das variaveis
  char name[4][21]={{""},{""},{""},{""}}; //array para armazenar o nome do jogadores
  int jog=0, tempo=0, games=0; //numero de jogadores, tempo de jogo, numero de jogos
  int colors=-1, keySize=0, attempt=0; //número de cores em jogo, tamanho da chave, numero de tentativas
  char repet='\0';//variavel que permite ou nao a existencia de repetições na chave

//INICIO
  printf("Vamos jogar um jogo de mastermind!\n");

//numero de jogadores
  initialization(&jog, 1, 4, "o numero de jogadores");
  cleanslate();

//nome dos jogadores
  for (int i = 0; i < jog; i++) {
    printf("Insira nome do jogador %d (maximo de 20 caracteres):  ", i+1);
    scanf("%20s", name[i]);
    cleanslate();
  }

//numero de jogos
  initialization(&games, 1, 4, "o numero de jogos");
  cleanslate();

//duração de cada jogo
  initialization(&tempo, 60, 300, "o tempo de jogo");
  cleanslate();

//numero maximo de tentivas por jogo
  initialization(&attempt, 10, 20, "o numero maximo de tentativas");
  cleanslate();

//dimensao da chave
  initialization(&keySize, 4, 8, "a dimensão da chave com que deseja jogar");
  cleanslate();

//numero de cores em jogo
  initialization(&colors, 6, 12, "o número de cores com que deseja jogar");
  cleanslate();

    //existencia de repetiçao de cores na chave
      /*while (1) {
        char buffer[100];
        printf("A chave pode ter cores repetidas? [S/N]:  ");
        fgets(buffer, 1, stdin);
        sscanf(buffer, "%s", &repet);
        printf("%c",repet);
        if (strncmp(repet, name1, 1)!=0 && strncmp(repet, name2, 1)!=0) {
          cleanslate();
          printf("Erro: valor introduzido inválido\n");

        }
      }*/




  return 0;
}

//definição da função para inicializar as variaveis do jogo

void initialization(int *var, int min, int max, char frase[30]){
  char err;
  while (*var<min || *var>max) {  //loop ate um valor válido ser introduzido
    int aux;
    printf("Insira %s (%d a %d):  ",frase,min,max);
    aux=scanf("%d", var);
    if (aux==0) {         //deteção de input do tipo errado
      fflush(stdin);      //limpeza do input errado
      scanf("%s", &err);
      printf("Erro: valor introduzido inválido\n");
      continue;
    }
    if (*var<min || *var>max) {   //deteção de valores fora dos aceitaveis
    printf("Erro: valor introduzido inválido\n");
    }
  }
}

//definição da função para limpar o buffer

void cleanslate(void){   //loop até se encontrar um nova linha ou o fim de o ficheiro
  char err1;
  while(1) {
    err1 = getchar();
    if (err1 == '\n' || err1 == EOF) break;
  }
}
