#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef unsigned packed_t;

int string2num (char *s, int base) {
  int a = 0;
  for (; *s; s++) {
    if(isdigit(*s))
      a = a*base + (*s - '0');
    else if((*s >= 'A') && (*s < (base-10+'A')))
      a = a*base + ((*s - 'A') + 10);
    else if((*s >= 'a') && (*s < (base-10+'a')))
      a = a*base + ((*s - 'a') + 10);
    else {
      printf("pane: numero invalido! \n");
      exit(1);
    }
  }
  return a;
}

int xbyte (packed_t word, int bytenum) {
  int teste;
  //separar a partir da seleção da casa e retornar o numero
  // 01abcd02 0  - retornar 02
  // 0 - 0 ate 7 bits (1111)
  // 1 - 8 ate 15 bits (1111 0000)
  // 2 - 16 ate 23 bits (1111 0000 0000)
  // 3 - 24 ate 31 bits (1111 0000 0000 0000)
  if(bytenum == 3){
    // deve pegar os primeiros (mais significativos) 8 bits e deslocar 24bits para direita
   teste =( word >> 24);
  }
  else if(bytenum == 2){
    teste=(word >> 16);
  }
  else if(bytenum == 1){
    teste = (word >>8);
  }
  else{
    teste = word; // onde retorna os bytes menos significativos
  }
  teste = (teste <<24) >>24; // desloca os bits para a esquerda e com o bit mais significativo ele é deslocado para a direita  
  return teste;
}

int main (int argc, char **argv) {
  int x;
  if (argc != 3) {
    printf ("uso: %s <word (em hexadecimal)> <bytenum>\n", argv[0]);
    exit(1);
  }

  x = xbyte(string2num(argv[1], 16), atoi(argv[2]));
  printf ("%08x  %d\n", x, x);
  return 0;
}