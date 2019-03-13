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
    while (1) {
    char buffer[100];
    printf("Insira nome do jogador %d (maximo de 20 caracteres):  ", i+1);
    fgets(buffer, 100, stdin);
    sscanf(buffer, "%20s", name[i]);
    if (strlen(buffer)>20) {
        if (strlen(buffer)>99) {
          cleanslate();
        }
      printf("Erro: input incorreto. Verifique que o nome não excede 20 caracteres\n");
    } else {
      break;
    }
    }
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

  do{
  //dimensao da chave
    initialization(&keySize, 4, 8, "a dimensão da chave com que deseja jogar");
    cleanslate();

  //numero de cores em jogo
    initialization(&colors, 6, 12, "o número de cores com que deseja jogar");
    cleanslate();

    while (repet!='s' && repet!='n' && repet!='S' && repet!='N') {
      int aux;
      char err1;
      printf("A chave pode ter cores repetidas? [S/N]:  ");
      aux=scanf(" %c", &repet);
      cleanslate();
      if (repet!='s' && repet!='n' && repet!='S' && repet!='N') {
        printf("Erro: input invalido 1\n");
      }
    }

    if (colors<keySize && (repet=='n' || repet=='N')) {
      printf("A combinação dos parametros 'tamanho chave', 'numero cores' e 'repetição de cores' está invalida, tente outra vez.\n" );
      colors=-1;
      keySize=0;
      repet='\0';
    } else {
      break;
    }
  }while(1);

  time_t t;
  srand((unsigned) time(&t));
  char code[9];
  char *codeptr=code;
  char coresdisp[13]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
  char *coresdispptr=coresdisp;
  //criação
  for (int i = 0; i < keySize; i++) {
    while (1) {
      int aux=0;
      aux=rand() % colors;
      if (coresdisp[aux]!='0') {
        *(codeptr+i)=*(coresdispptr+aux);
        break;
        if (repet=='n' || repet=='N') {
          coresdisp[aux]=0;
        }
      }
    }
  }
  return 0;
}

//definição da função para inicializar as variaveis do jogo

void initialization(int *var, int min, int max, char frase[30]){
  while (*var<min || *var>max) {  //loop ate um valor válido ser introduzido
    int aux;
    printf("Insira %s (%d a %d):  ",frase,min,max);
    aux=scanf("%d", var);
    if (aux==0) {         //deteção de input do tipo errado
      cleanslate();
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

void generateKey(){
  time_t t;
}
