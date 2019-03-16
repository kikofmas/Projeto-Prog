//testground: code and test functions before inserting them in main project
#include <stdio.h>
#include <stdlib.h>


int main (){
  int jog=0, tempo=0, games=0; //numero de jogadores, tempo de jogo, numero de jogos
  int stats[jog][games][3];//0=temp, 1=jogadas, 2=conseguiu
  int mediaTempos[jog];
  stats[i][a][0]=tempo_jogo;
  stats[i][a][1]=b;


  stats[i][a][2]=1;
  stats[i][a][2]=0;


  for (int i = 0; i < jog; i++) {
    for (int u = 0; u < games; u++) {
      mediaTempos[i]+=stats[i][u][0];
    }
    mediaTempos[i]/=games;
  }
  int z=0, x=0, y=0;
  for (int i = 0; i < jog; i++) {
    x=0;
    for (int u = 0; u < games; u++) {
      x+=stats[i][u][2];
    }
    if (x>y) {
      z=i;
      y=x;
    } else if (x==y) {
      if (mediaTempos[z]<mediaTempos[i]) {
        z=i;
        y=x;
      }
    }
  }
  printf("O vencedor do torneio é: o jogador %d, %s", z+1, name[z]);
  z=0;
  y=0;
  x=301;
  for (int i = 0; i < jog; i++) {
    for (size_t u = 0; u < games; u++) {
      if (stats[i][u][2]==1) {
        if (stats[i][u][0]<x) {
          z=i;
          x=stats[i][u][0];
          y=u;
        } else if (stats[i][u][0]==x) {
          if (stats[i][u][1]<stats[z][y][1]) {
            x=stats[i][u][0];
            y=u;
            z=i;
          }
        }
      }
    }
  }
  z=0;
  y=0;
  x=301;
  printf("O vencedor para o jogo mais rapido é: o jogador %d, %s", z+1, name[z]);
  for (int i = 0; i < jog; i++) {
    for (size_t u = 0; u < games; u++) {
      if (stats[i][u][2]==1) {
        if (stats[i][u][1]<x) {
          z=i;
          x=stats[i][u][1];
          y=u;
        } else if (stats[i][u][1]==x) {
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
