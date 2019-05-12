#ifndef clear_memory_included
#define clear_memory_included


void clear_memory(char **vect1, int v1, dados **ptr_dados, float *vect3, int *vect4, game_reg *registo_jogo);
void free_guess_list(guess_list *current);
void free_game_registry(game_reg *current);


#endif
