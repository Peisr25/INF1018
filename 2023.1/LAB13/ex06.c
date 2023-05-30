#include <stdio.h>

typedef union
{
  void *p;
  long l;
  unsigned char bytes[8];
} Ender;

typedef int (*funcp)(int x);

int main(void)
{
  int add(int x)
  {
    return x + 1;
  };

  int i, j;
  Ender cod, func;

  unsigned char codigo[] = {0x55, 0x48, 0x89, 0xe5, 0xe9, 0x00, 0x00, 0x00, 0x00,
                            0xc9, 0xc3};

  cod.p = (codigo + 9); // aponta Ender.*p para o end de 0xc9
  func.p = &add; // atribui a func.p o end de add

  func.l -= cod.l; // obtem pela diff entre 0xe8 e 0xc9 (delta)


  for (j = 0; j < 4; j++)
    codigo[5 + j] = func.bytes[j]; // percorre os 4 primeiros bytes de func.bytes e altera no array codigo  

  funcp f = (funcp)codigo; // "chama" codigo com o end de add inserido

  i = (*f)(10);

  printf("%d\n", i);

  return 0;
}
