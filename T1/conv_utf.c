#include <stdio.h>

int converteUtf8Para32(FILE *arquivo_entrada, FILE *arquivo_saida){
    char aux;
    while(aux = fgetc(arquivo_entrada)!= EOF){
        putchar(aux);
        printf("a");
    }
}
int main(void){
    FILE* a = fopen("utf8_peq.txt","r");
    FILE* aa = fopen("aa.bin","wb");
    int af = converteUtf8Para32(a,aa);

    return 0;
}