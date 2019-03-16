// C program to demonstrate
// example of time() function.
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main ()
{
    time_t inicial,medio,final;

    inicial = time(NULL);
    sleep(3);
    medio = time(NULL);
    sleep(3);
    medio = time(NULL);
    printf("%d\n", medio-inicial);
    return(0);
}
