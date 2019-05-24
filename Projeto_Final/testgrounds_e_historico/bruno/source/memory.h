#ifndef memory_included
#define memory_included

//Funcao recursiva que faz free da memoria alocada para guardar o registo de jogo
void free_game_registry (game_reg *reg);

//Funcao recursiva que faz free da memoria alocada para guardar as tentativas, dentro do registo de jogo
void free_guess_list (tentativas *current);

//Faz free da memoria alocada pelo projeto intermedio
void clear_memory (char **nome, int num_jogadores, dados **ptr_dados, float *tempo, int *vitorias, game_reg *registo_jogo);

//fFaz free a toda a memoria alocada pelo algoritmo que descobre a chave
void clear_keyFinder (int size, tentativas **lista_tentativas, letras ***lista_cores);

#endif
