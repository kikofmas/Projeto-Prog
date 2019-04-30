#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oraculo.h"

int main(int argc, char ** argv)
{
  reply * r;
  char attempt[100];
  char try1[100], try2[100];
  int size, colors, repeat, visible;

  printf("Tester_message: Please provide size, colors and repeat option (0/1)\n");
  if (scanf("%d %d %d", &size, &colors, &repeat) != 3) {
    printf("Tester_message: No 3 integers provided. Exiting...\n");
    exit(0);
  }

  activate_oracle(size,colors,repeat);
  printf("Tester_message: Indicate if you want the key to be displayed (0 if not)\n");
  if (scanf("%d", &visible)!=1) {
    printf("Tester_message: No integer provided. Exiting...\n");
    exit(0);
  }
  generate_key(visible);
  while(1) {
    printf("Tester_message: Please provide the first key (-1 when you want to stop)\n");
    if (scanf("%s", try1) == 1 && strlen(try1) <= size) {
      if (strcmp(try1, "-1") == 0)
	break;
    }
    printf("Tester_message: Please provide the second key (-1 when you want to stop)\n");
    if (scanf("%s", try2) == 1 && strlen(try2) <= size) {
      if (strcmp(try2, "-1") == 0)
	break;
    }
    r = compare_keys(try1, try2);
    if (r!=NULL)
      printf("Tester_message: You got %d blacks and %d whites.\n", get_blacks(r), get_whites(r));
    else
      printf("Tester message: One of the keys does not follow constraints (wrong size, wrong colors, etc.).\n");
  }
  printf("Tester message: Entering the guessing of the secret key...\n");
  while(1) {
    printf("Tester_message: Please provide a guess (-1 when you want to stop)\n");
    if (scanf("%s", attempt) == 1 && strlen(attempt) <= size) {
      if (strcmp(attempt, "-1") == 0)
	break;
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
