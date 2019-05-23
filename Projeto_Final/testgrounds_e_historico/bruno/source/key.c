#include <stdlib.h>
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <sys/time.h> //permite fazer a contagem de tempo em milissegundos

#include "oraculo.h"
#include "estruturas.h"
#include "key.h"


/******************************************************************************
* Nome da funcao: listaCores()
*
* Argumentos: size - tamanho da chave de jogos
*             colors - numero de cores em jogo
*
* Return: **lista_cores - pointer para uma array de listas com as cores de cada posicao
*
* Side-effects: se a alocacao nao for bem sucedida força a saida do programa
*
* Descricao: cria uma lista das cores possiveis para cada posicao da chave
*
******************************************************************************/
letras ** listaCores (int size, int colors) {
  letras *aux;
  letras **lista_cores = (letras **) calloc(size, sizeof(letras*));
  if (lista_cores == NULL) exit(-1); //confirma a correta alocacao de memoria
  for (int index = 0; index < size; index++) {
    lista_cores[index] = (letras *) calloc(1, sizeof(letras));
    if (lista_cores[index] == NULL) exit(-1);  //confirma a correta alocacao de memoria
    aux = lista_cores[index];

    aux->letra = 'A';
    aux->next = NULL;

    for (int offset = 1; offset < colors; offset++) {
      aux->next = calloc(1, sizeof(letras));
      if (aux->next == NULL) exit(-1); //confirma a correta alocacao de memoria
      aux->next->letra = 'A'+offset;
      aux->next->next = NULL;
      aux = aux->next;
    }
  }
  return lista_cores;
}


/******************************************************************************
* Nome da funcao: tentativasAlea()
*
* Argumentos: def - estrutura com as configuracoes do jogo
*             *count - variavel que guarda o numero de tentativas efetuadas
*             ***lista_cores - array de listas com as cores para cada posicao
*             *win - variavel que indica se a chave foi acertada
*             *tempo_exec - variavel que guarda o tempo que o algoritmo demora
*             modo_jogo - variavel que inidica o modo de jogo (1-automatico/2-manual)
*
* Return: *lista_tentativas - lista das tentativas aleatorias efetuadas
*
* Side-effects: se a alocacao nao for bem sucedida força a saida do programa
*
* Descricao: cria uma lista com as tentativas aleatorias efetuadas
*
******************************************************************************/
tentativas * tentativasAlea (defs def, int *count, letras ***lista_cores, int *win, int *tempo_exec, int modo_jogo) {
  tentativas *lista_tentativas = NULL, *aux = NULL;
  struct timeval stop, start;
  if (def.tentativas_alea > 0) {
    printf("Tentativas aleatorias:\n");

    lista_tentativas = (tentativas *) calloc(1, sizeof(tentativas));
    if (lista_tentativas == NULL) exit(-1);  //confirma a correta alocacao de memoria
    aux = lista_tentativas;
    gettimeofday(&start, NULL);
    fillAlea(aux, def.tamanho_chave, def.num_cores, count, NULL, modo_jogo);
    printf("%d: %s %s\n", aux->tent_ID, aux->tentativa, aux->resultado);
    if (verificaResultAlea(aux, lista_cores, def.tamanho_chave) == 1) {
      *win = 1;
      gettimeofday(&stop, NULL);
      *tempo_exec = *tempo_exec + stop.tv_usec-start.tv_usec;
      return lista_tentativas;
    }

    for (int i = 1; i < def.tentativas_alea; i++) {
      aux->next = (tentativas *) calloc(1,sizeof(tentativas));
      if (aux->next == NULL) exit(-1); //confirma a correta alocacao de memoria
      fillAlea(aux->next, def.tamanho_chave, def.num_cores, count, aux, modo_jogo);
      printf("%d: %s %s\n", aux->next->tent_ID, aux->next->tentativa, aux->next->resultado);
      if (verificaResultAlea(aux->next, lista_cores, def.tamanho_chave) == 1) {
        *win = 1;
        return lista_tentativas;
        gettimeofday(&stop, NULL);
        *tempo_exec = *tempo_exec + stop.tv_usec-start.tv_usec;
      }
      aux = aux->next;
    }

    printf("\n");
    return lista_tentativas;
    gettimeofday(&stop, NULL);
    *tempo_exec = *tempo_exec + stop.tv_usec-start.tv_usec;
  }
  return NULL;
}


/******************************************************************************
* Nome da funcao: fillAlea()
*
* Argumentos: *ptr - localizao em memoria da estrutura a preencher
*             size - tamanho da chave de jogo
*             colors - numero de cores em jogo
*             *count - variavel que guarda o numero de tentativas efetuadas
*             *prev - localizacao em memoria da estrutura anterior
*             modo_jogo - variavel que inidica o modo de jogo (1-automatico/2-manual)
*
* Return: none
*
* Side-effects: se a alocacao nao for bem sucedida força a saida do programa
*
* Descricao: gera uma tentativa aleatoria, faz a avaliacao da mesma (P_B_) e
*            insere a tentativa na lista
*
******************************************************************************/
void fillAlea (tentativas *ptr, int size, int colors, int *count, tentativas *prev, int modo_jogo) {
  reply *answer = NULL;
  int pretas = 0, brancas = 0;
  ptr->tentativa = (char *) calloc(size+1,sizeof(char));
  if (ptr->tentativa == NULL) exit(-1);  //confirma a correta alocacao de memoria
  for (int a = 0; a < size; a++) {
    ptr->tentativa[a] = 'A'+(rand()%colors);
  }
  (*count)++;
  ptr->tent_ID = *count;
  if (modo_jogo == 1){
    answer = validate_key(ptr->tentativa);
    ptr->pretas = get_blacks(answer);
    ptr->brancas = get_whites(answer);
  } else if (modo_jogo == 2) {
      printf("\n%s\n", ptr->tentativa);
      printf("Pretas: ");
      scanf("%d", &pretas);
      printf("Brancas: ");
      scanf("%d", &brancas);
      printf("\n");
      ptr->pretas = pretas;
      ptr->brancas = brancas;
  }
  sprintf(ptr->resultado,"P%dB%d", ptr->pretas, ptr->brancas);
  ptr->next = NULL;
  ptr->prev = prev;
}


/******************************************************************************
* Nome da funcao: verificaResultAlea()
*
* Argumentos: *ptr - localizao em memoria da estrutura a analisar
*             ***lista_cores - array de listas com as cores para cada posicao
*             size - tamanho da chave de jogo
*
* Return: 1 - se a tentativa coincidir com a Chave
*         0 - nos restantes casos
*
* Side-effects: none
*
* Descricao: funcao que otimiza o algoritmo eliminando cores da lista (lista_cores)
*            com base no resultado da avalicao das tentativas
*
******************************************************************************/
int verificaResultAlea (tentativas *ptr, letras ***lista_cores, int size) {
  letras *color_aux = NULL, *aux_rm = NULL;
  if (ptr->pretas == size) return 1;
  else if (ptr->pretas == 0  &&  ptr->brancas == 0) {
    for (int i = 0; i < size; i++) {
      for (int a = 0; a < size; a++) {
        color_aux = (*lista_cores)[a];
        if (color_aux->letra == ptr->tentativa[i]) {
          (*lista_cores)[a] = (*lista_cores)[a]->next;
          free(color_aux);
        } else{
            while(color_aux->next->letra != ptr->tentativa[i]) {
              color_aux = color_aux->next;
              if(color_aux->next==NULL) break;
            }
            if (color_aux->next != NULL) {
              aux_rm = color_aux->next;
              color_aux->next = color_aux->next->next;
              free(aux_rm);
          }
        }
      }
    }
  }
  else if (ptr->pretas==0) {
    for (int i = 0; i < size; i++) {
      color_aux = (*lista_cores)[i];
      if (color_aux->letra == ptr->tentativa[i]) {
        (*lista_cores)[i] = (*lista_cores)[i]->next;
        free(color_aux);
      } else{
          while (color_aux->next->letra != ptr->tentativa[i]) {
            color_aux = color_aux->next;
            if (color_aux->next == NULL) break;
          }
          if (color_aux->next != NULL) {
          aux_rm = color_aux->next;
          color_aux->next = color_aux->next->next;
          free(aux_rm);
        }
      }
    }
  }
  return 0;
}


/******************************************************************************
* Nome da funcao: keyFinder()
*
* Argumentos: size - tamanho da chave de jogo
*             ***lista_cores - array de listas com as cores para cada posicao
*             **lista_tentativas - lista que guarda as tentativas efetuadas pelo computador
*             *count - variavel que guarda o numero de tentativas efetuadas
*             *tempo_exec - variavel que guarda o tempo que o algoritmo demora
*             modo_jogo - variavel que inidica o modo de jogo (1-automatico/2-manual)
*
* Return: 1 - se a tentativa coincidir com a Chave
*         0 - nos restantes casos
*
* Side-effects: se a alocacao nao for bem sucedida força a saida do programa
*
* Descricao: funcao que percorre as diversas combinacoes para descobrir a chave de jogo
*
******************************************************************************/
int keyFinder (defs def, int size, letras ***lista_cores, tentativas **lista_tentativas, int *count, int *tempo_exec, int modo_jogo) {
  reply *answer;
  int valid = 0, pretas = 0, brancas = 0, tentativa_atual = 0;
  tentativas *aux = NULL;
  struct timeval stop, start;
  letras **index = (letras **) calloc(size,sizeof(letras*));
  if (index == NULL) exit(-1); //confirma a correta alocacao de memoria
  char *tentativa = (char *) calloc(size+1,sizeof(char));
  if (tentativa == NULL) exit(-1); //confirma a correta alocacao de memoria

  printf("Tentativas logicas:\n");

  for (int i = 0; i < size; i++) {
    index[i] = (*lista_cores)[i];
  }


  while (index[0] != NULL  &&  tentativa_atual < def.tentativas-def.tentativas_alea) {
    for (int i = 0; i < size; i++) {
      tentativa[i] = index[i]->letra;
    }
    valid = 0;
    gettimeofday(&start, NULL);


    if (*lista_tentativas == NULL) {

      *lista_tentativas = (tentativas*) calloc(1,sizeof(tentativas));
      if (*lista_tentativas == NULL) exit(-1); //confirma a correta alocacao de memoria

      fillLogic(size, count, tentativa, lista_tentativas, NULL, modo_jogo);

      printf("%d: %s %s\n", *count, tentativa, (*lista_tentativas)->resultado);

      if (verificaResultLogic(*lista_tentativas, tentativa, lista_cores, size, &index) == 1) {
        free(tentativa);
        free(index);
        gettimeofday(&stop, NULL);
        *tempo_exec = *tempo_exec + stop.tv_usec-start.tv_usec;
        return 1;
      }
      tentativa_atual++;
    } else {
        aux = *lista_tentativas;
        while(aux->next != NULL) {
          aux = aux->next;
        }
        while (aux != NULL) {
          answer = compare_keys(aux->tentativa,tentativa);
          pretas = get_blacks(answer);
          brancas = get_whites(answer);
          if (pretas != aux->pretas || brancas != aux->brancas) {
            valid = 0;
            break;
        }
        valid = 1;
        aux=aux->prev;
      }
      if (valid == 1) {
        tentativa_atual++;
        aux = *lista_tentativas;
        while (aux->next != NULL) aux = aux->next;
        aux->next = (tentativas *) calloc(1,sizeof(tentativas));
        if (aux->next == NULL) exit(-1); //confirma a correta alocacao de memoria
        fillLogic(size, count, tentativa, &(aux->next), aux, modo_jogo);
        printf("%d: %s %s\n", *count, tentativa, aux->next->resultado);
        if (verificaResultLogic(aux->next, tentativa, lista_cores, size, &index) == 1) {
          free(tentativa);
          free(index);
          gettimeofday(&stop, NULL);
          *tempo_exec = *tempo_exec + stop.tv_usec-start.tv_usec;
          return 1;
        }
      }
      else index[size-1] = index[size-1]->next;
    }
    reset(&index,*lista_cores,size-1);
  }
  free(tentativa);
  free(index);
  gettimeofday(&stop, NULL);
  *tempo_exec = *tempo_exec + stop.tv_usec-start.tv_usec;
  return 0;
}


/******************************************************************************
* Nome da funcao: fillLogic()
*
* Argumentos: size - tamanho da chave de jogo
*             *count - variavel que guarda o numero de tentativas efetuadas
*             *tentativa - tentativa efetuada pelo computador
*             **ptr - localizao em memoria da estrutura a preencher
*             *prev - localizacao em memoria da estrutura anterior
*             modo_jogo - variavel que inidica o modo de jogo (1-automatico/2-manual)
*
* Return: none
*
* Side-effects: se a alocacao nao for bem sucedida força a saida do programa
*               faz free das variaveis index e tentativas no fim da sua execucao
*
* Descricao: faz a avaliacao da tentativa (P_B_) e insere a mesma na lista
*
******************************************************************************/
void fillLogic (int size, int *count, char *tentativa, tentativas **ptr, tentativas *prev, int modo_jogo) {
  reply *answer = NULL;
  if (modo_jogo == 1) {
    answer = validate_key(tentativa);
    (*ptr)->pretas = get_blacks(answer);
    (*ptr)->brancas  = get_whites(answer);
  } else if (modo_jogo == 2) {
      printf("\n%s\n", tentativa);
      printf("Pretas: ");
      scanf("%d", &((*ptr)->pretas));
      printf("Brancas: ");
      scanf("%d", &((*ptr)->brancas));
      printf("\n");
  }
  sprintf((*ptr)->resultado,"P%dB%d", (*ptr)->pretas, (*ptr)->brancas);
  (*ptr)->tentativa = calloc(size+1,sizeof(char));
  if ((*ptr)->tentativa == NULL) exit(-1); //confirma a correta alocacao de memoria
  strcpy((*ptr)->tentativa,tentativa);
  (*ptr)->next = NULL;
  (*ptr)->prev = prev;
  (*count)++;
  (*ptr)->tent_ID = *count;
}


/******************************************************************************
* Nome da funcao: verificaResultLogic()
*
* Argumentos: *ptr - localizao em memoria da estrutura a analisar
*             *tentativa - tentativa efetuada pelo computador
*             ***lista_cores - array de listas com as cores para cada posicao
*             size - tamanho da chave de jogo
*             ***index - array de listas usado para gerar as tentativas
*
* Return: 1 - se a tentativa coincidir com a Chave
*         0 - nos restantes casos
*
* Side-effects: none
*
* Descricao: funcao que otimiza o algoritmo eliminando cores da lista (index e lista_cores)
*            com base no resultado da avalicao das tentativas
*
******************************************************************************/
int verificaResultLogic (tentativas *ptr, char *tentativa, letras ***lista_cores, int size, letras ***index) {
  letras *color_aux = NULL, *aux_rm = NULL;
  if (ptr->pretas == size) return 1;
  else if (ptr->pretas == 0) {
    (*index)[0] = (*index)[0]->next;
    if (ptr->brancas == 0) {
      for (int i = 1; i < size; i++) {
        if ((*index)[0]->letra == tentativa[i]) {
          (*index)[0] = (*index)[0]->next;
          i = 0;
        }
      }
      for (int i = 0; i < size; i++) {
        for (int a = 0; a < size; a++) {
          color_aux = (*lista_cores)[a];
          if (color_aux->letra == tentativa[i]) {
            (*lista_cores)[a] = (*lista_cores)[a]->next;
            free(color_aux);
          } else {
              while (color_aux->next->letra != tentativa[i]) {
                color_aux = color_aux->next;
                if (color_aux->next == NULL) break;
              }
              if (color_aux->next != NULL) {
                aux_rm = color_aux->next;
                color_aux->next = color_aux->next->next;
                free(aux_rm);
              }
            }
        }
      }
    } else {
      for (int i = 0; i < size; i++) {
        color_aux = (*lista_cores)[i];
        if (color_aux->letra == tentativa[i]) {
          (*lista_cores)[i] = (*lista_cores)[i]->next;
          free(color_aux);
        } else {
            while (color_aux->next->letra != tentativa[i]) {
              color_aux = color_aux->next;
              if (color_aux->next == NULL) break;
            }
            if(color_aux->next!=NULL){
              aux_rm = color_aux->next;
              color_aux->next=color_aux->next->next;
              free(aux_rm);
          }
        }
      }
    }
    for (int i = 1; i < size; i++) (*index)[i] = (*lista_cores)[i];
  } else (*index)[size-1] = (*index)[size-1]->next;
  return 0;
}


/******************************************************************************
* Nome da funcao: reset()
*
* Argumentos: ***index - array de listas usado para gerar as tentativas
*             **lista_cores - array de listas com as cores para cada posicao
*             size - tamanho da chave de jogo
*
* Return: 1 - se a tentativa coincidir com a Chave
*         0 - nos restantes casos
*
* Side-effects: none
*
* Descricao: realiza a iteracao pela lista index
*
******************************************************************************/
void reset (letras ***index, letras **lista_cores, int size) {
  if (size > 0) {
    if ((*index)[size] == NULL) {
      (*index)[size] = lista_cores[size];
      (*index)[size-1] = (*index)[size-1]->next;
      reset(index, lista_cores, size-1);
    }
  }
}
