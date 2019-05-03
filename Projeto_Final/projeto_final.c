/******************************************************************************
*
* Projeto intermedio de programacao - MASTERMIND
*
* Bruno Miguel da Silva Cebola - 93030
* Frederico Maria Almeida Santos - 93065
*
******************************************************************************/
//LIBRARIES
#include <stdlib.h>
#include <errno.h>    //library de error handling
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions
#include <unistd.h>   //permite usar a funcao sleep
#include <termios.h>  //permite usar a funcao tcflush


//DECLARACAO DE FUNCOES
void introducao(void); //introducao ao jogo
void cleanslate(void); //limpa o input indesejado
void clearScreen(int k); //elimina o ecra
void countdown(int i, char **nome); //inicia uma contagem decrescente
void initialization(int *var, int min, int max, char frase[]); //inicializacao das variaveis tipo int
void initializationNames(int num_jogadores, char **nome); //introducao dos nomes dos jogadores
void initializationRepetitions(char *repeticao_cores); //escolha da existencia repticao de cores
int checkCombinacao(int *num_cores, int *tamanho_chave, char *repeticao_cores); //confirma os parametros da chave de jogo
int checkInput(char jogada[8], int tamanho_chave, int num_cores); //valida que a jogada é possivel




int main(int argc, char const *argv[]) {
  char **nome;
  char *jogada = NULL;

  return 0;
}


/******************************************************************************
* Nome da funcao: introducao()
*
* Argumentos: none
*
* Return: none
*
* Descricao: funcao para mostrar as regras e o objetivo do jogo
*
******************************************************************************/
void introducao(void){
  printf("Vamos jogar um jogo de MASTERMIND!\n\n");
  printf("Objetivo do Mastermind: Descobrir uma chave (combinacao de cores representada por letras)\n");
  printf("                        que e gerada aleatoriamente pelo computador em cada jogo.\n\n");
  printf("Indicacoes:\n");
  printf(" -Cada jogador tem um limite de tentativas e de tempo para adivinhar a chave;\n");
  printf(" -Cada jogador joga a vez todos os seus jogos;\n");
  printf(" -Apos cada jogada o computador gera uma resposta com a forma PxBy,\n");
  printf("  em que x corresponde ao numero de cores certas no lugar certo\n");
  printf("  e y corresponde ao numero de cores certas no lugar errado;\n\n");
}

/******************************************************************************
* Nome da funcao: cleanslate()
*
* Argumentos: none
*
* Return: none
*
* Descricao: funcao para limpar input indesejado introduzido pelo utilizador
*
******************************************************************************/
void cleanslate(void){
  char err1;
  while(1) {  //loop ate se encontrar um nova linha ou o fim de o ficheiro
    err1 = getchar();
    if (err1 == '\n' || err1 == EOF) break;
  }
}

/******************************************************************************
* Nome da funcao: clearScreen()
*
* Argumentos: k - define se pede input do utilizador antes de apagar o ecrã
*
* Return: none
*
* Side-effects: para a execucao do codigo ate o utilizador clicar enter
*
* Descricao: funcao para limpar o ecra
*
******************************************************************************/
void clearScreen(int k){
  if(k==1){
    printf("\nCLIQUE ENTER PARA CONTINUAR!");
    cleanslate();
  }
  system("clear");
}

/******************************************************************************
* Nome da funcao: countdown()
*
* Argumentos: i - numero do jogador atual
              nome - nome do jogador atual
*
* Return: none
*
* Side-effects: conta 5 segundos no ecrã
*
* Descricao: conta 5 segundos no ecrã e apaga o input do utilizador durante esse tempo
*
******************************************************************************/
void countdown(int k, char **nome){
  for (int i = 5; i > 0 ; i--) {
    printf("Jogador %d: %s, e a sua vez\n\n", k, nome[k]);
    printf("%d\n", i);
    sleep(1);
    clearScreen(0);
  }
  tcflush(0,TCIFLUSH); // 0 representa o stdin, TCIFLUSH limpa o input do utilizador não foi lido
  clearScreen(0);
}

/******************************************************************************
* Nome da funcao: initialization()
*
* Argumentos: *var - localizacao em memoria da variavel a inicializar
*             min - valor minimo que a variavel a inicializar pode tomar
*             max - valor maximo que a variavel a inicializar pode tomar
*             frase[30] - descrição breve (max: 29 chars) da variavel a inicializar
*
* Return: none
*
* Descricao: funcao para inicializar as variaveis do jogo do tipo int
*            (num_jogadores, num_jogos, tentativas, duracao_jogo,
*            tamanho_chave, num_cores)
*
******************************************************************************/
void initialization(int *var, int min, int max, char frase[]){
  while (*var < min || *var > max) {  //loop ate um valor valido ser introduzido
  printf("Insira %s (%d a %d):  ", frase, min, max);
    char input[6];
    fgets(input, 6, stdin);
    if((strlen(input)==2 && atoi(input)<10 && atoi(input)>0)||(strlen(input)==3\
          && atoi(input)>=10 && atoi(input)<100)||(strlen(input)==4 && atoi(input)>=100)){
      if(atoi(input)>=min && atoi(input)<=max){
        *var = atoi(input);
        printf("\n");
      }
      else{
        printf("Erro: Input invalido\n");
      }
    }
    else{
      printf("Erro: Input invalido\n");
      if(strlen(input)>4 && input[4]!='\n'){
        cleanslate();
      }
    }
  }
}

/******************************************************************************
* Nome da funcao: initializationNames()
*
* Argumentos: num_jogadores - numero de jogadores que vao jogar
*             **nome - vetor de ponteiros que guarda a posição do nome dos jogadores
*
* Return: none
*
* Descricao: funcao para introduzir o nome dos jogadores
*
******************************************************************************/
void initializationNames(int num_jogadores, char **nome){
  char aux[101]="\0"; //variavel auxiliar para recolher o input do user
  nome=malloc(sizeof(char *)*num_jogadores);
  for (int jogador=0; jogador < num_jogadores; jogador++) {
    while (1) {
      printf("Insira o nome do jogador %d (maximo de 20 caracteres):  ", jogador+1);
      fgets(aux, 100, stdin);
      if (strlen(aux)>21 || strlen(aux)<=1) {  //confirmacao que o input tem apenas 20 caracteres
        if (strlen(aux)>90) cleanslate();
        printf("Erro: Input invalido. Verifique que o nome tem entre 1 e 20 caracteres\n");
      }
      else{
        nome[jogador]=malloc(sizeof(char)*strlen(aux));
        sscanf(aux, "%20s", nome[jogador]);
        break;
      }
    }
  }
  printf("\n");
}

/******************************************************************************
* Nome da funcao: initializationRepetitions()
*
* Argumentos: *repeticao_cores - localizacao em memoria da variavel que guarda
*                                se existe repeticao de cores
*
* Return: none
*
* Descricao: funcao para o utilizador escolher se existe repeticao de cores
*            na chave de jogo
*
******************************************************************************/
void initializationRepetitions(char *repeticao_cores){
  char aux[4];
  while (tolower(*repeticao_cores)!='s' && tolower(*repeticao_cores)!='n') {
    printf("A chave pode ter cores repetidas? [S/N]:  ");
    fgets(aux,4,stdin);
    if(strlen(aux)!=2){
      if(strlen(aux)>2 && aux[2]!='\n'){
        cleanslate();
        printf("Erro: Input invalido\n");
      }
    }
    else if (tolower(aux[0])!='s' && tolower(aux[0])!='n' && aux[1]!='\n') {
      printf("Erro: Input invalido\n");
    }
    else{
      *repeticao_cores = aux[0];
    }
  }
  printf("\n");
}

/******************************************************************************
* Nome da funcao: checkCombinacao()
*
* Argumentos: *num_cores - localizacao em memoria da variavel a inicializar
*             *tamanho_chave - valor minimo que a variavel a inicializar pode tomar
*             *repeticao_cores - valor maximo que a variavel a inicializar pode tomar
*
* Return: 1 se a combinacao e possivel
*         0 se a combinacao e impossivel
*
* Side-effects: Quando a funcao retorna 0, o valor das variaveis dadas como argumento
*               e alterado: num_cores=0, tamanho_chave=0, repeticao_cores='\0'
*
* Descricao: funcao para confirmar se e possivel criar uma chave de jogo com
*            os parametros definidos
*
******************************************************************************/
int checkCombinacao(int *num_cores, int *tamanho_chave, char *repeticao_cores){
  if (*num_cores < *tamanho_chave && tolower(*repeticao_cores)=='n') {
    printf("A combinacao dos parametros 'tamanho chave', 'numero cores' e\n'repeticao de cores' esta invalida, tente outra vez.\n\n" );
    *num_cores=0;
    *tamanho_chave=0;
    *repeticao_cores='\0';
    return 0;
  }
  return 1;
}

/******************************************************************************
* Nome da funcao: checkInput()
*
* Argumentos: jogada[8] - array onde esta guardada a jogada efetuada pelo jogador
*             tamanho_chave - indica o tamanho que a chave de jogo tem
*             num_cores - indica o numero de cores que estao em jogo
*
* Return: 0 se a jogada for possivel
*         -1 se se a jogada nao for valida
*
* Descricao: funcao para verificar se a jogada feita pelo utilizador esta
*            correta dentro dos parametros definidos durante a inicializacao
*
******************************************************************************/
int checkInput(char *jogada, int tamanho_chave, int num_cores){
  char cores[13]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'};
  for(int i=0;i<tamanho_chave;i++){
    int flag=0;
    for(int z=0;z<num_cores;z++){
      if(toupper(*(jogada+i))==cores[z]) flag=1;
    }
    if (flag==0) return -1;
  }
  return 0;
}
