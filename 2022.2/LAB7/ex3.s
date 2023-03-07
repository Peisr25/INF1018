/*int main(void){
    int i,temp;
    int val[] = {1,2,3,4,5,6,7,8,9,10};
    for(i=0;i<10;i++){
        temp = val[i]*val[i];
        printf("%d\n",temp);
    }
    return 0;
}*/
.data
Sf: .string "%d\n"

.text
.globl main
main:
  /* prologo */
  pushq %rbp               #aponta para o topo da pilha
  movq  %rsp, %rbp
  subq  $16, %rsp
  movq  %rbx, -8(%rbp)   /* guarda rbx */
  movq  %r12, -16(%rbp)  /* guarda r12 */

  /*
  Dicionario 
  Variavel Registrador
  i           EBX
  */

  movl $1, %r12d           #int i=1
  #i<10
Loop:
  cmpl $10, %r12d          #if(i==10)
  jg FimLoop   
  movl %r12d, %ebx           #jmp to return 0 if >10;
  imul %ebx, %ebx         #i*i

#printf abaixo
  movq  $Sf, %rdi    /* primeiro parametro (ponteiro)*/
  movl  %ebx, %esi   /* segundo parametro  (inteiro) */
  movl  $0, %ebx
  call  printf       /* chama a funcao da biblioteca */

  addl $1, %r12d           #i++
  jmp Loop

FimLoop:
  movq     $0, %rax  /* rax = 0  (valor de retorno) */
  movq    -8(%rbp), %rbx  /* recupera rbx */
  movq    -16(%rbp), %r12 /* recupera r12 */
  leave
  ret   
