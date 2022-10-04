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
Sf: .string "%d/n"
val: .int 1,2,3,4,5,6,7,8,9,10

.text
.globl main
main:
  /* prologo */
  pushq %rbp               #aponta para o topo da pilha
  movq  %rsp, %rbp
  movq    %rbx, -8(%rbp)   /* guarda rbx */
  movq    %r12, -16(%rbp)  /* guarda r12 */

  /*
  Dicionario 
  Variavel Registrador
  i           EBX
  p           R12
  temp        EAX
  */

  movq $val, %r12         #int val[] == %r12
  movl $0, %ebx           #int i=0
  movl $0, %eax           #temp = 0;  
  #i<10
Loop:
  cmpl $10, %ebx          #if(i==10)
  je FimLoop              #jmp to return
  movl (%r12), %eax       #temp += val*val
  imul %eax, %eax         #val[i]*val[i]
  addq $4, %r12           #r12+=4
  addl $1, %ebx           #i++

  movq  $Sf, %rdi    /* primeiro parametro (ponteiro)*/
  movl  %eax, %esi   /* segundo parametro  (inteiro) */
  movl  $0, %eax
  call  printf       /* chama a funcao da biblioteca */
  jmp Loop


FimLoop:
  movl $0, %eax
  leave
  ret
