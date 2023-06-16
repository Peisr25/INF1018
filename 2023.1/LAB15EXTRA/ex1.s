.text 
.global boo
boo:
   pushq %rbp
   movq %rsp, %rbp
   subq $64,%rsp

   movl $1, ...

   movsd %xmm0, -64(%rbp)
   leaq -48(%rbp),%rsi /*a2[4]*/   
   leaq -16(%rbp),%rdi /*a1[4]*/
   movl $4,%edx
   call foo/*foo(a1,a2,4)*/

   movsd -64(%rbp), %xmm0
   leaq -48(%rbp),%rsi /*a2[4]*/

   movl $0,%eax/*i=0*/
L1:
   cmpl $4,%eax
   je fim
   
   movl %eax, %edi
   imull $8, %edi
   addq %rsi, %rdi
   
   addsd (%rdi),%xmm0/*v+=a2[i]*/
   addl $1,%eax/*i++*/
   jmp L1
fim:
   leave 
   ret/*retorna o %xmm0*/

/*
double boo (double v) {
  int a1[4] = {1,2,3,4};
  double a2[4];
  int i;

  foo(a1, a2, 4);
  for (i = 0; i < 4; i++)
    v += a2[i];
	
  return v;
}
*/