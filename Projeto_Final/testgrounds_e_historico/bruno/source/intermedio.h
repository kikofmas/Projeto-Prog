#ifndef intermedio_included
#define intermedio_included

//Introducao ao jogo
void introducao (void);

//Limpa o input indesejado
void cleanslate (void);

//Apaga o ecra
void clearScreen (int k);

//Inicia uma contagem decrescente
void countdown (int i, char **nome);

//Inicializacao das variaveis tipo int
void initialization (int *var, int min, int max, char frase[30]);

//Introducao dos nomes dos jogadores
char **initializationNames (int num_jogadores);

//Escolha da existencia repticao de cores
void initializationRepetitions (char *repeticao_cores);

//Confirma os parametros da chave de jogo
int checkCombinacao (defs *def);

//Valida que a jogada é possivel
int checkInput (char *jogada, int tamanho_chave, int num_cores);

//Criacao da chave de jogo e retorna a ultima cor em jogo
char createKey (char chave[8], char repeticao_cores, int tamanho_chave, int num_cores);

//Comparacao com a chave de jogo
void comparaChave (int tamanho_chave, char jogada[8], char copia_chave[8], int *lugar_certo, int *lugar_errado);

//Tentativa do jogador
int userAttempt (dados **ptr_dados, char ultima_cor, char *jogada, int tamanho_chave, time_t tempo_inicial,
                time_t *tempo_jogo, time_t *tempo_restante, int duracao_jogo, int num_cores, int jogador, int jogo);

//Funcao que permite jogar
dados **jogo (defs def, char **nome_jogadores, game_reg **registo_jogo, hist_data *last_game, char *file);

//Criacao da media de tempo de jogo de cada jogador
void criaDados (int num_jogadores, int num_jogos, dados **ptr_dados, float **mediaTempos, int **numVitorias);

//Definicao do vencedor do jogo
void vencedor (float *mediaTempos, char **nome, int num_jogadores, int *numVitorias);

//Apresenta as estatisticas
void resultados (int num_jogadores, int num_jogos, dados **ptr_dados, int dado_principal, char frase[], char **nome);

//Apresenta dados extra de jogo
void showData (dados **ptr_dados, float *mediaTempos, int num_jogadores, int *numVitorias, int num_jogos, char **nome_jogadores);

#endif
