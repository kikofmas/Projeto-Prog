#ifndef key_included
#define key_included

//Cria uma lista das cores possiveis para cada posicao da chave
letras ** listaCores (int size, int colors);

//Cria uma lista com as tentativas aleatorias efetuadas
tentativas * tentativasAlea (defs def, int *count, letras ***lista_cores, int *win, double *tempo_exec, int modo_jogo);

//Gera uma tentativa aleatoria, faz a avaliacao da mesma (P_B_) e insere a tentativa na lista
void fillAlea (tentativas *ptr, int size, int colors, int *count, tentativas *prev, int modo_jogo);

//Otimiza o algoritmo eliminando cores da lista de cores (criada na primeira funcao), com base no resultado da avalicao das tentativas
int verificaResultAlea (tentativas *ptr, letras ***lista_cores, int size);

//Percorre as diversas combinacoes, com base na lista de cores, para descobrir a chave de jogo
int keyFinder (defs def, int size, letras ***lista_cores, tentativas **lista_tentativas, int *count, double *tempo_exec, int modo_jogo);

//Faz a avaliacao da tentativa (P_B_) e insere a mesma na lista
void fillLogic (int size, int *count, char *tentativa, tentativas **ptr, tentativas *prev, int modo_jogo);

//Otimiza o algoritmo eliminando cores da lista de cores e avancando a lista index, com base no resultado da avalicao das tentativas
int verificaResultLogic (tentativas *ptr, char *tentativa, letras ***lista_cores, int size, letras ***index);

//Realiza a iteracao pela lista index
void reset (letras ***index, letras **lista_cores, int size);

#endif
