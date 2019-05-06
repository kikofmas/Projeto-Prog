#include <stdlib.h>
#include <errno.h>    //library de error handling
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions
#include <unistd.h>   //permite usar a funcao sleep
#include <termios.h>  //permite usar a funcao tcflush

typedef struct point_t{
  int x;
  int y;
  struct point_t *next2;
}Point;

typedef struct Polygon{
  Point *pts;
  int number_of_points;
  struct Polygon *next;
}Polygon_t;


Point *readPoints(int *_n);
void createPolygon(Point *_lstPoints, Polygon_t *list);
void writePolygons(Polygon_t *list);
void free_memory(Polygon_t *ptr2);
int free_list(Polygon_t *ptr);
int free_list_2(Point *ptr);



int main() {

  int _n=0, m=0;
  Point *ptr1=NULL;
  Polygon_t *list=NULL;
  list=malloc(sizeof(Polygon_t));
  list->next=NULL;
  printf("Quantos poligonos?(m)  \n");
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    printf("Poligono %d\n", i+1);
    ptr1=readPoints(&_n);
    createPolygon(ptr1, list);
  }


  writePolygons(list);
  free_memory(list);
  printf("\n\nDONE\n");
  return 0;
}


Point *readPoints(int *_n){
  Point *ptr=NULL, *ptr2=NULL;
  int a, b;
  printf("Quantos pontos? (_n)?  ");
  scanf("%d", _n);
  ptr=malloc(sizeof(Point));
  ptr2=ptr;
  printf("Qual o x do ponto %d?  ", 1);
  scanf("%d", &a);
  printf("Qual o y do ponto %d?  ", 1);
  scanf("%d", &b);
  (*(ptr)).x=a;
  (*(ptr)).y=b;
  (*(ptr)).next2=NULL;
  for (int i = 1; i < *_n; i++) {
    (*(ptr)).next2=malloc(sizeof(Point));
    ptr=(*(ptr)).next2;
    int x, y;
    printf("Qual o x do ponto %d?  ", i+1);
    scanf("%d", &x);
    printf("Qual o y do ponto %d?  ", i+1);
    scanf("%d", &y);
    (*(ptr)).x=x;
    (*(ptr)).y=y;
    (*(ptr)).next2=NULL;
  }
  return (ptr2);
}


void createPolygon(Point *_lstPoints, Polygon_t *list){
  static int a=1;
  int b=1;

  Point *ptr=_lstPoints;
  Polygon_t *current = list;
  while (current->next != NULL){
    current = current->next;

  }
  while ( ptr->next2 != NULL) {
    ptr=ptr->next2;
    b++;
  }
  if (a) {
    current->pts = _lstPoints;
    current->number_of_points=b;
    current->next = NULL;
    a=0;
  } else {
    current->next = malloc(sizeof(Polygon_t));
    current->next->pts = _lstPoints;
    current->next->number_of_points=b;
    current->next->next = NULL;
  }
}


void writePolygons(Polygon_t *list){

  Polygon_t *current=list;
  int a=1;
  int b=1;


  printf("\n\n");
  printf("Poligono %d ", a);
  printf("tem %d ponto(s): ", current->number_of_points);

  Point *current3=(current->pts);
  printf(" ponto %d [%d,%d] ", b, current3->x, current3->y);
  b++;

  while (current3->next2 != NULL) {
    current3=current3->next2;
    printf(" ponto %d [%d,%d] ", b, current3->x, current3->y);
    b++;
  }

  a++;
  printf("\n");

  while (current->next != NULL) {
    int b=1;
    Point *current2;

    current=current->next;
    printf("Poligono %d ", a);
    printf("tem %d ponto(s): ", current->number_of_points);

    current2=(current->pts);
    printf(" ponto %d [%d,%d] ", b, current2->x, current2->y);
    b++;

    while (current2->next2 != NULL) {
      current2=current2->next2;
      printf(" ponto %d [%d,%d] ", b, current2->x, current2->y);
      b++;
    }
    printf("\n");
    a++;
  }

}


void free_memory(Polygon_t *ptr2){
  int a=30;
  while (a != 0) {
    a=free_list(ptr2);
  }
}


int free_list(Polygon_t *ptr) {
  int a=30;
  if (ptr->next == NULL) {
    while (a != 0) {
      a=free_list_2(ptr->pts);
    }
    free(ptr);
    return 0;
  }


  Polygon_t *current = ptr;

  while (current->next->next != NULL) {
    current = current->next;
  }
  while (a != 0) {
    a=free_list_2(current->next->pts);
  }

  free(current->next);
  current->next = NULL;

  return 1;
}

int free_list_2(Point *ptr){
  if (ptr->next2 == NULL) {
    free(ptr);
    return 0;
  }
  Point *current = ptr;
  while (current->next2->next2 != NULL) {
    current = current->next2;
  }
  free(current->next2);
  current->next2 = NULL;

  return 1;
}
