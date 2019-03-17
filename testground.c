//testground: code and test functions before inserting them in main project file
#include <stdio.h>
#include <stdlib.h>


int main (){

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

//fução para comparar os resultados e calcular o vencedor em cada categoria
z=0;//guarda o numero do jogador vencedor atual
y=0;//guarda o jogo em que o parametro foi o melhor
x=301;//guarda o valor do parametro
for (int i = 0; i < jog; i++) {
  for (size_t u = 0; u < games; u++) {
    if (stats[i][u][2]==1) {//verifica se o jogo foi acabado
      if (stats[i][u][0]<x) {//compara com o tempo mais baixo atual
        z=i;
        x=stats[i][u][0];
        y=u;
      } else if (stats[i][u][0]==x) {//em caso de empate compara-se o numero de jogadas
        if (stats[i][u][1]<stats[z][y][1]) {
          x=stats[i][u][0];
          y=u;
          z=i;
        }
      }
    }
  }
}
printf("O vencedor para o jogo mais rapido é: o jogador %d, %s", z+1, name[z]);



//fução para comparar os resultados e apresentar quem teve o jogo mais curto
  z=0;
  y=0;
  x=301;
  for (int i = 0; i < jog; i++) {
    for (size_t u = 0; u < games; u++) {
      if (stats[i][u][2]==1) {//verifica se o jogo foi acabado
        if (stats[i][u][1]<x) {//compara com o numero de jogadas mais baixo atual
          z=i;
          x=stats[i][u][1];
          y=u;
        } else if (stats[i][u][1]==x) {//em caso de empate compara-se o tempo de jogo
          if (stats[i][u][0]<stats[z][y][0]) {
            x=stats[i][u][1];
            y=u;
            z=i;
          }
        }
      }
    }
  }
  printf("O vencedor para o jogo mais curto é: o jogador %d, %s", z+1, name[z]);
    return(0);
}
