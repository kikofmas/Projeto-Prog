#ifndef files_included
#define files_included

void read_init(char const * file, defs *ptr, char ***nome);
void hist_max_values(char const *argv[], int arg_num, hist_data *last_game, char *file);
void read_hist(char const *argv[], int arg_num, game_reg **registo_jogo, char *file, int mode);
void sort_registry(game_reg **registo_jogo, int pos, char const *argv[]);
game_reg *recursive_bubble_sort_fast(game_reg *top, game_reg *limit);
game_reg *recursive_bubble_sort_short(game_reg *top, game_reg *limit);
void reord_2_elements(game_reg *ptr);


void write_file_raw(tentativas *lista_tentativas, char const *argv[], char *file, int mode, hist_data *last_game, char **nome, int tent, int tempo, defs defs_jogo, int win);
void write_file(game_reg *reg, char const *argv[], char *file, int mode);



void save_game_ini(game_reg **registo_jogo, hist_data *last_game, char **nome_jogadores, defs defs_jogo, int jogador);
void save_key(int k, game_reg *registo_jogo, char jogada[], time_t tempo_jogo, defs def);
void save_guess_ini(game_reg *top, int lugar_certo, int lugar_errado, int tentativa, char jogada[]);

#endif
