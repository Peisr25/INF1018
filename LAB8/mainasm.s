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
   sum         EAX

   */
   #int i=0;
   movl $0, %ebx
   
   #int *p = nums;
   

  /* finalizacao */
     movq -8(%rbp), %rbx
     movq -16(%rbp), %r12
     leave
     ret