#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oraculo.h"

int main(int argc, char ** argv)
{
  reply * r;
  char *attempt;
  int size, colors, repeat, visible;

  printf("Tester_message: Please provide size, colors and repeat option (0/1)\n");
  if (scanf("%d %d %d", &size, &colors, &repeat) != 3) {
    printf("Tester_message: No 3 integers provided. Exiting...\n");
    exit(0);
  }
  attempt = (char *) malloc((size+1)*sizeof(char));
  activate_oracle(size,colors,repeat);
  printf("Tester_message: Indicate if you want the key to be displayed (0 if not)\n");
  if (scanf("%d", &visible)!=1) {
    printf("Tester_message: No integer provided. Exiting...\n");
    exit(0);
  }
  generate_key(visible);
  while(1) {
    printf("Tester_message: Please provide a guess (-1 when you want to stop)\n");
    if (scanf("%s", attempt) == 1 && strlen(attempt) <= size) {
      if (attempt[0]=='-')
	exit(0);
      r = validate_key(attempt);
      if (r != NULL)
	printf("Tester_message: You got %d blacks and %d whites.\n", get_blacks(r), get_whites(r));
      else
	printf("Tester_message: Key provided contains invalid colors.\n");
    }
    else
      printf("Tester_message: Attempt does not have specified size.\n");
  }
  terminate_oracle();
}
