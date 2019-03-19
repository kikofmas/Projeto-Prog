/*Projeto intermedio de programação - Mastermind
*
*Bruno Miguel da Silva Cebola - 93030
*Frederico Maria Almeida Santos - 93065*/

//LIBRARIES
#include <locale.h>   //poder usar acentos
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>   //funções de strings
#include <time.h>     //poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions

//DECLARAÇÃO DE FUNÇÕES
void cleanslate(void); //limpa o input indesejado
void initialization(int *var, int min, int max, char frase[10]); //inicializacao das variaveis tipo int
void initializationNames(int num_jogadores, char nome[4][21]); //introducao dos nomes dos jogadores
void initializationRepetitions(char *repeticao_cores); //escolha da existencia repticao de cores
void createKey(char chave[8], char repeticao_cores, int tamanho_chave, int num_cores); //criacao da chave de jogo
int checkInput(char jogada[8], int tamanho_chave, int num_cores); //valida que a jogada é possivel
void vencedor(int dados[4][5][3], float mediaTempos[4], char nome[4][21], int num_jogadores, int num_jogos); //definicao do vencedor do jogo
void resultados(int num_jogadores, int num_jogos, int dados[4][5][3], int g, int h, char frase[15], char nome[4][21]); //apresenta as estatisticas


int main() {
  setlocale(LC_ALL,""); //aceita caracteres especiais e acentos

//declaracao das variaveis da inicializção:
  char nome_jogadores[4][21]={"\0"}, repeticao_cores='\0';
  int num_jogadores=0, duracao_jogo=0, num_jogos=0, num_cores=0, tamanho_chave=0, tentativas=0;
//declaracao das variaveis de jogo:
  char chave[8]="\0", copia_chave[8]="\0", jogada[8]="\0", ultima_cor='\0';
  int lugar_certo=0, lugar_errado=0;
  time_t tempo_inicial=0, tempo_atual=0, tempo_jogo=0, tempo_restante=0;
//declaracao das variaveis das estatisticas:
  int dados[4][5][3]={0}; //[][][0]=tempo, [][][1]=tentativas, [][][2]=vitoria
  float mediaTempos[4]={0, 0, 0, 0};
//inicializacao da funcao srand:
  time_t t;
  srand((unsigned) time(&t)); //inicializa o gerador aleatorio


//INICIALIZACAO DAS VARIAVEIS DE JOGO
  printf("Vamos jogar um jogo de MASTERMIND!\n\n");

  //numero de jogadores
  initialization(&num_jogadores, 1, 4, "o numero de jogadores");
  cleanslate();

  //nome dos jogadores
   initializationNames(num_jogadores, nome_jogadores);

  //numero de jogos
  initialization(&num_jogos, 1, 5, "o numero de jogos");
  cleanslate();

  //numero maximo de tentivas por jogo
  initialization(&tentativas, 10, 20, "o numero maximo de tentativas");
  cleanslate();

  //duracao de cada jogo
  initialization(&duracao_jogo, 60, 300, "o tempo de jogo");
  cleanslate();

  do{
  //dimensao da chave
    initialization(&tamanho_chave, 4, 8, "a dimensao da chave com que deseja jogar");
    cleanslate();

  //numero de cores em jogo
    initialization(&num_cores, 6, 12, "o numero de cores com que deseja jogar");
    cleanslate();

  //repeticao de cores
    initializationRepetitions(&repeticao_cores);

  //verificacao de que a combinacao de parametros e possivel
    if (num_cores<tamanho_chave && (repeticao_cores=='n' || repeticao_cores=='N')) {
      printf("A combinacao dos parametros 'tamanho chave', 'numero cores' e 'repeticao de cores' esta invalida, tente outra vez.\n" );
      num_cores=-1;
      tamanho_chave=0;
      repeticao_cores='\0';
    } else break;
  }while(1);


//JOGO

  for(int jogador=0; jogador<num_jogadores; jogador++){   //passagem por cada jogador
    printf("Jogador %s é a sua vez\n",nome_jogadores[jogador]);
    for(int jogo=0; jogo<num_jogos; jogo++){   //passagem por cada jogo a fazer
      tempo_inicial = time(NULL);   //guarda o valor do tempo no inicio do jogo
      printf("Jogo numero %d\n",jogo+1);

      createKey(chave, repeticao_cores, tamanho_chave, num_cores); //criacao da chave no inicio de cada jogo
      ultima_cor = 'A'+num_cores-1;

      for(int tentativa=0; tentativa<tentativas; tentativa++){//ate maximo tentativa
        lugar_certo=0;     //inicialização das variaveis com o valor 0 no inicio de cada jogo
        lugar_errado=0;
        dados[jogador][jogo][1]=tentativa+1;//grava o numero de jogadas efetuadas
        while (1) {
          char buffer[100];
          printf("Insira uma combinação de cores (A a %c): ", ultima_cor);
          fgets(buffer, 100, stdin);
          strncpy(jogada, buffer, tamanho_chave+1);
          tempo_atual=time(NULL);       //armazenamento do tempo atual
          tempo_jogo = tempo_atual-tempo_inicial;    //calculo do tempo atual que o jogo tem
          tempo_restante = duracao_jogo - tempo_jogo;
          dados[jogador][jogo][0]=tempo_jogo;//grava o tempo do jogo atual
          if(tempo_jogo>duracao_jogo){    //se o limite de tempo for atingido sai do jogo
            printf("O tempo máximo de jogo foi atingido\n");
            break;
          }
          if (strlen(buffer)!=tamanho_chave+1) {
            if (strlen(buffer)>90) cleanslate();
            printf("Erro: input incorreto. Verifique que a combinação tem %d caracteres\n",tamanho_chave);
          }
          else {    //validação do input
            if(checkInput(jogada, tamanho_chave, num_cores)==1){
              break;
            }
            else{
              printf("Erro: input incorreto. A combinação de cores só pode ter caracteres de (A a %c)\n",ultima_cor);
            }
          }
        }

        //se o limite de tempo for atingido sai do jogo
        if(tempo_jogo>duracao_jogo) break;

        for(int index1=0; index1<tamanho_chave; index1++){   //copia da chave para se fazer a comparação
          copia_chave[index1]=chave[index1];
        }

      //verificacao de igualdade entre a chave de jogo e a tentativa do jogador

        for(int index1=0; index1<tamanho_chave; index1++){
          for(int index2=0; index2<tamanho_chave; index2++){
            //confirmacao de cor certa na posicao certa
            if(tolower(jogada[index1])==copia_chave[index2] && index1==index2){
              lugar_certo++;
              copia_chave[index2]='0';
              break;
            }
            //confirmacao de cor certa na posicao errada
            else if(tolower(jogada[index1])==copia_chave[index2]){
              lugar_errado++;
              copia_chave[index2]='0';
              break;
            }
          }
        }

        printf("P%dB%d\n", lugar_certo, lugar_errado);

        if(lugar_certo==tamanho_chave){
          printf("Parabens por ter conseguido acabar o jogo!\n\n");
          dados[jogador][jogo][2]=1;//guarda se o jogador conseguiu completar a partida
          printf("Acabou o jogo apos %li s\n", tempo_jogo);
          break;
        }
        else if(tentativa+1!=tentativas){
          printf("Ainda tem %li s de jogo e %d jogada(s) restante(s)\n", tempo_restante, tentativas-(tentativa+1));
        }
      }
      if(lugar_certo!=tamanho_chave){
        dados[jogador][jogo][2]=0;//guarda se o jogador conseguiu completar a partida
        printf("Lamentamos mas não conseguiu acabar o jogo...\n\n");
      }
    }
  }


//ESTATISTICAS: calculo dos resultados e apresentacao das estatisticas

  //criacao da media de tempo de jogo para cada jogador
  for (int jogador = 0; jogador < num_jogadores; jogador++) {
    for (int jogo = 0; jogo < num_jogos; jogo++) {
      mediaTempos[jogador]+= (float)dados[jogador][jogo][0];
    }
    mediaTempos[jogador]/= (float)num_jogos;
  }

  vencedor(dados, mediaTempos, nome_jogadores, num_jogadores, num_jogos);
  resultados(num_jogadores, num_jogos, dados, 0, 1, "mais rápido", nome_jogadores);
  resultados(num_jogadores, num_jogos, dados, 1, 0, "mais curto", nome_jogadores);

  return 0;
}




//DEFINICAO DE FUNCOES

//funcao para limpar input indesejado
void cleanslate(void){
  char err1;
  while(1) {  //loop ate se encontrar um nova linha ou o fim de o ficheiro
    err1 = getchar();
    if (err1 == '\n' || err1 == EOF) break;
  }
}

//funcao para inicializar as variaveis do jogo do tipo int
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
    else if (*var<min || *var>max) {   //deteção de valores fora dos aceitaveis
    printf("Erro: valor introduzido inválido\n");
    }
  }
  printf("\n");
}

//funcao para introduzir o nome dos jogadores
void initializationNames(int num_jogadores, char nome[4][21]){
  int jogador=0;
  char aux[100]="\0"; //variavel auxiliar para recolher o input do user
  for (; jogador < num_jogadores; jogador++) {
    while (1) {
      printf("Insira o nome do jogador %d (maximo de 20 caracteres):  ", jogador+1);
      fgets(aux, 100, stdin);
      sscanf(aux, "%20s", nome[jogador]);
      if (strlen(aux)>20 || strlen(aux)<=1) {  //confirmação que o input tem apenas 20 caracteres
        if (strlen(aux)>90) cleanslate();
        printf("Erro: input incorreto. Verifique que o nome tem entre 1 e 20 caracteres\n");
      } else break;
    }
  }
  printf("\n");
}

//funcao para escolher se existe repticao de cores
void initializationRepetitions(char *repeticao_cores){
  while (*repeticao_cores!='s' && *repeticao_cores!='n' && *repeticao_cores!='S' && *repeticao_cores!='N') {
    printf("A chave pode ter cores repetidas? [S/N]:  ");
    scanf(" %c", repeticao_cores);
    cleanslate();
    if (*repeticao_cores!='s' && *repeticao_cores!='n' && *repeticao_cores!='S' && *repeticao_cores!='N') {
      printf("Erro: input invalido 1\n");
    }
  }
  printf("\n");
}

//funcao para criar a chave de jogo
void createKey(char chave[8], char repeticao_cores, int tamanho_chave, int num_cores){
  int i=0,aux=0;
  char coresdisp[13]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
  for (i = 0; i < tamanho_chave; i++) {
    //criação de numeros aleatorios ate a condição se verificar
    do{
      aux = rand() % num_cores;
    } while(coresdisp[aux]=='0');
    chave[i]=coresdisp[aux];
    //se n for possivel a repetição de cores elimina-se da  lista a cor inserida na chave
    if(repeticao_cores=='n' || repeticao_cores=='N') coresdisp[aux]='0';
  }
}

//funcao para verificar se o input dado pelo utilizdor durante o jogo e aceitavel
int checkInput(char jogada[], int tamanho_chave, int num_cores){
  char cores[13]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
  for(int i=0;i<tamanho_chave;i++){
    int flag=0;
    for(int z=0;z<num_cores;z++){
      if(tolower(jogada[i])==cores[z]) flag=1;
    }
    if (flag==0) return 0;
  }
  return 1;
}

//funcao para ver quem e o vencedor do jogo
void vencedor(int dados[4][5][3], float mediaTempos[4], char nome[4][21], int num_jogadores, int num_jogos){
  int vencedor=0, vitorias_jogador=0, maximo_vitorias=0;
  for (int index1 = 0; index1 < num_jogadores; index1++) {
    vitorias_jogador=0;
    //contagem do numero de vitorias do jogador
    for (int index2 = 0; index2 < num_jogos; index2++) {
      vitorias_jogador+=dados[index1][index2][2];
    }
    if (vitorias_jogador>maximo_vitorias) { //compara o numero de vitorias com o mais alto atual
      vencedor=index1;  //z e o numero do jogador vencedor atual
      maximo_vitorias = vitorias_jogador;  //y e o parametro vencedor atual
    } else if (vitorias_jogador==maximo_vitorias) { //em caso de empate compara-se a media de tempos dos jogadores
      if (mediaTempos[index1]<mediaTempos[vencedor]) {
        vencedor=index1;
      }
    }
  }
  printf("\n\n\nO vencedor do torneio é: o jogador %d, %s\n\n", vencedor+1, nome[vencedor]);
}

//funcao para comparar os resultados e calcular o vencedor em cada categoria
void resultados(int num_jogadores, int num_jogos, int dados[4][5][3], int dado_principal, int dado_desempate, char frase[15], char nome[4][21]){
  int vencedor=0;//guarda o numero do jogador vencedor atual
  int x=301;//guarda o valor do parametro
  int z=301;
  for (int jogador = 0; jogador < num_jogadores; jogador++) {
    for (int jogo = 0; jogo < num_jogos; jogo++) {
        if (dados[jogador][jogo][dado_principal]<x && dados[jogador][jogo][2]==1) { //compara com o tempo mais baixo atual e verifica se o jogo foi acabado
          vencedor=jogador;
          x=dados[jogador][jogo][dado_principal];
          z=dados[jogador][jogo][dado_desempate];
        } else if (dados[jogador][jogo][dado_principal]==x && dados[jogador][jogo][2]==1) {//em caso de empate compara-se o numero de jogadas e verifica se o jogo foi acabado
          if (dados[jogador][jogo][dado_desempate]<z) {
            x=dados[jogador][jogo][dado_principal];
            z=dados[jogador][jogo][dado_desempate];
            vencedor=jogador;
          }
        }
      }
    }
  printf("O vencedor para o jogo %s é: o jogador %d, %s\n", frase, vencedor+1, nome[vencedor]);
}
