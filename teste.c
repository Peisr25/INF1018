#include <stdio.h>
void dump (void *p, int n) {
  unsigned char *p1 = (unsigned char *) p;
    while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}
struct S {
  short cs;
  int ci;
} s = {0x55aa, -2050};
struct S1 {
  struct S *ps;
  long cl1;
  short cs1;
} s1;

int main (void) {
  s1.ps = &s;
  s1.cl1 = (long) s.ci;
  s1.cs1 = (s.cs >> 8) & 3;
  dump (&s1, sizeof(s1));
  printf("%d\n",sizeof(struct S1));
  printf("sizeof(short) = %d\n", (int)sizeof(short));
  printf("sizeof(int) = %d\n", (int)sizeof(int));
  printf("sizeof(long) = %d\n", (int)sizeof(long));
  printf("sizeof(float) = %d\n", (int)sizeof(float));
  printf("sizeof(double) = %d\n", (int)sizeof(double));
  printf("sizeof(long double) = %d\n", (int)sizeof(long double));
  return 0;
}