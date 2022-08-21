#include <stdio.h>
#include <stdlib.h>
#define TAM 8

unsigned char switch_byte(unsigned char x){
    unsigned char y;
    y=x>>4;
    x=x<<4;
    x=x|y;
    return x;
}
unsigned char rotate_left(unsigned char x,int n){
    unsigned char y;
    y=x>>(TAM-n);
    x=x<<n;
    x=x+y;
    return x;
}
int main(void){
    unsigned char x,s,z,w;
    x=0x61;
    s = switch_byte(x);
    printf("original: %08x\n switch:%08x\n",x,s);
    z = rotate_left(x,2);
    printf("rotacao 1: %08x\n",z);
    w = rotate_left(x,4);
    printf("rotacao 2: %08x\n",w);
    return 0;
}