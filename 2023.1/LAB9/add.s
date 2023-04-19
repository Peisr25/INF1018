.text
.globl add

add:
    pushq %rbp
    movq %rsp, %rbp

    addl %edi, %esi
    addl %edx, %esi
    movl %esi, %eax
    leave
    ret