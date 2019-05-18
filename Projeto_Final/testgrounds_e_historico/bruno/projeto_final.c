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

#include "estruturas.h"
#include "oraculo.h"
#include "intermedio.h"
#include "key.h"


//DECLARACAO DE FUNCOES
char createKey(char chave[8], char repeticao_cores, int tamanho_chave, int num_cores); //criacao da chave de jogo e retorna a ultima cor em jogo
void comparaChave(int tamanho_chave, char jogada[8], char copia_chave[8], int *lugar_certo, int *lugar_errado); //comparacao com a chave de jogo
int userAttempt(dados **ptr_dados, char ultima_cor, char *jogada, int tamanho_chave, time_t tempo_inicial,
                time_t *tempo_jogo, time_t *tempo_restante, int duracao_jogo, int num_cores, int jogador, int jogo); //tentativa do jogador
dados **jogo(int num_jogadores, int num_jogos, int num_cores, int tamanho_chave, int duracao_jogo,\
            int tentativas, char repeticao_cores, char **nome_jogadores);  //funcao que permite jogar
void criaDados(int num_jogadores, int num_jogos, dados **ptr_dados, float **mediaTempos, int **numVitorias); //criacao da media de tempo de jogo de cada jogador
void vencedor(float *mediaTempos, char **nome, int num_jogadores, int *numVitorias); //definicao do vencedor do jogo
void resultados(int num_jogadores, int num_jogos, dados **ptr_dados, int dado_principal, char frase[], char **nome); //apresenta as estatisticas
void showData(dados **ptr_dados, float *mediaTempos, int num_jogadores, int *numVitorias, int num_jogos, char **nome_jogadores);  //apresenta dados extra de jogo
void clear_memory(char **vect1, int v1, dados **ptr_dados, float *vect3, int *vect4);

int mode_check(int argc, char const *argv[], flags *cmd_flag);
int test_mode_config(int k, char const *argv[], flags **cmd_flag);


int main(int argc, char const *argv[]) {

//declaracao das variaveis para o modo de funcionamento do programa
  int error=0;
  flags cmd_flag={0, 0, 0};

//declaracao das variaveis da inicializacao:
  char **nome_jogadores=NULL;
  int combo_possivel=0, rep=0, num_total_tent=0, win=0, tempo=0;
  defs defs_jogo={'\0',0,0,0,0,0,0,0};
  letras **lista_cores=NULL;
  tentativas *lista_tentativas=NULL;

//declaracao das variaveis das estatisticas:
  dados **ptr_dados=NULL; //[][][0]=tempo, [][][1]=tentativas, [][][2]=vitoria
  int *numVitorias=NULL;
  float *mediaTempos=NULL;

//inicializacao da funcao srand:
  time_t t;
  srand((unsigned) time(&t)); //inicializa o gerador aleatorio

  error=mode_check(argc, argv, &cmd_flag);
  if (error==-1) exit(-1);


  //passar para funcao??
  if (cmd_flag.init==0 && cmd_flag.hist==0 && cmd_flag.ord==0) {
    printf("MODO INTERATIVO\n");

    //INICIALIZACAO DAS VARIAVEIS DE JOGO
      introducao();

      //numero de jogadores
      initialization(&defs_jogo.num_jogadores, 1, 4, "o numero de jogadores");

      //nome dos jogadores
      nome_jogadores=initializationNames(defs_jogo.num_jogadores);

      //numero de jogos
      initialization(&defs_jogo.num_jogos, 1, 5, "o numero de jogos");

      //numero maximo de tentivas por jogo
      initialization(&defs_jogo.tentativas, 10, 20, "o numero maximo de tentativas");

      //duracao de cada jogo
      initialization(&defs_jogo.duracao_jogo, 60, 300, "o tempo de jogo (em segundos)");

      do{
      //dimensao da chave
        initialization(&defs_jogo.tamanho_chave, 4, 8, "a dimensao da chave com que deseja jogar");

      //numero de cores em jogo
        initialization(&defs_jogo.num_cores, 6, 12, "o numero de cores com que deseja jogar");

      //repeticao de cores
        initializationRepetitions(&defs_jogo.repeticao_cores);

      //verificacao de que a combinacao de parametros e possivel
        combo_possivel=checkCombinacao(&defs_jogo.num_cores, &defs_jogo.tamanho_chave, &defs_jogo.repeticao_cores);
      }while(combo_possivel==-1);

      if(tolower(defs_jogo.repeticao_cores)=='s') rep=1;

      clearScreen(1);


    //JOGO

      activate_oracle(defs_jogo.tamanho_chave, defs_jogo.num_cores, rep);

      ptr_dados=jogo(defs_jogo.num_jogadores, defs_jogo.num_jogos, defs_jogo.num_cores, defs_jogo.tamanho_chave,
                     defs_jogo.duracao_jogo, defs_jogo.tentativas, defs_jogo.repeticao_cores, nome_jogadores);


    //ESTATISTICAS: calculo dos resultados e apresentacao das estatisticas

      criaDados(defs_jogo.num_jogadores, defs_jogo.num_jogos, ptr_dados, &mediaTempos, &numVitorias);
      vencedor(mediaTempos, nome_jogadores, defs_jogo.num_jogadores, numVitorias);
      resultados(defs_jogo.num_jogadores, defs_jogo.num_jogos, ptr_dados, 0, "mais rapido", nome_jogadores);
      resultados(defs_jogo.num_jogadores, defs_jogo.num_jogos, ptr_dados, 1, "mais curto", nome_jogadores);
      showData(ptr_dados, mediaTempos, defs_jogo.num_jogadores, numVitorias, defs_jogo.num_jogos, nome_jogadores);

      printf("\nESPERAMOS QUE SE TENHA DIVERTIDO!!!\n");

      clear_memory(nome_jogadores, defs_jogo.num_jogadores, ptr_dados, mediaTempos, numVitorias);
}
  else if(cmd_flag.init==0 && cmd_flag.hist!=0 && cmd_flag.ord!=0){
    printf("MODO TESTE\n\nAPENAS REORDENAÇAO");
    /* fazer so o algoritmo de reordenaçao */
    /* load -h file and reord*/
  }
  else if(cmd_flag.init==0 && ((cmd_flag.hist!=0 && cmd_flag.ord==0) || (cmd_flag.hist==0 && cmd_flag.ord!=0))){
    printf("ERRO: Falta o ficheiro das inicializações\n");
    exit(-1);
  }
  else if(cmd_flag.init!=0){
    printf("MODO TESTE\n\n");
    /* jogar EvE */
    /*load init files and others if needed -- use ifs to allow or not passage*/
    FILE *fptr = fopen("init.dat","rb");
    if(fptr!=NULL){
      char *text=NULL, *token=NULL, c='\0';
      int counter=1;
      text = (char *)malloc(sizeof(char));
      while((c=fgetc(fptr))!=EOF){
        text = (char *)realloc(text,counter);
        text[counter-1]=c;
        counter++;
      }
      fclose(fptr);

      token = strtok(text,"\n");
      nome_jogadores = (char **)malloc(sizeof(char*));
      if(nome_jogadores==NULL) exit(-1);
      *nome_jogadores = (char *)malloc((strlen(token)+1)*sizeof(char));
      if(*nome_jogadores==NULL) exit(-1);
      strcpy(nome_jogadores[0],token);
      token = strtok(NULL,"\n");
      defs_jogo.num_jogos = atoi(token);
      token = strtok(NULL,"\n");
      defs_jogo.num_cores = atoi(token);
      token = strtok(NULL,"\n");
      defs_jogo.tamanho_chave = atoi(token);
      token = strtok(NULL,"\n");
      defs_jogo.repeticao_cores = token[0];
      token = strtok(NULL,"\n");
      defs_jogo.tentativas_alea = atoi(token);
      token = strtok(NULL,"\n");
      defs_jogo.tentativas = atoi(token);
      if(defs_jogo.repeticao_cores=='S') rep=1;
      free(text);
    }
    else{
      perror("ERRO:");
      exit(-1);
    }
    activate_oracle(defs_jogo.tamanho_chave, defs_jogo.num_cores, rep);

    //for(int i=0;i<defs_jogo.num_jogos;i++){
      //printf("\nJogo %d\n",i);
      printf("Chave: ");
      generate_key(1);
      printf("\n");

      lista_cores = listaCores(defs_jogo.tamanho_chave, defs_jogo.num_cores);
      lista_tentativas = tentativasAlea(defs_jogo.tentativas_alea, defs_jogo.tamanho_chave, defs_jogo.num_cores, &num_total_tent, &lista_cores, &win, &tempo);
      if(win==0){
        win = keyFinder(defs_jogo.tamanho_chave, &lista_cores, &lista_tentativas, &num_total_tent, &tempo);
      }
      printf("\nNumero de tentativas: %d\n", num_total_tent);
      clear(defs_jogo.tamanho_chave, &lista_tentativas, &lista_cores);
      num_total_tent = 0;
      //sleep(1);
    //}

    printf("%d\n", tempo);
    terminate_oracle();
    free(nome_jogadores[0]);
    free(nome_jogadores);

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
    strncpy(jogada, buffer, tamanho_chave+1);
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
dados **jogo(int num_jogadores, int num_jogos, int num_cores, int tamanho_chave, int duracao_jogo,
          int tentativas, char repeticao_cores, char **nome_jogadores){

  int verificacao=0, lugar_certo=0, lugar_errado=0;
  char *chave = (char *)calloc(tamanho_chave,sizeof(char));
  char *copia_chave = (char *)calloc(tamanho_chave,sizeof(char));
  char *jogada = (char *)calloc(tamanho_chave,sizeof(char));
  char ultima_cor='\0';
  time_t tempo_inicial=0, tempo_restante=0, tempo_jogo=0;

  dados **ptr_dados=calloc(num_jogadores, sizeof(dados *));

  for(int jogador=0; jogador<num_jogadores; jogador++){   //passagem por cada jogador
    ptr_dados[jogador]=calloc(num_jogos, sizeof(dados));

    for(int jogo=0; jogo<num_jogos; jogo++){   //passagem por cada jogo a fazer
      printf("Jogador %d: %s, e a sua vez\n\n", jogador+1, *(nome_jogadores+jogador));
      countdown(jogador+1, (nome_jogadores+jogador));
      printf("Tamanho da chave: %d; Numero de cores: %d; Repeticao de cores: %c;\n", tamanho_chave, num_cores, repeticao_cores);
      printf("Tem %d tentativas e %ds disponiveis\n\n", tentativas, duracao_jogo);
      printf("Jogador %d: %s, e a sua vez\n\n", jogador+1, *(nome_jogadores+jogador));
      tempo_inicial = time(NULL);   //guarda o valor do tempo no inicio do jogo
      printf("Jogo numero %d\n", jogo+1);

      //criacao da chave no inicio de cada jogo
      ultima_cor = createKey(chave, repeticao_cores, tamanho_chave, num_cores);

      for(int tentativa=0; tentativa<tentativas; tentativa++){  //ate maximo tentativas
        lugar_certo=0;     //inicialização das variaveis com o valor 0 no inicio de cada jogo
        lugar_errado=0;
        (ptr_dados[jogador][jogo]).tentativas=tentativa+1;  //grava o numero de jogadas efetuadas

        verificacao = userAttempt(ptr_dados, ultima_cor, jogada, tamanho_chave, tempo_inicial, &tempo_jogo,
                    &tempo_restante, duracao_jogo, num_cores, jogador, jogo);

        if(verificacao==-1) {
          tentativa=tentativas;
        }
        else{
          for(int index1=0; index1<tamanho_chave; index1++){   //copia da chave para se fazer a comparacao
            copia_chave[index1]=chave[index1];
          }

        //verificacao da igualdade entre a chave de jogo e a tentativa do jogador
          comparaChave(tamanho_chave, jogada, copia_chave, &lugar_certo, &lugar_errado);

          if(lugar_certo==tamanho_chave){
            printf("PARABENS por ter conseguido acabar o jogo!\n");
            (ptr_dados[jogador][jogo]).vitoria=1;  //guarda se o jogador conseguiu completar a partida
            printf("Acabou o jogo apos %lis e em %d jogada(s)\n\n", tempo_jogo, tentativa+1);
            tentativa=tentativas;
          }
          else if(tentativas-(tentativa +1)!=0){
            printf("Ainda tem %lis de jogo e %d jogada(s) restante(s)\n", tempo_restante, tentativas-(tentativa +1));
          }
        }
      }
      if(lugar_certo!=tamanho_chave){
        (ptr_dados[jogador][jogo]).vitoria=0;  //guarda se o jogador conseguiu completar a partida
        printf("Lamentamos mas nao conseguiu acabar o jogo...\n");
        printf("A chave correta era: %s\n\n", chave);
      }
      clearScreen(1);
    }
  }

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


void clear_memory(char **vect1, int v1, dados **ptr_dados, float *vect3, int *vect4){
  for (int i = 0; i < v1; i++) {
    free(vect1[i]);
  }
  free(vect1);
  for (int i = 0; i < v1; i++) {
    free(ptr_dados[i]);
  }
  free(ptr_dados);
  free(vect3);
  free(vect4);
}





int mode_check(int argc, char const *argv[], flags *cmd_flag){
  int func_valid=0;

  switch (argc) {
    case 1:
      cmd_flag->init=0;
      cmd_flag->hist=0;
      cmd_flag->ord=0;
      break;
    case 3:
      func_valid = test_mode_config(3, argv, &cmd_flag);
      break;
    case 5:
      func_valid = test_mode_config(5, argv, &cmd_flag);
      break;
    case 7:
      func_valid = test_mode_config(7, argv, &cmd_flag);
      break;
    default:
      printf("ERRO: Numero de argumentos inválido\n");
  }

  if (func_valid == -1) exit(-1);
  return 0;
}

int test_mode_config(int k, char const *argv[], flags **cmd_flag) {
  char ini[] = "-i", hist[] = "-h", ord[] = "-o";

  for (int i = 1; i < k; i += 2) {
    if (strcmp(ini, argv[i]) == 0) {
      (*cmd_flag)->init = i+1;
    } else if (strcmp(hist, argv[i]) == 0) {
      (*cmd_flag)->hist = i+1;
    } else if (strcmp(ord, argv[i]) == 0) {
      (*cmd_flag)->ord = i+1;
    } else {
      printf("ERRO: Argumentos incorretos ou não identificados\n");
      exit(-1);
    }
  }

  return 0;
}
