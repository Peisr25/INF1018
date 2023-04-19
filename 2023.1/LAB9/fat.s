.text
.globl fat

fat:
    pushq %rbp
    movq %rsp, %rbp

    movl %eax, %ebx # salva o retorno de fat em ebx para multiplicar posteriormente

    # caso base
    cmpl $0, %edi
    jne Else
    movl $1, %eax
Else:

    # movl %edi, %r12d
    # subl $1, %r12d
    subl $1, %edi
    # movl %r12d, %edi
    call fat
    imull %eax, %ebx

Fim:
    leave
    ret