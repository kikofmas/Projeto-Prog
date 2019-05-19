#ifndef estruturas_included
#define estruturas_included

typedef struct {
  int tempo;
  int tentativas;
  int vitoria;
}dados;

typedef struct letras_t {
  char letra;
  struct letras_t *next;
} letras;

typedef struct tentativas_t {
  int tent_ID;
  char *tentativa;
  char resultado[5];
  int pretas, brancas;
  struct tentativas_t *next, *prev;
} tentativas;

typedef struct {
  char repeticao_cores;
  int num_jogadores, duracao_jogo, num_jogos, num_cores, tamanho_chave, tentativas, tentativas_alea;
} defs;

typedef struct{
  int init;
  int hist;
  int ord;
}flags; //flags guardam o numero do argumento, iguais a 0 se não estiverem presentes

typedef struct game_reg_t {
  int game_ID;
  int colors;
  int key_size;
  int tentativas;
  float game_time;
  char repet;
  char player_ID[5];
  char *key;
  char *player_name;
  struct game_reg_t *next;
  struct game_reg_t *prev;
  tentativas *first;
}game_reg;

typedef struct {
  int ID;
  int player_ID;
  game_reg *last;
}hist_data;

#endif
