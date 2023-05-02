.text 
add2: 
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    cmpq $0 %rdi
    jne cont
    movl $0, %eax
    jmp FimLoop

cont:
    movq %rdi, -8(%rbp) # salva o retorno de add2 na pilha
    movq 8(%rdi), %rdi # 8(%rdi) chama o proximo valor da struct
    call add2
    movq -8(%rbp), %rdi
    addl (%rdi), %eax
    call FimLoop

FimLoop:
    leave
    ret