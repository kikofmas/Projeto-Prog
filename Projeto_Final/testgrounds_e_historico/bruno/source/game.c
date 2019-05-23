#include <stdlib.h>
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
#include "files.h"
#include "memory.h"
#include "sort.h"
#include "game.h"


/******************************************************************************
* Nome da funcao: mode_check()
*
* Argumentos: argc - numero de argumentos passados pela linha de comandos
*             *argv[] - valores passados atraves da linha de comandos
*             *cmd_flag - ponteiro para a estrutura que guarda as posicoes dos argumentos
*
* Return: 1,2 ou 3 dependendo do modo de jogo
*
* Side-effects: se os argumentos nao forem validos forca a saida do programa
*
* Descricao: analisa os argumentos passados atraves da linha de
*            comandos e retorna um modo de jogo
*
******************************************************************************/
int mode_check (int argc, char const *argv[], flags *cmd_flag) {
  int func_valid=0;

  switch (argc) { //analise dos arguemntos dependendo da quantidade
    case 1:
      cmd_flag->init=0;
      cmd_flag->hist=0;
      cmd_flag->ord=0;
      break;
    case 3:
    case 5:
    case 7:
      func_valid = test_mode_config(argc, argv, &cmd_flag);
      break;
    default:
      func_valid=-1;
      printf("ERRO: Numero de argumentos inválido\n");
  }

  //atribuicao do modo de jogo
  if (func_valid == -1) exit(-1);
  else if (cmd_flag->init==0 && cmd_flag->hist==0 && cmd_flag->ord==0) return 1;
  else if (cmd_flag->init == 0  &&  cmd_flag->hist != 0  &&  cmd_flag->ord != 0) return 2;
  else if (cmd_flag->init==0 && ((cmd_flag->hist != 0  &&  cmd_flag->ord == 0) || (cmd_flag->hist == 0  &&  cmd_flag->ord != 0))){
    printf("ERRO: Falta o ficheiro das inicializações\n");
    exit(-1);
  }
  else if (cmd_flag->init!=0) return 3;
  return 0;
}


/******************************************************************************
* Nome da funcao: test_mode_config()
*
* Argumentos: k - numero de argumentos passados pela linha de comandos
*             *argv[] - valores passados atraves da linha de comandos
*             *cmd_flag - ponteiro para a estrutura que guarda as posicoes dos argumentos
*
* Return: 0 quando os argumentos sao validos
*
* Side-effects: se os argumentos nao forem validos forca a saida do programa
*
* Descricao: guarda a posicao de cada argumento na estrutura cmd_flag
*
******************************************************************************/
int test_mode_config (int k, char const *argv[], flags **cmd_flag) {
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


/******************************************************************************
* Nome da funcao: modo_ordancao()
*
* Argumentos: *argv[] - valores passados atraves da linha de comandos
*             cmd_flag - ponteiro para a estrutura que guarda as posicoes dos argumentos
*             *file - ficheiro secundario para abrir
*
* Return: none
*
* Side-effects: none
*
* Descricao: chama as funcoes para realizar a ordenacao do ficheiro de historico
*
******************************************************************************/
void modo_ordenacao(char const *argv[], flags cmd_flag, char *file){
  game_reg *registo_jogo;

  read_hist(argv, cmd_flag.hist, &registo_jogo, file, cmd_flag.hist);
  sort_registry(&registo_jogo, cmd_flag.ord, argv);
  write_file(registo_jogo, argv, file, cmd_flag.hist);
  free_game_registry(registo_jogo);
}


/******************************************************************************
* Nome da funcao: modo_auto()
*
* Argumentos: *argv[] - valores passados atraves da linha de comandos
*             cmd_flag - ponteiro para a estrutura que guarda as posicoes dos argumentos
*             *file - ficheiro secundario para abrir
*
* Return: none
*
* Side-effects: none
*
* Descricao: chama as funcoes que permitem ao computador adivinhar a chave de jogo
*
******************************************************************************/
void modo_auto(char const *argv[], flags cmd_flag, char *file){
  defs defs_jogo={'\0',0,0,0,0,0,0,-1};
  hist_data last_game={0, 0, NULL};
  letras **lista_cores=NULL;
  tentativas *lista_tentativas=NULL;
  char **nome_jogadores=NULL;
  int rep=0, win=0, tempo=0, num_total_tent=0;

  read_init(argv[cmd_flag.init], &defs_jogo, &nome_jogadores);
  hist_max_values(argv, cmd_flag.hist, &last_game, file);
  last_game.player_ID++;

  if(tolower(defs_jogo.repeticao_cores) == 's') rep=1;
  activate_oracle(defs_jogo.tamanho_chave, defs_jogo.num_cores, rep);

  for (int i = 0; i < defs_jogo.num_jogos; i++) {
    win = 0;  //faz as reset as variaveis no inicio de cada no jogo
    tempo=0;
    num_total_tent = 0;
    printf("\nJogo %d\n", i+1);
    printf("Chave: ");
    generate_key(1);
    printf("\n");

    lista_cores = listaCores(defs_jogo.tamanho_chave, defs_jogo.num_cores);
    lista_tentativas = tentativasAlea(defs_jogo, &num_total_tent, &lista_cores, &win, &tempo, 1);

    if(win == 0) win = keyFinder(defs_jogo, defs_jogo.tamanho_chave, &lista_cores, &lista_tentativas, &num_total_tent, &tempo, 1);

    printf("\nNumero de tentativas: %d\n", num_total_tent);

    write_file_raw(lista_tentativas, argv, file, cmd_flag.hist, &last_game, nome_jogadores, num_total_tent, tempo, defs_jogo, win);
    clear_keyFinder(defs_jogo.tamanho_chave, &lista_tentativas, &lista_cores);  //limpa toda a memoria usada pelo algoritmo
    sleep(1);
  }

  terminate_oracle();
  free(nome_jogadores[0]);
  free(nome_jogadores);

  if (cmd_flag.ord != 0) modo_ordenacao(argv, cmd_flag, file);
}


/******************************************************************************
* Nome da funcao: modo_inter_pc()
*
* Argumentos: *argv[] - valores passados atraves da linha de comandos
*             cmd_flag - ponteiro para a estrutura que guarda as posicoes dos argumentos
*             *file - ficheiro secundario para abrir
*
* Return: none
*
* Side-effects: forca a saida caso a alocacao de memoria nao for bem sucedida
*
* Descricao: chama as funcoes que permitem jogar o modo interativo PESSOA/COMPUTADOR
*
******************************************************************************/
void modo_inter_pc(char const *argv[], flags cmd_flag, char *file){
  defs defs_jogo={'\0',0,0,0,0,0,0,-1};
  hist_data last_game={0, 0, NULL};
  letras **lista_cores=NULL;
  tentativas *lista_tentativas=NULL;
  char **nome_jogadores=NULL;
  int combo_possivel=0, rep=0, win=0, tempo=0, num_total_tent=0;

  hist_max_values(argv, cmd_flag.hist, &last_game, file);
  last_game.player_ID++;

  defs_jogo.num_jogadores=1;
  //nome dos jogadores
  nome_jogadores=calloc(1,sizeof(char*));
  if(nome_jogadores==NULL) exit(-1);  //confirma a correta alocacao de memoria
  nome_jogadores[0]=calloc(strlen("computer")+1,sizeof(char));
  if(nome_jogadores[0]==NULL) exit(-1); //confirma a correta alocacao de memoria
  strcpy(nome_jogadores[0],"computer");
  //numero de jogos
  initialization(&defs_jogo.num_jogos, 1, 5, "o numero de jogos");
  //numero maximo de tentivas por jogo
  initialization(&defs_jogo.tentativas, 10, 20, "o numero maximo de tentativas");
  //numero maximo de tentivas aleatorias por jogo
  initialization(&defs_jogo.tentativas_alea, 0, (20-defs_jogo.tentativas), "o numero maximo de tentativas aleatorias");
  do {
  //dimensao da chave
    initialization(&defs_jogo.tamanho_chave, 4, 8, "a dimensao da chave com que deseja jogar");
  //numero de cores em jogo
    initialization(&defs_jogo.num_cores, 6, 12, "o numero de cores com que deseja jogar");
  //repeticao de cores
    initializationRepetitions(&defs_jogo.repeticao_cores);
  //verificacao de que a combinacao de parametros e possivel
    combo_possivel=checkCombinacao(&defs_jogo);
  } while(combo_possivel == -1);

  if(tolower(defs_jogo.repeticao_cores)=='s') rep=1;
  activate_oracle(defs_jogo.tamanho_chave, defs_jogo.num_cores, rep);

  for(int i=0;i<defs_jogo.num_jogos;i++){
    win = 0;  //reset das variaveis a cada jogo
    tempo=0;
    num_total_tent = 0;
    printf("\nJogo %d\n",i);
    lista_cores = listaCores(defs_jogo.tamanho_chave, defs_jogo.num_cores);
    lista_tentativas = tentativasAlea(defs_jogo, &num_total_tent, &lista_cores, &win, &tempo, 2);

    if (win==0) win = keyFinder(defs_jogo, defs_jogo.tamanho_chave, &lista_cores, &lista_tentativas, &num_total_tent, &tempo, 2);

    printf("\nNumero de tentativas: %d\n", num_total_tent);

    write_file_raw(lista_tentativas, argv, file, cmd_flag.hist, &last_game, nome_jogadores, num_total_tent, tempo, defs_jogo, win);

    clear_keyFinder(defs_jogo.tamanho_chave, &lista_tentativas, &lista_cores);  //free da memoria usada pelo algoritmo
    sleep(1);
  }

  terminate_oracle();
  free(nome_jogadores[0]);
  free(nome_jogadores);
}


/******************************************************************************
* Nome da funcao: modo_inter_intermedio()
*
* Argumentos: *argv[] - valores passados atraves da linha de comandos
*             cmd_flag - ponteiro para a estrutura que guarda as posicoes dos argumentos
*             *file - ficheiro secundario para abrir
*
* Return: none
*
* Side-effects: none
*
* Descricao: chama as funcoes que permitem jogar o modo interativo PESSOA/PESSOA
*
******************************************************************************/
void modo_inter_intermedio(char const *argv[], flags cmd_flag, char *file){
  int combo_possivel=0;
  char **nome_jogadores=NULL;
  int *numVitorias=NULL;
  float *mediaTempos=NULL;
  dados **ptr_dados=NULL; //[][][0]=tempo, [][][1]=tentativas, [][][2]=vitoria
  defs defs_jogo={'\0',0,0,0,0,0,0,-1};
  hist_data last_game={0, 0, NULL};
  game_reg *registo_jogo;

  time_t t;
  srand((unsigned) time(&t)); //inicializa o gerador aleatorio

  //INICIALIZACAO DAS VARIAVEIS DE JOGO
    cleanslate();

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
    do {
    //dimensao da chave
      initialization(&defs_jogo.tamanho_chave, 4, 8, "a dimensao da chave com que deseja jogar");
    //numero de cores em jogo
      initialization(&defs_jogo.num_cores, 6, 12, "o numero de cores com que deseja jogar");
    //repeticao de cores
      initializationRepetitions(&defs_jogo.repeticao_cores);
    //verificacao de que a combinacao de parametros e possivel
      combo_possivel=checkCombinacao(&defs_jogo);
    } while(combo_possivel == -1);
    clearScreen(1);

  //JOGO
    //activate_oracle(defs_jogo.tamanho_chave, defs_jogo.num_cores, rep);
    hist_max_values(argv, cmd_flag.hist, &last_game, file);
    ptr_dados=jogo(defs_jogo, nome_jogadores, &registo_jogo, &last_game);
  //ESTATISTICAS: calculo dos resultados e apresentacao das estatisticas
    write_file(registo_jogo, argv, file, cmd_flag.hist);
    criaDados(defs_jogo.num_jogadores, defs_jogo.num_jogos, ptr_dados, &mediaTempos, &numVitorias);
    vencedor(mediaTempos, nome_jogadores, defs_jogo.num_jogadores, numVitorias);
    resultados(defs_jogo.num_jogadores, defs_jogo.num_jogos, ptr_dados, 0, "mais rapido", nome_jogadores);
    resultados(defs_jogo.num_jogadores, defs_jogo.num_jogos, ptr_dados, 1, "mais curto", nome_jogadores);
    showData(ptr_dados, mediaTempos, defs_jogo.num_jogadores, numVitorias, defs_jogo.num_jogos, nome_jogadores);

    printf("\nESPERAMOS QUE SE TENHA DIVERTIDO!!!\n");

    clear_memory(nome_jogadores, defs_jogo.num_jogadores, ptr_dados, mediaTempos, numVitorias, registo_jogo);
}