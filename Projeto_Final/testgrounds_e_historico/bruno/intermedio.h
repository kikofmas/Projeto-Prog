#ifndef intermedio_included
#define intermedio_included

void introducao(void); //introducao ao jogo
void cleanslate(void); //limpa o input indesejado
void clearScreen(int k); //elimina o ecra
void countdown(int i, char **nome); //inicia uma contagem decrescente
void initialization(int *var, int min, int max, char frase[30]); //inicializacao das variaveis tipo int
char **initializationNames(int num_jogadores); //introducao dos nomes dos jogadores
void initializationRepetitions(char *repeticao_cores); //escolha da existencia repticao de cores
int checkCombinacao(defs *def); //confirma os parametros da chave de jogo
int checkInput(char *jogada, int tamanho_chave, int num_cores); //valida que a jogada é possivel
char createKey(char chave[8], char repeticao_cores, int tamanho_chave, int num_cores); //criacao da chave de jogo e retorna a ultima cor em jogo
void comparaChave(int tamanho_chave, char jogada[8], char copia_chave[8], int *lugar_certo, int *lugar_errado); //comparacao com a chave de jogo
int userAttempt(dados **ptr_dados, char ultima_cor, char *jogada, int tamanho_chave, time_t tempo_inicial,
                time_t *tempo_jogo, time_t *tempo_restante, int duracao_jogo, int num_cores, int jogador, int jogo); //tentativa do jogador
dados **jogo(defs def, char **nome_jogadores);  //funcao que permite jogar
void criaDados(int num_jogadores, int num_jogos, dados **ptr_dados, float **mediaTempos, int **numVitorias); //criacao da media de tempo de jogo de cada jogador
void vencedor(float *mediaTempos, char **nome, int num_jogadores, int *numVitorias); //definicao do vencedor do jogo
void resultados(int num_jogadores, int num_jogos, dados **ptr_dados, int dado_principal, char frase[], char **nome); //apresenta as estatisticas
void showData(dados **ptr_dados, float *mediaTempos, int num_jogadores, int *numVitorias, int num_jogos, char **nome_jogadores);  //apresenta dados extra de jogo



void clear_memory(char **vect1, int v1, dados **ptr_dados, float *vect3, int *vect4);

#endif
