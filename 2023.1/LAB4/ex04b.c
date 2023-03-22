/* programa 2*/
#include <stdio.h>

int main (void) {
  unsigned int x = 0xffffffff;
  unsigned int y = 2;
  printf("x=%u, y=%u\n", x, y);
  printf("x é menor do que y? %s\n", (x<y)?"sim":"nao");
  return 0;
}

//a representação interna dos numeros muda ou seja 4294967295 é maior do que 2.
