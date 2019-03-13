char key[9];
char coresdisp[13]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
for (int i = 0; i < keySize; i++) {
  int aux;
  do{
    aux = rand() % colors;
  } while(coresdisp[aux]=='0');
  key[i]=coresdisp[aux];
  if(repet=='n' || repet=='N'){
    coresdisp[aux]='0';
  }
}

printf("%s\n", key);
