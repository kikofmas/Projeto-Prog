/****************************
*       testground KIKO    *
****************************/


void free_game_registry(game_reg **reg);


void free_game_registry(tentativas *current){
  if (current->next != NULL) {
    free_guess_list(current->next);
  }
  free(current);
}
