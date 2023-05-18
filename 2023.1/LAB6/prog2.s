/*
char S2[] = {65, 108, 111, 32, 123, 103, 97, 108, 101, 114, 97, 125, 33, 0};
int main (void) {
  char *pc = S2;
  while (*pc)
    printf ("%c", *pc++);
  printf("\n");
  return 0;
}
*/

.data
nums:  .int  10, -21, -30, 45
Sf:  .string "%d\n"    # string de formato para printf

.text
.globl  main
main:

/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
  pushq   %rbp
  movq    %rsp, %rbp
  subq    $16, %rsp
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
/*************************************************************/
/* este trecho imprime o valor de %eax (estraga %eax)  */
  movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
  movl    %eax, %esi   /* segundo parametro  (inteiro) */
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
