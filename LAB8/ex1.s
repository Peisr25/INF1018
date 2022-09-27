  .data
  s1: .string "ls -ls"

  .text
  .globl main
  main:
  /* prologo */
    pushq %rbp #aponta para o topo da pilha
    movq  %rsp, %rbp

    movq $s1, %rdi    
    call system
    movl $0, %eax

  /* finalizacao */
    leave
    ret
