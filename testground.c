#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
  char str[4];
  char oi[10]="oi";

   fgets(str,4,stdin);
   printf("%s\n", str);
   printf("%d\n", strlen(str));
   printf("%d\n", atoi(str));

   return(0);
}
