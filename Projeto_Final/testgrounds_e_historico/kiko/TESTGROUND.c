/****************************
*       testground KIKO    *
****************************/


void free_game_registry(tentativas *current);


void free_game_registry(tentativas *current){
  if (current->next != NULL) {
    free_guess_registry(current->next);
  }
  free_guess_list(current->first);
  free(current->key);
  free(current->player_name);
  free(current);
}
