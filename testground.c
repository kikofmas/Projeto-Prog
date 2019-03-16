//testground: code and test functions before inserting them in main project
#include <stdio.h>
#include <stdlib.h>


int main (){
  int jog=0, tempo=0, games=0; //numero de jogadores, tempo de jogo, numero de jogos
  int stats[jog][games][3];//matriz que guarda a informação de todos os jogos de todos os jogadores
                           //0=temp, 1=jogadas, 2=conseguiu
  int mediaTempos[jog];//media do tempo de jogo para cada jogador
  stats[i][a][0]=tempo_jogo;//grava o tempo do jogo atual
  stats[i][a][1]=b;//grava o numero de jogadas efetuadas


  stats[i][a][2]=1;//guarda se o jogador conseguiu completar a partida
  stats[i][a][2]=0;//guarda se o jogador conseguiu completar a partida

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
  printf("O vencedor do torneio é: o jogador %d, %s", z+1, name[z]);



  //fução para comparar os resultados e apresentar quem teve o jogo mais rapido
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
