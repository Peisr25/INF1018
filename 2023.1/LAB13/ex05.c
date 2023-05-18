#include <stdio.h>
typedef int (*funcp)(int x);

int add(int x){
    return x + 1;
}


int main(void){
    funcp f;
    int i,j;
    unsigned char codigo[] = {
    0x55,
    0x48,0x89,0xE5,
    0xE8,0x00,0x00,0x00,0x00,
    0xC9,
    0xC3
    };
    f = (funcp)codigo;
    // unsigned char* add_address = (unsigned char*)&add;
    // printf("%x",&add);
    // codigo[5] = add_address[3]; //26
    // codigo[6] = add_address[2]; //11
    // codigo[7] = add_address[1]; //40
    // // codigo[8] = add_address[0];
    unsigned char* add_address = (unsigned char*)&add;
    // int i;
    j = 2;

    unsigned char* add_address = (unsigned char*)&add;
    unsigned int add_value = *(unsigned int*)(add_address) & 0xFFFF;

    unsigned char byte1 = (unsigned char)(add_value & 0xFF);
    unsigned char byte2 = (unsigned char)((add_value >> 8) & 0xFF);

    printf("%02x\n",&add_address[0]);
    for (i = 8 ;i >4; i--) {
        printf("%02x\n",add_address[j]);
        codigo[i+1] = add_address[j];
        printf("%02X\n", codigo[i]);
        j--;
    }

    i = (*f)(10);
    printf("o valor de i é %d\n",i);

    return 0;
}