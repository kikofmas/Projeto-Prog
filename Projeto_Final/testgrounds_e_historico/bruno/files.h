#ifndef files_included
#define files_included

void read_init(char const * file, defs *ptr, char ***nome);
void hist_max_values(char const *argv[], int arg_num, hist_data *last_game, char *file, int mode);
void read_hist(char const *argv[], int arg_num, game_reg **registo_jogo);

#endif
