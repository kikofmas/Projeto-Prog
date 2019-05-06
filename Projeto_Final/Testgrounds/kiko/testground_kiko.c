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


typedef struct{
  int init;
  int hist;
  int ord;
}flags;


//flags guardam o numero do argumento, iguais a 0 se não estiverem presentes
int mode_check(int argc, char const *argv[], flags *cmd_flag);
int test_mode_config(int k, char const *argv[], flags **cmd_flag);


int main(int argc, char const *argv[]) {
  int error=0;
  flags cmd_flag={0, 0, 0};


  error=mode_check(argc, argv, &cmd_flag);
  if (error==-1) exit(-1);

  if (cmd_flag.init==0 && cmd_flag.hist==0 && cmd_flag.ord==0) {
    /* fazer as inicializações */
  } elif(cmd_flag.init==0 && (cmd_flag.hist!=0 || cmd_flag.ord!=0)){
    printf("ERRO: Falta o ficheiro das inicializações\n");
    exit(-1);
  }


  return 0;
}


int mode_check(int argc, char const *argv[], flags *cmd_flag){
  int func_valid=0;
  switch (argc) {
    case 1:
      printf("MODO INTERATIVO\n");
      break;
    case 3:
      func_valid = test_mode_config(3, argv, &cmd_flag);
      break;
    case 5:
      func_valid = test_mode_config(5, argv, &cmd_flag);
      break;
    case 7:
      func_valid = test_mode_config(7, argv, &cmd_flag);
      break;
    default:
      printf("ERRO: Numero de argumentos inválido\n");
  }
  if (func_valid == -1) exit(-1);
  return 0;
}


int test_mode_config(int k, char const *argv[], flags **cmd_flag) {
  char ini[] = "-i", hist[] = "-h", ord[] = "-o";
  printf("MODO TESTE\n");
  for (int i = 1; i < k; i += 2) {
    if (strcmp(ini, argv[i]) == 0) {
      (*cmd_flag)->init = i+1;
    } else if (strcmp(hist, argv[i]) == 0) {
      (*cmd_flag)->hist = i+1;
    } else if (strcmp(ord, argv[i]) == 0) {
      (*cmd_flag)->ord = i+1;
    } else {
      printf("ERRO: Argumentos incorretos ou não identificados\n");
      exit(-1);
    }
  }
  return 0;
}
