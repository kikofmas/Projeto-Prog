/****************************
       testground BRUNO
****************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions
#include <unistd.h>   //permite usar a funcao sleep
#include <termios.h>  //permite usar a funcao tcflush
//#include "oraculo.h"

typedef struct {
  char repeticao_cores;
  int num_jogadores, duracao_jogo, num_jogos, num_cores, tamanho_chave, tentativas_alea, tentativas;
} defs;

int main(int argc, char const *argv[]) {
  FILE *fptr = fopen(argv[2],"rb");
  if(fptr!=NULL){
    defs defs_jogo={'\0',0,0,0,0,0,0};
    char *nome_jogadores=NULL;
    char c;
    char *text = (char *)malloc(sizeof(char));
    int counter=1;
    while((c=fgetc(fptr))!=EOF){
      text = (char *)realloc(text,counter);
      text[counter-1]=c;
      counter++;
    }
    fclose(fptr);
    char *token;
    token = strtok(text,"\n");
    nome_jogadores = (char *)malloc((strlen(token)+1)*sizeof(char));
    strcpy(nome_jogadores,token);
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

    printf("%s\n", nome_jogadores);
    printf("%d\n", defs_jogo.num_jogos);
    printf("%d\n", defs_jogo.num_cores);
    printf("%d\n", defs_jogo.tamanho_chave);
    printf("%c\n", defs_jogo.repeticao_cores);
    printf("%d\n", defs_jogo.tentativas_alea);
    printf("%d\n", defs_jogo.tentativas);

  }
  else{
    perror("Erro");
    exit(-1);
  }




  return 0;
}
