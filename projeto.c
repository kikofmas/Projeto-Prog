/*Projeto de programação de
*Bruno Cebola - 93030
*Frederico Maria Almeida Santos - 93065*/

#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <ctype.h>    //toupper and tolower functions


void cleanslate(void); //limpa o buffer = loop para eliminar o input extra do utilizador
void initialization(int *var, int min, int max, char frase[10]); //inicializações efetuadas com while
int checkInput(char try[], int size); //valida que a jogada é possivel

int main() {
  setlocale(LC_ALL,""); //aceita caracteres especiais e acentos

//declaração das variaveis
  char name[4][21]={{""},{""},{""},{""}}; //array para armazenar o nome do jogadores
  int jog=0, tempo=0, games=0; //numero de jogadores, tempo de jogo, numero de jogos
  int colors=-1, keySize=0, attempt=0; //número de cores em jogo, tamanho da chave, numero de tentativas
  char repet='\0'; //variavel que permite ou nao a existencia de repetições na chave
  int rp=0,wp=0; //rp para posição correta e wp para cor correta na posição errada
  time_t tempo_inicial,tempo_atual,tempo_jogo; // variavies para medir os tempos ao longo do jogo

  time_t t;
  srand((unsigned) time(&t)); //inicializa o gerador aleatório

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
  initialization(&games, 1, 5, "o numero de jogos");
  cleanslate();

  //numero maximo de tentivas por jogo
    initialization(&attempt, 10, 20, "o numero maximo de tentativas");
    cleanslate();

//duração de cada jogo
  initialization(&tempo, 60, 300, "o tempo de jogo");
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

  //declaração de variaveis de jogo que dependem de dados introduzidos pelo user

  char key[keySize],key_copy[keySize],try[keySize];

  //JOGO

  for(int i=0; i<jog; i++){
    printf("Jogador %s é a sua vez\n",name[i]);
    for(int a=0; a<games; a++){
      tempo_inicial = time(NULL);     //guarda o valor do tempo no inicio do jogo
      printf("Jogo numero %d\n",a+1);
    //criacao da chave no inicio de cada jogo
      char coresdisp[13]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
      char last = coresdisp[colors-1];  //ultima cor da lista que o utilizador pode inserir
      for (int i = 0; i < keySize; i++) {
        int aux;
        //criação de numeros aleatorios ate a condição se verificar
        do{
          aux = rand() % colors;
        } while(coresdisp[aux]=='0');
        key[i]=coresdisp[aux];
        //se n for possivel a repetição de cores elimina-se da  lista a cor inserida na chave
        if(repet=='n' || repet=='N'){
          coresdisp[aux]='0';
        }
      }

      for(int b=0;b<attempt;b++){
        rp=0;     //inicialização das variaveis com o vlor 0 no inicio de cada jogo
        wp=0;
        while (1) {
          char buffer[100];
          printf("Insira uma combinação de cores (A a %c): ",toupper(last));
          fgets(buffer, 100, stdin);
          strncpy(try, buffer, keySize+1);
          tempo_atual=time(NULL);           //armazenamento do tempo atual
          tempo_jogo = tempo_atual-tempo_inicial;     //calculo do tempo atual que o jogo tem
          if(tempo_jogo>=tempo){    //se o limite de tempo for atingido sai do jogo
            printf("O tempo máximo de jogo foi atingido\n");
            break;
          }
          if (strlen(buffer)!=keySize+1) {
              if (strlen(buffer)>99) {
                cleanslate();
              }
            printf("Erro: input incorreto. Verifique que a combinação tem %d caracteres\n",keySize);
          } else {    //validação do input
            if(checkInput(try, keySize)==1){
              break;
            }
            else{
              printf("Erro: input incorreto. A combinação de cores só pode ter caracteres de (A a %c)\n",toupper(last));
            }
          }
        }

        if(tempo_jogo>=tempo){    //se o limite de tempo for atingido sai do jogo
          break;
        }
        for(int a=0;a<keySize;a++){   //copia da chave para se fazer a comparação
          key_copy[a]=key[a];
        }

      //verificação de igualdade entre a chave de jogo e a tentativa do jogador

        for(int i=0;i<keySize;i++){
          for(int a=0;a<keySize;a++){
            //confirmação de cor certa na posição certa
            if(tolower(try[i])==key_copy[a] && i==a){
              rp++;
              key_copy[a]='0';
              break;
            }
            //confirmação de cor certa na posição errada
            else if(tolower(try[i])==key_copy[a]){
              wp++;
              key_copy[a]='0';
              break;
            }
          }
        }

        printf("%dP%dB\n", rp, wp);
        if(rp==keySize){
          printf("Parabens por ter conseguido acabar o jogo!\n");
          break;
        }
      }
      if(rp!=keySize){
        printf("Lamentamos mas não conseguiu acabar o jogo...\n");
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

//definição da função para verificar se o input dado pelo utilizdor durante o jogo é aceitavel

int checkInput(char try[], int size){
  char cores[13]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
  for(int i=0;i<size;i++){
    int flag=0;
    for(int z=0;z<size;z++){
      if(tolower(try[i])==cores[z]){
        flag=1;
      }
    }
    if (flag==0) {
      return 0;
    }
  }
  return 1;
}
