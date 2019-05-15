#ifndef estruturas_included
#define estruturas_included


//DECLARACAO DE ESTRUTURAS
typedef struct {
  int tempo;
  int tentativas;
  int vitoria;
}dados;

typedef struct {
  char repeticao_cores;
  int num_jogadores, duracao_jogo, num_jogos, num_cores, tamanho_chave, tentativas, tentativas_alea;
} defs;

typedef struct{
  int init;
  int hist;
  int ord;
}flags; //flags guardam o numero do argumento, iguais a 0 se não estiverem presentes

typedef struct guess_t {
  int guess_ID;
  char *guess;
  char result[5];
  struct guess_t *next;
  struct guess_t *prev;
}guess_list;

typedef struct game_registry {
  int game_ID;
  char player_ID[5];
  char *player_name;
  int colors;
  int key_size;
  char repet;
  char *key;
  int tentativas;
  float game_time;
  struct game_registry *next;
  struct game_registry *prev;
  guess_list *first;
}game_reg;

typedef struct {
  int ID;
  char player_ID[5];
  game_reg *last;
}hist_data;


#endif
