/*TRANSICAO*/



void comparaChave(int tamanho_chave, char jogada[8], char copia_chave[8], int *lugar_certo, int *lugar_errado); //comparacao com a chave de jogo
int userAttempt(int dados[4][5][3], char ultima_cor, char jogada[8], int tamanho_chave, time_t tempo_inicial,
                time_t *tempo_jogo, time_t *tempo_restante, int duracao_jogo, int num_cores, int jogador, int jogo); //tentativa do jogador
void jogo(int num_jogadores, int num_jogos, int num_cores, int tamanho_chave, int duracao_jogo,
          int tentativas, char repeticao_cores, char nome_jogadores[4][21], int dados[4][5][3]);  //funcao que permite jogar
void criaDados(int num_jogadores, int num_jogos, int dados[4][5][3], float mediaTempos[4], int numVitorias[4]); //criacao da media de tempo de jogo de cada jogador
void vencedor(float mediaTempos[4], char nome[4][21], int num_jogadores, int numVitorias[4]); //definicao do vencedor do jogo
void resultados(int num_jogadores, int num_jogos, int dados[4][5][3], int dado_principal, int dado_desempate, char frase[15], char nome[4][21]); //apresenta as estatisticas
void showData(int dados[4][5][3], float mediaTempos[4], int num_jogadores, int numVitorias[4], int num_jogos, char nome_jogadores[4][21]);  //apresenta dados extra de jogo

/***************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************
***************************************************************************************************************************************************************************/
