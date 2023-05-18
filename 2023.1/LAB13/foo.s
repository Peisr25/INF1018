.text
.globl foo
foo:
    pushq %rbp
    movq %rsp, %rbp

    movl %edi, %eax
    inc %eax
    leave 
    ret
