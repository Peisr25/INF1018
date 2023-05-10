/*int foo (int a[], int tam) {
  int i;
  int b[tam];
  for (i = 0; i<tam; i++)
    b[i] = calcula (&(a[i]), tam-i);
  return calcula (b, tam);
}*/

.text
.globl foo

foo:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    