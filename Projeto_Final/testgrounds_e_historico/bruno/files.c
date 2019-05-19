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
#include "files.h"

void read_init(char const * file, defs *ptr, char ***nome){
  char *text=NULL, *token=NULL, c='\0';
  int counter=1;
  FILE *fptr = fopen(file,"rb");

  if(fptr!=NULL){
    text = (char *)malloc(sizeof(char));
    while((c=fgetc(fptr))!=EOF){
      text = (char *)realloc(text,counter);
      text[counter-1]=c;
      counter++;
    }
    fclose(fptr);

    token = strtok(text,"\n");
    *nome = (char **)malloc(sizeof(char*));
    if(*nome==NULL) exit(-1);
    **nome = (char *)malloc((strlen(token)+1)*sizeof(char));
    if(**nome==NULL) exit(-1);
    strcpy(**nome,token);
    token = strtok(NULL,"\n");
    ptr->num_jogos = atoi(token);
    token = strtok(NULL,"\n");
    ptr->num_cores = atoi(token);
    token = strtok(NULL,"\n");
    ptr->tamanho_chave = atoi(token);
    token = strtok(NULL,"\n");
    ptr->repeticao_cores = token[0];
    token = strtok(NULL,"\n");
    ptr->tentativas_alea = atoi(token);
    token = strtok(NULL,"\n");
    ptr->tentativas = atoi(token);
    free(text);
  }
  else{
    perror("ERRO:");
    exit(-1);
  }
}


void hist_max_values(char const *argv[], int arg_num, hist_data *last_game){
  int k=0, a=0, b=0, a1=0, b1=0;

  FILE *fptr=fopen(argv[arg_num], "rb");

  while(!feof(fptr)){
    fscanf(fptr, "%d J%d %*s %*s %*s %*s %*s %d %*[^\n]\n", &a, &b, &k);
    for (int i = 0; i < k; i++) {
      fscanf(fptr, "%*[^\n]\n");
    }
    if (a>a1) a1=a;
    if (b>b1) b1=b;
  }
  if (b1>998) b1=0;
  last_game->ID=a1;
  sprintf(last_game->player_ID, "J%03d", b1);
  fclose(fptr);
}
