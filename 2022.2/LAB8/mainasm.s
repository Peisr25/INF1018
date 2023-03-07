  .data
  nums: .int 3, -5, 7, 8, -2
  s1:   .string "%d\n"

  .text
  .globl main
  main:
  /* prologo */
     pushq %rbp
     movq  %rsp, %rbp
     subq  $16, %rsp
     movq  %rbx, -8(%rbp)
     movq  %r12, -16(%rbp)

  /* coloque seu codigo aqui */
  /*
   Dicionario 
   Variavel Registrador
   i           EBX
   p           R12
               rbx

   */
   #int i=0;
   movl $0, %ebx
   
   #int *p = nums;
   movq $nums, %r12

FOR:
   cmpl $5, %ebx
   je FimLoop

   movl (%r12), %edi
   movl $1, %esi
   call filtro

   movq $s1, %rdi        #string s1 como primeiro argumento

   movl %eax, %esi       #move retorno da func filtro para segundo argumento
   movl $0, %eax
   call printf

   addq $4, %r12
   addl $1,%ebx
   jmp FOR

FimLoop:
  /* finalizacao */
     movq -8(%rbp), %rbx
     movq -16(%rbp), %r12
     leave
     ret
