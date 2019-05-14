/****************************
*       testground KIKO    *
****************************/


int main(int argc, char const *argv[]) {
  int modo_jogo_int = 0;
  printf("Selecione o modo de jogo.\n");
  printf("Pode jogar contra outros jogadore (modo PvP)[modo 1]\n");
  printf("Pode jogar contra computador e ele tenta adivinhar uma chave\ncriada pelo utilizador [modo 2]");
  printf("Qual o modo de jogo que quer jogar?  \n");
  scanf("%d\n", &modo_jogo_int);
  /*
  *   fazer
  *   verificacoes
  */
  if (modo_jogo_int == 1) {
    /*
    *   fazer modo interativo
    *   do projeto intermedio
    */
  } else if (modo_jogo_int == 2) {
    printf("Neste modo o jogador inventa uma chave e o computador vai tentar adivinha-la.\n");
    printf("Primeiro defina a configuracao em que o computador vai jogar.\n");
    printf("Quantas tentativas pode fazer o computador?  ");
    scanf("%d\n", /*tentativas*/);
    printf("Quantas tentativas aliatorias deve gerar o computador?  ");
    scanf("%d\n", /*tentativas aleatorias*/);
    /*
    *   ha mais parametros
    *   para o pc??
    */

    printf("Deseja inserir a chave ?[S/N]  "); //dizer que nao influencia o jogo por esta noutro processo?
    scanf("%c\n", /*inserir chave*/);
    printf("Deseja receber recomendacoes dos numeros para os pinos pretos e brancos?[S/N]  ");
    scanf("%c\n", /*recomendacoes*/);
    /*
    *   fazer
    *   verificacoes
    */


    /*
    *   inserir funcao de tentativas
    *   fazer tentativa
    *   meter num ciclo??
    */

    printf("Quantas cores estao certas no sitio certo (pinos pretos)?  ");
    scanf("%d\n", /*pinos pretos*/);
    printf("Quantas cores estao certas no sitio errado (pinos brancos)?  ");
    scanf("%d\n", /*pinos brancos*/);



  }

  return 0;
}
