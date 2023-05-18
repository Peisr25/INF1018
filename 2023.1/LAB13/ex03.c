#include <stdio.h>

typedef int (*funcp)(int x);

int main(void){
unsigned char codigo[] = {
    0x55,
    0x48,0x89,0xE5,
    0x89,0xF8,
    0xFF,0xC0,
    0xC9,
    0xC3
    };
    int i;
    funcp f;
    f = (funcp)codigo;
    i = (*f)(10);
    printf("o valor de i é %d\n",i);

    return 0;
}