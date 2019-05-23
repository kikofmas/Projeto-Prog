#ifndef game_included
#define game_included

//Analisa os argumentos passados atraves da linha de comandos e retorna um modo de jogo
int mode_check (int argc, char const *argv[], flags *cmd_flag);

//Guarda a posicao de cada argumento na estrutura cmd_flag
int test_mode_config (int k, char const *argv[], flags **cmd_flag);

//Chama as funcoes para realizar a ordenacao do ficheiro de historico
void modo_ordenacao (char const *argv[], flags cmd_flag, char *file);

//Chama as funcoes que permitem ao computador adivinhar a chave de jogo
void modo_auto (char const *argv[], flags cmd_flag, char *file);

//Chama as funcoes que permitem jogar o modo interativo PESSOA/COMPUTADOR
void modo_inter_pc (char const *argv[], flags cmd_flag, char *file);

//Chama as funcoes que permitem jogar o modo interativo PESSOA/PESSOA
void modo_inter_intermedio (char const *argv[], flags cmd_flag, char *file);

#endif
