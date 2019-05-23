#include <stdlib.h>
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions
#include <unistd.h>   //permite usar a funcao sleep
#include <termios.h>  //permite usar a funcao tcflush

#include "estruturas.h"
#include "intermedio.h"
#include "sort.h"

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
    printf("%d\n", i);
    sleep(1);
    clearScreen(0);
    printf("Jogador %d: %s, e a sua vez\n\n", k, *nome);
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
void initialization(int *var, int min, int max, char frase[30]){
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
char **initializationNames(int num_jogadores){
  char aux[101]="\0"; //variavel auxiliar para recolher o input do user
  char **nome_jogadores=calloc(num_jogadores, sizeof(char *));
  if(nome_jogadores==NULL) exit(-1);  //confirma a correta alocacao de memoria
  for (int jogador=0; jogador < num_jogadores; jogador++) {
    while (1) {
      printf("Insira o nome do jogador %d (maximo de 20 caracteres):  ", jogador+1);
      fgets(aux, 100, stdin);
      if (strlen(aux)>21 || strlen(aux)<=1) {  //confirmacao que o input tem apenas 20 caracteres
        if (strlen(aux)>90) cleanslate();
        printf("Erro: Input invalido. Verifique que o nome tem entre 1 e 20 caracteres\n");
      }
      else{
        nome_jogadores[jogador]=(char *)calloc(strlen(aux)+1, sizeof(char));
        if(nome_jogadores[jogador]==NULL) exit(-1);  //confirma a correta alocacao de memoria
        sscanf(aux, "%s", nome_jogadores[jogador]);
        break;
      }
    }
  }
  printf("\n");
  return nome_jogadores;
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
* Return: 0 se a combinacao e possivel
*         -1 se a combinacao e impossivel
*
* Side-effects: Quando a funcao retorna 0, o valor das variaveis dadas como argumento
*               e alterado: num_cores=0, tamanho_chave=0, repeticao_cores='\0'
*
* Descricao: funcao para confirmar se e possivel criar uma chave de jogo com
*            os parametros definidos
*
******************************************************************************/
int checkCombinacao(defs *def){
  if (def->num_cores < def->tamanho_chave && tolower(def->repeticao_cores)=='n') {
    printf("A combinacao dos parametros 'tamanho chave', 'numero cores' e\n'repeticao de cores' esta invalida, tente outra vez.\n\n" );
    def->num_cores=0;
    def->tamanho_chave=0;
    def->repeticao_cores='\0';
    return -1;
  }
  return 0;
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
int checkInput(char jogada[8], int tamanho_chave, int num_cores){
  char cores[13]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'};
  for(int i=0;i<tamanho_chave;i++){
    int flag=0;
    for(int z=0;z<num_cores;z++){
      if(toupper(jogada[i])==cores[z]) flag=1;
    }
    if (flag==0) return -1;
  }
  return 0;
}

/******************************************************************************
* Nome da funcao: createKey()
*
* Argumentos: chave[8] - variavel onde a chave de jogo vai ser guardada
*             repeticao_cores - indica se a chave tem ou nao repeticao de cores
*             tamanho_chave - indica o tamanho que a chave de jogo tem de ter
*             num_cores - indica quantas cores estao em jogo
*
* Return: devolve um char correspondente a ultima cor em jogo
*
* Descricao: funcao usada para criar a chave de jogo
*
******************************************************************************/
char createKey(char chave[8], char repeticao_cores, int tamanho_chave, int num_cores){
  int aux=0;
  char coresdisp[13]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'};
  for (int i = 0; i < tamanho_chave; i++) {
    //criacao de numeros aleatorios ate a condição se verificar
    do{
      aux = rand() % num_cores;
    } while(coresdisp[aux]=='0');
    chave[i]=coresdisp[aux];
    //se n for possivel a repeticao de cores elimina-se da lista a cor inserida na chave
    if(repeticao_cores=='n' || repeticao_cores=='N') coresdisp[aux]='0';
  }

  return 'A'+num_cores-1;
}


/******************************************************************************
* Nome da funcao: comparaChave()
*
* Argumentos: tamanho_chave - indica o tamanho que a chave de jogo tem
*             jogada[8] - array onde esta guardada a jogada do utilizador
*             copia_chave[8] - copia da chave de jogo para se efetuar a comparacao
*             *lugar_certo - localizacao em memoria da variavel que guarda o
*                            numero de cores certa na posicao certa
*             *lugar_errado - localizacao em memoria da variavel que guarda o
*                            numero de cores certa na posicao errada
*
* Return: none
*
* Descricao: funcao para comparar a chave de jogo com a jogada feita pelo jogador.
*            Altera as variavies lugar_certo e lugar_errado de acordo com as
*            comparacoes efetuadas
*
******************************************************************************/
void comparaChave(int tamanho_chave, char jogada[8], char copia_chave[8], int *lugar_certo, int *lugar_errado){
  for(int index1=0; index1<tamanho_chave; index1++){
    if(toupper(jogada[index1])==copia_chave[index1]){
      *lugar_certo+=1;
      copia_chave[index1]='0';
      jogada[index1]='1';
    }
  }

  for(int index1=0; index1<tamanho_chave; index1++){
    for(int index2=0; index2<tamanho_chave; index2++){
      if(toupper(jogada[index1])==copia_chave[index2]){
        *lugar_errado+=1;
        copia_chave[index2]='0';
        jogada[index1]='1';
        index2=tamanho_chave;
      }
    }
  }
  printf("P%dB%d\n\n", *lugar_certo, *lugar_errado);
}


/******************************************************************************
* Nome da funcao: userAttempt()
*
* Argumentos: dados[4][5][3] - array onde se guardam os dados de jogo
*             ultima_cor - indica a ultima cor em jogo
*             jogada[8] - variavel onde se guarda a jogada efetuada
*             tamanho_chave - indica o tamanho maximo que a jogada pode ter
*             tempo_inicial - usado para calcular o tempo de jogos
*             *tempo_jogo - localizacao em memoria da variavel que guarda o
*                           tempo em que o jogo vai
*             *tempo_restante - localizacao em memoria da variavel que guarda
*                               quanto tempo falta para o fim do jogo
*             duracao_jogo - indica o tempo maximo que o jogo pode durar
*             num_cores - indica quantas cores estao em jogo
*             jogador - indica o jogador que se encontra a jogar
*             jogo - indica o jogo em que o jogador se encontra
*
* Return: 0 se a jogada efetuada for valida e o tempo de jogo ainda nao tiver acabado
*         -1 se o tempo de jogo chegar ao maximo defindo pelo utilizador
*
* Side-effects: Quando a funcao retorna zero leva acpassagem para o proximo
*               jogo no decorrer do fluxo de jogo
*
* Descricao: funcao para confirmar a validade da jogada efetuada pelo jogador
*
******************************************************************************/
int userAttempt(dados **ptr_dados, char ultima_cor, char *jogada, int tamanho_chave, time_t tempo_inicial,
                time_t *tempo_jogo, time_t *tempo_restante, int duracao_jogo, int num_cores, int jogador, int jogo){
  time_t tempo_atual=0;
  while (1) {
    char buffer[100];
    printf("Insira uma combinacao de cores (A a %c): ", ultima_cor);
    fgets(buffer, 100, stdin);
    strncpy(jogada, buffer, tamanho_chave);
    tempo_atual=time(NULL);       //armazenamento do tempo atual
    *tempo_jogo = tempo_atual-tempo_inicial;    //calculo do tempo atual que o jogo tem
    *tempo_restante = duracao_jogo - *tempo_jogo;
    ptr_dados[jogador][jogo].tempo=*tempo_jogo;   //grava o tempo do jogo atual
    if(*tempo_jogo>duracao_jogo){    //se o limite de tempo for atingido sai do jogo
      printf("\nO tempo maximo de jogo foi atingido\n");
      ptr_dados[jogador][jogo].tempo=duracao_jogo;
      return -1;
    }
    else if ((int)strlen(buffer)!=tamanho_chave+1) {
      if (strlen(buffer)>90) cleanslate();
      printf("Erro: input incorreto. Verifique que a combinacao tem %d caracteres\n",tamanho_chave);
    }
    else {    //validacao do input
      if(checkInput(jogada, tamanho_chave, num_cores)==0){
        return 0;
      }
      else{
        printf("Erro: input incorreto. A combinacao de cores so pode ter caracteres de (A a %c)\n",ultima_cor);
      }
    }
  }
}


/******************************************************************************
* Nome da funcao: jogo()
*
* Argumentos: num_jogadores - indica quantos jogadores exitem em jogo
*             num_jogos - indica quantos jogos cada jogador realiza
*             num_cores - indica quantas cores estao em jogo
*             tamanho_chave - indica o tamanho maximo que a jogada pode ter
*             duracao_jogo - indica o tempo maximo que o jogo pode durar
*             tentativas - indica quantas tentativas cada jogador tem
*             repeticao_cores - indica se exite repeticao de cores na chave
*             nome_jogadores[4][21] - array onde estao guardados os nomes dos jogadores
*             dados[4][5][3] - array onde se guardam os dados de jogo
*
* Return: none
*
* Descricao: funcao que realiza todo o processo de jogo
*
******************************************************************************/
dados **jogo(defs def, char **nome_jogadores, game_reg **registo_jogo, hist_data *last_game){
  FILE *fptr=fopen("game_history.dat","wb");
  if(fptr==NULL) exit(-1);

  int verificacao=0, lugar_certo=0, lugar_errado=0;
  time_t tempo_inicial=0, tempo_restante=0, tempo_jogo=0;
  char ultima_cor='\0';
  char *chave = (char *)calloc(def.tamanho_chave+1,sizeof(char));
  char *copia_chave = (char *)calloc(def.tamanho_chave+1,sizeof(char));
  char *jogada = (char *)calloc(def.tamanho_chave+1,sizeof(char));
  char *copia_jogada = (char *)calloc(def.tamanho_chave+1,sizeof(char));
  dados **ptr_dados=calloc(def.num_jogadores, sizeof(dados *));

  if(chave==NULL || copia_chave==NULL || jogada==NULL || ptr_dados==NULL) exit(-1); //confirma a correta alocacao de memoria

  for(int jogador=0; jogador<def.num_jogadores; jogador++){   //passagem por cada jogador
    ptr_dados[jogador]=calloc(def.num_jogos, sizeof(dados));
    if(ptr_dados[jogador]==NULL) exit(-1);  //confirma a correta alocacao de memoria
    for(int jogo=0; jogo<def.num_jogos; jogo++){   //passagem por cada jogo a fazer
      save_game_ini(registo_jogo, last_game, nome_jogadores, def, jogador);
      printf("Jogador %d: %s, e a sua vez\n\n", jogador+1, *(nome_jogadores+jogador));
      countdown(jogador+1, (nome_jogadores+jogador));
      printf("Tamanho da chave: %d; Numero de cores: %d; Repeticao de cores: %c;\n", def.tamanho_chave, def.num_cores, def.repeticao_cores);
      printf("Tem %d tentativas e %ds disponiveis\n\n", def.tentativas, def.duracao_jogo);
      printf("Jogador %d: %s, e a sua vez\n\n", jogador+1, *(nome_jogadores+jogador));
      tempo_inicial = time(NULL);   //guarda o valor do tempo no inicio do jogo
      printf("Jogo numero %d\n", jogo+1);

      //criacao da chave no inicio de cada jogo
      ultima_cor = createKey(chave, def.repeticao_cores, def.tamanho_chave, def.num_cores);

      for(int tentativa=0; tentativa<def.tentativas; tentativa++){  //ate maximo tentativas
        lugar_certo=0;     //inicialização das variaveis com o valor 0 no inicio de cada jogo
        lugar_errado=0;
        (ptr_dados[jogador][jogo]).tentativas=tentativa+1;  //grava o numero de jogadas efetuadas

        verificacao = userAttempt(ptr_dados, ultima_cor, jogada, def.tamanho_chave, tempo_inicial, &tempo_jogo,
                    &tempo_restante, def.duracao_jogo, def.num_cores, jogador, jogo);

        if(verificacao==-1) {
          tentativa=def.tentativas;
        }
        else{
          for(int index1=0; index1<def.tamanho_chave; index1++){   //copia da chave para se fazer a comparacao
            copia_chave[index1]=chave[index1];
          }

        //verificacao da igualdade entre a chave de jogo e a tentativa do jogador
          strcpy(copia_jogada,jogada);
          comparaChave(def.tamanho_chave, jogada, copia_chave, &lugar_certo, &lugar_errado);
          save_guess_ini(*registo_jogo, lugar_certo, lugar_errado, tentativa, copia_jogada);

          if(lugar_certo==def.tamanho_chave){
            printf("PARABENS por ter conseguido acabar o jogo!\n");
            (ptr_dados[jogador][jogo]).vitoria=1;  //guarda se o jogador conseguiu completar a partida
            save_key(1, *registo_jogo, copia_jogada, tempo_jogo, def);
            printf("Acabou o jogo apos %lis e em %d jogada(s)\n\n", tempo_jogo, tentativa+1);
            tentativa=def.tentativas;
          }
          else if(def.tentativas-(tentativa +1)!=0){
            printf("Ainda tem %lis de jogo e %d jogada(s) restante(s)\n", tempo_restante, def.tentativas-(tentativa +1));
          }
        }
      }
      if(lugar_certo!=def.tamanho_chave){
        (ptr_dados[jogador][jogo]).vitoria=0;  //guarda se o jogador conseguiu completar a partida
        save_key(0, *registo_jogo, copia_jogada, tempo_jogo, def);
        printf("Lamentamos mas nao conseguiu acabar o jogo...\n");
        printf("A chave correta era: %s\n\n", chave);
      }
      clearScreen(1);
    }
  }
  fclose(fptr);
  free(chave);
  free(copia_chave);
  free(jogada);
  return (ptr_dados);
}


/******************************************************************************
* Nome da funcao: criaDados()
*
* Argumentos: num_jogadores - indica o numero de jogadores
*             num_jogos - indica o numeros de jogos
*             dados[4][5][3] - array onde estao guardados os dados de jogo
*             mediaTempos[4] - array onde se guarda a media de tempo de cada jogador
*             numVitorias[4] - array onde se guarda o numero de vitorias de cada jogador
*
* Return: none
*
* Descricao: funcao para gerar os dados de jogo gerais de cada jogador:
*            media de tempo de jogo e numero de vitorias
*
******************************************************************************/
void criaDados(int num_jogadores, int num_jogos, dados **ptr_dados, float **mediaTempos, int **numVitorias){

  *mediaTempos=(float *)calloc(num_jogadores+1, sizeof(float));
  *numVitorias=(int *)calloc(num_jogadores+1, sizeof(int));

  if(*mediaTempos==NULL || *numVitorias==NULL) exit(-1);  //confirma a correta alocacao de memoria

  for (int jogador = 0; jogador < num_jogadores; jogador++) {
    for (int jogo = 0; jogo < num_jogos; jogo++) {
      if((ptr_dados[jogador][jogo]).vitoria==1) *mediaTempos[jogador] += (float)((ptr_dados[jogador][jogo]).tempo);
      *numVitorias[jogador] += (ptr_dados[jogador][jogo]).vitoria;
    }
    if(*numVitorias[jogador]!=0) *mediaTempos[jogador]/= (float)(*numVitorias[jogador]);
  }
}


/******************************************************************************
* Nome da funcao: vencedor()
*
* Argumentos: mediaTempos[4] - array onde etsa guardada a media de tempo de cada jogador
*             nome[4][21] - array onde estao guardados os nomes dos jogadores
*             num_jogadores - indica o numero de jogadores
*             num_jogos - indica o numeros de jogos
*             numVitorias[4] - array onde estao guardados o numero de vitorias de cada jogador
*
* Return: none
*
* Descricao: funcao para descobrir o vencedor do jogo
*
******************************************************************************/
void vencedor(float *mediaTempos, char **nome, int num_jogadores, int *numVitorias){
  int vencedor=0, maximo_vitorias=0, empate=0;

  printf("ESTATISTICAS:\n");

  for (int jogador = 0; jogador < num_jogadores; jogador++) {

    if (numVitorias[jogador]>maximo_vitorias) { //compara o numero de vitorias com o mais alto atual
      vencedor=jogador;  //z e o numero do jogador vencedor atual
      maximo_vitorias = numVitorias[jogador];  //y e o parametro vencedor atual
      empate=0;
    }
    else if (numVitorias[jogador]==maximo_vitorias) { //em caso de empate compara-se a media de tempos dos jogadores
      if (mediaTempos[jogador]<mediaTempos[vencedor]) {
        vencedor=jogador;
        empate=0;
      }
      else if(mediaTempos[jogador]==mediaTempos[vencedor]){
        empate=1;
      }
    }
  }

  if(maximo_vitorias==0) printf("\nNinguem consegiu acertar em nenhuma chave de jogo. Nao ha vencedores.\n");
  else if(num_jogadores==1) printf("\nNao e possivel determinar um vencedor devido a falta de oponentes.\n");
  else if(empate==1) printf("\nExiste um empate no jogo!\n");
  else printf("\nO vencedor do torneio e: o jogador %d, %s.\n", vencedor+1, *(nome+vencedor));
}


/******************************************************************************
* Nome da funcao: resultados()
*
* Argumentos: num_jogadores - indica o numero de jogadores
*             num_jogos - indica o numeros de jogos
*             dados[4][5][3] - array onde estao guardados os dados de jogo
*             dado_principal - indica o dado que esta a ser comparado:
*                               0 - tempo de jogo
*                               1 - tentativas de jogo
*             dado_desempate - indica o dado para desempatar a comparacao:
*                               0 - tempo de jogo
*                               1 - tentativas de jogo
*             frase[15] - descrição breve (max: 14 chars) da comparacao
*             nome[4][21] - array onde estao guardados os nomes dos jogadores
*
* Return: none
*
* Descricao: funcao para comparar os dados de jogo e indicar o vencedor de cada
*            categoria (jogo mais rapido ou jogo em menos tentativas) dependendo
*            do dado principal indicado
*
******************************************************************************/
void resultados(int num_jogadores, int num_jogos, dados **ptr_dados, int dado_principal, char frase[], char **nome){
  int vencedor=0; //guarda o numero do jogador vencedor atual
  int x=301;  //guarda o valor do parametro principal
  int z=301;  //guarda o valor do parametro secundario
  int y=0; //verifica se ha pelo menos um jogo ganho por alguem
  int empate=0;
  int principal = 0, desempate = 0;
  if(num_jogadores!=1){
    for (int jogador = 0; jogador < num_jogadores; jogador++) {
      for (int jogo = 0; jogo < num_jogos; jogo++) {
        //compara com o tempo mais baixo atual e verifica se o jogo foi acabado
        if(dado_principal==0){
          principal=ptr_dados[jogador][jogo].tempo;
          desempate=ptr_dados[jogador][jogo].tentativas;
        }
        else if(dado_principal==1){
          principal=ptr_dados[jogador][jogo].tentativas;
          desempate=ptr_dados[jogador][jogo].tempo;
        }
        if (principal<x && ptr_dados[jogador][jogo].vitoria==1) {
          vencedor=jogador;
          x=principal;
          z=desempate;
          y=1;
          empate=0;
        }
        //em caso de empate compara-se o numero de jogadas e verifica se o jogo foi acabado
        else if (principal==x && ptr_dados[jogador][jogo].vitoria==1) {
          if (desempate<z) {
            y=1;
            x=principal;
            z=desempate;
            vencedor=jogador;
            y=1;
            empate=0;
          }
          else if (desempate==z){
            empate=1;
          }
        }
      }
    }
    if(y!=0 && empate==0) printf("\nO vencedor do jogo %s e: o jogador %d, %s\n", frase, vencedor+1, nome[vencedor]);
    else if(y!=0 && empate==1) printf("\nHa um empate na categoria de jogo %s\n", frase);
  }
}


/******************************************************************************
* Nome da funcao: showData()
*
* Argumentos: dados[4][5][3] - array onde estao guardados os dados de jogo
*             mediaTempos[4] - array onde esta guardada a media de tempo de cada jogador
*             num_jogadores - indica o numero de jogadores
*             numVitorias[4] - array onde esta guardado o numero de vitorias de cada jogador
*             num_jogos - indica o numero de jogos
*             char nome_jogadores[4][21] - array onde estao guardados os nomes dos jogadores
*
* Return: none
*
* Descricao: funcao para mostrar os resultados de cada jogador
*
******************************************************************************/
void showData(dados **ptr_dados, float *mediaTempos, int num_jogadores, int *numVitorias, int num_jogos, char **nome_jogadores){
  int mostraDados=0, melhorTempo=301, melhorPerformance=20;
  printf("\nSe desejar ver os dados de jogo insira 1: ");
  scanf("%d",&mostraDados);
  if(mostraDados==1){
    for(int jogador=0;jogador<num_jogadores;jogador++){
      melhorTempo=301;
      melhorPerformance=20;
      for(int jogo=0; jogo<num_jogos; jogo++){
        if((ptr_dados[jogador][jogo]).tempo<melhorTempo){
          melhorTempo=(ptr_dados[jogador][jogo]).tempo;
        }
        if((ptr_dados[jogador][jogo]).tentativas<melhorPerformance){
          melhorPerformance=(ptr_dados[jogador][jogo]).tentativas;
        }
      }
      printf("\nDados do jogador %d, %s\n",jogador+1, *(nome_jogadores+jogador));
      printf("  Numero de vitorias: %d\n", numVitorias[jogador]);
      if(numVitorias[jogador]!=0){
        printf("  Tempo medio: %.2fs\n", mediaTempos[jogador]);
        printf("  Melhor tempo: %ds\n", melhorTempo);
        printf("  Melhor performance: %d jogada(s)\n", melhorPerformance);
      }
      else if(numVitorias[jogador]==0){
        printf("  Tempo medio: Nao aplicavel\n");
        printf("  Melhor tempo: Nao aplicavel\n");
        printf("  Melhor performance: Nao aplicavel\n");
      }
    }
    getchar();
    clearScreen(1);
  } else{
    clearScreen(0);
  }
}
