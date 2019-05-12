#ifndef test_mode_ord_included
#define test_mode_ord_included


void sort_registry(game_reg **registo_jogo, int pos, char const *argv[]);
game_reg *recursive_bubble_sort_fast(game_reg *current, game_reg *limit);
game_reg *recursive_bubble_sort_short(game_reg *current, game_reg *limit);
void reord_2_elements(game_reg *ptr);


#endif
