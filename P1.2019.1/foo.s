/*int bar(int s);

void foo(long vl[], int n, int s) {
    while (s) {
        s = bar(s);
        if ((s >= 0) && (s < n)) {
            vl[s] = 1;
        }
    }
}*/

  /*
  Dicionario 
  Variavel Registrador
  n           EBX
  vl          esi
  s           EDX

  */

foo:
/* prologo */
    pushq %rbp
    movq  %rsp, %rbp
    subq  $16, %rsp
    movq  %rdi, -8(%rbp)   #long vl[]
    movl  %esi, -12(%rbp)  #int n
    movl  %edx, -16(%rbp)  #int s

  #while(s)
While:
    cmpl $0, %edx   #s==0
    je FimLoop

    movl -16(%rbp), %eax    #mover da memoria para eax
    movl %eax, %edi         #mover %eax para primeiro argumento
    call bar                #chama funcao bar()
    movl %eax, -16(%rbp)    #move o retorno de bar() para memoria -16(%rpb)

    #if((s >= 0) && (s < n))
    cmpl $0, -16(%rbp)      #s >= 0
    js FimLoop              #pula para o final se s for negativo
    cmpl -16(%rbp), -12(rbp) #compara s com n 
    jge FimLoop             #pula para o fim do loop de s for maior ou igual a n
    


FimLoop:
/* finalizacao */
    movq -8(%rbp), %rbx
    movq -16(%rbp), %r12
    leave
    ret