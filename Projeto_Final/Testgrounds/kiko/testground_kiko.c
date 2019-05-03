/****************************
*       testground KIKO    *
****************************/

#include <stdlib.h>
#include <errno.h>    //library de error handling
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions
#include <unistd.h>   //permite usar a funcao sleep
#include <termios.h>  //permite usar a funcao tcflush



//flags guardam o numero do argumento, iguais a 0 se não estiverem presentes
int test_mode_check(int k, char const *argv[], int *flag_init, int *flag_ord, int *flag_hist);


int main(int argc, char const *argv[]) {
  int flag_init = 0, flag_ord = 0, flag_hist = 0, func_valid = 0;
  switch (argc) {
    case 1:
      printf("MODO INTERATIVO\n");
      break;
    case 3:
      func_valid = test_mode_check(3, argv, &flag_init, &flag_ord, &flag_hist);
      break;
    case 5:
      func_valid = test_mode_check(5, argv, &flag_init, &flag_ord, &flag_hist);
      break;
    case 7:
      func_valid = test_mode_check(7, argv, &flag_init, &flag_ord, &flag_hist);
      break;
    default:
      printf("ERRO: Numero de argumentos inválido\n");
  }

  if (func_valid == -1) exit(-1);
  return 0;
}



int test_mode_check(int k, char const *argv[], int *flag_init, int *flag_ord, int *flag_hist) {
  char ini[] = "-i", hist[] = "-h", ord[] = "-o";
  printf("MODO TESTE\n");
  for (int i = 1; i < k; i += 2) {
    if (strcmp(ini, argv[i]) == 0) {
      *flag_init = i+1;
    } else if (strcmp(hist, argv[i]) == 0) {
      *flag_hist = i+1;
    } else if (strcmp(ord, argv[i]) == 0) {
      *flag_ord = i+1;
    } else {
      printf("ERRO: Argumentos incorretos ou não identificados\n");
      exit(-1);
    }
  }
  return 0;
}
