#include <stdio.h>

int main() {
    signed char sc = -1;
    unsigned int ui = (unsigned int) sc;
    
    printf("Valor de sc: %d\n", sc);
    printf("Valor de ui: %u\n", ui);
    
    return 0;
}
