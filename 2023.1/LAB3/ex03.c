#include <stdio.h>

unsigned char switch_byte(unsigned char x){
    unsigned char part1 = (x & 0xF0) >> 4; //1111 1111
    unsigned char part2 = (x & 0x0F) << 4;
    return part1 | part2 // faz a troca
}

unsigned char rotate_left(unsigned char x, int n){
    
}
