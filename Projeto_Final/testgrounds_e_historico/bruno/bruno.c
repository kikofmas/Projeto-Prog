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

#include "oraculo.h"
#include "estruturas.h"
#include "key.h"

int main(int argc, char const *argv[]) {
  time_t t;
  srand((unsigned) time(&t));

  int repet=0, num_total_tent=0, win=0;
  letras **lista_cores=NULL;
  tentativas *lista_tentativas=NULL;
  defs defs_jogo={'\0',0,0,0,0,0,0};
  char *nome_jogador=NULL;

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
    nome_jogador = (char *)malloc((strlen(token)+1)*sizeof(char));
    strcpy(nome_jogador,token);
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

    free(text);
  }
  else{
    perror("ERRO:");
    exit(-1);
  }

  if(defs_jogo.repeticao_cores=='S') repet=1;

  activate_oracle(defs_jogo.tamanho_chave, defs_jogo.num_cores, repet);

  for(int i=0;i<defs_jogo.num_jogos;i++){

    printf("\n");
    printf("Chave: ");
    generate_key(1);
    printf("\n");

    lista_cores = listaCores(defs_jogo.tamanho_chave, defs_jogo.num_cores);
    lista_tentativas = tentativasAlea(defs_jogo.tentativas_alea, defs_jogo.tamanho_chave, defs_jogo.num_cores, &num_total_tent, &lista_cores, &win);
    if(win==0){
      win = keyFinder(defs_jogo.tamanho_chave, &lista_cores, &lista_tentativas, &num_total_tent);
    }
    printf("\nNumero de tentativas: %d\n", num_total_tent);
    clear(defs_jogo.tamanho_chave, &lista_tentativas, &lista_cores);
    num_total_tent = 0;

  }

  terminate_oracle();
  free(nome_jogador);
  return 0;
}
