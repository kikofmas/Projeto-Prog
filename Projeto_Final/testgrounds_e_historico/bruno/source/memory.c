#include <stdlib.h>
#include <stdio.h>

#include "estruturas.h"
#include "memory.h"

void free_game_registry(game_reg *reg){
  if (reg->next != NULL) {
    free_game_registry(reg->next);
  }
  free_guess_list(reg->first);
  free(reg->key);
  free(reg->player_name);
  free(reg);
}

void free_guess_list(tentativas *current){
  if (current->next != NULL) {
    free_guess_list(current->next);
  }
  free(current->tentativa);
  free(current);
}

void clear_memory(char **vect1, int v1, dados **ptr_dados, float *vect3, int *vect4, game_reg *registo_jogo){
  for (int i = 0; i < v1; i++) {
    free(vect1[i]);
  }
  free(vect1);
  for (int i = 0; i < v1; i++) {
    free(ptr_dados[i]);
  }
  free(ptr_dados);
  free(vect3);
  free(vect4);
  free_game_registry(registo_jogo);
}

/******************************************************************************
* Nome da funcao: reset()
*
* Argumentos: size - tamanho da chave de jogo
*             ***lista_cores - array de listas com as cores para cada posicao
*             **lista_tentativas - lista que guarda as tentativas efetuadas pelo computador
*
* Return: 1 - se a tentativa coincidir com a Chave
*         0 - nos restantes casos
*
* Side-effects: none
*
* Descricao: funcao para dar free a toda a memoria alocada pelo algoritmo
*
******************************************************************************/
void clear_keyFinder(int size, tentativas **lista_tentativas, letras ***lista_cores){
  tentativas *aux_tenta;
  letras *aux_letras;

  for(int i=0;i<size;i++){
    while((*lista_cores)[i]!=NULL){
      aux_letras = (*lista_cores)[i];
      (*lista_cores)[i]=(*lista_cores)[i]->next;
      free(aux_letras);
    }
  }

  while (*lista_tentativas!=NULL) {
    aux_tenta=(*lista_tentativas);
    (*lista_tentativas)=(*lista_tentativas)->next;
    free(aux_tenta->tentativa);
    free(aux_tenta);
  }

  free(*lista_cores);
  free(*lista_tentativas);
}