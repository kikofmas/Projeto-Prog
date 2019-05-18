#ifndef intermedio_included
#define intermedio_included

void introducao(void); //introducao ao jogo
void cleanslate(void); //limpa o input indesejado
void clearScreen(int k); //elimina o ecra
void countdown(int i, char **nome); //inicia uma contagem decrescente
void initialization(int *var, int min, int max, char frase[30]); //inicializacao das variaveis tipo int
char **initializationNames(int num_jogadores); //introducao dos nomes dos jogadores
void initializationRepetitions(char *repeticao_cores); //escolha da existencia repticao de cores
int checkCombinacao(int *num_cores, int *tamanho_chave, char *repeticao_cores); //confirma os parametros da chave de jogo
int checkInput(char *jogada, int tamanho_chave, int num_cores); //valida que a jogada é possivel

#endif
