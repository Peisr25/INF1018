/*
<<<<<<< HEAD
char S2[] = {65, 108, 111, 32, 123, 103, 97, 108, 101, 114, 97, 125, 33, 0};
int main (void) {
  char *pc = S2;
  while (*pc)
    printf ("%c", *pc++);
  printf("\n");
=======
int nums[] = {10, -21, -30, 45};
int main() {
  int i, *p;
  int sum = 0;
  for (i = 0, p = nums; i != 4; i++, p++)
    sum += *p;
  printf("%d\n", sum);
>>>>>>> ba8ab8d2337cec71627de54ebd7bd59e6703416a
  return 0;
}
*/

.data
<<<<<<< HEAD
S2:    .byte 65, 108, 111, 32, 123, 103, 97, 108, 101, 114, 97, 125, 33, 0
Sf:  .string "%c"    /* primeira string de formato para printf */
Sf2: .string "\n"    /* segunda string de formato para printf */
=======
nums:  .int  10, -21, -30, 45
Sf:  .string "%d\n"    # string de formato para printf
>>>>>>> ba8ab8d2337cec71627de54ebd7bd59e6703416a

.text
.globl  main
main:

/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
  pushq   %rbp
  movq    %rsp, %rbp
  subq    $16, %rsp
<<<<<<< HEAD
  movq    %rbx, -8(%rbp)  /* guarda rbx */
  movq    %r12, -16(%rbp)  /* guarda r12 */
/********************************************************/

  movq  $S2, %r12  /* r12 = &S2 */

L1:
  cmpb  $0, (%r12)  /* if (*pc == 0) ? */
  je  L2          /* goto L2 */

  cmpb $123, (%r12)
  je L3
  cmpb $125, (%r12)
  je L3

  movsbl  (%r12), %eax    /* eax = *r12 (estendendo o byte para 32 bits */

=======
  movq    %rbx, -8(%rbp)
  movq    %r12, -16(%rbp)
/********************************************************/

  movl  $0, %ebx  /* ebx = 0; */
  movq  $nums, %r12  /* r12 = &nums */
  movl  $0, %ecx # int sum = 0

L1:
  cmpl  $4, %ebx  /* if (ebx == 4) ? */
  je  L2          /* goto L2 */
  addl (%r12), %ecx # sum += *p

  addl  $1, %ebx  /* ebx += 1; */
  addq  $4, %r12  /* r12 += 4; */
  jmp  L1         /* goto L1; */

L2:  

  movl  %ecx, %eax    /* eax = *r12 */
>>>>>>> ba8ab8d2337cec71627de54ebd7bd59e6703416a
/*************************************************************/
/* este trecho imprime o valor de %eax (estraga %eax)  */
  movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
  movl    %eax, %esi   /* segundo parametro  (inteiro) */
<<<<<<< HEAD
  movl  $0, %eax
  call  printf       /* chama a funcao da biblioteca */
/*************************************************************/

  addq  $1, %r12  /* r12 += 1; */
  jmp  L1         /* goto L1; */

L2:  
/*************************************************************/
/* este trecho imprime o \n (estraga %eax)                  */
  movq    $Sf2, %rdi    /* primeiro parametro (ponteiro)*/
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

L3:
  addq $1, %r12
  jmp L1
=======
  call  printf       /* chama a funcao da biblioteca */
/*************************************************************/
/***************************************************************/
/* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
  movq  $0, %rax  /* rax = 0  (valor de retorno) */
  movq  -8(%rbp), %rbx
  movq  -16(%rbp), %r12
  leave
  ret      
/***************************************************************/
>>>>>>> ba8ab8d2337cec71627de54ebd7bd59e6703416a
