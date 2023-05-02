/*
void foo (int a[], int n) {
  int i;
  int s = 0;
  for (i=0; i<n; i++) {
    s += a[i];
    if (a[i] == 0) {
      a[i] = s;
      s = 0;
    }
  }
}
*/
.text
.globl foo 

foo:
    pushq %rbp
    movq %rsp, %rbp

ini:
    movl $0, %ebx # s = 0
    movl $0, %ecx # i=0

iniFor:
    cmpl %esi, %ecx 
    jge Fim

    movl $4, %edx       # define ebx como 4 (int) para multiplicar com i e obter a posição
    imull %ecx, %edx    # obtem a posição de s[i] ao multiplicar i*4 onde 4 refere ao tamanhio do tipo inteiro
    movslq %edx, %rdx   # estende edx para 64bits
    movq %rdi, %r12     # salva em r12 o endereço de s[]
    addq %rdx, %r12     # seta r12 para endereço atual de i
    addl (%r12), %ebx

    cmpl $0, (%r12)     # if(a[i] == 0)
    je FimFor

    addl %ebx, (%r12)   # a[i] += s
    movl $0, %ebx       # s=0


FimFor:
    addl $1, %ecx
    jmp iniFor

Fim:
    leave
    ret
