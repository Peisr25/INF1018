/*
int nums[] = {10, -21, -30, 45};
int main() {
  int i, *p;
  int sum = 0;
  for (i = 0, p = nums; i != 4; i++, p++)
    sum += *p;
  printf("%d\n", sum);
  return 0;
}
*/
/*
Dicionario 
Variavel Registrador
i           EBX
p           R12
sum         EAX

*/

.data
nums:  .int  10, -21, -30, 45
Sf:  .string "Resultado da soma: %d\n"    # string de formato para printf

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
#int sum=0;
  movl  $0, %ecx  /* ebx = 0; */

#for(i=0,p=nums; i!=4;i++,p++)
#i=0;
  movl $0,%ebx
#p = nums;
  movq  $nums, %r12  /* r12 = &nums */

  #while(i!=4)
Loop:
  cmpl  $4, %ebx  /* if (ebx == 4) ? */
  je FimLoop          /* goto L2 */

  #incluir bloco while aqui
  #sum+=*p;
  addl (%r12),%ecx
    #i++;
  addl $1,%ebx
    #p++;
  addq $4,r12 /* r12+=4 */
  jmp Loop

/*************************************************************/
/* este trecho imprime o valor de %eax (estraga %eax)  */
  movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
  movl    %eax, %esi   /* segundo parametro  (inteiro) */
  call  printf       /* chama a funcao da biblioteca */
/*************************************************************/
FimLoop:  
  #printf("%d\n",sum);
  movl  (%r12), %eax    /* eax = *r12 */
/***************************************************************/
/* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
  movq  $0, %rax  /* rax = 0  (valor de retorno) */
  movq  -8(%rbp), %rbx
  movq  -16(%rbp), %r12
  leave
  ret      
/***************************************************************/
