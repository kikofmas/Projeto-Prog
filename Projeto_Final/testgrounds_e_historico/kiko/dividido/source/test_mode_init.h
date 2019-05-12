#ifndef test_mode_init_included
#define test_mode_init_included


void read_hist_file_1(char const *argv[], int arg_num, hist_data *last_game);
void read_hist_file_2(char const *argv[], int arg_num, game_reg **registo_jogo);

int mode_check(int argc, char const *argv[], flags *cmd_flag);
int test_mode_config(int k, char const *argv[], flags **cmd_flag);


#endif
