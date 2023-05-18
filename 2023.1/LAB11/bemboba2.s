/*int bemboba (int num) {
  int local[4]; 16 bytes
  int *a;       08 bytes
  int i;        04 bytes

  for (i=0,a=local;i<4;i++) {
    *a = num;
    a++;
  }
  return addl (local, 4);
}
*/

.text
.globl bemboba

bemboba:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    movl $0, %r12d /* i = 0 */
    movq -16(%rbp), %r11 /* a = num */

For:
    cmpl $4, %r12d
    je FimFor

    movl %edi, (%r11) /* *a = num */
    addq $4, %r11
    inc %r12d
    jmp For

FimFor:
    leaq -16(%rbp), %rdi
    movl $4, $esi
    call addl
    leave
    ret