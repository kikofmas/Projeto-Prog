/*TRANSICAO*/



void resultados(int num_jogadores, int num_jogos, dados **ptr_dados, int dado_principal, int dado_desempate, char frase[], char **nome); //apresenta as estatisticas


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
