
time_t t;
srand((unsigned) time(&t));

char code[9];
char *codeptr=code;
char coresdisp[12]={"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l"};
char *coresdispptr=coresdisp;

for (int i = 0; i < keySize; i++) {
  int aux=0;
  aux=rand() % colors;
  
  *(ptr+i)=*(coresdispptr+aux);
}
