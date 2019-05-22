#ifndef memory_included
#define memory_included

void free_game_registry(game_reg *reg);
void free_guess_list(tentativas *current);
void clear_memory(char **vect1, int v1, dados **ptr_dados, float *vect3, int *vect4, game_reg *registo_jogo);

#endif