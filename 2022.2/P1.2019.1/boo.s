/*#define NULL 0
struct A {
    int v;
    struct A *esq;
    struct A *dir;
};
int max(int x, int y);

int boo(struct A *pa) {
    int pesq, pdir;
    if (pa == NULL) return 0;
    pesq = boo(pa->esq);
    pdir = boo(pa->dir);
    return max(pesq, pdir) + 1;
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
    subq  $32, %rsp
    movq  %rdi, -24(%rbp)   #struct A
    movl  %esi, -4(%rbp)    #int pesq
    movl  %edx, -8(%rbp)    #int pdir

    cmpq $0, -24(%rbp)     #if(pa == NULL)
    jne Loop                #se nao for NULL continua
    movl $0, %eax           #return 0
    jmp FimLoop

  #while(s)
Loop:
    movq -24(%rbp), %rax     #move struct A da memoria para %rax
    movq  8(%rax), %rax      #move pa->esq para %rax
    call boo
    movl %eax, -4(%rbp)      #salva o retorno de boo(pa>esq) em pesq

    movq -24(%rbp), %rax     #move struct A da memora para %rax
    movq  16(%rbp), %rax     #move pa->dir para %rax
    call boo
    movl %eax, -8(%rbp)      #move retorno de boo(pa->esq) em pdir

    #transformar valores em memoria para variaveis de argumento
    movl -8(%rbp), %edx      #pega da memoria e salva em %edx
    movl -16(%rbp), %eax     #pega da memoria e salva em %eax
    movl %edx, %esi          #salva no Registrador de primeiro argumento
    movl %eax, %edi          #salva no Registrador de segundo argumento
    call max
    addl $1, %eax
    jmp FimLoop

FimLoop:
/* finalizacao */
    leave
    ret
