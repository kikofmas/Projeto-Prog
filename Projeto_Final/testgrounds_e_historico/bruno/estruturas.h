#ifndef estruturas_included
#define estruturas_included

typedef struct letras_t{
  char letra;
  struct letras_t *next;
} letras;

typedef struct tentativas_t{
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

#endif
