#ifndef sort_included
#define sort_included

//Escolhe o tipo de ordenacao fast/short dependendo do input do user
void sort_registry(game_reg **registo_jogo, int pos, char const *argv[]);

//Ordena o registo de jogo do menor tempo para o maior e agrupa os jogos por classes
game_reg *recursive_bubble_sort_fast(game_reg *top, game_reg *limit);

//Ordena o registo de jogo do menor numero de jogadas para o maior e agrupa os jogos por classes
game_reg *recursive_bubble_sort_short(game_reg *top, game_reg *limit);

//Troca a posicao de dois elementos consecutivos
void reord_2_elements(game_reg *ptr);

//Cria/guarda na lista do registo de jogo os dados do jogo a decorrer
void save_game_ini(game_reg **registo_jogo, hist_data *last_game, char **nome_jogadores, defs defs_jogo, int jogador);

//Guarda na lista do registo de jogo a chave de jogo (no caso de ser descoberta)
void save_key(int k, game_reg *registo_jogo, char jogada[], time_t tempo_jogo, defs def);

//Cria/guarda na lista de tentativas as tentativas do utilizador
void save_guess_ini(game_reg *top, int lugar_certo, int lugar_errado, int tentativa, char jogada[]);

#endif