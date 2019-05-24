#include <stdlib.h>
#include <stdio.h>

#include "estruturas.h"
#include "memory.h"

/******************************************************************************
* Nome da funcao: free_game_registry()
*
* Argumentos: *reg - ponteiro para uma estrutura da lista do registo de jogo
*
* Return: none
*
* Side-effects: none
*
* Descricao: funcao recursiva que faz free da memoria alocada para guardar
*            o registo de jogo
*
******************************************************************************/
void free_game_registry (game_reg *reg) {
  if (reg->next != NULL) {
    free_game_registry(reg->next);
  }
  free_guess_list(reg->first);
  free(reg->key);
  free(reg->player_name);
  free(reg);
}


/******************************************************************************
* Nome da funcao: free_guess_list()
*
* Argumentos: *current - ponteiro para uma estrutura da lista de tentativas
*
* Return: none
*
* Side-effects: none
*
* Descricao: funcao recursiva que faz free da memoria alocada para guardar
*            as tentativas, dentro do registo de jogo
*
******************************************************************************/
void free_guess_list (tentativas *current) {
  if (current->next != NULL) {
    free_guess_list(current->next);
  }
  free(current->tentativa);
  free(current);
}


/******************************************************************************
* Nome da funcao: clear_memory()
*
* Argumentos: **nome - ponteiro para o nome dos jogadores
*             num_jogadores - numero de jogadores
*             **ptr_dados - ponteiro com os dados de jogo dos jogadores
*             *tempo - ponteiro para os tempos de cada jogador
*             *vitorias - ponteiro para as vitorias de cada jogador
*             *registo_jogo - ponteiro para a lista com o registo de jogo
*
* Return: none
*
* Side-effects: none
*
* Descricao: faz free da memoria alocada pelo projeto intermedio
*
******************************************************************************/
void clear_memory (char **nome, int num_jogadores, dados **ptr_dados, float *tempo, int *vitorias, game_reg *registo_jogo) {
  for (int i = 0; i < num_jogadores; i++) {
    free(nome[i]);
  }
  free(nome);
  for (int i = 0; i < num_jogadores; i++) {
    free(ptr_dados[i]);
  }
  free(ptr_dados);
  free(tempo);
  free(vitorias);
  free_game_registry(registo_jogo);
}


/******************************************************************************
* Nome da funcao: clear_keyFinder()
*
* Argumentos: size - tamanho da chave de jogo
*             ***lista_cores - array de listas com as cores para cada posicao
*             **lista_tentativas - lista que guarda as tentativas efetuadas pelo computador
*
* Return: none
*
* Side-effects: none
*
* Descricao: funcao para dar free a toda a memoria alocada pelo algoritmo
*            que descobre a chave
*
******************************************************************************/
void clear_keyFinder (int size, tentativas **lista_tentativas, letras ***lista_cores) {
  tentativas *aux_tenta = NULL;
  letras *aux_letras = NULL;

  for(int i = 0; i < size; i++) {
    while ((*lista_cores)[i] != NULL) {
      aux_letras = (*lista_cores)[i];
      (*lista_cores)[i] = (*lista_cores)[i]->next;
      free(aux_letras);
    }
  }

  while (*lista_tentativas != NULL) {
    aux_tenta = (*lista_tentativas);
    (*lista_tentativas) = (*lista_tentativas)->next;
    free(aux_tenta->tentativa);
    free(aux_tenta);
  }

  free(*lista_cores);
  free(*lista_tentativas);
}
