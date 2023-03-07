/*int add (int a, int b, int c) {
  return a+b+c;
}

add:
    pushq %rbp
    movq %rsp, %rbp
    sub $12, %rsp
    movl %edi, -4(%rbp) #int a
    movl %esi, -8(%rbp) #int b
    movl %edx, -12(%rbp) #int c

    addl %edi, %esi
    addl %esi, %edx
    popq %rbp
    ret
*/

add:
        pushq   %rbp
        movq    %rsp, %rbp
        movl    %edi, -4(%rbp)
        movl    %esi, -8(%rbp)
        movl    %edx, -12(%rbp)
        movl    -4(%rbp), %edx
        movl    -8(%rbp), %eax
        addl    %eax, %edx
        movl    -12(%rbp), %eax
        addl    %edx, %eax
        popq    %rbp
        ret