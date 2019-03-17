/*Projeto intermedio de programação - Mastermind
*
*Bruno Cebola - 93030
*Frederico Maria Almeida Santos - 93065*/

//LIBRARIES
#include <locale.h>   //poder usar acentos
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>   //funções com strings
#include <time.h>     //poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions

//DECLARAÇÃO DE FUNÇÕES
void cleanslate(void); //limpa o buffer = loop para eliminar o input extra do utilizador
void initialization(int *var, int min, int max, char frase[10]); //inicializações efetuadas com while
int checkInput(char try[], int size); //valida que a jogada é possivel
void resultados(int jog, int games, int stats[][][], int int g, int h, char frase[15]);//apresenta as estatisticas

//MAIN
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
  printf("Vamos jogar um jogo de mastermind!\n\n");

//numero de jogadores
  initialization(&jog, 1, 4, "o numero de jogadores");
  cleanslate();

//nome dos jogadores
  for (int i = 0; i < jog; i++) {
    while (1) {
      char aux[100];//variavel auxiliar para recolher os nomes
      printf("Insira nome do jogador %d (maximo de 20 caracteres):  ", i+1);
      fgets(aux, 100, stdin);
      sscanf(aux, "%20s", name[i]);
      if (strlen(aux)>20) {
        if (strlen(aux)>99) cleanslate();
        printf("Erro: input incorreto. Verifique que o nome não excede 20 caracteres\n");
      } else break;
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
    } else break;
  }while(1);

  //declaração de variaveis de jogo que dependem de dados introduzidos pelo user

  char key[keySize],key_copy[keySize],try[keySize];
  int stats[jog][games][3];//matriz que guarda a informação de todos os jogos de todos os jogadores
                           //0=temp, 1=jogadas, 2=conseguiu
  int mediaTempos[jog];//media do tempo de jogo para cada jogador

  //JOGO

  for(int i=0; i<jog; i++){//por cada jogador
    printf("Jogador %s é a sua vez\n",name[i]);
    for(int a=0; a<games; a++){//por cada jogo a fazer
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
        if(repet=='n' || repet=='N') coresdisp[aux]='0';
      }

      for(int b=0;b<attempt;b++){//ate maximo tentativa
        rp=0;     //inicialização das variaveis com o vlor 0 no inicio de cada jogo
        wp=0;
        stats[i][a][1]=b;//grava o numero de jogadas efetuadas
        while (1) {
          char buffer[100];
          printf("Insira uma combinação de cores (A a %c): ",toupper(last));
          fgets(buffer, 100, stdin);
          strncpy(try, buffer, keySize+1);
          tempo_atual=time(NULL);           //armazenamento do tempo atual
          tempo_jogo = tempo_atual-tempo_inicial;     //calculo do tempo atual que o jogo tem
          stats[i][a][0]=tempo_jogo;//grava o tempo do jogo atual
          if(tempo_jogo>=tempo){    //se o limite de tempo for atingido sai do jogo
            printf("O tempo máximo de jogo foi atingido\n");
            break;
          }
          if (strlen(buffer)!=keySize+1) {
            if (strlen(buffer)>99) cleanslate();
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

        //se o limite de tempo for atingido sai do jogo
        if(tempo_jogo>=tempo) break;

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

        printf("P%dB%d\n", rp, wp);
        if(rp==keySize){
          printf("Parabens por ter conseguido acabar o jogo!\n");
          stats[i][a][2]=1;//guarda se o jogador conseguiu completar a partida
          break;
        }
      }
      if(rp!=keySize){
        stats[i][a][2]=0;//guarda se o jogador conseguiu completar a partida
        printf("Lamentamos mas não conseguiu acabar o jogo...\n");
      }
    }
  }


//ESTATISTICAS
//calculo dos resultados e apresentação das estatisticas


//cria a media do tempo de jogo para cada jogador
  for (int i = 0; i < jog; i++) {
    for (int u = 0; u < games; u++) {
      mediaTempos[i]+=stats[i][u][0];
    }
    mediaTempos[i]/=games;
  }

//fução para comparar os resultados e apresentar o vencedor do torneio
  int z=0, x=0, y=0;
  for (int i = 0; i < jog; i++) {
    x=0;
    for (int u = 0; u < games; u++) {
      x+=stats[i][u][2];//conta o numero de vitorias
    }
    if (x>y) {//compara o numero de vitorias com o mais alto atual
      z=i;//z e o numero do jogador vencedor atual
      y=x;//y e o parametro vencedor atual
    } else if (x==y) {//em caso de empate compara-se a media de tempos dos jogadores
      if (mediaTempos[z]<mediaTempos[i]) {
        z=i;
        y=x;
      }
    }
  }
  printf("\n\n\nO vencedor do torneio é: o jogador %d, %s\n\n", z+1, name[z]);

  resultados(jog, games, stats, 0, 1, "mais rápido");
  resultados(jog, games, stats, 1, 0, "mais curto");

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
      if(tolower(try[i])==cores[z]) flag=1;
    }
    if (flag==0) return 0;
  }
  return 1;
}

//fução para comparar os resultados e calcular o vencedor em cada categoria
void resultados(int jog, int games, int stats[][][], int int g, int h, char frase[15]){
  int z=0;//guarda o numero do jogador vencedor atual
  int y=0;//guarda o jogo em que o parametro foi o melhor
  int x=301;//guarda o valor do parametro
  for (int i = 0; i < jog; i++) {
    for (size_t u = 0; u < games; u++) {
        if (stats[i][u][g]<x && stats[i][u][g]==1) {//compara com o tempo mais baixo atual e verifica se o jogo foi acabado
          z=i;
          x=stats[i][u][g];
          y=u;
        } else if (stats[i][u][g]==x) {//em caso de empate compara-se o numero de jogadas e verifica se o jogo foi acabado
          if (stats[i][u][h]<stats[z][y][h] && stats[i][u][g]==1) {
            x=stats[i][u][g];
            y=u;
            z=i;
          }
        }
      }
    }
  printf("O vencedor para o jogo %s é: o jogador %d, %s", frase, z+1, name[z]);
}
