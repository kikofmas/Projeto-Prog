#ifndef key_included
#define key_included

letras ** listaCores(int size, int colors);
tentativas * tentativasAlea(defs def, int *count, letras ***lista_cores, int *win, int *tempo_exec, int modo_jogo);
void fillAlea(tentativas *ptr, int size, int colors, int *count, tentativas *prev, int modo_jogo);
int verificaResultAlea(tentativas *ptr, letras ***lista_cores, int size);
int keyFinder(int size, letras ***lista_cores, tentativas **lista_tentativas, int *count,  int *tempo_exec, int modo_jogo);
void fillLogic(int size, int *count, char *tentativa, tentativas **ptr, tentativas *prev, int modo_jogo);
int verificaResultLogic(tentativas *ptr, char *tentativa, letras ***lista_cores, int size, letras ***index);
void reset(letras ***index, letras **lista_cores, int size);
void clear(int size, tentativas **lista_tentativas, letras ***lista_cores);

#endif