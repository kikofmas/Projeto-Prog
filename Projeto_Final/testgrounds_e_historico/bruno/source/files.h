#ifndef files_included
#define files_included

//Le o ficheiro de inicializacao e guarda os dados numa estrutura
void read_init (char const * file, defs *ptr, char ***nome);

//Encontra os valores mais elevados do ID de jogador e ID de jogo
void hist_max_values (char const *argv[], int arg_num, hist_data *last_game, char *file);

//Le o ficheiro de historico e cria a lista que contem o registo de jogo
void read_hist (char const *argv[], int arg_num, game_reg **registo_jogo, char *file, int mode);

//Escreve os dados de jogo no ficheiro de historico
void write_file_raw (tentativas *lista_tentativas, char const *argv[], char *file, int mode, hist_data *last_game, char **nome, int tent, double tempo, defs defs_jogo, int win);

//Escreve os dados de jogo no ficheiro de historico
void write_file (game_reg *reg, char const *argv[], char *file, int mode);

#endif
