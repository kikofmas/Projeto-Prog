#ifndef files_included
#define files_included

void read_init(char const * file, defs *ptr, char ***nome);
void hist_max_values(char const *argv[], int arg_num, hist_data *last_game, char *file);
void read_hist(char const *argv[], int arg_num, game_reg **registo_jogo, char *file, int mode);
void sort_registry(game_reg **registo_jogo, int pos, char const *argv[]);
game_reg *recursive_bubble_sort_fast(game_reg *top, game_reg *limit);
game_reg *recursive_bubble_sort_short(game_reg *top, game_reg *limit);
void reord_2_elements(game_reg *ptr);
void write_file_unord(tentativas *lista_tentativas, char const *argv[], char *file, int mode, hist_data *last_game, char **nome, int tent, int tempo, defs defs_jogo);
void write_file_ord(game_reg *reg, char const *argv[], char *file, int mode);

#endif
