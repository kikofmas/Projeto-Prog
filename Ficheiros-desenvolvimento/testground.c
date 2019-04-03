/******************************************************************************
* Nome da funcao: countdown()
*
* Argumentos: none
*
* Return: none
*
* Side-effects: imprime os numeros 5 a 1 com 1 segundo de intrvalo
*
* Descricao: funcao para iniciar uma contagem decrescente
*
******************************************************************************/
void countdown(void){
  char aux[1024], v;
  printf("5\n");
  sleep(1);
  printf("4\n");
  sleep(1);
  printf("3\n");
  sleep(1);
  printf("2\n");
  sleep(1);
  printf("1\n");
  sleep(1);
  clearScreen(0);
}
