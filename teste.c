#include <stdio.h>
void dump (void *p, int n) {
  unsigned char *p1 = (unsigned char *) p;
    while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}
struct prof {
  short nivel;
  int grau;
  char *cursos;
  char ano;
};
int main (void) {
  struct prof univ[2];
  char nomes[] = {'c', 'e'};
  univ[0].nivel = 12 << 3;
  univ[0].grau = -3;
  univ[0].cursos = &nomes[1];
  univ[0].ano = 'd';
  dump(univ, sizeof(struct prof));
  printf("sizeof(short) = %d\n", (int)sizeof(short));
  printf("sizeof(int) = %d\n", (int)sizeof(int));
  printf("sizeof(long) = %d\n", (int)sizeof(long));
  printf("sizeof(float) = %d\n", (int)sizeof(float));
  printf("sizeof(double) = %d\n", (int)sizeof(double));
  printf("sizeof(long double) = %d\n", (int)sizeof(long double));
  return 0;
}