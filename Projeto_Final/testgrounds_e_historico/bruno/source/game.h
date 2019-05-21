#ifndef game_included
#define game_included

int mode_check(int argc, char const *argv[], flags *cmd_flag);
int test_mode_config(int k, char const *argv[], flags **cmd_flag);

void modo_ordenacao(char const *argv[], flags cmd_flag, char *file);
void modo_auto(char const *argv[], flags cmd_flag, char *file);
void modo_inter_pc(char const *argv[], flags cmd_flag, char *file);

#endif