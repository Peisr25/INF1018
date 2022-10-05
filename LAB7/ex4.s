/*#include <stdio.h>

int nums[4] = {65, -105, 111, 34};

int main (void) {
  int i;
  int s = 0;

  for (i=0;i<4;i++)
    s = s+nums[i];

  printf ("soma = %d\n", s);

  return 0;
}*/

data
S2:    .int 65, -105, 111, 34
Sf:  .string "soma = %d\n"    /* primeira string de formato para printf */

.text
.globl  main
main:

/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
  pushq   %rbp
  movq    %rsp, %rbp
  subq    $16, %rsp
  movq    %rbx, -8(%rbp)  /* guarda rbx */
  movq    %r12, -16(%rbp)  /* guarda r12 */
/********************************************************/

  /*
  Dicionario 
  Variavel Registrador
  i           EBX
  s           R12d
  S2          r12
  */
  movq $S2, %12
  movl $0, %ebx   #i = 0;
  movl $0, %r12d  #s = 0;
L1:
  cmpl $4, %ebx     #i==4
  je L2             #jmp printf e retorno
  movl (%r12), %r12d    #r12d == *S2
  addq $4, %r12     #S2++

  

L2:  
/*************************************************************/
/* este trecho imprime o \n (estraga %eax)                  */
  movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
  movl  $0, %eax
  call  printf       /* chama a funcao da biblioteca */
/*************************************************************/

/***************************************************************/
/* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
  movq  $0, %rax  /* rax = 0  (valor de retorno) */
  movq    -16(%rbp), %r12 /* recupera r12 */
  movq    -8(%rbp), %rbx  /* recupera rbx */
  leave
  ret      
/***************************************************************/

#include <stdio.h>
void dump (void *p, int n) {
  unsigned char *p1 = (unsigned char *) p;
    while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}
struct S1 {
  short val_short;
  int val_int;
  char *val_string;
};
struct S2 {
  void *p;
  int i;
  char c;
};

char minha_string[] = "turma 3wb";
struct S1 s1 = {12, 34, minha_string};
struct S2 s2[2] = {{&s1.val_int, -129, 'E' << 4},{&s1.val_string, 1026,0x55 & 0x0f}};