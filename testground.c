//NAO MEXAS EM NADA DO QUE ESTA AQUI FEITO PLZ

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct{
  int hora;
  char descricao[10];
} eventos;

int main () {
  char input[1000];
  scanf("%s\n", input);
  printf("%s\n", input);
  char str[]="a festaEputas:1000";
  int i=0;
  char parsed[9][64]={"\0"};
  //eventos sala[10][100];
  char* token = strtok(str, " ");
  token = strtok(NULL, ":");
  while (token != NULL) {
    strcpy(parsed[i],token);
    token = strtok(NULL, ":");
    i++;
  }
  printf("%s\n", parsed[1]);

}
