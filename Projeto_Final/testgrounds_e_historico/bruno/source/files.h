#ifndef files_included
#define files_included

void read_init(char const * file, defs *ptr, char ***nome);
void hist_max_values(char const *argv[], int arg_num, hist_data *last_game, char *file);
void read_hist(char const *argv[], int arg_num, game_reg **registo_jogo, char *file, int mode);
void write_file_raw(tentativas *lista_tentativas, char const *argv[], char *file, int mode, hist_data *last_game, char **nome, int tent, int tempo, defs defs_jogo, int win);
void write_file(game_reg *reg, char const *argv[], char *file, int mode);

#endif
