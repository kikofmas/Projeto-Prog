/*TRANSICAO*/



void resultados(int num_jogadores, int num_jogos, dados **ptr_dados, int dado_principal, int dado_desempate, char frase[], char **nome); //apresenta as estatisticas
void showData(dados **ptr_dados, float *mediaTempos, int num_jogadores, int *numVitorias, int num_jogos, char **nome_jogadores);  //apresenta dados extra de jogo

/***************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************
***************************************************************************************************************************************************************************/







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
void resultados(int num_jogadores, int num_jogos, dados **ptr_dados, int dado_principal, int dado_desempate, char frase[], char **nome){
  int vencedor=0; //guarda o numero do jogador vencedor atual
  int x=301;  //guarda o valor do parametro principal
  int z=301;  //guarda o valor do parametro secundario
  int y=0; //verifica se ha pelo menos um jogo ganho por alguem
  int empate=0;
  if(num_jogadores!=1){
    for (int jogador = 0; jogador < num_jogadores; jogador++) {
      for (int jogo = 0; jogo < num_jogos; jogo++) {
        //compara com o tempo mais baixo atual e verifica se o jogo foi acabado
        if (dados[jogador][jogo][dado_principal]<x && dados[jogador][jogo][2]==1) {
          vencedor=jogador;
          x=dados[jogador][jogo][dado_principal];
          z=dados[jogador][jogo][dado_desempate];
          y=1;
          empate=0;
        }
        //em caso de empate compara-se o numero de jogadas e verifica se o jogo foi acabado
        else if (dados[jogador][jogo][dado_principal]==x && dados[jogador][jogo][2]==1) {
          if (dados[jogador][jogo][dado_desempate]<z) {
            y=1;
            x=dados[jogador][jogo][dado_principal];
            z=dados[jogador][jogo][dado_desempate];
            vencedor=jogador;
            y=1;
            empate=0;
          }
          else if (dados[jogador][jogo][dado_desempate]==z){
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
        if(dados[jogador][jogo][0]<melhorTempo){
          melhorTempo=dados[jogador][jogo][0];
        }
        if(dados[jogador][jogo][1]<melhorPerformance){
          melhorPerformance=dados[jogador][jogo][1];
        }
      }
      printf("\nDados do jogador %d, %s\n",jogador+1, nome_jogadores[jogador]);
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
