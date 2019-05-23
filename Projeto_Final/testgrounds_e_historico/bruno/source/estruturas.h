#ifndef estruturas_included
#define estruturas_included


//estrutura para guardar os melhores dados de jogo para o modo torneio do projeto intermedio
typedef struct {
  int tempo;
  int tentativas;
  int vitoria;
}dados;


//estrutura para criar a lista de cores para o algoritmo que adivinha a chave
typedef struct letras_t {
  char letra;
  struct letras_t *next;
} letras;


//estrutura para criar a lista de tentativas efetuadas durante os jogos
typedef struct tentativas_t {
  int tent_ID;
  char *tentativa;
  char resultado[5];
  int pretas, brancas;
  struct tentativas_t *next, *prev;
} tentativas;


//estrutura para guardar os dados das inicializacoes
typedef struct {
  char repeticao_cores;
  int num_jogadores;
  int duracao_jogo;
  int num_jogos;
  int num_cores;
  int tamanho_chave;
  int tentativas;
  int tentativas_alea;
} defs;


//estrutura para guardar em que posicao do array argv[] os argumentos se encontram
typedef struct {
  int init;
  int hist;
  int ord;
}flags; //flags guardam o numero do argumento, iguais a 0 se não estiverem presentes


//estrutura para criar a lista do registo de jogo
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


//estrutura para guardar os maiores valores no ficheiro de historico
typedef struct {
  int ID;
  int player_ID;
  game_reg *last;
}hist_data;

#endif
